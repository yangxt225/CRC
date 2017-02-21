CC=gcc
CFLAGS=-Wall -O2
ATRIPLEDES=libCRC.a
TARGET=maintest
AR=ar
ARFLAGS=-rc

OBJECTS=*.o

staticLib: $(ATRIPLEDES)
main: $(TARGET)

$(TARGET): crc_test.o
	$(CC) -o $(TARGET) crc_test.o -L. -lCRC

$(ATRIPLEDES): crc.o
	$(AR) $(ARFLAGS) $(ATRIPLEDES) crc.o

%.o: %.c
	$(CC) -c $< $(CLAGS)

clean:
	rm -f *.o
	rm -f $(ATRIPLEDES)
	rm -f $(TARGET)

