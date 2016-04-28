#include "Controller.h"
#include <iostream>

void Controller::mouse_callback(int button, int state, int x, int y) {


    if(state==GLUT_DOWN && button==GLUT_LEFT_BUTTON)
    {
        arcball_on = true;
        arcball->set_current_xy(x,y);
        arcball->set_last_xy(x,y);

    }else {
        arcball_on = false;
        if(state==GLUT_DOWN && button==GLUT_RIGHT_BUTTON){
        	unsigned int stencilIndex;
        	glReadPixels(x,SCREEN_HEIGHT-y,1,1,GL_STENCIL_INDEX,GL_UNSIGNED_INT, &stencilIndex);
        	int tmp=rand()%texture_files_size;

        	switch(stencilIndex)
        	{
        		case 1: 
        			model->plymodel1->freeTextBuffer();
        			model->plymodel1->readTexture2Buffer(texture_files[tmp],64,64);
        		break;

        		case 2:
        			model->plymodel2->freeTextBuffer();
        			model->plymodel2->readTexture2Buffer(texture_files[tmp],64,64);
        		break;

        	    case 3:
        	    	model->walls->readNewTexture(texture_files[tmp]);        		
        		break;
        	}

        	glutPostRedisplay();

        }

    }


}
void  Controller::mouse_motion_callback(int x, int y) {


    if (arcball_on) {  // if left button is pressed
        arcball->set_current_xy(x,y);
     }
     glMatrixMode(GL_MODELVIEW);

    //arcball->rotateModelvthMouse(dim);
    arcball->rotateCameravthMouse(dim,&eye_vector);
    glutPostRedisplay();


}

void  Controller::display_callback() {


    glClearStencil(0);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION,spotDir2);
    gluLookAt(eye_vector.x(),eye_vector.y(),eye_vector.z(), 0,-8,0 , 0,1,0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
     
    model->setScaleFactor(dim);
    model->drawScene(dim,dx,dy,dz,tex_toggle);

    glFlush();
   
}


void  Controller::reshape_callback(int w,int h)
{

    SCREEN_WIDTH=w;
    SCREEN_HEIGHT=h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov,SCREEN_WIDTH/SCREEN_HEIGHT,dim,25*dim);
    glViewport(0,0, SCREEN_WIDTH,SCREEN_HEIGHT);

    arcball->set_width_height(SCREEN_WIDTH,SCREEN_HEIGHT);
    view->set_width_height(SCREEN_WIDTH,SCREEN_HEIGHT);

    glClearStencil(0);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION,spotDir2);
    gluLookAt(eye_vector.x(),eye_vector.y(),eye_vector.z(), 0,-8,0 , 0,1,0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    
    model->setScaleFactor(dim);
    model->drawScene(dim,dx,0,dz,tex_toggle);


}

void  Controller::keyboard_special_callback(int key,int x,int y)
{

    if (key == GLUT_KEY_RIGHT) {th =0.2;ph=0.0;}
    else if (key == GLUT_KEY_LEFT) {th =-0.2;ph=0.0;}
    else if (key == GLUT_KEY_UP) {th=0.0;ph =0.2;}
    else if (key == GLUT_KEY_DOWN){ th=0.0 ;ph =-0.2;}
    else return;
    Vector trans(th,ph,0);
    eye_vector=eye_vector+trans;

    glutPostRedisplay();
}

void  Controller::keyboard_callback(unsigned char key,int x,int y)
{   	
	 if (key == 27) exit(0);
    else if (key == '-' && key>1) zoomfactor=1.1;
    else if (key == '+' && key<179) zoomfactor=0.9;
    else if (key == 'a'||key == 'A') toggle1=!toggle1;
    else if (key == 's'||key == 'S') toggle2=!toggle2;
    else if (key == 'd'||key == 'D') toggle3=!toggle3;
    else if (key == 'u'||key == 'U') dx+=0.2;
    else if (key == 'i'||key == 'I') dx-=0.2;
    else if (key == 'j'||key == 'J') dz+=0.2;
    else if (key == 'k'||key == 'K') dz-=0.2;
    else if (key == 't'||key == 'T') tex_toggle=!tex_toggle;
    else if (key == 'x'||key == 'X') global_tex_flag=!global_tex_flag;
    else return;
    (toggle1)?glDisable(GL_LIGHT0):glEnable(GL_LIGHT0);
    (toggle2)?glDisable(GL_LIGHT1):glEnable(GL_LIGHT1);
    (toggle3)?glDisable(GL_LIGHT2):glEnable(GL_LIGHT2);
    (global_tex_flag)?glEnable( GL_TEXTURE_2D ):glDisable( GL_TEXTURE_2D );
    eye_vector=eye_vector*zoomfactor;
    zoomfactor=1.0;
    glutPostRedisplay();

}


