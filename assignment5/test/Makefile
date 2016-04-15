CC=g++
#CFLAGS=-c -Wall
#CFLAGS=-c -w -std=c++11
CFLAGS=-c -w

all: mesh.out

mesh.out: test.o plyfile.o Vector.o PlyUtility.o PlyModel.o SceneNode.o
	$(CC) -g test.o plyfile.o Vector.o PlyUtility.o PlyModel.o SceneNode.o -o mesh.out -lGL -lGLU -lglut

test.o: test.cpp 
	$(CC) $(CFLAGS) test.cpp

plyfile.o: plyfile.c
	gcc $(CFLAGS) plyfile.c

Vector.o: Vector.cpp
	$(CC) $(CFLAGS) Vector.cpp

PlyUtility.o: PlyUtility.cpp 
	$(CC) $(CFLAGS) PlyUtility.cpp

PlyModel.o: PlyModel.cpp
	$(CC) $(CFLAGS) PlyModel.cpp 

SceneNode.o:SceneNode.cpp
	$(CC) $(CFLAGS) SceneNode.cpp
	
clean:
	rm -rf *.o assgn
