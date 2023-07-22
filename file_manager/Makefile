bin := file_manager
obj := file_manager.o
src := file_manager.c

.PHONY: all clean
all: $(bin)

$(bin): $(obj)
	gcc $^ -o $@ -lncurses

%.o: %.c
	gcc $^ -c -o $@

clean:
	rm $(bin) $(obj)
