CXX = g++
DOXYGEN = doxygen
LATEX = pdflatex

BIN = bin
DOC = doc/BLL4
Arbeit = Arbeit.tex
DOC_DIR = doc
EXEC = main
DOXYFILE = Doxyfile
SRCS = $(shell find -name "*.cpp")
OBJS = $(SRCS:./src/%.cpp=./$(BIN)/%.o)

INCLUDES = -Iinclude
LIBS = -lsfml-system -lsfml-window -lsfml-graphics -lboost_system -lboost_thread
DEBUG = -pg -g

CXX_FLAGS = $(INCLUDES) $(DEBUG) -std=c++11 -fpermissive

all: dirs Bin Doc

clean: 
	@echo
	@echo removing files
	rm -rf $(BIN)
	rm -rf $(DOC)
	rm -f  $(EXEC)
	rm $(DOC_DIR)/$(basename $(Arbeit)).pdf
	@echo

Doc: dirs $(DOC_DIR)/$(Arbeit)
	@echo
	@echo building documentation
	$(DOXYGEN) $(DOXYFILE) >> /dev/null
	$(LATEX) $(DOC_DIR)/$(Arbeit)
	$(LATEX) $(DOC_DIR)/$(Arbeit)
	mv $(basename $(Arbeit)).pdf $(DOC_DIR)/$(basename $(Arbeit)).pdf
	rm $(basename $(Arbeit)).*
	@echo

Bin: dirs $(OBJS)
	@echo
	@echo building/linking executeable
	$(CXX) $(CXX_FLAGS) $(OBJS) -o $(EXEC) $(LIBS)
	@echo

bin/%.o: src/%.cpp
	@echo
	@echo building $@
	$(CXX) $(CXX_FLAGS) -c -o $@ $<
	@echo

dirs:
	@echo
	@echo creating folders
	@mkdir -p $(BIN)
	@mkdir -p $(DOC)
	@echo

.PHONY: clean Doc
.IGNORE: dirs Doc
