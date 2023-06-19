all : main.o fsm.o event_connect.o event_supply.o
	g++ -std=c++11 -o main -I ./ main.o fsm.o event_connect.o event_supply.o

main.o : main.cpp
	g++ -std=c++11 -c -I ./ main.cpp
fsm.o : fsm.cpp 
	g++ -std=c++11 -c fsm.cpp
event_connect.o : event_connect.cpp 
	g++ -std=c++11 -c -I ./ event_connect.cpp
event_supply.o : event_supply.cpp 
	g++ -std=c++11 -c -I ./ event_supply.cpp

clean : 
	rm -f *.o main 

