bin := file_editor
obj := file_editor.o
src := file_editor.c

$(bin): $(obj)
	gcc $^ -o $@ -lncurses

%.o: %.c
	gcc $^ -c -o $@