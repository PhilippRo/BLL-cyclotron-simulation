CXX = g++
DOXYGEN = doxygen

BIN = bin
DOC = doc
EXEC = main
DOXYFILE = Doxyfile
SRCS = $(shell find -name "*.cpp")
OBJS = $(SRCS:./src/%.cpp=./$(BIN)/%.o)

INCLUDES = -Iinclude
LIBS = -lsfml-system -lsfml-window -lsfml-graphics -lboost_system -lboost_thread
DEBUG = -pg

CXX_FLAGS = $(INCLUDES) $(DEBUG) -std=c++11 -fpermissive

all: dirs Bin Doc

clean: 
	@echo
	@echo removing files
	rm -rf $(BIN)
	rm -rf $(DOC)
	rm -f  $(EXEC)
	@echo

Doc: dirs
	@echo
	@echo building documentation
	@$(DOXYGEN) $(DOXYFILE) >> /dev/null
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
.IGNORE: dirs
