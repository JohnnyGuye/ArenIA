test : testStats.o Gauge.o Stats.o
	g++ -o thisIsATest testStats.o Gauge.o Stats.o

testStats.o : testStats.cpp Gauge.cpp Gauge.h Stats.cpp Stats.h
	g++ -c testStats.cpp

Gauge.o : Gauge.cpp Gauge.h
	g++ -c Gauge.cpp

Stats.o : Stats.cpp Stats.h
	g++ -c Stats.cpp

clean :
	rm *.o thisIsATest	
