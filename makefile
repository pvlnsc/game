CC := g++# This is the main compiler
# CC := clang --analyze # and comment out the linker last line for sanity
SRCDIR := src
BUILDDIR := build
BIN := bin
TARGET := bin/GameOfThrone
 
SRCEXT := cpp


CFLAGS := -std=c++17 -Wall -w
LIB := -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer 
INC := -I include


compile:
	@echo " Compiling...";
	$(shell mkdir $(BIN) && $(CC) $(SRCDIR)/*.$(SRCEXT) $(CFLAGS) $(LIB) -o $(TARGET))
clean:
	@echo " Cleaning..."; 
	$(shell rm -rf bin -y)

run:
	@echo " Running...";
	@ $(shell $(TARGET))


.PHONY: clean