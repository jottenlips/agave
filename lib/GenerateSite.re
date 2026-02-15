open Themes;
open Server;

let green = s => "\027[32m" ++ s ++ "\027[0m";
let yellow = s => "\027[33m" ++ s ++ "\027[0m";

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

type metadata = {
  title: option(string),
  description: option(string),
  image: option(string),
};

let emptyMeta = {title: None, description: None, image: None};

let shorthandRegex = Str.regexp("@\\([a-zA-Z]+\\) \\(.*\\)");

let parseShorthand: string => (metadata, string) =
  rawContent => {
    let lines = String.split_on_char('\n', rawContent);
    let rec loop = (lines, meta) =>
      switch (lines) {
      | [line, ...rest] when String.length(line) > 0 && line.[0] == '@' =>
        if (Str.string_match(shorthandRegex, line, 0)) {
          let key = Str.matched_group(1, line);
          let value = Str.matched_group(2, line);
          let meta =
            switch (key) {
            | "title" => {...meta, title: Some(value)}
            | "description" => {...meta, description: Some(value)}
            | "image" => {...meta, image: Some(value)}
            | _ => meta
            };
          loop(rest, meta);
        } else {
          (meta, String.concat("\n", [line, ...rest]));
        }
      | _ => (meta, String.concat("\n", lines))
      };
    loop(lines, emptyMeta);
  };

let headingRegex = Str.regexp("^# \\(.*\\)$");

let extractFirstHeading: string => option(string) =
  content => {
    let lines = String.split_on_char('\n', content);
    let rec find =
      fun
      | [] => None
      | [line, ...rest] =>
        if (Str.string_match(headingRegex, line, 0)) {
          Some(Str.matched_group(1, line));
        } else {
          find(rest);
        };
    find(lines);
  };

let extractFirstParagraph: string => option(string) =
  content => {
    let lines = String.split_on_char('\n', content);
    let rec find =
      fun
      | [] => None
      | [line, ...rest] => {
          let trimmed = String.trim(line);
          if (String.length(trimmed) > 0
              && trimmed.[0] != '#'
              && trimmed.[0] != '!'
              && trimmed.[0] != '-'
              && trimmed.[0] != '*'
              && trimmed.[0] != '`') {
            Some(trimmed);
          } else {
            find(rest);
          };
        };
    find(lines);
  };

let imageRegex = Str.regexp("!\\[.*\\](\\(.*\\))");

let extractFirstImage: string => option(string) =
  content =>
    try({
      let _ = Str.search_forward(imageRegex, content, 0);
      Some(Str.matched_group(1, content));
    }) {
    | Not_found => None
    };

let titleRegex = Str.regexp("<title>\\([^<]*\\)</title>");

let extractBaseTitle: string => string =
  basehtml =>
    try({
      let _ = Str.search_forward(titleRegex, basehtml, 0);
      Str.matched_group(1, basehtml);
    }) {
    | Not_found => "Agave Site"
    };

let escapeHtml: string => string =
  s =>
    s
    |> Str.global_replace(Str.regexp("&"), "&amp;")
    |> Str.global_replace(Str.regexp("\""), "&quot;")
    |> Str.global_replace(Str.regexp("<"), "&lt;")
    |> Str.global_replace(Str.regexp(">"), "&gt;");

let buildMetaTags: (metadata, string, string) => (string, string) =
  (meta, markdown, basehtml) => {
    let baseTitle = extractBaseTitle(basehtml);
    let pageTitle =
      switch (meta.title) {
      | Some(t) => t
      | None =>
        switch (extractFirstHeading(markdown)) {
        | Some(h) => h ++ " | " ++ baseTitle
        | None => baseTitle
        }
      };
    let description =
      switch (meta.description) {
      | Some(d) => Some(d)
      | None => extractFirstParagraph(markdown)
      };
    let image =
      switch (meta.image) {
      | Some(i) => Some(i)
      | None => extractFirstImage(markdown)
      };
    let tags = ref("");
    tags :=
      tags^
      ++ "\n    <meta property=\"og:title\" content=\""
      ++ escapeHtml(pageTitle)
      ++ "\" />"
      ++ "\n    <meta name=\"twitter:title\" content=\""
      ++ escapeHtml(pageTitle)
      ++ "\" />";
    switch (description) {
    | Some(d) =>
      tags :=
        tags^
        ++ "\n    <meta name=\"description\" content=\""
        ++ escapeHtml(d)
        ++ "\" />"
        ++ "\n    <meta property=\"og:description\" content=\""
        ++ escapeHtml(d)
        ++ "\" />"
        ++ "\n    <meta name=\"twitter:description\" content=\""
        ++ escapeHtml(d)
        ++ "\" />"
    | None => ()
    };
    switch (image) {
    | Some(i) =>
      tags :=
        tags^
        ++ "\n    <meta property=\"og:image\" content=\""
        ++ escapeHtml(i)
        ++ "\" />"
        ++ "\n    <meta name=\"twitter:image\" content=\""
        ++ escapeHtml(i)
        ++ "\" />"
        ++ "\n    <meta name=\"twitter:card\" content=\"summary_large_image\" />"
    | None =>
      tags :=
        tags^
        ++ "\n    <meta name=\"twitter:card\" content=\"summary\" />"
    };
    (pageTitle, tags^);
  };

let headCloseRegex = Str.regexp("</head>");

let injectMetaTags: (string, string, string) => string =
  (html, pageTitle, metaTags) => {
    let withTitle =
      Str.global_replace(
        titleRegex,
        "<title>" ++ escapeHtml(pageTitle) ++ "</title>",
        html,
      );
    Str.replace_first(
      headCloseRegex,
      metaTags ++ "\n  </head>",
      withTitle,
    );
  };

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
         (a, b) => {
           let rawContent = readf("./" ++ inputdir ++ "/" ++ b);
           let (meta, markdown) = parseShorthand(rawContent);
           let (pageTitle, metaTags) =
             buildMetaTags(meta, markdown, basehtml);
           markdown
           |> Omd.of_string
           |> Omd.to_html
           |> addmarkdown(basehtml)
           |> injectMetaTags(_, pageTitle, metaTags)
           |> writef(buildoutdir(b, outputdir) ++ "/index.html")
           |> (
             () =>
               green("🍯" ++ b ++ "\n")
               ++ a
           );
         },
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
    if (Sys.file_exists(markdown) && Sys.is_directory(markdown)) {
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

      let res = buildfiletree(markdown, public, basehtml);
      writef(public ++ "/styles.css", baseCss);

      Format.print_string(res);

      print_endline(yellow("☀️ Done!"));
    };

    if (serve) {
      let _ = Server.serveFiles(public);
      ();
    };
  };

  let term = Cmdliner.Term.(const(run) $ markdown $ public $ theme $ serve);
  let info = Cmdliner.Cmd.info("agave", ~doc);
  Cmdliner.Cmd.v(info, term);
};

let agave = () => {
  let _ = Cmdliner.Cmd.eval(cmd);
  ();
};
