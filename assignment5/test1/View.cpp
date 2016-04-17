#include "View.h"


View::View(float width, float height){
    this->screenHeight=height;
    this->screenWidth=width;


}
void View::set_width_height(float width,float height)
{

    this->screenWidth=width;
    this->screenHeight=height;


}
void  View::createWindow(char *windowName){
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(screenWidth,screenHeight);
    glutInitWindowPosition(0,0);
    glutCreateWindow(windowName);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glColor3f(0.0,1.0,1.0);

}
void  View::initialize(){
    glViewport(0,0,screenWidth,screenHeight);

   glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70,screenWidth/screenHeight,1,20);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2.5,2.5,2.5, 0,0,0 , 0,1,0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); 
    glEnable(GL_LIGHT1); 
    glEnable(GL_LIGHT2);
    glEnable(GL_NORMALIZE);
    glEnable( GL_TEXTURE_2D );
 


    GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.2, 0.2, 0.2)
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
    
    //point source    
    GLfloat diffuseLightColor0[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat specularLightColor0[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLightColor0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLightColor0);

    //Add directed light
    GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.2, 0.2)
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);


    // Light values and coordinates
    GLfloat  lightPos2[] = {0.0f,0.0f, 10, 1.0f };
    GLfloat  specular2[] = { 1.0f, 0.0f, 0.0f, 1.0f};
    GLfloat  ambientLight2[] = { 1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat spotDir2[3]={0.0f,0.0f,-1.0f};
    glLightfv(GL_LIGHT2,GL_DIFFUSE,ambientLight2);
    glLightfv(GL_LIGHT2,GL_SPECULAR,specular2);
    glLightfv(GL_LIGHT2,GL_POSITION,lightPos2);
    glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION,spotDir2);

     // Specific spot effects
    // Cut off angle is 60 degrees
    glLightf(GL_LIGHT2,GL_SPOT_CUTOFF,30.0f);
    // Fairly shiny spot
    glLightf(GL_LIGHT2,GL_SPOT_EXPONENT,10.0f);
    glShadeModel(GL_SMOOTH);
 

}
