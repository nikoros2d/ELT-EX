all: bin/n1 bin/n2 bin/n3 bin/n4 bin/n6 bin/n8 bin/n12

bin/n1: src/main/n1.c
	gcc src/main/n1.c -o bin/n1

bin/n2: src/main/n2.c
	gcc src/main/n2.c -o bin/n2

bin/n3: src/main/n3.c
	gcc src/main/n3.c -o bin/n3

bin/n4: src/main/n4.c
	gcc src/main/n4.c -o bin/n4

bin/n6: src/main/n6.c
	gcc src/main/n6.c -o bin/n6

obj/libcalcfunc.a: src/lib/add.o src/lib/sub.o src/lib/mul.o src/lib/div.o
	ar rc obj/libcalcfunc.a src/lib/add.o src/lib/sub.o src/lib/mul.o src/lib/div.o

bin/n8: src/main/n8.c obj/libcalcfunc.a 
	gcc -o bin/n8 src/main/n8.c -L -l obj/libcalcfunc.a

bin/n12: src/main/n12.c
	gcc src/main/n12.c -o bin/n12

