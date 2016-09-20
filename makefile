CC := g++

SRCDIR := src
BUILDDIR := build
TARGET := bin/TRK

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -w -std=c++11
INC := -I include
STATIC_ANALYZER := oclint

$(TARGET) : $(OBJECTS)
	@echo " Linking "
	@mkdir -p bin
	@mkdir -p data
	@mkdir -p tmp
	@echo " $(CC) $^ -o $(TARGET) $(LIB) $(LINKER)"; $(CC) $^ -o $(TARGET)

$(BUILDDIR)/%.o : $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) $(LIB) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

static-analyze:
	$(STATIC_ANALYZER) $(SOURCES) -- -c $(CFLAGS) $(INC) $(LIB)

clean:
	@echo " Cleaning... "
	@echo " rm -rf $(BUILDDIR) $(TARGET)"; rm -rf $(BUILDDIR) $(TARGET)


.PHONY: clean