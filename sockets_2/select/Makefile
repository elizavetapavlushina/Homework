bin1 := server 
bin2 := client_tcp
bin3 := client_udp
obj1 := server.o
obj2 := client_tcp.o
obj3 := client_udp.o
src := server.c client_tcp.c client_udp.c

all: $(bin1) $(bin2) $(bin3)

$(bin1): $(obj1)
	$(CC) $(LDFLAGS) $^ -o $@

$(bin2): $(obj2)
	$(CC) $(LDFLAGS) $^ -o $@

$(bin3): $(obj3)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm $(bin1) $(bin2) $(bin3) *.o
