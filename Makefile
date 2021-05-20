CC = g++
CFLAGS = -g -Wall
TARGET = calc
	
all: calc.o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o

$(TARGET): $(TARGET)
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp

$(TARGET).o: $(TARGET).cpp
	$(CC) $(CFLAGS) -c $(TARGET).cpp

clean:
	$(RM) $(TARGET) *.o *~
