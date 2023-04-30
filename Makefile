all: cmp copy encode decode stshell

copy: copy.o
	gcc -Wall -g -o $@ $^


cmp: cmp.o
	gcc -Wall -g -o $@ $^

decode: decode.o libcodecA.so libcodecB.so
	gcc -Wall -g -ldl -o $@ decode.o

encode: encode.o libcodecA.so libcodecB.so
	gcc -Wall -g -ldl -o $@ encode.o

stshell: stshell.o
	gcc -Wall -g -o $@ $^

libcodecA.so: codecA.o
	gcc -Wall -g -shared -o $@ $^

libcodecB.so: codecB.o
	gcc -Wall -g -shared -o $@ $^

codecA.o: codecA.c codec.h
	gcc -Wall -g -fPIC -c $^

codecB.o: codecB.c codec.h
	gcc -Wall -g -fPIC -c $^


stshell.o: stshell.c 
	gcc -Wall -g -c $^

.PHONY: all clean

clean:
	rm -f  *.o *.a *.so *.dll *.h.gch *.dylib cmp copy encode decode stshell