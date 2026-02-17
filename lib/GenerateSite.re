open Markdown;
open Html;
open Sitemap;
open Themes;
open Server;

let green = s => "\027[32m" ++ s ++ "\027[0m";
let yellow = s => "\027[33m" ++ s ++ "\027[0m";

let buildBackArrow: string => string =
  urlPrefix =>
    switch (urlPrefix) {
    | "" => ""
    | _ =>
      let parts =
        String.split_on_char('/', urlPrefix)
        |> List.filter(s => s != "");
      let parentUrl =
        switch (parts) {
        | [] => "/"
        | [_] => "/"
        | _ =>
          let parentParts = List.filteri((i, _) => i < List.length(parts) - 1, parts);
          "/" ++ String.concat("/", parentParts) ++ "/"
        };
      "<a href=\""
      ++ parentUrl
      ++ "\" style=\"display:inline-block;margin-bottom:1em;text-decoration:none;color:currentColor;opacity:0.7;\" aria-label=\"Go back\">"
      ++ "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"24\" height=\"24\" viewBox=\"0 0 24 24\" fill=\"none\" stroke=\"currentColor\" stroke-width=\"2\" stroke-linecap=\"round\" stroke-linejoin=\"round\"><line x1=\"19\" y1=\"12\" x2=\"5\" y2=\"12\"></line><polyline points=\"12 19 5 12 12 5\"></polyline></svg>"
      ++ "</a>\n";
    };

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

let capitalize: string => string =
  s =>
    switch (String.length(s)) {
    | 0 => s
    | _ => String.uppercase_ascii(String.sub(s, 0, 1)) ++ String.sub(s, 1, String.length(s) - 1)
    };

let buildTopNav: string => string =
  inputdir => {
    let allfiles =
      Sys.readdir("./" ++ inputdir)
      |> Array.to_list;
    let subdirNames =
      allfiles
      |> List.filter(x => Sys.is_directory("./" ++ inputdir ++ "/" ++ x))
      |> List.sort(String.compare);
    let pageNames =
      allfiles
      |> List.filter(x => is_markdown(x) && x != "index.md")
      |> List.map(removemd)
      |> List.sort(String.compare);
    let allNames =
      List.sort_uniq(String.compare, pageNames @ subdirNames);
    let links =
      ["<a href=\"/\">Home</a>"]
      @ List.map(
          name => "<a href=\"/" ++ name ++ "/\">" ++ capitalize(name) ++ "</a>",
          allNames,
        )
      @ ["<a href=\"/sitemap/\">Sitemap</a>"];
    "<nav>\n    "
    ++ String.concat("\n    ", links)
    ++ "\n  </nav>";
  };

let rec buildfiletree: (string, string, string, string) => (string, list(page_entry)) =
  (inputdir, outputdir, urlPrefix, basehtml) => {
    let allfiles =
      Sys.readdir("./" ++ inputdir)
      |> Array.to_list;

    /* Collect subdirectory names */
    let subdirNames =
      allfiles
      |> List.filter(x => {
           let currentfile = inputdir ++ "/" ++ x;
           Sys.is_directory(currentfile);
         });

    /* First pass: process directories, collect their entries */
    let subdirEntries =
      subdirNames
      |> List.fold_left(
           (acc, x) => {
             mkdir("./" ++ outputdir);
             let nextoutputdir = "./" ++ outputdir ++ "/" ++ x;
             mkdir(nextoutputdir);
             let (res, entries) =
               buildfiletree(
                 "./" ++ inputdir ++ "/" ++ x,
                 nextoutputdir,
                 urlPrefix ++ "/" ++ x,
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
             let htmlContent =
               markdown
               |> Omd.of_string
               |> Omd.to_html;
             let backArrowPrefix =
               switch (b) {
               | "index.md" => urlPrefix
               | _ => urlPrefix ++ "/" ++ removemd(b)
               };
             let backArrow = buildBackArrow(backArrowPrefix);
             (backArrow ++ htmlContent)
             |> addmarkdown(basehtml)
             |> injectMetaTags(_, pageTitle, metaTags)
             |> writef(outdir ++ "/index.html");
             let urlPath =
               switch (b) {
               | "index.md" =>
                 if (urlPrefix == "") { "/" } else { urlPrefix ++ "/" }
               | _ => urlPrefix ++ "/" ++ removemd(b) ++ "/"
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

let generateSitemap:
  (string, string, string, list(page_entry)) => unit =
  (markdownDir, outputdir, basehtml, entries) => {
    let template =
      switch (readf(markdownDir ++ "/search.html")) {
      | "" => basehtml
      | t => t
      };
    let sitemapContent = buildSitemapHtml(entries);
    let meta = {
      title: Some("Sitemap"),
      description: Some("Index of all pages"),
      image: None,
    };
    let (pageTitle, metaTags) = buildMetaTags(meta, "", template);
    let html =
      sitemapContent
      |> addmarkdown(template)
      |> injectMetaTags(_, pageTitle, metaTags);
    mkdir(outputdir ++ "/sitemap");
    writef(outputdir ++ "/sitemap/index.html", html);
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
    let doc = "theme name. choices: [arrakis, caladan, giediprime, ix, salusasecundus, spice]";
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
        switch (readf(markdown ++ "/base.html")) {
        | "" => getTheme(theme)
        | x => x
        };

      let baseCss =
        switch (readf(markdown ++ "/styles.css")) {
        | "" => getThemeCss(theme)
        | x => x
        };

      let topNav = buildTopNav(markdown);
      let basehtml = injectNav(basehtml, topNav);
      let (res, pageEntries) = buildfiletree(markdown, public, "", basehtml);
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
