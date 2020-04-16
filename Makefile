all: artificialLife

artificialLife: main.o world.o element.o
	g++ main.o world.o element.o -o artificialLife -lglut -lGLU -lGL -lpthread

main.o: main.cpp
	g++ -c main.cpp 

world.o: world.cpp
	g++ -c world.cpp

element.o: element.cpp
	g++ -c element.cpp

clean:
	rm -rf *.o artificialLife
