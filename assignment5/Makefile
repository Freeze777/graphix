CC=g++
#CFLAGS=-c -Wall
#CFLAGS=-c -w -std=c++11
CFLAGS=-c -w

all: test.out

test.out: main.o plyfile.o View.o PlyUtility.o PlyModel.o Walls.o Quaternion.o Vector.o Arcball.o Controller.o Model.o Image.o SceneNode.o
	$(CC) -g main.o plyfile.o View.o PlyUtility.o PlyModel.o Walls.o Quaternion.o Vector.o Arcball.o Controller.o Model.o Image.o SceneNode.o -o test.out -lGL -lGLU -lglut

main.o: main.cpp View.h PlyUtility.h  PlyModel.h  Quaternion.h  Walls.h  Vector.h  Arcball.h  Controller.h  Model.h  Image.h
	$(CC) $(CFLAGS) main.cpp

plyfile.o: plyfile.c
	gcc $(CFLAGS) plyfile.c

View.o: View.cpp 
	$(CC) $(CFLAGS) View.cpp

PlyUtility.o: PlyUtility.cpp 
	$(CC) $(CFLAGS) PlyUtility.cpp

PlyModel.o: PlyModel.cpp
	$(CC) $(CFLAGS) PlyModel.cpp 

Walls.o: Walls.cpp
	$(CC) $(CFLAGS) Walls.cpp

Quaternion.o: Quaternion.cpp
	$(CC) $(CFLAGS) Quaternion.cpp

Vector.o: Vector.cpp
	$(CC) $(CFLAGS) Vector.cpp

Arcball.o: Arcball.cpp
	$(CC) $(CFLAGS) Arcball.cpp

Controller.o: Controller.cpp
	$(CC) $(CFLAGS) Controller.cpp

Model.o: Model.cpp
	$(CC) $(CFLAGS) Model.cpp

Image.o: Image.cpp
	$(CC) $(CFLAGS) Image.cpp

SceneNode.o:SceneNode.cpp
	$(CC) $(CFLAGS) SceneNode.cpp
	
clean:
	rm -rf *.o assgn
