mkdir bin
g++ -c -I. -std=c++11 -fpermissive Application.cpp -o bin/Application.o
g++ -c -I. -std=c++11 -fpermissive Channel.cpp -o bin/Channel.o
g++ -c -I. -std=c++11 -fpermissive Double.cpp -o bin/Double.o
g++ -c -I. -std=c++11 -fpermissive Graph.cpp -o bin/Graph.o
g++ -c -I. -std=c++11 -fpermissive Point.cpp -o bin/Point.o
g++ -c -I. -std=c++11 -fpermissive StdGraphController.cpp -o bin/StdGraphController.o
g++ -c -I. -std=c++11 -fpermissive Widget.cpp -o bin/Widget.o
g++ -c -I. -std=c++11 -fpermissive Window.cpp -o bin/Window.o
g++ -c -I. -std=c++11 -fpermissive Zyklotron.cpp -o bin/Zyklotron.o
g++ -c -I. -std=c++11 -fpermissive ZyklotronController.cpp -o bin/ZyklotronController.o
g++ -I. -std=c++11 -fpermissive main.cpp bin/*.o -o main -lboost_system -lboost_thread -lsfml-system -lsfml-window -lsfml-graphics
