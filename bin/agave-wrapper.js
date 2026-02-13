#!/usr/bin/env node

const { execFileSync } = require("child_process");
const path = require("path");

const binary = path.join(__dirname, "agave-native");

try {
  execFileSync(binary, process.argv.slice(2), { stdio: "inherit", cwd: process.cwd() });
} catch (err) {
  if (err.status !== undefined) {
    process.exit(err.status);
  }
  console.error("Failed to run agave:", err.message);
  process.exit(1);
}
