cc=gcc
source=bcplink.c
cflags=-O3 -s

bcplink.exe:$(source)
	$(cc) $? -o $@ $(cflags)

clean:
	rm $(source)