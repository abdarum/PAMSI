#
#  To sa opcje dla kompilacji
#
CPPTYPE=g++
WNOFLAGS=-Wno-write-strings -Wno-unused-variable
CPPFLAGS= -c -g -Iinc -Wall ${WNOFLAGS} -pedantic -std=c++11

__start__: sprawdzenie_testu
#	./sprawdzenie_testu
	cat test.dat	
	./sprawdzenie_testu < test.dat 

sprawdzenie_testu: obj/main.o obj/WyrazenieAlgeb.o obj/Statystyka.o
	${CPPTYPE} -Wall -pedantic -o sprawdzenie_testu obj/main.o\
                                  obj/WyrazenieAlgeb.o obj/Statystyka.o 

obj/main.o: src/main.cpp inc/WyrazenieAlgeb.hh inc/Statystyka.hh inc/Symbol.hh
	${CPPTYPE} ${CPPFLAGS} -o obj/main.o src/main.cpp

obj/WyrazenieAlgeb.o: src/WyrazenieAlgeb.cpp inc/WyrazenieAlgeb.hh inc/Symbol.hh
	${CPPTYPE} ${CPPFLAGS} -o obj/WyrazenieAlgeb.o src/WyrazenieAlgeb.cpp

obj/Statystyka.o: src/Statystyka.cpp inc/Statystyka.hh
	${CPPTYPE} ${CPPFLAGS} -o obj/Statystyka.o src/Statystyka.cpp


clean:
	rm -f obj/*.o sprawdzenie_testu



#sprawdzenie_testu: obj/main.o obj/WyrazenieAlgeb.o obj/Statystyka.o
#	${CPPTYPE} -Wall -pedantic -o sprawdzenie_testu obj/main.o\
                                  obj/WyrazenieAlgeb.o obj/Statystyka.o
