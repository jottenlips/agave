let defaulthtml = {|<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Agave Site</title>
  <link rel="stylesheet" href="/styles.css">
</head>
<body>
  <main>
    <!-- MARKDOWN -->
  </main>
  <footer>
    <p>Built with Agave</p>
  </footer>
</body>
</html>
|};

let defaultCss = {|* { margin: 0; padding: 0; box-sizing: border-box; }

body {
  font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif;
  line-height: 1.6;
  color: #333;
  max-width: 720px;
  margin: 0 auto;
  padding: 20px;
  background: #fafaf8;
}

nav {
  display: flex;
  flex-wrap: wrap;
  gap: 16px;
  padding: 16px 0;
  border-bottom: 2px solid #2d5016;
  margin-bottom: 32px;
}

nav a {
  color: #2d5016;
  text-decoration: none;
  font-weight: 600;
}

nav a:hover { text-decoration: underline; }

main { min-height: 60vh; }

h1 { color: #2d5016; margin-bottom: 16px; }
h2 { color: #3a6b1e; margin: 24px 0 12px; }
h3 { color: #4a8525; margin: 20px 0 8px; }

p { margin-bottom: 12px; }

a { color: #2d5016; }

ul, ol { margin: 12px 0 12px 24px; }

code {
  background: #e8f0e0;
  padding: 2px 6px;
  border-radius: 3px;
  font-size: 0.9em;
}

pre {
  background: #2d2d2d;
  color: #f0f0f0;
  padding: 16px;
  border-radius: 6px;
  overflow-x: auto;
  margin: 16px 0;
}

pre code { background: none; color: inherit; padding: 0; }

footer {
  margin-top: 48px;
  padding: 16px 0;
  border-top: 1px solid #ddd;
  color: #888;
  font-size: 0.85em;
}

img[alt*="small"] {
  height: 500px;
}

img[alt*="extrasmall"] {
  height: 250px;
}
|};

/* Arrakis - Sun-bleached desert, endless sand, spice shimmer
   Warm sandy tones, burnt sienna, hot white sun, melange blue eyes */
let arrakisCss = {|@import url("https://fonts.googleapis.com/css2?family=Cinzel:wght@400;700&display=swap");
@import url("https://fonts.googleapis.com/css2?family=Crimson+Text:wght@400;700&display=swap");
html {
  background: #e8d5b0;
  height: 100%;
}

body {
  font-family: "Crimson Text", serif;
  line-height: 28px;
  margin: 0;
  color: #3d2b1a;
}

img[alt*="small"] {
  height: 500px;
}

img[alt*="extrasmall"] {
  height: 250px;
}

.coverimage {
  background: linear-gradient(180deg, #f5e6c8 0%, #e8cc8a 20%, #d4a855 40%, #c2853e 60%, #a0673a 80%, #7a4b2a 100%);
  background-repeat: no-repeat;
  background-size: cover;
  background-attachment: fixed;
  min-width: 100%;
  max-width: 300%;
  height: 100%;
}

h1 {
  font-family: "Cinzel", serif;
  color: #8b4513;
  line-height: 110%;
  text-transform: uppercase;
  letter-spacing: 4px;
  text-shadow: 1px 1px 0px #e8d5b0;
}

h2 {
  font-family: "Cinzel", serif;
  color: #a0522d;
  line-height: 110%;
  letter-spacing: 2px;
}

h3 {
  color: #6b3a1f;
  line-height: 110%;
}

code {
  border-radius: 3px;
  background-color: #3d2b1a;
  color: #e8cc8a;
  line-height: 200%;
  word-wrap: break-word;
}

pre {
  background-color: #3d2b1a;
  width: 90%;
  border-radius: 2px;
  padding-top: 10px;
  padding-left: 10px;
  padding-right: 10px;
  padding-bottom: 10px;
  overflow-x: scroll;
  border-left: 3px solid #c2853e;
}

.container {
  padding-top: 50px;
  padding-bottom: 50px;
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  min-height: 100vh;
  background: #dcc9a3;
}

.block {
  max-width: 800px;
  min-width: 270px;
  width: 90%;
  background-color: #f0e0c0;
  padding: 24px;
  margin-bottom: 15px;
  overflow-y: auto;
  border-radius: 2px;
  border-top: 3px solid #c2853e;
  box-shadow: 0 2px 12px rgba(61,43,26,0.15);
}

nav {
  display: flex;
  flex-wrap: wrap;
  gap: 12px;
  padding: 10px;
  max-width: 800px;
  min-width: 270px;
  width: 90%;
}

.nav {
  max-width: 800px;
  min-width: 300px;
  width: 90%;
  background-color: #f0e0c0;
  padding: 10px;
  overflow-y: auto;
  border-radius: 2px;
  align-items: center;
  justify-content: space-evenly;
  display: flex;
  flex-wrap: wrap;
  margin-bottom: 10px;
  border-top: 3px solid #c2853e;
}

.footer {
  max-width: 800px;
  min-width: 300px;
  width: 90%;
  background-color: #f0e0c0;
  padding: 10px;
  overflow-y: auto;
  border-radius: 2px;
  align-items: center;
  justify-content: space-evenly;
  display: flex;
  flex-wrap: wrap;
  margin-bottom: 10px;
  border-top: 3px solid #c2853e;
}

@media only screen and (max-width: 500px) {
  .nav {
    max-width: 800px;
    min-width: 300px;
    width: 90%;
    background-color: #f0e0c0;
    padding: 10px;
    overflow-y: scroll;
    border-radius: 2px;
    align-items: flex-start;
    justify-content: space-evenly;
    display: flex;
    flex-wrap: wrap;
    margin-bottom: 10px;
    flex-direction: column;
  }
  .footer {
    max-width: 800px;
    min-width: 300px;
    width: 90%;
    background-color: #f0e0c0;
    padding: 10px;
    border-radius: 2px;
    align-items: flex-start;
    justify-content: space-evenly;
    display: flex;
    flex-wrap: wrap;
    margin-bottom: 10px;
    flex-direction: column;
  }
  .coverimage {
    background: transparent;
    background-repeat: no-repeat;
    background-size: cover;
    background-attachment: fixed;
    min-width: 100%;
    max-width: 300%;
    height: 100%;
  }
  .container {
    padding-top: 20px;
    padding-bottom: 50px;
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
    min-height: 100vh;
  }
}

a {
  text-decoration: none;
  color: #1a6b8a;
  align-items: center;
}

a:hover {
  -webkit-transform: scale(1.1);
  -ms-transform: scale(1.1);
  transform: scale(1.1);
  color: #2596be;
}

.back {
  text-decoration: underline;
}
|};

let arrakishtml = {|
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <title>Arrakis</title>
    <link rel="stylesheet" href="/styles.css" />
  </head>
  <body>
    <div class="coverimage"></div>
    <div class="container">
      <div class="block">
        <!-- MARKDOWN -->
      </div>
    </div>
  </body>
</html>
|};

/* Caladan - Earth ocean theme, lush greens and deep blues */
let caladanCss = {|@import url("https://fonts.googleapis.com/css2?family=Lora:ital,wght@0,400;0,700;1,400&display=swap");
@import url("https://fonts.googleapis.com/css2?family=Source+Sans+3&display=swap");
html {
  background: #0a1628;
  height: 100%;
}

body {
  font-family: "Source Sans 3", sans-serif;
  line-height: 28px;
  margin: 0;
  color: #c8dce8;
}

img[alt*="small"] {
  height: 500px;
}

img[alt*="extrasmall"] {
  height: 250px;
}

.coverimage {
  background: linear-gradient(180deg, #87CEEB 0%, #2e6b8a 30%, #1a4a6b 60%, #0a2840 100%);
  background-repeat: no-repeat;
  background-size: cover;
  background-attachment: fixed;
  min-width: 100%;
  max-width: 300%;
  height: 100%;
}

h1 {
  font-family: "Lora", serif;
  color: #5bb5d5;
  line-height: 110%;
}

h2 {
  font-family: "Lora", serif;
  color: #3d9b6e;
  line-height: 110%;
}

h3 {
  color: #7ecba1;
  line-height: 110%;
}

code {
  border-radius: 3px;
  background-color: #0a1628;
  color: #7ecba1;
  line-height: 200%;
  word-wrap: break-word;
  border: 1px solid #1a3048;
}

pre {
  background-color: #0a1628;
  width: 90%;
  border-radius: 6px;
  padding-top: 10px;
  padding-left: 10px;
  padding-right: 10px;
  padding-bottom: 10px;
  overflow-x: scroll;
  border: 1px solid #1a3048;
}

.container {
  padding-top: 50px;
  padding-bottom: 50px;
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  min-height: 100vh;
  background: #0d1f35;
}

.block {
  max-width: 800px;
  min-width: 270px;
  width: 90%;
  background-color: #132a45;
  padding: 20px;
  margin-bottom: 15px;
  overflow-y: auto;
  border-radius: 8px;
  border: 1px solid #1a3a5c;
  box-shadow: 0 4px 20px rgba(0,0,0,0.3);
}

nav {
  display: flex;
  flex-wrap: wrap;
  gap: 12px;
  padding: 10px;
  max-width: 800px;
  min-width: 270px;
  width: 90%;
}

.nav {
  max-width: 800px;
  min-width: 300px;
  width: 90%;
  background-color: #132a45;
  padding: 10px;
  overflow-y: auto;
  border-radius: 8px;
  align-items: center;
  justify-content: space-evenly;
  display: flex;
  flex-wrap: wrap;
  margin-bottom: 10px;
  border: 1px solid #1a3a5c;
}

.footer {
  max-width: 800px;
  min-width: 300px;
  width: 90%;
  background-color: #132a45;
  padding: 10px;
  overflow-y: auto;
  border-radius: 8px;
  align-items: center;
  justify-content: space-evenly;
  display: flex;
  flex-wrap: wrap;
  margin-bottom: 10px;
  border: 1px solid #1a3a5c;
}

@media only screen and (max-width: 500px) {
  .nav {
    max-width: 800px;
    min-width: 300px;
    width: 90%;
    background-color: #132a45;
    padding: 10px;
    overflow-y: scroll;
    border-radius: 8px;
    align-items: flex-start;
    justify-content: space-evenly;
    display: flex;
    flex-wrap: wrap;
    margin-bottom: 10px;
    flex-direction: column;
  }
  .footer {
    max-width: 800px;
    min-width: 300px;
    width: 90%;
    background-color: #132a45;
    padding: 10px;
    border-radius: 8px;
    align-items: flex-start;
    justify-content: space-evenly;
    display: flex;
    flex-wrap: wrap;
    margin-bottom: 10px;
    flex-direction: column;
  }
  .coverimage {
    background: transparent;
    background-repeat: no-repeat;
    background-size: cover;
    background-attachment: fixed;
    min-width: 100%;
    max-width: 300%;
    height: 100%;
  }
  .container {
    padding-top: 20px;
    padding-bottom: 50px;
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
    min-height: 100vh;
  }
}

a {
  text-decoration: none;
  color: #5bb5d5;
  align-items: center;
}

a:hover {
  -webkit-transform: scale(1.1);
  -ms-transform: scale(1.1);
  transform: scale(1.1);
  color: #8ed4ec;
}

.back {
  text-decoration: underline;
}
|};

let caladanhtml = {|
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <title>Caladan</title>
    <link rel="stylesheet" href="/styles.css" />
  </head>
  <body>
    <div class="coverimage"></div>
    <div class="container">
      <div class="block">
        <!-- MARKDOWN -->
      </div>
    </div>
  </body>
</html>
|};

/* Giedi Prime - Black and white minimalist, stark industrial */
let giediprimeCss = {|@import url("https://fonts.googleapis.com/css2?family=Space+Grotesk:wght@400;700&display=swap");
html {
  background: #000000;
  height: 100%;
}

body {
  font-family: "Space Grotesk", sans-serif;
  line-height: 26px;
  margin: 0;
  color: #d0d0d0;
}

img[alt*="small"] {
  height: 500px;
}

img[alt*="extrasmall"] {
  height: 250px;
}

.coverimage {
  background: #000000;
  min-width: 100%;
  max-width: 300%;
  height: 100%;
}

h1 {
  color: #ffffff;
  line-height: 110%;
  font-weight: 700;
  text-transform: uppercase;
  letter-spacing: 6px;
  border-bottom: 2px solid #ffffff;
  padding-bottom: 8px;
}

h2 {
  color: #ffffff;
  line-height: 110%;
  font-weight: 700;
  letter-spacing: 2px;
}

h3 {
  color: #999999;
  line-height: 110%;
  text-transform: uppercase;
  letter-spacing: 1px;
}

code {
  border-radius: 0;
  background-color: #1a1a1a;
  color: #ffffff;
  line-height: 200%;
  word-wrap: break-word;
  border: 1px solid #333333;
}

pre {
  background-color: #1a1a1a;
  width: 90%;
  border-radius: 0;
  padding-top: 10px;
  padding-left: 10px;
  padding-right: 10px;
  padding-bottom: 10px;
  overflow-x: scroll;
  border: 1px solid #333333;
}

.container {
  padding-top: 50px;
  padding-bottom: 50px;
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  min-height: 100vh;
  background: #000000;
}

.block {
  max-width: 800px;
  min-width: 270px;
  width: 90%;
  background-color: #0a0a0a;
  padding: 20px;
  margin-bottom: 15px;
  overflow-y: auto;
  border-radius: 0;
  border: 1px solid #333333;
}

nav {
  display: flex;
  flex-wrap: wrap;
  gap: 12px;
  padding: 10px;
  max-width: 800px;
  min-width: 270px;
  width: 90%;
}

.nav {
  max-width: 800px;
  min-width: 300px;
  width: 90%;
  background-color: #0a0a0a;
  padding: 10px;
  overflow-y: auto;
  border-radius: 0;
  align-items: center;
  justify-content: space-evenly;
  display: flex;
  flex-wrap: wrap;
  margin-bottom: 10px;
  border: 1px solid #333333;
}

.footer {
  max-width: 800px;
  min-width: 300px;
  width: 90%;
  background-color: #0a0a0a;
  padding: 10px;
  overflow-y: auto;
  border-radius: 0;
  align-items: center;
  justify-content: space-evenly;
  display: flex;
  flex-wrap: wrap;
  margin-bottom: 10px;
  border: 1px solid #333333;
}

@media only screen and (max-width: 500px) {
  .nav {
    max-width: 800px;
    min-width: 300px;
    width: 90%;
    background-color: #0a0a0a;
    padding: 10px;
    overflow-y: scroll;
    border-radius: 0;
    align-items: flex-start;
    justify-content: space-evenly;
    display: flex;
    flex-wrap: wrap;
    margin-bottom: 10px;
    flex-direction: column;
  }
  .footer {
    max-width: 800px;
    min-width: 300px;
    width: 90%;
    background-color: #0a0a0a;
    padding: 10px;
    border-radius: 0;
    align-items: flex-start;
    justify-content: space-evenly;
    display: flex;
    flex-wrap: wrap;
    margin-bottom: 10px;
    flex-direction: column;
  }
  .coverimage {
    background: #000000;
    min-width: 100%;
    max-width: 300%;
    height: 100%;
  }
  .container {
    padding-top: 20px;
    padding-bottom: 50px;
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
    min-height: 100vh;
  }
}

a {
  text-decoration: none;
  color: #ffffff;
  align-items: center;
  border-bottom: 1px solid #666666;
}

a:hover {
  -webkit-transform: scale(1.1);
  -ms-transform: scale(1.1);
  transform: scale(1.1);
  color: #999999;
}

.back {
  text-decoration: underline;
}
|};

let gieidiprimehtml = {|
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <title>Giedi Prime</title>
    <link rel="stylesheet" href="/styles.css" />
  </head>
  <body>
    <div class="coverimage"></div>
    <div class="container">
      <div class="block">
        <!-- MARKDOWN -->
      </div>
    </div>
  </body>
</html>
|};

/* Ix - 90s cyberdelia, neon on dark, hacker aesthetic */
let ixCss = {|@import url("https://fonts.googleapis.com/css2?family=Share+Tech+Mono&display=swap");
@import url("https://fonts.googleapis.com/css2?family=Orbitron:wght@400;700&display=swap");
html {
  background: #0a0a12;
  height: 100%;
}

body {
  font-family: "Share Tech Mono", monospace;
  line-height: 26px;
  margin: 0;
  color: #b0b0d0;
}

img[alt*="small"] {
  height: 500px;
}

img[alt*="extrasmall"] {
  height: 250px;
}

.coverimage {
  background: linear-gradient(135deg, #0a0a12 0%, #1a0a2e 30%, #0a1a2e 60%, #0a0a12 100%);
  background-repeat: no-repeat;
  background-size: cover;
  background-attachment: fixed;
  min-width: 100%;
  max-width: 300%;
  height: 100%;
}

h1 {
  font-family: "Orbitron", sans-serif;
  color: #00ff88;
  line-height: 110%;
  text-transform: uppercase;
  letter-spacing: 4px;
  text-shadow: 0 0 10px #00ff8844, 0 0 30px #00ff8822;
}

h2 {
  font-family: "Orbitron", sans-serif;
  color: #ff00ff;
  line-height: 110%;
  letter-spacing: 2px;
  text-shadow: 0 0 10px #ff00ff44;
}

h3 {
  color: #00ccff;
  line-height: 110%;
  text-shadow: 0 0 8px #00ccff33;
}

code {
  border-radius: 3px;
  background-color: #0d0d1a;
  color: #00ff88;
  line-height: 200%;
  word-wrap: break-word;
  border: 1px solid #1a1a3a;
}

pre {
  background-color: #0d0d1a;
  width: 90%;
  border-radius: 6px;
  padding-top: 10px;
  padding-left: 10px;
  padding-right: 10px;
  padding-bottom: 10px;
  overflow-x: scroll;
  border: 1px solid #1a1a3a;
  box-shadow: 0 0 15px rgba(0, 255, 136, 0.05);
}

.container {
  padding-top: 50px;
  padding-bottom: 50px;
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  min-height: 100vh;
  background: #0a0a12;
}

.block {
  max-width: 800px;
  min-width: 270px;
  width: 90%;
  background-color: #12121f;
  padding: 20px;
  margin-bottom: 15px;
  overflow-y: auto;
  border-radius: 6px;
  border: 1px solid #2a1a4a;
  box-shadow: 0 0 20px rgba(255, 0, 255, 0.05), 0 0 40px rgba(0, 255, 136, 0.03);
}

nav {
  display: flex;
  flex-wrap: wrap;
  gap: 12px;
  padding: 10px;
  max-width: 800px;
  min-width: 270px;
  width: 90%;
}

.nav {
  max-width: 800px;
  min-width: 300px;
  width: 90%;
  background-color: #12121f;
  padding: 10px;
  overflow-y: auto;
  border-radius: 6px;
  align-items: center;
  justify-content: space-evenly;
  display: flex;
  flex-wrap: wrap;
  margin-bottom: 10px;
  border: 1px solid #2a1a4a;
}

.footer {
  max-width: 800px;
  min-width: 300px;
  width: 90%;
  background-color: #12121f;
  padding: 10px;
  overflow-y: auto;
  border-radius: 6px;
  align-items: center;
  justify-content: space-evenly;
  display: flex;
  flex-wrap: wrap;
  margin-bottom: 10px;
  border: 1px solid #2a1a4a;
}

@media only screen and (max-width: 500px) {
  .nav {
    max-width: 800px;
    min-width: 300px;
    width: 90%;
    background-color: #12121f;
    padding: 10px;
    overflow-y: scroll;
    border-radius: 6px;
    align-items: flex-start;
    justify-content: space-evenly;
    display: flex;
    flex-wrap: wrap;
    margin-bottom: 10px;
    flex-direction: column;
  }
  .footer {
    max-width: 800px;
    min-width: 300px;
    width: 90%;
    background-color: #12121f;
    padding: 10px;
    border-radius: 6px;
    align-items: flex-start;
    justify-content: space-evenly;
    display: flex;
    flex-wrap: wrap;
    margin-bottom: 10px;
    flex-direction: column;
  }
  .coverimage {
    background: transparent;
    background-repeat: no-repeat;
    background-size: cover;
    background-attachment: fixed;
    min-width: 100%;
    max-width: 300%;
    height: 100%;
  }
  .container {
    padding-top: 20px;
    padding-bottom: 50px;
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
    min-height: 100vh;
  }
}

a {
  text-decoration: none;
  color: #ff00ff;
  align-items: center;
}

a:hover {
  -webkit-transform: scale(1.1);
  -ms-transform: scale(1.1);
  transform: scale(1.1);
  color: #00ff88;
  text-shadow: 0 0 8px #00ff8844;
}

.back {
  text-decoration: underline;
}
|};

let ixhtml = {|
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <title>Ix</title>
    <link rel="stylesheet" href="/styles.css" />
  </head>
  <body>
    <div class="coverimage"></div>
    <div class="container">
      <div class="block">
        <!-- MARKDOWN -->
      </div>
    </div>
  </body>
</html>
|};

/* Salusa Secundus - Brutalist, raw concrete, heavy type */
let salusasecundusCss = {|@import url("https://fonts.googleapis.com/css2?family=Bebas+Neue&display=swap");
@import url("https://fonts.googleapis.com/css2?family=Inter:wght@400;700&display=swap");
html {
  background: #8a8a82;
  height: 100%;
}

body {
  font-family: "Inter", sans-serif;
  line-height: 26px;
  margin: 0;
  color: #1a1a18;
  font-weight: 400;
}

img[alt*="small"] {
  height: 500px;
}

img[alt*="extrasmall"] {
  height: 250px;
}

.coverimage {
  background: #6b6b63;
  min-width: 100%;
  max-width: 300%;
  height: 100%;
}

h1 {
  font-family: "Bebas Neue", sans-serif;
  color: #1a1a18;
  line-height: 100%;
  font-size: 3em;
  text-transform: uppercase;
  letter-spacing: 4px;
  border-left: 8px solid #cc2200;
  padding-left: 16px;
  margin-left: -16px;
}

h2 {
  font-family: "Bebas Neue", sans-serif;
  color: #1a1a18;
  line-height: 110%;
  font-size: 2em;
  text-transform: uppercase;
  letter-spacing: 2px;
}

h3 {
  font-family: "Bebas Neue", sans-serif;
  color: #4a4a44;
  line-height: 110%;
  text-transform: uppercase;
  letter-spacing: 1px;
}

code {
  border-radius: 0;
  background-color: #1a1a18;
  color: #c0c0b8;
  line-height: 200%;
  word-wrap: break-word;
}

pre {
  background-color: #1a1a18;
  width: 90%;
  border-radius: 0;
  padding-top: 10px;
  padding-left: 10px;
  padding-right: 10px;
  padding-bottom: 10px;
  overflow-x: scroll;
}

.container {
  padding-top: 50px;
  padding-bottom: 50px;
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  min-height: 100vh;
  background: #8a8a82;
}

.block {
  max-width: 800px;
  min-width: 270px;
  width: 90%;
  background-color: #a0a098;
  padding: 24px;
  margin-bottom: 15px;
  overflow-y: auto;
  border-radius: 0;
  border-top: 6px solid #cc2200;
  box-shadow: 8px 8px 0px #6b6b63;
}

nav {
  display: flex;
  flex-wrap: wrap;
  gap: 12px;
  padding: 10px;
  max-width: 800px;
  min-width: 270px;
  width: 90%;
}

.nav {
  max-width: 800px;
  min-width: 300px;
  width: 90%;
  background-color: #a0a098;
  padding: 10px;
  overflow-y: auto;
  border-radius: 0;
  align-items: center;
  justify-content: space-evenly;
  display: flex;
  flex-wrap: wrap;
  margin-bottom: 10px;
  border-top: 4px solid #cc2200;
}

.footer {
  max-width: 800px;
  min-width: 300px;
  width: 90%;
  background-color: #a0a098;
  padding: 10px;
  overflow-y: auto;
  border-radius: 0;
  align-items: center;
  justify-content: space-evenly;
  display: flex;
  flex-wrap: wrap;
  margin-bottom: 10px;
  border-top: 4px solid #cc2200;
}

@media only screen and (max-width: 500px) {
  .nav {
    max-width: 800px;
    min-width: 300px;
    width: 90%;
    background-color: #a0a098;
    padding: 10px;
    overflow-y: scroll;
    border-radius: 0;
    align-items: flex-start;
    justify-content: space-evenly;
    display: flex;
    flex-wrap: wrap;
    margin-bottom: 10px;
    flex-direction: column;
  }
  .footer {
    max-width: 800px;
    min-width: 300px;
    width: 90%;
    background-color: #a0a098;
    padding: 10px;
    border-radius: 0;
    align-items: flex-start;
    justify-content: space-evenly;
    display: flex;
    flex-wrap: wrap;
    margin-bottom: 10px;
    flex-direction: column;
  }
  .coverimage {
    background: #6b6b63;
    min-width: 100%;
    max-width: 300%;
    height: 100%;
  }
  .container {
    padding-top: 20px;
    padding-bottom: 50px;
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
    min-height: 100vh;
  }
}

a {
  text-decoration: none;
  color: #cc2200;
  align-items: center;
  font-weight: 700;
}

a:hover {
  -webkit-transform: scale(1.1);
  -ms-transform: scale(1.1);
  transform: scale(1.1);
  color: #ff3311;
}

.back {
  text-decoration: underline;
}
|};

let salusasecundushtml = {|
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <title>Salusa Secundus</title>
    <link rel="stylesheet" href="/styles.css" />
  </head>
  <body>
    <div class="coverimage"></div>
    <div class="container">
      <div class="block">
        <!-- MARKDOWN -->
      </div>
    </div>
  </body>
</html>
|};

/* Spice - Psychedelic melange trip, the spice expands consciousness
   Molten oranges, gold shimmer, spice glow, sparkling dust */
let spiceCss = {|@import url("https://fonts.googleapis.com/css2?family=Monoton&display=swap");
@import url("https://fonts.googleapis.com/css2?family=Quicksand:wght@400;700&display=swap");
html {
  background: #1a0800;
  height: 100%;
}

body {
  font-family: "Quicksand", sans-serif;
  line-height: 28px;
  margin: 0;
  color: #f0d8b8;
}

img[alt*="small"] {
  height: 500px;
}

img[alt*="extrasmall"] {
  height: 250px;
}

.coverimage {
  background: linear-gradient(135deg, #ff6b00 0%, #ff9500 15%, #ffcc00 30%, #ff6b00 50%, #e83a00 65%, #ffaa00 80%, #ff6b00 100%);
  background-size: 400% 400%;
  animation: spiceflow 10s ease infinite;
  min-width: 100%;
  max-width: 300%;
  height: 100%;
  position: relative;
}

.coverimage::after {
  content: "";
  position: absolute;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  background-image: radial-gradient(2px 2px at 20% 30%, #ffffffcc, transparent),
    radial-gradient(2px 2px at 40% 70%, #ffe08088, transparent),
    radial-gradient(1px 1px at 60% 20%, #ffffffaa, transparent),
    radial-gradient(2px 2px at 80% 50%, #ffcc0088, transparent),
    radial-gradient(1px 1px at 10% 80%, #ffffffcc, transparent),
    radial-gradient(2px 2px at 70% 85%, #ffe08088, transparent),
    radial-gradient(1px 1px at 35% 45%, #ffffffaa, transparent),
    radial-gradient(2px 2px at 90% 15%, #ffcc0088, transparent),
    radial-gradient(1px 1px at 50% 60%, #ffffffcc, transparent),
    radial-gradient(2px 2px at 15% 55%, #ffe08088, transparent);
  animation: sparkle 4s ease-in-out infinite alternate;
}

@keyframes spiceflow {
  0% { background-position: 0% 50%; }
  50% { background-position: 100% 50%; }
  100% { background-position: 0% 50%; }
}

@keyframes sparkle {
  0% { opacity: 0.4; }
  50% { opacity: 1; }
  100% { opacity: 0.6; }
}

h1 {
  font-family: "Monoton", cursive;
  color: #ff8800;
  line-height: 120%;
  font-size: 2.5em;
  text-shadow: 0 0 10px #ff880066, 0 0 30px #ff660044, 0 0 60px #ffaa0022;
  animation: glow 3s ease-in-out infinite alternate;
}

@keyframes glow {
  0% { text-shadow: 0 0 10px #ff880066, 0 0 30px #ff660044, 0 0 60px #ffaa0022; }
  100% { text-shadow: 0 0 20px #ff880088, 0 0 40px #ff660066, 0 0 80px #ffaa0044, 0 0 120px #ffcc0022; }
}

h2 {
  font-family: "Quicksand", sans-serif;
  color: #ffaa00;
  line-height: 110%;
  font-weight: 700;
  text-shadow: 0 0 12px #ff880033;
}

h3 {
  color: #e8a040;
  line-height: 110%;
  text-shadow: 0 0 8px #ff880022;
}

code {
  border-radius: 4px;
  background-color: #1a0800;
  color: #ffaa00;
  line-height: 200%;
  word-wrap: break-word;
  border: 1px solid #4a2000;
}

pre {
  background-color: #1a0800;
  width: 90%;
  border-radius: 6px;
  padding-top: 10px;
  padding-left: 10px;
  padding-right: 10px;
  padding-bottom: 10px;
  overflow-x: scroll;
  border: 1px solid #4a2000;
  box-shadow: 0 0 20px rgba(255, 136, 0, 0.08);
}

.container {
  padding-top: 50px;
  padding-bottom: 50px;
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  min-height: 100vh;
  background: radial-gradient(ellipse at 50% 0%, #2a1000 0%, #1a0800 60%, #0d0400 100%);
}

.block {
  max-width: 800px;
  min-width: 270px;
  width: 90%;
  background: linear-gradient(135deg, #261200 0%, #1f0e00 50%, #261200 100%);
  padding: 24px;
  margin-bottom: 15px;
  overflow-y: auto;
  border-radius: 8px;
  border: 1px solid #4a2000;
  box-shadow: 0 0 25px rgba(255, 136, 0, 0.06), inset 0 0 30px rgba(255, 170, 0, 0.02);
}

nav {
  display: flex;
  flex-wrap: wrap;
  gap: 12px;
  padding: 10px;
  max-width: 800px;
  min-width: 270px;
  width: 90%;
}

.nav {
  max-width: 800px;
  min-width: 300px;
  width: 90%;
  background: linear-gradient(135deg, #261200 0%, #1f0e00 50%, #261200 100%);
  padding: 10px;
  overflow-y: auto;
  border-radius: 8px;
  align-items: center;
  justify-content: space-evenly;
  display: flex;
  flex-wrap: wrap;
  margin-bottom: 10px;
  border: 1px solid #4a2000;
}

.footer {
  max-width: 800px;
  min-width: 300px;
  width: 90%;
  background: linear-gradient(135deg, #261200 0%, #1f0e00 50%, #261200 100%);
  padding: 10px;
  overflow-y: auto;
  border-radius: 8px;
  align-items: center;
  justify-content: space-evenly;
  display: flex;
  flex-wrap: wrap;
  margin-bottom: 10px;
  border: 1px solid #4a2000;
}

@media only screen and (max-width: 500px) {
  .nav {
    max-width: 800px;
    min-width: 300px;
    width: 90%;
    background: #261200;
    padding: 10px;
    overflow-y: scroll;
    border-radius: 8px;
    align-items: flex-start;
    justify-content: space-evenly;
    display: flex;
    flex-wrap: wrap;
    margin-bottom: 10px;
    flex-direction: column;
  }
  .footer {
    max-width: 800px;
    min-width: 300px;
    width: 90%;
    background: #261200;
    padding: 10px;
    border-radius: 8px;
    align-items: flex-start;
    justify-content: space-evenly;
    display: flex;
    flex-wrap: wrap;
    margin-bottom: 10px;
    flex-direction: column;
  }
  .coverimage {
    background: transparent;
    min-width: 100%;
    max-width: 300%;
    height: 100%;
  }
  .container {
    padding-top: 20px;
    padding-bottom: 50px;
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
    min-height: 100vh;
  }
}

a {
  text-decoration: none;
  color: #ff9500;
  align-items: center;
  text-shadow: 0 0 8px #ff880022;
}

a:hover {
  -webkit-transform: scale(1.1);
  -ms-transform: scale(1.1);
  transform: scale(1.1);
  color: #ffcc00;
  text-shadow: 0 0 15px #ffcc0066;
}

.back {
  text-decoration: underline;
}
|};

let spicehtml = {|
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <title>Spice</title>
    <link rel="stylesheet" href="/styles.css" />
  </head>
  <body>
    <div class="coverimage"></div>
    <div class="container">
      <div class="block">
        <!-- MARKDOWN -->
      </div>
    </div>
  </body>
</html>
|};

let hasTheme: string => bool =
  theme =>
    switch (theme) {
    | "" => false
    | _ => true
    };

let getTheme: string => string =
  theme =>
    switch (theme) {
    | "arrakis" => arrakishtml
    | "caladan" => caladanhtml
    | "giediprime" => gieidiprimehtml
    | "ix" => ixhtml
    | "salusasecundus" => salusasecundushtml
    | "spice" => spicehtml

    | _ => defaulthtml
    };

let getThemeCss: string => string =
  theme =>
    switch (theme) {
    | "arrakis" => arrakisCss
    | "caladan" => caladanCss
    | "giediprime" => giediprimeCss
    | "ix" => ixCss
    | "salusasecundus" => salusasecundusCss
    | "spice" => spiceCss

    | _ => defaultCss
    };
