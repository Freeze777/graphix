CC=g++
CFLAGS=-c -w

all: mesh.out

mesh.out: main.o plyfile.o Vector.o PlyUtility.o PlyModel.o SceneNode.o Image.o Arcball.o Quaternion.o View.o Model.o Controller.o
	$(CC) -g main.o plyfile.o Vector.o PlyUtility.o PlyModel.o SceneNode.o Image.o Arcball.o Quaternion.o View.o Model.o Controller.o -o mesh.out -lGL -lGLU -lglut

main.o: main.cpp Vector.h PlyUtility.h PlyModel.h SceneNode.h Image.h Arcball.h Quaternion.h View.h Model.h Controller.h
	$(CC) $(CFLAGS) main.cpp

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

Controller.o: Controller.cpp Controller.h
	$(CC) $(CFLAGS)  Controller.cpp

clean:
	rm -rf *.o assgn
