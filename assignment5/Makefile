CC=g++
#CFLAGS=-c -Wall
#CFLAGS=-c -w -std=c++11
CFLAGS=-c -w

all: mesh.out

mesh.out: test.o plyfile.o Vector.o PlyUtility.o PlyModel.o SceneNode.o Image.o Arcball.o Quaternion.o View.o Model.o Controller.o
	$(CC) -g test.o plyfile.o Vector.o PlyUtility.o PlyModel.o SceneNode.o Image.o Arcball.o Quaternion.o View.o Model.o Controller.o -o mesh.out -lGL -lGLU -lglut

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

Image.o:Image.cpp
	$(CC) $(CFLAGS) Image.cpp

Arcball.o:Arcball.cpp
	$(CC) $(CFLAGS) Arcball.cpp

Quaternion.o: Quaternion.cpp
	$(CC) $(CFLAGS)  Quaternion.cpp	

View.o: View.cpp
	$(CC) $(CFLAGS)  View.cpp

Model.o: Model.cpp
	$(CC) $(CFLAGS)  Model.cpp

Controller.o: Controller.cpp
	$(CC) $(CFLAGS)  Controller.cpp

clean:
	rm -rf *.o assgn
