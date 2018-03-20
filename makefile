BM_DIR = basic-bitmap-fileio
O_WB = windows_bitmap
O_DIB = device_independent_bitmap
O_RI = raster_image
O_BRW = binary_rw

OBJECTS = main.o \
	$(BM_DIR)/$(O_WB).o \
	$(BM_DIR)/$(O_DIB).o \
	$(BM_DIR)/$(O_RI).o \
	$(BM_DIR)/$(O_BRW).o

TARGET = sun.exe
CPP = g++

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CPP) -o $(TARGET) $(OBJECTS)

.PHONY: clean

clean:
	rm -f *.o *.exe $(BM_DIR)/*.o
