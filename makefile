graf: main.o prepareGraph.o dijkstra.o
	g++ -std=c++14 -o graf main.o prepareGraph.o dijkstra.o

main.o: main.cpp
	g++ -c -std=c++14 main.cpp -o main.o

dijkstra.o: dijkstra.cpp dijkstra.h
	g++ -c -std=c++14 dijkstra.cpp -o dijkstra.o

prepareGraph.o: prepareGraph.cpp prepareGraph.h const.h
	g++ -c -std=c++14 prepareGraph.cpp

clean:
	rm *.o
