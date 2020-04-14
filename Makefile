all: artificialLife

artificialLife: main.o world.o elements.o bot.o
	g++ main.o world.o elements.o bot.o -o artificialLife -lglut -lGLU -lGL

main.o: main.cpp
	g++ -c main.cpp 

world.o: world.cpp
	g++ -c world.cpp

elements.o: elements.cpp
	g++ -c elements.cpp

bot.o: bot.cpp
	g++ -c bot.cpp

clean:
	rm -rf *.o artificialLife
