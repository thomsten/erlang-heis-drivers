# Erlang headers directory
ERLLIB = "../../../lib/erlang/usr/include/"

# Compiler flags go here.
CFLAGS = -std=c99 -g -Wall -I$(ERLLIB) -MMD -O0

# Linker flags go here. -lcomedi
LDFLAGS = -g -lm -fpic -shared -lcomedi

# list of sources #$(shell find -name "*.c")
SOURCES = io.c elev.c elev_nif.c

# Program executable file name.
TARGET = elev.so

# Default rule, to compile everything.
all: $(TARGET)


# -- The below lines should not need to be changed --

# Define dependencies
DEPS = $(shell find -name "*.d")

# Define all object files.
OBJECTS = $(SOURCES:.c=.o)

# rule to link the program
$(TARGET): $(OBJECTS)
	gcc $(LDFLAGS) -o $@ $^

# Compile: create object files from C source files.
%.o : %.c
	gcc $(CFLAGS) -c -o $@ $< 

# Include dependencies, if any.
-include $(DEPS)

# rule for cleaning re-compilable files.
clean:
	rm -f $(TARGET) $(OBJECTS) $(DEPS)

rebuild: clean all

.PHONY: all rebuild clean

