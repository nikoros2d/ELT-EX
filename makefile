all: bin/n1 bin/n2 bin/n3 bin/n4 bin/n6 bin/n8 bin/n12 bin/n13 bin/n15 bin/n16 bin/n17_1 bin/n17_2_1 bin/n17_2_2 bin/n17_3 bin/n18_1_1 bin/n18_1_2 bin/n18_2_1 bin/n18_2_2 bin/n18_3_1 bin/n18_3_2

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
	gcc src/main/n12.c -o bin/n12 -lncurses
	
bin/n13: src/main/n13.c
	gcc src/main/n13.c -o bin/n13 -lncurses	
	
bin/n15: src/main/n15.c
	gcc src/main/n15.c -o bin/n15 -lpthread

bin/n16: src/main/n16.c
	gcc src/main/n16.c -o bin/n16 -lpthread
	
bin/n17_1: src/main/n17_1.c
	gcc src/main/n17_1.c -o bin/n17_1

bin/n17_2_1: src/main/n17_2_1.c
	gcc src/main/n17_2_1.c -o bin/n17_2_1
	
bin/n17_2_2: src/main/n17_2_2.c
	gcc src/main/n17_2_2.c -o bin/n17_2_2
	
bin/n17_3: src/main/n17_3.c
	gcc src/main/n17_3.c -o bin/n17_3

bin/n18_1_1: src/main/n18_1_1.c
	gcc src/main/n18_1_1.c -o bin/n18_1_1

bin/n18_1_2: src/main/n18_1_2.c
	gcc src/main/n18_1_2.c -o bin/n18_1_2
	
bin/n18_2_1: src/main/n18_2_1.c
	gcc src/main/n18_2_1.c -o bin/n18_2_1 -lrt

bin/n18_2_2: src/main/n18_2_2.c
	gcc src/main/n18_2_2.c -o bin/n18_2_2 -lrt
	
bin/n18_3_1: src/main/n18_3_1.c
	gcc src/main/n18_3_1.c -o bin/n18_3_1 -lrt -lpthread

bin/n18_3_2: src/main/n18_3_2.c
	gcc src/main/n18_3_2.c -o bin/n18_3_2 -lrt -lpthread
