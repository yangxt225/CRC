#CC=gcc
CC=/usr/local/arm/4.3.2/bin/arm-linux-gcc
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

$(ALIB): libcrc.o
	$(AR) $(ARFLAGS) $(ALIB) libcrc.o

%.o: %.c
	$(CC) -c $< $(CLAGS)

clean:
	rm -f *.o
	rm -f $(ALIB)
	rm -f $(TARGET)

