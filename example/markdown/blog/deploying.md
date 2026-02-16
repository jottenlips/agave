@title Deploying Your Agave Site
@description How to deploy your static site to GitHub Pages, Netlify, or any host

# Deploying Your Agave Site

Once you've built your site, deploying is straightforward since it's just static files.

## GitHub Pages

1. Push your `public` directory to a `gh-pages` branch
2. Enable GitHub Pages in your repo settings
3. Your site is live!

## Netlify

1. Connect your repository
2. Set build command: `dune exec bin/Agave.exe -- -m markdown -p public`
3. Set publish directory: `public`

## Any Static Host

The `public` directory contains plain HTML, CSS, and nothing else. Upload it anywhere that serves static files — S3, Cloudflare Pages, Vercel, or even a simple nginx server.
