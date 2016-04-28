#ifndef controller_h
#define controller_h
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <iostream>
#include <math.h>
#include <string.h>
#include "PlyUtility.h"
#include "View.h"
#include "PlyModel.h"
#include "Quaternion.h"
#include "Vector.h"
#include "Arcball.h"
#include "Model.h"

#define texture_files_size 15


class Controller
{   float SCREEN_WIDTH=1366,SCREEN_HEIGHT=768;
    Arcball *arcball;
    View *view;
    Model *model;
   
public:
    int cube_speed =100;
    int f16_speed= 120;
    int cube_increm=0,f16_increm=0;
    Vector *eye_vector;
    int cube_counter=0,f16_counter=0,cube_period=0,f16_period=0,detach_period=0,cam_toggle=0;
    bool hooked=false,detach_request=false,arcball_on=false,toggle1=false,toggle2=false,toggle3=false,toggle4=false;
    GLfloat spotDir2[3]={0.0f,0.0f,-1.0f};
    GLfloat lightPos0[4]= {0.0,4.0,0.0, 1.0f};
    GLfloat lightPos1[4] = {1.0,1.0,1.0, 0.0f};
    GLfloat lightPos3[4] = {2.5,2.5,2.5, 1.0f};
    GLfloat spotDir3[3]={-2.5f,-7.5f,2.5f};

   
Controller(View *v,Model *m) {

        view=v;
        model=m;
        arcball=new Arcball(1366,768,1.5);
        eye_vector=new Vector(2.5,2.5,2.5);
   }

    ~Controller(){

        delete view;
        delete model;
        delete arcball;
        delete eye_vector;
    }
    void reshape_callback(int w, int h);
    void keyboard_callback(unsigned char key,int x, int y);
    void mouse_callback(int button, int state, int x, int y);
    void display_callback(void);
    void keyboard_special_callback(int key,int x,int y);
    void mouse_motion_callback(int x, int y) ;
    void idle_callback(void) ;
    


};


#endif
