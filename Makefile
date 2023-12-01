#MAKEFILE 13:42-29/11/2023


INC_DIR=./include

CXX_FLAGS=-std=c++2a
CXX_FLAGS+=-fpermissive
LINKER=ld


all: lsa main



main:
	@echo "Compiling in bin/lsa."
	@$(CXX) -o bin/lsa $(CXX_FLAGS) src/lsa.cpp src/main.cpp -I $(INC_DIR)
	@echo "Compiling in bin/lsall."
	@$(CXX) -o bin/lsall $(CXX_FLAGS) src/lsa.cpp src/main.cpp -I $(INC_DIR)

lsa:
	@echo "Creating object file for library.";$(CXX) -c -o bin/lsall.o src/lsa.cpp $(CXX_FLAGS) -I $(INC_DIR)

.PHONY:clear

clean:
	@find -type f ! -name "*.cpp" ! -name "*.h" ! -name "Makefile" -delete
