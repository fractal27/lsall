#Makefile 7/12/2023
#SHELL := /bin/bash 
CXX=g++
CXX_FLAGS=-g
CXX_FLAGS+=-std=c++2a
CXX_FLAGS+=-w
CXX_FLAGS+=-fpermissive


LSA_DIR=..
BUILD=$(LSA_DIR)/build
SRC_DIR=$(LSA_DIR)/src

INCLUDE=$(LSA_DIR)/include
CXX_FLAGS+=-I $(INCLUDE)


SRC=$(SRC_DIR)/main.cpp $(SRC_DIR)/lsa.cpp
OBJ=$(BUILD)/lsa.o $(BUILD)/main.o

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
	$(CXX) $(CXX_FLAGS) $(BUILD)/lsa.o $(BUILD)/main.o -o $(BUILD)/lsa -w #Silent
	$(CXX) $(CXX_FLAGS) $(BUILD)/lsa.o $(BUILD)/main.o -o $(BUILD)/lsall

install: compile link
	@echo "\e[33m[*] Installing...\e[0m"
	$(LSA_DIR)/install
	@echo "\e[32m[+] Installation done.\e[0m"



.PHONY: clean install

