output: main.o Config.o DataManagement.o Region.o Cell.o Simulation.o Analyze.o
	g++ main.o Config.o DataManagement.o Region.o Cell.o Simulation.o Analyze.o -o SimCity

main.o: main.cpp
	g++ -c main.cpp

Config.o: Config.cpp Config.h
	g++ -c Config.cpp

DataManagement.o: DataManagement.cpp DataManagement.h
	g++ -c DataManagement.cpp

Region.o: Region.cpp Region.h
	g++ -c Region.cpp

Cell.o: Cell.cpp Cell.h
	g++ -c Cell.cpp

Simulation.o: Simulation.cpp Simulation.h
	g++ -c Simulation.cpp

Analyze.o: Analyze.cpp Analyze.h
	g++ -c Analyze.cpp

clean:
	rm *.o SimCity