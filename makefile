all: bin/n1 bin/n2 bin/n3 bin/n4 bin/n5 bin/n6 bin/n8 bin/n9 bin/n10 bin/n12 bin/n13 bin/n14 bin/n15 bin/n16 bin/n17_1 bin/n17_2_1 bin/n17_2_2 bin/n17_3 bin/n18_1_1 bin/n18_1_2 bin/n18_2_1 bin/n18_2_2 bin/n18_3_1 bin/n18_3_2 bin/n19_1_1 bin/n19_1_2 bin/n20_1_1 bin/n20_1_2 bin/n20_2_1 bin/n20_2_2 bin/n21_1_1 bin/n21_1_2 bin/n21_2_1 bin/n21_2_2 bin/n21_3_1 bin/n21_3_2 bin/n21_4_1 bin/n21_4_2 bin/n22_1_1 bin/n22_1_2 bin/n22_2_1 bin/n22_2_2 bin/n22_3_1 bin/n22_3_2 bin/n22_4_1 bin/n22_4_2 bin/n22_4_3 bin/n23 bin/n24 bin/n25 bin/n26 bin/n24_25_26 bin/n27_1_1 bin/n27_1_2 bin/n27_2_1 bin/n27_2_2

bin/n1: src/main/n1.c
	gcc src/main/n1.c -o bin/n1

bin/n2: src/main/n2.c
	gcc src/main/n2.c -o bin/n2

bin/n3: src/main/n3.c
	gcc src/main/n3.c -o bin/n3

bin/n4: src/main/n4.c
	gcc src/main/n4.c -o bin/n4

bin/n5: src/main/n5.c
	gcc src/main/n5.c -o bin/n5 -g

bin/n6: src/main/n6.c
	gcc src/main/n6.c -o bin/n6 -g

obj/libcalcfunc.a: src/lib/add.o src/lib/sub.o src/lib/mul.o src/lib/div.o
	ar rc obj/libcalcfunc.a src/lib/add.o src/lib/sub.o src/lib/mul.o src/lib/div.o
	
bin/n8: src/main/n8.c obj/libcalcfunc.a 
	gcc -o bin/n8 src/main/n8.c -L -l obj/libcalcfunc.a

obj/add.o: src/lib/add.c	
	gcc -c -fPIC -o $@ $<
	
obj/sub.o: src/lib/sub.c	
	gcc -c -fPIC -o $@ $<
	
obj/mul.o: src/lib/mul.c	
	gcc -c -fPIC -o $@ $<
	
obj/div.o: src/lib/div.c
	gcc -c -fPIC -o $@ $<

obj/libmyname.iso: obj/add.o obj/sub.o obj/mul.o obj/div.o
	gcc -shared obj/add.o obj/sub.o obj/mul.o obj/div.o -o obj/libmyname.iso
	
bin/n9: src/main/n9.c obj/libmyname.iso
	gcc -o bin/n9 src/main/n9.c -L -l obj/libmyname.iso
	
obj/add1.o: src/lib/add1.c
	gcc -c -fPIC -o $@ $<
	
obj/sub1.o: src/lib/sub1.c
	gcc -c -fPIC -o $@ $<
	
obj/mul1.o: src/lib/mul1.c
	gcc -c -fPIC -o $@ $<
	
obj/div1.o: src/lib/div1.c
	gcc -c -fPIC -o $@ $<
	
obj/libadd.so: obj/add1.o
	gcc -shared obj/add1.o -o obj/libadd.so

obj/libsub.so: obj/sub1.o
	gcc -shared obj/sub1.o -o obj/libsub.so

obj/libmul.so: obj/mul1.o
	gcc -shared obj/mul1.o -o obj/libmul.so

obj/libdiv.so: obj/div1.o
	gcc -shared obj/div1.o -o obj/libdiv.so
	
bin/n10: src/main/n10.c obj/libadd.so obj/libsub.so obj/libmul.so obj/libdiv.so
	gcc src/main/n10.c -o bin/n10 obj/libadd.so obj/libsub.so obj/libmul.so obj/libdiv.so -rdynamic -ldl -g

bin/n12: src/main/n12.c
	gcc src/main/n12.c -o bin/n12 -lncurses
	
bin/n13: src/main/n13.c
	gcc src/main/n13.c -o bin/n13 -lncurses
	
bin/n14: src/main/n14.c
	gcc src/main/n14.c -o bin/n14
	
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
	
