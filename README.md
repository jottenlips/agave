# ☀️ Agave 🍯

Minimal markdown to HTML for static sites with pretty URLs.

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

Here is an example of using custom base html.

[Blog](https://jottenlips.github.io/)

[Repo](https://github.com/jottenlips/jottenlips.github.io)

## File structure (folders work)

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

### Deploy

Github Pages

```shell
agave markdown docs
git add --all
git commit -m"deploy"
git push
```

Setup your repo to look at the docs folder on your main branch in the repo settings.
