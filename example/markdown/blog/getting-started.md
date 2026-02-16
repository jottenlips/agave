@title Getting Started with Agave
@description A beginner's guide to building your first static site with Agave

# Getting Started with Agave

Setting up your first Agave site takes just a few minutes.

## Installation

Install via opam or build from source:

```
dune build
dune install
```

## Create Your First Site

1. Create a `markdown` directory
2. Add a `base.html` template with `<!-- MARKDOWN -->` placeholder
3. Write some `.md` files
4. Run `agave -m markdown -p public`

## Adding Meta Tags

Use shorthand notation at the top of your markdown files:

```
@title My Page Title
@description A brief description of this page
@image /images/hero.jpg
```

These get injected as Open Graph and Twitter Card meta tags automatically.
