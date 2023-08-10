SRC := $(wildcard *.c)
OBJ1 := client.o
OBJ2 := server.o
BIN1 := client
BIN2 := server
LFLAGS := -lrt

all:$(BIN1) $(BIN2)

$(BIN1): $(OBJ1) 
	$(CC) $^ -o $@ $(LFLAGS)

$(BIN2): $(OBJ2) 
	$(CC) $^ -o $@ $(LFLAGS)

%.o:%.c
	$(CC) -c $< $(CFLAGS) -o $@


clean:
	rm $(OBJ1) $(BIN1) $(OBJ2) $(BIN2)