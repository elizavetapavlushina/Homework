BIN1 := server 
BIN2 := client
OBJ1 := server.o
OBJ2 := client.o
SRC := $(wildcard *.c)

all: $(BIN1) $(BIN2)

$(BIN1): $(OBJ1)
	$(CC) $(LDFLAGS) $^ -o $@
	
$(BIN2): $(OBJ2)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	rm $(OBJ1) $(BIN1) $(OBJ2) $(BIN2)
