CFLAGS := -Wall
CC := clang
LINK_FLAGS := -lfswatch

LD_LIBRARY_PATH := ./libs/
INCLUDE := -I include/

SOURCES := src/main.c src/arg_parse.c src/inotifier.c
BUILDPATH := build/
TARGET := neowatch 

.all = $(TARGET)


$(TARGET): $(SOURCES) $(BUILDPATH)
	@clang \
		-L$(LD_LIBRARY_PATH) \
		$(INCLUDE) \
		$(LINK_FLAGS) \
		$(SOURCES) \
		-o $(BUILDPATH)$(TARGET)


$(BUILDPATH):
	@if [ ! -d "$(BUILDPATH)" ]; then \
		mkdir $(BUILDPATH); \
	fi;


debug: CFLAGS += -DDEBUG -g -O0
debug: TARGET := $(TARGET)_debug
debug: $(TARGET)


run: $(TARGET)
	@$(BUILDPATH)$(TARGET) $(ARGS)

clean:
	@rm -rf $(BUILDPATH)