SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)
BIN := shop
LFLAGS := -lpthread

all:$(BIN) 

$(BIN): $(OBJ) 
	$(CC) $(OBJ) -o $@ $(LFLAGS)

%.o:%.c
	$(CC) -c $< $(CFLAGS) -o $@


clean:
	rm $(OBJ) $(BIN)