CXX = g++
CXXFLAGS = -Wall -std=c++17
TARGET = gorun
INSTALL_DIR = $(HOME)/bin
WRAPPER = ogre-enc

SRCS = $(wildcard src/*.cpp)

all: compile install

compile:
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

install:
	mkdir -p $(INSTALL_DIR)
	cp $(TARGET) $(INSTALL_DIR)/
	cp $(WRAPPER) $(INSTALL_DIR)/
	chmod +x $(INSTALL_DIR)/$(WRAPPER)
	@echo "Build complete and installed to $(INSTALL_DIR)"

clean:
	rm -f $(TARGET)
