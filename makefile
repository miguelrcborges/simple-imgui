CC = clang
CFLAGS = $$(sdl2-config --cflags)
LINKS = $$(sdl2-config --libs) -mconsole

.PHONY: demo run 

demo: src/demo
src/demo: src/demo.c src/s-imgui.c
	$(CC) $(CFLAGS) $(LINKS) -o $@ $^

run: demo
	src/demo