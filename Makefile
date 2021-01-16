# @describe: Compiles the code
# @author: Zeynep Cankara
target: all
all: A B

A: partA.c
	gcc -Wall -o A partA.c

B: partB.c
	gcc -Wall -o B partB.c

clean:
	rm -f *o A B fm
