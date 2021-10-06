SRCDIR := src
INCLUDEDIR := include
LIBDIR := lib
BINDIR := bin
TESTSDIR := tests
BUILDDIR := build
MKDIR := MKDIR_

LD_LIBRARY_PATH := $(LD_LIBRARY_PATH):$(PWD)/$(LIBDIR)/

EXE := $(BINDIR)/lab
HEADERS := $(wildcard $(INCLUDEDIR)/*.h)

LIBS := $(addprefix $(LIBDIR)/,libscalar.a libmatrix.so)
LIBSDEPENDECIES := $(addprefix $(BUILDDIR)/,exceptions Logger Matrix Scalar utils)
SCALARDEPENDENCIES := $(addsuffix _static.o,$(LIBSDEPENDECIES))
MATRIXDEPENDENCIES := $(addsuffix _dynamic.o,$(LIBSDEPENDECIES))

INPUTFILE := run.in
OUTPUTFILE := run.out

TEST1ARGS := txam
TEST2ARGS := x
TEST3ARGS := asmtxd
TEST4ARGS := asmxd
TEST5ARGS := asdmts

vpath %.cpp $(SRCDIR)
vpath %.h $(INCLUDEDIR)

all: build
	@echo "Success"

.PHONY: build
build: $(BUILDDIR)/main_static.o $(BUILDDIR)/input_static.o $(BUILDDIR)/output_static.o $(LIBS) | $(MKDIR)$(BINDIR)
	g++ -o $(EXE) -I $(INCLUDEDIR) $< $(word 2,$^) $(word 3,$^) -L lib -lscalar -lmatrix

#! Not working approach...
# $(BUILDDIR)/%_static.o $(BUILDDIR)/%_dynamic.o: %.cpp $(HEADERS) | MKDIR_BUILD
# 	g++ -o $@ -c -I $(INCLUDEDIR) $< $(if $(filter %_dynamic.o,$@),-fPIC,)

$(BUILDDIR)/%_static.o: %.cpp $(HEADERS) | $(MKDIR)$(BUILDDIR)
	g++ -o $@ -c -I $(INCLUDEDIR) $<

$(BUILDDIR)/%_dynamic.o: %.cpp $(HEADERS) | $(MKDIR)$(BUILDDIR)
	g++ -o $@ -c -I $(INCLUDEDIR) $< -fPIC

$(LIBDIR)/libscalar.a: $(SCALARDEPENDENCIES) | $(MKDIR)$(LIBDIR)
	ar rcs $@ $^

$(LIBDIR)/libmatrix.so: $(MATRIXDEPENDENCIES) | $(MKDIR)$(LIBDIR)
	g++ -shared -o $@ $^

$(MKDIR)%:
	mkdir -p $(patsubst $(MKDIR)%,%,$@)

.PHONY: libs
libs: $(LIBS)

.PHONY: tests
tests: test1 test2 test3 test4 test5

test%: $(TESTSDIR)/test%.in $(TESTSDIR)/test%.out | build
	$(EXE) -$(TEST$(patsubst test%,%,$@)ARGS) < $< > $(BUILDDIR)/test.out
	-diff $(word 2, $^) $(BUILDDIR)/test.out > $(BUILDDIR)/test.log
	[ -s $(BUILDDIR)/test.log ] && echo "Test $(patsubst test%,%,$@) Failed :(" || echo "Test $(patsubst test%,%,$@) Passed :)"
	rm -rf $(BUILDDIR)/test.out $(BUILDDIR)/test.log

.PHONY: clean
clean:
	rm -rf $(BINDIR) $(BUILDDIR) $(LIBDIR)