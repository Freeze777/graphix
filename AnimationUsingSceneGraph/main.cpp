#include "PlyModel.h"
#include "Arcball.h"
#include "SceneNode.h"
#include "View.h"
#include "Model.h"
#include "Controller.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
void myReshape(int w, int h);
void myKeyBoard(unsigned char key,int x, int y);
void myMouse(int button, int state, int x, int y);
void myDisplay(void);
void specialKeys(int key,int x,int y);
void myMouseMotion(int x, int y) ;
void myIdle(void);


float SCREEN_WIDTH=1366;
float SCREEN_HEIGHT=768;

View * view;
Model* model;
Controller *controller;

int main(int argc, char *argv[]) {
        
	Model * model=new Model();
    model->createSceneGraph();
   
    view=new View(SCREEN_WIDTH,SCREEN_HEIGHT);


    glutInit(&argc, argv);
    
    view->createWindow("SceneGraph");

    view->initialize();

    controller=new Controller(view,model);

    //register callbacks
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myReshape);
    glutKeyboardFunc(myKeyBoard);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(myMouse);
    glutMotionFunc(myMouseMotion);
    glutIdleFunc(myIdle);

    glutMainLoop();

    return 0;
}

void myKeyBoard(unsigned char key,int x,int y)
{

	controller->keyboard_callback(key,x,y);

}

void myIdle(void) {
  
   controller->idle_callback();
}
void myMouse(int button, int state, int x, int y) {

	controller->mouse_callback(button,state,x,y);
  
}
void myMouseMotion(int x, int y) {

   controller->mouse_motion_callback(x,y);

}

void myDisplay() {

	controller->display_callback();
}

void myReshape(int w,int h)
{
	controller->reshape_callback(w,h);
}

void specialKeys(int key,int x,int y)
{
 
 	controller->keyboard_special_callback(key,x,y);

}




