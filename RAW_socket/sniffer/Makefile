SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)
BIN = sniffer

all:$(BIN) 

$(BIN): $(OBJ) 
	$(CC) $(OBJ) -o $@ $(LFLAGS)

%.o:%.c
	$(CC) -c $< $(CFLAGS) -o $@


clean:
	rm $(OBJ) $(BIN)