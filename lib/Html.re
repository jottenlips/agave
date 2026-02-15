open Markdown;

let escapeHtml: string => string =
  s =>
    s
    |> Str.global_replace(Str.regexp("&"), "&amp;")
    |> Str.global_replace(Str.regexp("\""), "&quot;")
    |> Str.global_replace(Str.regexp("<"), "&lt;")
    |> Str.global_replace(Str.regexp(">"), "&gt;");

let escapeJson: string => string =
  s =>
    s
    |> Str.global_replace(Str.regexp("\\\\"), "\\\\\\\\")
    |> Str.global_replace(Str.regexp("\""), "\\\\\"")
    |> Str.global_replace(Str.regexp("\n"), "\\\\n")
    |> Str.global_replace(Str.regexp("\r"), "\\\\r");

let titleRegex = Str.regexp("<title>\\([^<]*\\)</title>");

let extractBaseTitle: string => string =
  basehtml =>
    try({
      let _ = Str.search_forward(titleRegex, basehtml, 0);
      Str.matched_group(1, basehtml);
    }) {
    | Not_found => "Agave Site"
    };

let buildMetaTags: (metadata, string, string) => (string, string) =
  (meta, markdown, basehtml) => {
    let baseTitle = extractBaseTitle(basehtml);
    let pageTitle =
      switch (meta.title) {
      | Some(t) => t
      | None =>
        switch (extractFirstHeading(markdown)) {
        | Some(h) => h
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

let regexmarkdown = Str.regexp("<!-- MARKDOWN -->");

let addmarkdown: (string, string) => string =
  (template, content) => Str.replace_first(regexmarkdown, content, template);

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
