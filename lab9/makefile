messenger: messenger.c
	gcc -o messenger messenger.c `pkg-config --libs --cflags gtk+-2.0`
run: messenger.c
	./messenger
clean:
	rm -f messenger