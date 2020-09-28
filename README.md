# ☀️ Agave 🍯

Minimal markdown to html for flat static sites with pretty urls.

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

Add any base html you would like.

base.html will wrap every generated page.

base.html must contain `<!-- MARKDOWN -->` where you would like your content placed.

```shell
touch markdown/base.html
echo "<html><!-- MARKDOWN --></html>" > markdown/base.html
```

### Deploy

gh pages

```shell
agave markdown docs
git add --all
git commit -m"deploy"
git push
```

Setup your repo to look at the docs folder on your main branch.
