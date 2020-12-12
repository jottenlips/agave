![Agave Logo](logo.gif)

Minimal markdown to HTML for static sites with pretty URLs.

## ☀️ Install

```
yarn global add agave-generator
```

## 🍯 Use

```console
mkdir blog
cd blog
mkdir markdown
touch markdown/index.md # home page
touch markdown/first-post.md # /first-post/ route
agave # reads all your readmes in ./markdown and outputs them to ./public
```

For full list of options run:

```console
agave --help
```

## 🏜 Themes

Simply pass the -t argument

```
agave -t desert
```

## 🌿 Full Customization

Add any base HTML you would like.

base.html will wrap every generated page.

base.html must contain `<!-- MARKDOWN -->` where you would like your content placed.

If you have a styles.css file in the markdown folder, it will be copied to the deployment folder.

```console
touch markdown/base.html
touch markdown/styles.css
echo "<html><!-- MARKDOWN --></html>" > markdown/base.html
agave # run the generator again
```

Here is an example of using custom base html.

[Blog](https://jottenlips.github.io/)

[Repo](https://github.com/jottenlips/jottenlips.github.io)

## 📂 File structure

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

## 🧗‍♀️ Deploy your site

Github Pages

```console
agave --markdown myblog --public docs
git add --all
git commit -m"deploy"
git push
```

Setup your repo to look at the docs folder on your main branch in the repo settings.

Want to support this project?

[![Contributor Covenant](https://img.shields.io/badge/Contributor%20Covenant-v2.0%20adopted-ff69b4.svg)](code_of_conduct.md)

[![ko-fi](https://www.ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/K3K01P2WT)

      /* let _resp = Response.add_header(~name="content-security-policy", ~value="default-src 'self' style-src 'self' 'unsafe-inline';") */
