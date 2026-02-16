![Agave Logo](logo.gif)

Minimal markdown to HTML for static sites with pretty URLs.

Written in [ReasonML](https://reasonml.github.io/) with native OCaml toolchain (opam + dune).

## Install

### Via npm

```
npm install -g agave-generator
```

### Build from source

Requires [opam](https://opam.ocaml.org/) and OCaml 5.1+.

```console
opam install . --deps-only -y
dune build
dune install
```

### Link locally for development

```console
opam install . --deps-only -y
dune build
cp _build/default/bin/Agave.exe bin/agave-native
npm link --ignore-scripts
```

Now `agave` is available globally. To unlink:

```console
npm unlink -g agave-generator
```

## Use

```console
mkdir blog
cd blog
mkdir markdown
touch markdown/index.md # home page
touch markdown/first-post.md # /first-post/ route
agave # reads all your readmes in ./markdown and outputs them to ./public
```

For the full list of options run `help`.

```console
agave --help
```

## Themes

Simply pass the -t argument and the theme name

```console
agave -t arrakis
```

Available themes:

- **arrakis** - Deep desert, spice orange and warm ochre on dark sand
- **caladan** - Ocean world, lush blues and greens
- **giediprime** - Black and white minimalist, stark industrial
- **ix** - 90s cyberdelia, neon on dark
- **salusasecundus** - Brutalist, raw concrete with heavy type
- **spice** - Psychedelic melange, molten oranges and gold shimmer
- **randomphoto** - Random cover photo with a light palette

## Example Site with Theme Previews

The `example/` directory contains a demo site with preview pages for every built-in theme. To build it:

```console
cd example
bash build-examples.sh
```

This generates the main site and a themed preview page for each theme at `public/themes/<theme>/`. To view it locally:

```console
agave -m markdown -p public -s
# Visit http://localhost:8080/ and click through the Theme Gallery
```

## Full Customization

If you didn't find a theme for you you can add any base HTML and CSS you would like.

base.html will wrap every generated page.

base.html must contain `<!-- MARKDOWN -->` where you would like your content placed.

If you have a `styles.css` file in the markdown folder, it will be copied to the deployment folder.

```console
touch markdown/base.html
touch markdown/styles.css
echo "<html><!-- MARKDOWN --></html>" > markdown/base.html
agave # run the generator again
```

Here is an example of using custom `base.html`.

[Blog](https://jottenlips.github.io/)

[Repo](https://github.com/jottenlips/jottenlips.github.io)

## File structure

```
./markdown
└──base.html
└──index.md
└──another-page.md
└──topic.md
└──/topic
    └──2019-1-1.md
    └──2020-1-1.md
    └──2021-1-1.md
```

results in

```
./public
└──index.html
└──another-page/index.html
└──/topic
    └──index.html
    └──2019-1-1/index.html
    └──2020-1-1/index.html
    └──2021-1-1/index.html
```

## Deploy your site

Github Pages

```console
agave --markdown myblog --public docs
git add --all
git commit -m"deploy"
git push
```

Setup your repo to look at the docs folder on your main branch in the repo settings.

## Run your site locally

```console
agave -s
# Server running at http://localhost:8080/
```

You can also serve any existing directory without generating:

```console
agave -p ./docs -s
```

## Release

1. Commit and tag:

```console
git add -A && git commit -m "v0.2.0: description"
git tag v0.2.0
git push origin main --tags
```

2. GitHub Actions builds native binaries for `linux-x64`, `darwin-x64`, and `darwin-arm64` and attaches them to a GitHub Release.

3. Publish to npm:

```console
npm publish
```

## Support

Want to support this project?

[![Contributor Covenant](https://img.shields.io/badge/Contributor%20Covenant-v2.0%20adopted-ff69b4.svg)](code_of_conduct.md)
