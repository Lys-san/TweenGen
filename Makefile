# Folders 
SRC    = src
HEADER = include
BIN    = bin

# Compilation flags and libraries
CC = i686-w64-mingw32-gcc
CFLAGS = -I$(HEADER) -Wall -ansi -lMLV -lm
LDLIBS = -lMLV -lm -lSDL -lSDL_mixer -lSDL_image -lSDL_ttf -lSDL_gfx -lxml2 -lglib-2.0 -D SDL_MAIN_HANDLED

# Compilation objects
CFILE = $(wildcard $(SRC)/*.c)
OBJ = $(CFILE:$(SRC)/%.c=$(BIN)/%.o)

# Executable file
EXEC = test

# for MLV compilation on windows
FILES =                  \
	redistributables/data  \
	redistributables/*.dll

# Execution of everything
all:$(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)
	@echo "Created exe file successfully."

$(BIN)/main.o: $(SRC)/main.c $(HEADER)/*.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDLIBS)
	@echo "Creation of object file for main.c complete."


$(BIN)/%.o:$(SRC)/%.c $(HEADER)/%.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDLIBS)
	@echo "Creation of object file complete."

.PHONY: clean mrproper

clean:
	rm -f $(BIN)/*.o;
	@echo "Cleaned repositories successfully."

mrproper: clean
	rm -f $(EXEC)
	rm -rf $(EXEC) *.dll data/