let defaulthtml = {|<!DOCTYPE html>
  <html>
    <head>
      <meta charset="utf-8" />
      <title>Agave Site</title>
      <meta name="description" content="Site generated by Agave" />
      <meta name="author" content="you" />
      <link rel="stylesheet" href="stylesheet.css" />
    </head>
    <body>
      <!-- MARKDOWN -->
    </body>
  </html>
  |};

let bloggerhtml = {|
  <!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <title>Blog</title>
    <style>
      @import url("https://fonts.googleapis.com/css2?family=Epilogue&display=swap");
      @import url("https://fonts.googleapis.com/css?family=Open+Sans&display=swap");
      html {
        background: #ffffff;
      }
      body {
        font-family: "Epilogue", sans-serif;
        line-height: 26px;
      }
      img[alt*="small"] {
        width: 500px;
      }
      .coverimage {
        background: url(https://i.picsum.photos/id/247/1200/800.jpg?hmac=jAKee_4tKtq3oEQw_QgJbqXlUcx8ON2vfJfNt1Zki_4);
        /* RANDOM PHOTO */
        /* background: url(https://picsum.photos/2000/1500); */
        background-repeat: no-repeat;
        background-size: 100vw;
        background-attachment:fixed;
      }
      svg {
        display: none;
        height: 0;
        width: 0;
        color: clear;
      }
      code {
        flex: 1;
        border-radius: 2px;
        padding: 4px;
        background-color: #000000;
        color: #ffffff;
        line-height: 200%;
        word-wrap: break-word;
      }
      pre {
        background-color: #000000;
        width: 90%;
        border-radius: 6px;
        padding-top: 10px;
        padding-left: 10px;
        padding-right: 10px;
        padding-bottom: 10px;
        overflow-x: scroll;
      }
      .container {
        padding-top: 50px;
        display: flex;
        flex-direction: column;
        justify-content: center;
        align-items: center;
        min-height: 100vh;
        min-width: 100%;
      }
      .block {
        width: 100%;
        max-width: 800px;
        min-width: 300px;
        background-color: aliceblue;
        padding: 20px;
        overflow-y: scroll;
      }
    </style>
  </head>
  <body>
    <div class="coverimage" />
    <div class="container">
      <div class="block">
        <!-- MARKDOWN -->
      </div>
    </div>
  </body>
</html>
|};