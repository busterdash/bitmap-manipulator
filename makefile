BM_DIR = bitmap-machine
include $(BM_DIR)/make_sm_vars
OBJECTS = main.o $(BM_OBJECTS)
TARGET = bitman
CPP = g++

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CPP) -o $(TARGET) $(OBJECTS)

main.o: main.cpp
	$(CPP) -c -o main.o main.cpp

include $(BM_DIR)/make_sm_rules

.PHONY: clean
clean:
	rm -f *.o *.exe $(BM_DIR)/*.o
