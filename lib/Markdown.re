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

type metadata = {
  title: option(string),
  description: option(string),
  image: option(string),
};

type page_entry = {
  url: string,
  pageTitle: string,
  pageDescription: string,
  filename: string,
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
