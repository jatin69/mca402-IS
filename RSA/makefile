CXX=g++
CFLAGS=-std=c++11
TARGET=rsa

INCLUDES=$(shell find ./src/ -name "*.hpp")
SRC=$(shell find ./src/ -name "*.cpp")
OBJ_SRC=$(subst .cpp,.o,$(SRC))

all: src

src: $(OBJ_SRC)	$(INCLUDES)
	$(CXX) $(CFLAGS) -o $(TARGET) $(OBJ_SRC)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean: 
	rm -rf $(shell find ./src/ -name "*.o")
	rm -rf ./$(TARGET)

run:
	./$(TARGET)