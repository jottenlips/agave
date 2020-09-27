.PHONY: deps
deps:
	opam install --deps-only .

.PHONY: install
install: build
	dune install

.PHONY: build
build:
	dune build