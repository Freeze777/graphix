#include "Controller.h"
#include "Model.h"
#include <string.h>
using namespace std;


void myReshape(int w, int h);
void myKeyBoard(unsigned char key,int x, int y);
void myMouse(int button, int state, int x, int y);
void myDisplay(void);
void specialKeys(int key,int x,int y);
void myMouseMotion(int x, int y) ;

Controller *controller;
Model *model;
View *view;
float SCREEN_WIDTH=1000;
float SCREEN_HEIGHT=650;

GLuint texture[2];

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

    SCREEN_WIDTH=w;
    SCREEN_HEIGHT=h;
    controller->reshape_callback(w,h);
}

void specialKeys(int key,int x,int y)
{

    controller->keyboard_special_callback(key,x,y);

}

void myKeyBoard(unsigned char key,int x,int y)
{
    controller->keyboard_callback(key,x,y);

}


int main(int argc, char *argv[]) {
    
   
    if(argc!=6)
    {
        printf("Insufficient arguments..!!\n");
        exit(0);
    }
    model=new Model(argv[5]);
    model->readModelsFromFile(argv[1],argv[2]);

    if(strcmp("NA",argv[3])!=0)
    model->plymodel1->readTexture2Buffer(argv[3],64,64);

    if(strcmp("NA",argv[4])!=0)
    model->plymodel2->readTexture2Buffer(argv[4],64,64);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    view=new View(SCREEN_WIDTH,SCREEN_HEIGHT);

    controller=new Controller(view,model);

    controller->SCREEN_HEIGHT=SCREEN_HEIGHT;
    controller->SCREEN_WIDTH=SCREEN_WIDTH;


    glutInit(&argc, argv);
    view->createWindow("3D Rendering");


    //register callbacks
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myReshape);

    glutKeyboardFunc(myKeyBoard);
    glutSpecialFunc(specialKeys);

    glutMouseFunc(myMouse);
    glutMotionFunc(myMouseMotion);


    view->initialize(controller->dim,controller->fov);
    glutMainLoop();

    return 0;
}






