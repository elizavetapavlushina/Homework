LFLAGS = -lpthread
HDR := $(wildcard *.h)
SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)
BIN = server

all:$(BIN) 

$(BIN): $(OBJ) 
	$(CC) $(OBJ) -o $@ $(LFLAGS)

%.o:%.c
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJ):$(HDR)

clean:
	rm $(OBJ) $(BIN)