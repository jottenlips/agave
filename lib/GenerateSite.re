open Themes;
open Server;

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

let regexmarkdown = Str.regexp("<!-- MARKDOWN -->");
let addmarkdown: (string, string) => string =
  (template, content) => Str.replace_first(regexmarkdown, content, template);

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

let rec buildfiletree: (string, string, string) => string =
  (inputdir, outputdir, basehtml) => {
    let markdownfiles =
      Sys.readdir("./" ++ inputdir)
      |> Array.to_list
      |> List.map(x => {
           let currentfile = inputdir ++ "/" ++ x;
           Sys.is_directory(currentfile)
             ? mkdir("./" ++ outputdir)
               |> (
                 () => {
                   let nextoutputdir = "./" ++ outputdir ++ "/" ++ x;
                   mkdir(nextoutputdir);
                   let res =
                     buildfiletree(
                       "./" ++ inputdir ++ "/" ++ x,
                       nextoutputdir,
                       basehtml,
                     );
                   Format.print_string(res);
                   "";
                 }
               )
             : x;
         })
      |> List.filter(x => is_markdown(x));

    markdownfiles
    |> List.map(file => mkdir(buildoutdir(file, outputdir)))
    |> ignore;

    markdownfiles
    |> List.fold_left(
         (a, b) =>
           readf("./" ++ inputdir ++ "/" ++ b)
           |> Omd.of_string
           |> Omd.to_html(~pindent=true)
           |> addmarkdown(basehtml)
           |> writef(buildoutdir(b, outputdir) ++ "/index.html")
           |> (
             () =>
               Pastel.(<Pastel color=Green> {"🍯" ++ b ++ "\n"} </Pastel>)
               ++ a
           ),
         "",
       );
  };

let cmd = {
  let doc = "CLI for generating static sites from markdown.";

  let markdown = {
    let doc = "Path to your markdown files.";
    Cmdliner.Arg.(
      value
      & opt(string, "markdown")
      & info(["m", "markdown"], ~docv="markdown", ~doc)
    );
  };

  let public = {
    let doc = "Path to output your static site.";
    Cmdliner.Arg.(
      value
      & opt(string, "public")
      & info(["p", "public"], ~docv="public", ~doc)
    );
  };

  let theme = {
    let doc = "theme name. choices: [desert, randomphoto]";
    Cmdliner.Arg.(
      value & opt(string, "") & info(["t", "theme"], ~docv="theme", ~doc)
    );
  };


  let serve = {
    let doc = "serve files";
    Cmdliner.Arg.(
      value & flag & info(["s", "serve"], ~docv="serve", ~doc)
    );
  };


  let run = (markdown, public, theme, serve) => {
    let basehtml =
      hasTheme(theme)
        ? getTheme(theme)
        : (
          switch (readf(markdown ++ "/base.html")) {
          | "" => getTheme(theme)
          | x => x
          }
        );

    let baseCss = 
        hasTheme(theme)
        ? getThemeCss(theme)
        : (
          switch (readf(markdown ++ "/styles.css")) {
          | "" => getThemeCss(theme)
          | x => x
          }
        );

    let _serve = switch (serve) {
        | true => 
          Server.serveFiles(public)
        | _ => ""
        };


    let res = buildfiletree(markdown, public, basehtml);
    /* Write css file */
    writef(public++"/styles.css", baseCss)

    Format.print_string(res);

    print_endline(Pastel.(<Pastel color=Yellow> "☀️ Done!" </Pastel>));
  };

  Cmdliner.Term.(
    const(run) $ markdown $ public $ theme $ serve,
    info("agave", ~doc),
  );
};

let agave = () => Cmdliner.Term.exit @@ Cmdliner.Term.eval(cmd);