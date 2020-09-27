# agave

Minimal markdown to html for flat static sites.

## Install

```
yarn global add agave
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

gh pages

```
agave markdown docs
```
