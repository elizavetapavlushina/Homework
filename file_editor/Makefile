bin := file_editor
obj := file_editor.o
src := file_editor.c

.PHONY: all clean
all: $(bin)

$(bin): $(obj)
	gcc $^ -o $@ -lncurses

%.o: %.c
	gcc $^ -c -o $@

clean:
	rm $(bin) $(obj)