bin := pr_tree
obj := pr_tree.o
src := pr_tree.c

.PHONY: all clean
all: $(bin)

$(bin): $(obj)
	gcc $^ -o $@

%.o: %.c
	gcc $^ -c -o $@

clean:
	rm $(bin) $(obj)