CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
LDFLAGS = -lm

TARGET = build\graph.exe
SRCS = graph.c
OBJS = $(SRCS:%.c=%.o)

LIB_SRCS = list_of_tokens.c \
		   my_stack.c \
		   polish_notation.c \
		   my_io.c \
		   check.c \
		   spaces.c \
		   matrix.c
LIB_OBJS = $(LIB_SRCS:%.c=%.o)

all: $(TARGET) clean_objects

$(TARGET): $(OBJS) $(LIB_OBJS) | build
	$(CC) $(OBJS) $(LIB_OBJS) -o $(TARGET) $(LDFLAGS)
	@echo "Build complete: $(TARGET)"

build:
	if not exist build mkdir build

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-del /Q "$(TARGET)"
	@echo "Files cleaned"

clean_objects:
	-del /Q $(OBJS) $(LIB_OBJS)
	@echo "Object files cleaned"

rebuild: clean all

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem --check-level=exhaustive *.c

clang-formatn:
	clang-format -n *.c *.h

clang-formati:
	clang-format -i *.c *.h

help:
	@echo "Available targets:"
	@echo "  all                    - Build"
	@echo "  clean                  - Remove object files and graph"
	@echo "  rebuild                - Rebuild from scratch"
	@echo "  clean_objects          - Remove object files"
	@echo "  cppcheck               - Cppcheck files"
	@echo "  clang-formatn          - Clang-format -n"
	@echo "  clang-formati          - Clang-format -i"
	@echo "  help                   - Show this help"


.PHONY: all clean rebuild help clean_objects cppcheck clang-formatn clang-formati
