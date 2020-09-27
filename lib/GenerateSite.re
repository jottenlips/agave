let readf: string => string =
  path =>
    switch (Bos.OS.File.read(Fpath.v(path))) {
    | Ok(a) => a
    | _ => ""
    };

let writef: (string, string) => unit =
  (path, content) => Bos.OS.File.write(Fpath.v(path), content) |> ignore;

let regexmd = Str.regexp("\\b.md\\b");
let is_markdown: string => bool =
  name =>
    try(
      switch (Str.search_forward(regexmd, name, 0)) {
      | _ => true
      }
    ) {
    | Not_found => false
    };
let removemd: string => string =
  filename => Str.replace_first(regexmd, "", filename);

exception NotADirectory(string);

let mkdir: string => unit =
  dir =>
    try(
      if (!Sys.is_directory(dir)) {
        raise(NotADirectory(dir ++ " Is not a directory."));
      }
    ) {
    | _ => Bos.OS.Dir.create(~path=true, Fpath.v(dir)) |> ignore
    };

let buildoutdir: (string, string) => string =
  (filename, dirname) =>
    switch (filename) {
    | "index.md" => "./" ++ dirname
    | _ => "./" ++ dirname ++ "/" ++ removemd(filename)
    };

let makedirectories = () => {
  let inputdir =
    try(Sys.argv[1]) {
    | _ => "markdown"
    };

  let outputdir =
    try(Sys.argv[2]) {
    | _ => "public"
    };
  mkdir(outputdir);

  [|inputdir, outputdir|];
};

let agave = () => {
  let dirs = makedirectories();
  let markdownfiles =
    Sys.readdir("./markdown")
    |> Array.to_list
    |> List.filter(x => is_markdown(x));

  markdownfiles
  |> List.map(file => mkdir(buildoutdir(file, dirs[1])))
  |> ignore;

  markdownfiles
  |> List.fold_left(
       (a, b) =>
         readf("./" ++ dirs[0] ++ "/" ++ b)
         |> Omd.of_string
         |> Omd.to_html(~pindent=true)
         |> writef(buildoutdir(b, dirs[1]) ++ "/index.html")
         |> (
           () =>
             Pastel.(
               <Pastel color=Green>
                 {"./"
                  ++ dirs[0]
                  ++ "/"
                  ++ b
                  ++ " has been added to "
                  ++ dirs[1]}
               </Pastel>
             )
             ++ "\n"
             ++ a
         ),
       "☀️ Done!",
     );
};