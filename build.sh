mkdir bin
echo building Application
g++ -c -I. -std=c++11 -fpermissive Application.cpp -o bin/Application.o
echo building Cannel
g++ -c -I. -std=c++11 -fpermissive Channel.cpp -o bin/Channel.o
echo building double
g++ -c -I. -std=c++11 -fpermissive Double.cpp -o bin/Double.o
echo building Graph
g++ -c -I. -std=c++11 -fpermissive Graph.cpp -o bin/Graph.o
echo building Point
g++ -c -I. -std=c++11 -fpermissive Point.cpp -o bin/Point.o
echo building StdGraphController
g++ -c -I. -std=c++11 -fpermissive StdGraphController.cpp -o bin/StdGraphController.o
echo building Widget
g++ -c -I. -std=c++11 -fpermissive Widget.cpp -o bin/Widget.o
echo building Window
g++ -c -I. -std=c++11 -fpermissive Window.cpp -o bin/Window.o
echo building Zyklotron
g++ -c -I. -std=c++11 -fpermissive Zyklotron.cpp -o bin/Zyklotron.o
echo building ZyklotronController
g++ -c -I. -std=c++11 -fpermissive ZyklotronController.cpp -o bin/ZyklotronController.o
echo building linking
g++ -I. -std=c++11 -fpermissive main.cpp bin/*.o -o main -lboost_system -lboost_thread -lsfml-system -lsfml-window -lsfml-graphics
