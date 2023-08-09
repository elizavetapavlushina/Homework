SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)
BIN = client1 client2

all:$(BIN) 

$(BIN): $(OBJ) 
	$(CC) $< -o $@ $(LFLAGS)

%.o:%.c
	$(CC) -c $< $(CFLAGS) -o $@


clean:
	rm $(OBJ) $(BIN)