open Markdown;
open Html;
open Sitemap;
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

let rec buildfiletree: (string, string, string) => (string, list(page_entry)) =
  (inputdir, outputdir, basehtml) => {
    let allfiles =
      Sys.readdir("./" ++ inputdir)
      |> Array.to_list;

    /* First pass: process directories, collect their entries */
    let subdirEntries =
      allfiles
      |> List.filter(x => {
           let currentfile = inputdir ++ "/" ++ x;
           Sys.is_directory(currentfile);
         })
      |> List.fold_left(
           (acc, x) => {
             mkdir("./" ++ outputdir);
             let nextoutputdir = "./" ++ outputdir ++ "/" ++ x;
             mkdir(nextoutputdir);
             let (res, entries) =
               buildfiletree(
                 "./" ++ inputdir ++ "/" ++ x,
                 nextoutputdir,
                 basehtml,
               );
             Format.print_string(res);
             acc @ entries;
           },
           [],
         );

    /* Second pass: process markdown files */
    let markdownfiles =
      allfiles
      |> List.filter(x => is_markdown(x));

    markdownfiles
    |> List.map(file => mkdir(buildoutdir(file, outputdir)))
    |> ignore;

    let (progressStr, fileEntries) =
      markdownfiles
      |> List.fold_left(
           ((accStr, accEntries), b) => {
             let rawContent = readf("./" ++ inputdir ++ "/" ++ b);
             let (meta, markdown) = parseShorthand(rawContent);
             let (pageTitle, metaTags) =
               buildMetaTags(meta, markdown, basehtml);
             let outdir = buildoutdir(b, outputdir);
             markdown
             |> Omd.of_string
             |> Omd.to_html
             |> addmarkdown(basehtml)
             |> injectMetaTags(_, pageTitle, metaTags)
             |> writef(outdir ++ "/index.html");
             let urlPath = {
               let raw = outdir;
               /* Strip leading "./" and the output dir prefix */
               let prefixLen = String.length("./" ++ outputdir);
               let pathPart =
                 if (String.length(raw) > prefixLen) {
                   String.sub(raw, prefixLen, String.length(raw) - prefixLen);
                 } else {
                   "/";
                 };
               if (pathPart == "") { "/" } else { pathPart ++ "/" };
             };
             let description =
               switch (meta.description) {
               | Some(d) => d
               | None =>
                 switch (extractFirstParagraph(markdown)) {
                 | Some(p) => p
                 | None => ""
                 }
               };
             let entry = {
               url: urlPath,
               pageTitle,
               pageDescription: description,
               filename: removemd(b),
             };
             (
               green("🍯" ++ b ++ "\n") ++ accStr,
               accEntries @ [entry],
             );
           },
           ("", []),
         );

    (progressStr, subdirEntries @ fileEntries);
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

      let (res, pageEntries) = buildfiletree(markdown, public, basehtml);
      writef(public ++ "/styles.css", baseCss);
      generateSitemap(markdown, public, basehtml, pageEntries);

      Format.print_string(res);

      print_endline(yellow("☀️ Done!"));
    };

    if (serve) {
      let _ = serveFiles(public);
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
