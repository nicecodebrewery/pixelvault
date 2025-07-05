CC=g++
CFLAGS = 
EXEC=run
MAIN=src/main.cpp

main:$(MAIN)
	$(CC) $? $(CFLAGS) -o build/$(EXEC) 

run:
	build/$(EXEC)

clear:
	rm build/* 

install:
	cp build/$(EXEC) /usr/local/bin/pixelvault

uninstall:
	rm -f /usr/local/bin/pixelvault
