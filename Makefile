#Makefile 7/12/2023
SHELL := /bin/bash 
CXX=g++
CXX_FLAGS=-g
CXX_FLAGS+=-std=c++2a
CXX_FLAGS+=-w
CXX_FLAGS+=-fpermissive


LSA_DIR=.
BUILD=$(LSA_DIR)/build
SRC_DIR=$(LSA_DIR)/src
INCLUDE_DIR=$(LSA_DIR)/include
TESTS_DIR=$(LSA_DIR)/tests


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
	./install
	@echo "\e[32m[+] Installation done.\e[0m"

$(BUILD_DIR)/demostatus_test: $(TESTS_DIR)/test_demostatus.cpp
	g++ -o $(BUILD)/demostatus_test $(TESTS_DIR)/test_demostatus.cpp $(CXX_FLAGS) -w $(INCLUDE_DIR)/build/lib/libgtest.a


test: $(BUILD_DIR)/demostatus_test
	@echo -e "\e[33m[*] Making tests...\e[0m"
	$(BUILD)/demostatus_test


.PHONY: clean install test

