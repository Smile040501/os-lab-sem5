SRCDIR := src
INCLUDEDIR := include
LIBDIR := lib
BINDIR := bin
TESTSDIR := tests
BUILDDIR := build

EXE := $(BINDIR)/lab
HEADERS := $(wildcard $(INCLUDEDIR)/*.h)

LIBS := $(addprefix $(LIBDIR)/, libscalar.a libmatrix.so)
LIBSDEPENDECIES := $(addprefix $(BUILDDIR)/, exceptions Logger Matrix Scalar utils)
SCALARDEPENDENCIES := $(addsuffix _static.o, $(LIBSDEPENDECIES))
MATRIXDEPENDENCIES := $(addsuffix _dynamic.o, $(LIBSDEPENDECIES))

vpath %.cpp $(SRCDIR)
vpath %.h $(INCLUDEDIR)

all: build
	@echo "Success"

.PHONY: build
build: $(BUILDDIR)/main_static.o $(BUILDDIR)/input_static.o $(BUILDDIR)/output_static.o $(LIBS) | $(BINDIR)
	g++ -o $(EXE) -I $(INCLUDEDIR) $< $(word 2, $^) $(word 3, $^) -L lib -lscalar -lmatrix

$(BUILDDIR)/%_static.o: %.cpp $(HEADERS) | MKDIR_BUILD
	g++ -o $@ -c -I $(INCLUDEDIR) $<

$(BUILDDIR)/%_dynamic.o: %.cpp $(HEADERS) | MKDIR_BUILD
	g++ -o $@ -c -I $(INCLUDEDIR) $< -fPIC

$(LIBDIR)/libscalar.a: $(SCALARDEPENDENCIES) | $(LIBDIR)
	ar rcs $@ $^

$(LIBDIR)/libmatrix.so: $(MATRIXDEPENDENCIES) | $(LIBDIR)
	g++ -shared -o $@ $^

$(BINDIR) $(LIBDIR):
	mkdir -p $@

MKDIR_BUILD:
	mkdir -p build

.PHONY: libs
libs: $(LIBS)

.PHONY: clean
clean:
	rm -rf $(BINDIR) $(BUILDDIR) $(LIBDIR)