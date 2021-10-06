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
LIBS_DEPENDECIES := $(addprefix $(BUILDDIR)/,exceptions Logger Matrix Scalar utils)
SCALAR_DEPENDENCIES := $(addsuffix _static.o,$(LIBS_DEPENDECIES))
MATRIX_DEPENDENCIES := $(addsuffix _dynamic.o,$(LIBS_DEPENDECIES))

DEFAULT_INPUT_FILE := run.in
DEFAULT_OUTPUT_FILE := run.out
INPUT_FILENAME_STORE := $(BUILDDIR)/input_file.txt
OUTPUT_FILENAME_STORE := $(BUILDDIR)/output_file.txt
ARGS_STORE := $(BUILDDIR)/args_file.txt

TESTS_START := 1
TESTS_END := 5
TESTS := $(addprefix test,$(shell seq $(TESTS_START) $(TESTS_END)))
TEST1ARGS := txam
TEST2ARGS := x
TEST3ARGS := asmtxd
TEST4ARGS := asmxd
TEST5ARGS := asdmts

vpath %.cpp $(SRCDIR)
vpath %.h $(INCLUDEDIR)

all: build

.PHONY: build
build: $(BUILDDIR)/main_static.o $(BUILDDIR)/input_static.o $(BUILDDIR)/output_static.o $(LIBS) | $(MKDIR)$(BINDIR)
	@g++ -o $(EXE) -I $(INCLUDEDIR) $< $(word 2,$^) $(word 3,$^) -L lib -lscalar -lmatrix
	@echo "Build Successfull!"

#! Not working approach...
# $(BUILDDIR)/%_static.o $(BUILDDIR)/%_dynamic.o: %.cpp $(HEADERS) | MKDIR_BUILD
# 	g++ -o $@ -c -I $(INCLUDEDIR) $< $(if $(filter %_dynamic.o,$@),-fPIC,)

$(BUILDDIR)/%_static.o: %.cpp $(HEADERS) | $(MKDIR)$(BUILDDIR)
	@g++ -o $@ -c -I $(INCLUDEDIR) $<

$(BUILDDIR)/%_dynamic.o: %.cpp $(HEADERS) | $(MKDIR)$(BUILDDIR)
	@g++ -o $@ -c -I $(INCLUDEDIR) $< -fPIC

$(LIBDIR)/libscalar.a: $(SCALAR_DEPENDENCIES) | $(MKDIR)$(LIBDIR)
	@ar rcs $@ $^

$(LIBDIR)/libmatrix.so: $(MATRIX_DEPENDENCIES) | $(MKDIR)$(LIBDIR)
	@g++ -shared -o $@ $^

$(MKDIR)%:
	@mkdir -p $(patsubst $(MKDIR)%,%,$@)

.PHONY: libs
libs: $(LIBS)

#! Remember to use `@` wherever possible
.PHONY: prepare
prepare: | $(MKDIR)$(BUILDDIR)
	@read -p "Enter the path to the input file: " input_file;\
	echo $$input_file > $(INPUT_FILENAME_STORE)
	@read -p "Enter the path to the output file: " output_file;\
	echo $$output_file > $(OUTPUT_FILENAME_STORE)
	@read -p "Enter the command line arguments for the program: " args;\
	echo $$args > $(ARGS_STORE)
 
.PHONY: run
run: | build
	@if [ -s $(INPUT_FILENAME_STORE) ]; then\
		input_file=$$(cat $(INPUT_FILENAME_STORE));\
	else\
		input_file=$(DEFAULT_INPUT_FILE);\
	fi;\
	if [ -s $(OUTPUT_FILENAME_STORE) ]; then\
		output_file=$$(cat $(OUTPUT_FILENAME_STORE));\
	else\
		output_file=$(DEFAULT_OUTPUT_FILE);\
	fi;\
	if [ -s $(ARGS_STORE) ]; then\
		args=$$(cat $(ARGS_STORE));\
	fi;\
	$(EXE) $$args < $$input_file > $$output_file

.PHONY: tests
tests: $(TESTS)

test%: $(TESTSDIR)/test%.in $(TESTSDIR)/test%.out | build
	@$(EXE) -$(TEST$(patsubst test%,%,$@)ARGS) < $< > $(BUILDDIR)/test.out
	@-diff $(word 2, $^) $(BUILDDIR)/test.out > $(BUILDDIR)/test.log
	@[ -s $(BUILDDIR)/test.log ] && echo "Test $(patsubst test%,%,$@) Failed :(" || echo "Test $(patsubst test%,%,$@) Passed :)"
	@rm -rf $(BUILDDIR)/test.out $(BUILDDIR)/test.log

.PHONY: clean
clean:
	@rm -rf $(BINDIR) $(BUILDDIR) $(LIBDIR)