bin/n19_1_1: src/main/n19_1_1.c
	gcc src/main/n19_1_1.c -o bin/n19_1_1

bin/n19_1_2: src/main/n19_1_2.c
	gcc src/main/n19_1_2.c -o bin/n19_1_2
	
bin/n20_1_1: src/main/n20_1_1.c
	gcc src/main/n20_1_1.c -o bin/n20_1_1 -lrt

bin/n20_1_2: src/main/n20_1_2.c
	gcc src/main/n20_1_2.c -o bin/n20_1_2 -lrt

bin/n20_2_1: src/main/n20_2_1.c
	gcc src/main/n20_2_1.c -o bin/n20_2_1 -lrt

bin/n20_2_2: src/main/n20_2_2.c
	gcc src/main/n20_2_2.c -o bin/n20_2_2 -lrt

bin/n21_1_1: src/main/n21_1_1.c
	gcc src/main/n21_1_1.c -o bin/n21_1_1

bin/n21_1_2: src/main/n21_1_2.c
	gcc src/main/n21_1_2.c -o bin/n21_1_2

bin/n21_2_1: src/main/n21_2_1.c
	gcc src/main/n21_2_1.c -o bin/n21_2_1

bin/n21_2_2: src/main/n21_2_2.c
	gcc src/main/n21_2_2.c -o bin/n21_2_2
	
bin/n21_3_1: src/main/n21_3_1.c
	gcc src/main/n21_3_1.c -o bin/n21_3_1

bin/n21_3_2: src/main/n21_3_2.c
	gcc src/main/n21_3_2.c -o bin/n21_3_2
	
bin/n21_4_1: src/main/n21_4_1.c
	gcc src/main/n21_4_1.c -o bin/n21_4_1

bin/n21_4_2: src/main/n21_4_2.c
	gcc src/main/n21_4_2.c -o bin/n21_4_2

bin/n22_1_1: src/main/n22_1_1.c
	gcc src/main/n22_1_1.c -o bin/n22_1_1 -lrt -lpthread
	
bin/n22_1_2: src/main/n22_1_2.c
	gcc src/main/n22_1_2.c -o bin/n22_1_2 -lrt -lpthread
	
bin/n22_2_1: src/main/n22_2_1.c
	gcc src/main/n22_2_1.c -o bin/n22_2_1 -lrt -lpthread
	
bin/n22_2_2: src/main/n22_2_2.c
	gcc src/main/n22_2_2.c -o bin/n22_2_2 -lrt -lpthread
	
bin/n22_3_1: src/main/n22_3_1.c
	gcc src/main/n22_3_1.c -o bin/n22_3_1 -lrt -lpthread
	
bin/n22_3_2: src/main/n22_3_2.c
	gcc src/main/n22_3_2.c -o bin/n22_3_2 -lrt -lpthread
	
bin/n22_4_1: src/main/n22_4_1.c
	gcc src/main/n22_4_1.c -o bin/n22_4_1 -lrt -lpthread
	
bin/n22_4_2: src/main/n22_4_2.c
	gcc src/main/n22_4_2.c -o bin/n22_4_2 -lrt -lpthread
	
bin/n22_4_3: src/main/n22_4_3.c
	gcc src/main/n22_4_3.c -o bin/n22_4_3 -lrt -lpthread
	
bin/n23: src/main/n23.c
	gcc src/main/n23.c -o bin/n23
	
bin/n24: src/main/n24.c
	gcc src/main/n24.c -o bin/n24
	
bin/n25: src/main/n25.c
	gcc src/main/n25.c -o bin/n25
	
bin/n26: src/main/n26.c
	gcc src/main/n26.c -o bin/n26
	
bin/n24_25_26: src/main/n24_25_26.c
	gcc src/main/n24_25_26.c -o bin/n24_25_26
	
bin/n27_1_1: src/main/n27_1_1.c
	gcc src/main/n27_1_1.c -o bin/n27_1_1
	
bin/n27_1_2: src/main/n27_1_2.c
	gcc src/main/n27_1_2.c -o bin/n27_1_2
	
bin/n27_2_1: src/main/n27_2_1.c
	gcc src/main/n27_2_1.c -o bin/n27_2_1
	
bin/n27_2_2: src/main/n27_2_2.c
	gcc src/main/n27_2_2.c -o bin/n27_2_2
