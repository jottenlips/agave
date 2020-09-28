# agave

Minimal markdown to html for flat static sites.

## Install

```
yarn global add agave-generator
```

## use

```
mkdir blog
cd blog
mkdir markdown
touch markdown/index.md # home page
touch markdown/first-post.md # /first-post/ route
agave markdown public # reads all your readmes in markdown and outputs them to public
```

## customize

Add any base html you would like.

base.html will wrap every generated page.

base.html must contain `<!-- MARKDOWN -->` where you would like your content placed.

```
touch markdown/base.html
echo "<html><!-- MARKDOWN --></html>" > markdown/base.html
```

gh pages

```
agave markdown docs
```
