CC=gcc
CFLAGS=-Wall -O2
ALIB=libCRC.a
TARGET=maintest
AR=ar
ARFLAGS=-rc

OBJECTS=*.o

staticLib: $(ALIB)
main: $(TARGET)

$(TARGET): crc_test.o
	$(CC) -o $(TARGET) crc_test.o -L. -lCRC

$(ALIB): crc.o
	$(AR) $(ARFLAGS) $(ALIB) crc.o

%.o: %.c
	$(CC) -c $< $(CLAGS)

clean:
	rm -f *.o
	rm -f $(ALIB)
	rm -f $(TARGET)

