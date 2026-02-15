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

let emptyMeta: metadata;

let is_markdown: string => bool;
let removemd: string => string;
let parseShorthand: string => (metadata, string);
let extractFirstHeading: string => option(string);
let extractFirstParagraph: string => option(string);
let extractFirstImage: string => option(string);
