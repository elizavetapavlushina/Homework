bin1 := server 
bin2 := client
obj1 := server.o
obj2 := client.o
src := server.c client.c

all: $(bin1) $(bin2)

$(bin1): $(obj1)
	$(CC) $(LDFLAGS) $^ -o $@
	
$(bin2): $(obj2)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm $(bin1) $(bin2) *.o
