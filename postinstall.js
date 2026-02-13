#!/usr/bin/env node

const https = require("https");
const fs = require("fs");
const path = require("path");
const { execSync } = require("child_process");

const VERSION = require("./package.json").version;
const REPO = "jottenlips/agave";

function getPlatformBinaryName() {
  const platform = process.platform;
  const arch = process.arch;

  if (platform === "linux" && arch === "x64") return "agave-linux-x64";
  if (platform === "darwin" && arch === "x64") return "agave-darwin-x64";
  if (platform === "darwin" && arch === "arm64") return "agave-darwin-arm64";

  console.error(
    `Unsupported platform: ${platform}-${arch}. You can build from source with opam + dune.`
  );
  process.exit(1);
}

function download(url, dest) {
  return new Promise((resolve, reject) => {
    const request = (url) => {
      https
        .get(url, (res) => {
          if (res.statusCode >= 300 && res.statusCode < 400 && res.headers.location) {
            request(res.headers.location);
            return;
          }
          if (res.statusCode !== 200) {
            reject(new Error(`Download failed with status ${res.statusCode}: ${url}`));
            return;
          }
          const file = fs.createWriteStream(dest);
          res.pipe(file);
          file.on("finish", () => {
            file.close();
            resolve();
          });
        })
        .on("error", reject);
    };
    request(url);
  });
}

async function main() {
  const binaryName = getPlatformBinaryName();
  const url = `https://github.com/${REPO}/releases/download/v${VERSION}/${binaryName}`;
  const dest = path.join(__dirname, "bin", "agave-native");

  fs.mkdirSync(path.join(__dirname, "bin"), { recursive: true });

  console.log(`Downloading agave binary for ${process.platform}-${process.arch}...`);

  try {
    await download(url, dest);
    fs.chmodSync(dest, 0o755);
    console.log("agave binary installed successfully.");
  } catch (err) {
    console.error(`Failed to download binary: ${err.message}`);
    console.error("You can build from source with: opam install . --deps-only && dune build");
    process.exit(1);
  }
}

main();
