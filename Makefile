build: bin bin/lemon
	@$(MAKE) -C src --no-print-directory

bin/lemon:
	clang src/lemon.c -o bin/lemon

tests:
	@$(MAKE) -C test --no-print-directory

bin:
	mkdir bin

