all: build run

build:
	cd src; yacc -d parse.y; lex scan.l
	clang -o bin/trial-lang -l edit -I ./include src/main.c src/state.c src/gc.c src/pair.c src/port.c src/symbol.c src/value.c src/y.tab.c src/lex.yy.c src/bool.c src/vm.c src/init.c

clean:
	rm -f src/y.tab.c src/y.tab.h src/lex.yy.c
	rm -f bin/trial-lang

run:
	bin/trial-lang
