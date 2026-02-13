.PHONY: deps build install clean test

deps:
	opam install . --deps-only -y

build:
	dune build

install: build
	dune install

clean:
	dune clean

test: build
	dune exec bin/Agave.exe -- --help
