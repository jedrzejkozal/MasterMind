CC = g++
CFLAGS  = -g -Wall

alg_gen: main.o populacja.o osobnik.o kolor.o
	$(CC) $(CFLAGS) -o alg_gen main.o populacja.o osobnik.o kolor.o

main.o: main.cpp populacja.h
	$(CC) $(CFLAGS) -c main.cpp 

populacja.o: populacja.cpp populacja.h zmienne_globalne.h
	$(CC) $(CFLAGS) -c populacja.cpp 

osobnik.o: osobnik.cpp osobnik.h zmienne_globalne.h
	$(CC) $(CFLAGS) -c osobnik.cpp

kolor.o: kolor.cpp kolor.h
	$(CC) $(CFLAGS) -c kolor.cpp

clean:
	rm alg_gen *.o
