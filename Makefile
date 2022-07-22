VERSION = 0.1

BUILD_OUT_DIR = build
OBJECTS_OUT_DIR = $(BUILD_OUT_DIR)/obj
EXECUTABLE_OUT_DIR = $(BUILD_OUT_DIR)/bin
EXECUTABLE_NAME = setrd
EXECUTABLE_OUT = $(EXECUTABLE_OUT_DIR)/$(EXECUTABLE_NAME)-$(VERSION)
DIRS_TO_MAKE = \
	$(BUILD_OUT_DIR)\
	$(OBJECTS_OUT_DIR)\
	$(EXECUTABLE_OUT_DIR)\

SOURCES_DIR = src
HEADERS_DIR = $(addprefix -I, )
SOURCES = $(patsubst $(SOURCES_DIR)/%, %, $(wildcard $(addsuffix /*.c*, $(SOURCES_DIR))))
OBJECTS = $(SOURCES:.c=.o)

COMPILER = gcc
CFLAGS = -ggdb -std=c11 -MD -pipe -Wall -Wextra -Wno-unused-parameter -Wno-long-long -pedantic
LFLAGS = -pipe
LIBS =

.PHONY: all

all: make_dirs compile_and_link

compile_and_link: $(OBJECTS)
	$(COMPILER) -o $(EXECUTABLE_OUT) $(addprefix $(OBJECTS_OUT_DIR)/, $(OBJECTS)) $(LFLAGS) $(LIBS)

%.o : $(SOURCES_DIR)/%.c
	$(COMPILER) -o $(OBJECTS_OUT_DIR)/$@ -c $< $(CFLAGS) $(build_flags) $(HEADERS_DIR)

make_dirs:
	mkdir -p $(DIRS_TO_MAKE)

clean:
	rm -fr $(DIRS_TO_MAKE)
