# ☀️ Agave 🍯

Minimal markdown to HTML for flat static sites with pretty URLs.

## Install

```
yarn global add agave-generator
```

## Use

```shell
mkdir blog
cd blog
mkdir markdown
touch markdown/index.md # home page
touch markdown/first-post.md # /first-post/ route
agave markdown public # reads all your readmes in markdown and outputs them to public
```

```shell
agave [markdowndir?] [websitedirectory?]
```

## Customization

Add any base HTML you would like.

base.html will wrap every generated page.

base.html must contain `<!-- MARKDOWN -->` where you would like your content placed.

```shell
touch markdown/base.html
echo "<html><!-- MARKDOWN --></html>" > markdown/base.html
agave # run the generator again
```

Here is an example of using custom base html. [Blog](https://jottenlips.github.io/blog/)

### Deploy

Github Pages

```shell
agave markdown docs
git add --all
git commit -m"deploy"
git push
```

Setup your repo to look at the docs folder on your main branch in the repo settings.
