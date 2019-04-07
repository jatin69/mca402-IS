CXX=g++
CFLAGS=-std=c++11
TARGET=rsa

SRC=$(shell find . -name "*.cpp")
OBJ_SRC=$(subst .cpp,.o,$(SRC))

all: src

src: $(OBJ_SRC)
	$(CXX) $(CFLAGS) -o $(TARGET) $(OBJ_SRC)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean: 
	rm -rf $(shell find . -name "*.o")
	rm -rf ./$(TARGET)

run:
	./$(TARGET)