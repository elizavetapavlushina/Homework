SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)
BIN = client

all:$(BIN) 

$(BIN): $(OBJ) 
	$(CC) $< -o $@ $(LFLAGS)

%.o:%.c
	$(CC) -c $< $(CFLAGS) -o $@


clean:
	rm $(OBJ) $(BIN)