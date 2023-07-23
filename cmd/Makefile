bin := cmd
obj := cmd.o
src := cmd.c

.PHONY: all clean
all: $(bin)

$(bin): $(obj)
	gcc $^ -o $@

%.o: %.c
	gcc $^ -c -o $@

clean:
	rm $(bin) $(obj)