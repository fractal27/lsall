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


SRC=$(SRC_DIR)/main.cpp $(SRC_DIR)/lsall.cpp
OBJ=$(BUILD)/lsall.o $(BUILD)/main.o
CXX_FLAGS+=-I $(INCLUDE_DIR)


all: $(BUILD) compile link

clean:
	@echo -e "\e[33m[*] Cleaning..\e[0m"
	rm -rf $(LSA_DIR)/build/*

compile: $(SRC)
	@echo -e "\e[32m[+]Compiling to object files $(SRC)\e[0m"
	$(MAKE) $(BUILD)/main.o
	$(MAKE) $(BUILD)/lsall.o
	$(MAKE) $(BUILD)/read_emojis.o

$(BUILD):
	if ![[ -f $(BUILD) ]]; then
		mkdir $(BUILD)
	fi

$(BUILD)/main.o: $(SRC_DIR)/main.cpp
	$(CXX) -c $(CXX_FLAGS) $(SRC_DIR)/main.cpp -o $(BUILD)/main.o

$(BUILD)/lsall.o: $(SRC_DIR)/lsall.cpp  $(SRC_DIR)/lsall.h 
	$(CXX) -c $(CXX_FLAGS) $(SRC_DIR)/lsall.cpp -o $(BUILD)/lsall.o

$(BUILD)/read_emojis.o: $(SRC_DIR)/read_emojis.cpp $(SRC_DIR)/read_emojis.h
	$(CXX) -c $(CXX_FLAGS) $(SRC_DIR)/read_emojis.cpp -o $(BUILD)/read_emojis.o

link: $(OBJ)
	@echo -e "\e[32m[+] Linking object files $(OBJ)\e[0m"
	$(CXX) -ljsoncpp $(CXX_FLAGS) $(BUILD)/lsall.o $(BUILD)/main.o $(BUILD)/read_emojis.o -o $(BUILD)/lsall

install: compile link
	@echo -e "\e[33m[*] Installing...\e[0m"
	./install_sh
	@echo -e "\e[32m[+] Installation done.\e[0m"

$(BUILD)/testRunner: $(TESTS_DIR)/test_demostatus.cpp $(TESTS_DIR)/read_emojis.test.cpp
	g++ -ljsoncpp $(CXX_FLAGS) -o $(BUILD)/testRunner $(TESTS_DIR)/main.cpp $(TESTS_DIR)/test_demostatus.cpp $(TESTS_DIR)/read_emojis.test.cpp $(INCLUDE_DIR)/build/lib/libgtest.a -w


test: $(BUILD)/testRunner
	@echo -e "\e[33m[*] Making tests...\e[0m"
	$(BUILD)/testRunner


.PHONY: clean install test

