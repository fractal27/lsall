#Makefile 7/12/2023
#SHELL := /bin/bash 
CXX=g++
CXX_FLAGS=-g
CXX_FLAGS+=-std=c++2a
CXX_FLAGS+=-w
CXX_FLAGS+=-fpermissive


LSA_DIR=.
BUILD=$(LSA_DIR)/build
SRC_DIR=$(LSA_DIR)/src
INCLUDE_DIR=$(LSA_DIR)/include


SRC=$(SRC_DIR)/main.cpp $(SRC_DIR)/lsa.cpp
OBJ=$(BUILD)/lsa.o $(BUILD)/main.o
CXX_FLAGS+=-I $(INCLUDE_DIR)


all: clean compile link

clean:
	@echo "\e[33m[*] Cleaning..\e[0m"
	rm -rf $(LSA_DIR)/build/*

compile: $(SRC)
	@echo "\e[32m[+]Compiling to object files $(SRC)\e[0m"
	$(CXX) -c $(CXX_FLAGS) $(SRC_DIR)/main.cpp -o $(BUILD)/main.o -w #Silent
	$(CXX) -c $(CXX_FLAGS) $(SRC_DIR)/lsa.cpp -o $(BUILD)/lsa.o

link: $(OBJ)
	@echo "\e[32m[+] Linking object files $(OBJ)\e[0m"
	$(CXX) $(CXX_FLAGS) $(BUILD)/lsa.o $(BUILD)/main.o -o $(BUILD)/lsall

install: compile link
	@echo "\e[33m[*] Installing...\e[0m"
	@#{ echo "\e[33m[*] Installing executables.\e[0m" && sudo cp build/lsa /usr/local/bin/lsa && sudo cp build/lsall /usr/local/bin/lsall && echo "\e[32m[+] Successfully installed executables.\e[0m"} || {echo "\e[31m[-] Failed executables installation.\e[0m"};
	@#{ echo "\e[33m[*] Installing man files.\e[0m" && sudo cp src/lsall.1 /usr/share/man/man1 && echo "\e[32m[+] Successfully installed man files.\e[0m"} || { echo "\e[31m[-] Failed man files installation.\e[0m" };
	./install
	@echo "\e[32m[+] Installation done.\e[0m"



.PHONY: clean install

