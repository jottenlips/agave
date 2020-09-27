# ☀️ Agave 🍯

Minimal markdown to html for flat static sites with pretty urls.

## Install

```
yarn global add agave-generator
```

## use

```shell
mkdir blog
cd blog
mkdir markdown
touch markdown/index.md # home page
touch markdown/first-post.md # /first-post/ route
agave markdown public # reads all your readmes in markdown and outputs them to public
```

```shell
agave [markdowndir?] [websiteirectory?]
```

gh pages

```shell
agave markdown docs
```
