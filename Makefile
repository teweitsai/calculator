CC := clang++ # This is the main compiler

SRCDIR := src
SRCDIRTEST := test

BUILDDIR := build/calc
BUILDDIRTEST := build/test

TARGET := bin/calc
TARGETTEST := bin/testCalc
 
DEPENDENCYDIR := dependency
GOOGLETESTDIR := $(DEPENDENCYDIR)/googletest

SRCEXT := cpp

SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

SOURCESTEST := $(shell find $(SRCDIRTEST) -type f -name *.$(SRCEXT))
OBJECTSTEST := $(patsubst $(SRCDIRTEST)/%,$(BUILDDIRTEST)/%,$(SOURCESTEST:.$(SRCEXT)=.o))

CFLAGS := -std=c++17 -stdlib=libc++

LIB := -L lib
LIBTEST := -L dependency/googletest/lib

LINKLIBTEST := -l gtest -l pthread

INC := -I include
INCTEST := -I dependency/googletest/googletest/include

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(TARGETTEST): $(OBJECTSTEST)
	$(CC) $^ -o $(TARGETTEST) $(LIB) $(LIBTEST) $(LINKLIBTEST)

$(BUILDDIRTEST)/%.o: $(SRCDIRTEST)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIRTEST)
	$(CC) $(CFLAGS) $(INC) $(INCTEST) -c -o $@ $<

all: $(TARGET)

test: $(TARGETTEST)

googletest:
	@echo " Install googletest..."
	@rm -rf $(GOOGLETESTDIR)
	@cd $(DEPENDENCYDIR); git clone https://github.com/google/googletest.git
	@cd $(GOOGLETESTDIR); cmake .; make

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)
	@echo " $(RM) -r $(BUILDDIRTEST) $(TARGETTEST)"; $(RM) -r $(BUILDDIRTEST) $(TARGETTEST)

.PHONY: all test googletest clean