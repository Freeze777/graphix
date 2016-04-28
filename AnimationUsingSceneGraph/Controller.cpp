#include "Controller.h"
#include <iostream>

void Controller::mouse_callback(int button, int state, int x, int y) {


  
   if(state==GLUT_DOWN && button==GLUT_LEFT_BUTTON)
    {
        if(!cam_toggle){
        arcball_on = true;
        arcball->set_current_xy(x,y);
        arcball->set_last_xy(x,y);
        }
    }else {
        if(!cam_toggle)
        arcball_on = false;
    }
    glutPostRedisplay();


}
void  Controller::mouse_motion_callback(int x, int y) {

    if (arcball_on && !cam_toggle) {  // if left button is pressed
        arcball->set_current_xy(x,y);
    }
    glMatrixMode(GL_MODELVIEW);

    
    if(!cam_toggle)
    arcball->rotateCameravthMouse(2.0,eye_vector);
    
    glutPostRedisplay();
}

void  Controller::display_callback() {

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glm::vec4 eye;
    glm::mat4 transform;
    glm::vec3 eye_;

    
    glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION,spotDir2);
  
    switch(cam_toggle)
    {   
    
    case 0 :gluLookAt(eye_vector->x(),eye_vector->y(),eye_vector->z(),0,0,0,0,1,0);
            break;
    
    case 1 :eye=glm::vec4(2.5,2.5,2.5,1.0);
            transform=(model->root->getChildren()[5])->getGlobalTransform();
            eye=transform*eye;
            eye_=glm::vec3(eye);
            gluLookAt(eye_.x/4.0,eye_.y/0.95,eye_.z/4.0,0,0,0 ,0,1,0);
            break;
    case 2 :eye=glm::vec4(2.5,2.5,2.5,1.0);
            transform=model->root->getChildren()[2]->getGlobalTransform();
            eye=transform*eye;
            eye_=glm::vec3(eye);
            gluLookAt((eye_.x/5.4),eye_.y+2.4,(eye_.z/5.4),0,0.8,0,0,1,0);
            break;

    }

    eye=glm::vec4(2.5,2.5,2.5,1.0);
    transform=model->root->getChildren()[2]->getGlobalTransform();
    eye=transform*eye;
    eye_=glm::vec3(eye);

    eye_.x=eye_.x/5.8;
    eye_.y=eye_.y+2.5;
    eye_.z=eye_.z/5.8;

    lightPos3[0]=eye_vector->x();
    lightPos3[1]=eye_vector->y();
    lightPos3[2]=eye_vector->z();

    spotDir3[0]=eye_.x-lightPos3[0];
    spotDir3[1]=eye_.y-lightPos3[1];
    spotDir3[2]=eye_.z-lightPos3[2];

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    glLightfv(GL_LIGHT3,GL_POSITION,lightPos3);
    glLightfv(GL_LIGHT3,GL_SPOT_DIRECTION,spotDir3);
  
    model->draw();
    //model->drawAxis();
    glFlush();
   
   
}


void  Controller::reshape_callback(int w,int h)
{
    SCREEN_WIDTH=w;
    SCREEN_HEIGHT=h;

     glViewport(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65,SCREEN_WIDTH/SCREEN_HEIGHT,1,20);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION,spotDir2);
    gluLookAt(eye_vector->x(),eye_vector->y(),eye_vector->z(), 0,0,0 , 0,1,0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

    arcball->set_width_height(SCREEN_WIDTH,SCREEN_HEIGHT);
    view->set_width_height(SCREEN_WIDTH,SCREEN_HEIGHT);
   
    model->draw();


}

void  Controller::keyboard_special_callback(int key,int x,int y)
{
    float th=0,ph=0;

    if (key == GLUT_KEY_RIGHT) {th =0.2;ph=0.0;}
    else if (key == GLUT_KEY_LEFT) {th =-0.2;ph=0.0;}
    else if (key == GLUT_KEY_UP) {th=0.0;ph =0.2;}
    else if (key == GLUT_KEY_DOWN){ th=0.0 ;ph =-0.2;}
    else return;
    Vector trans(th,ph,0);
    *eye_vector=*eye_vector+trans;

    glutPostRedisplay();
}

void  Controller::keyboard_callback(unsigned char key,int x,int y)
{   cube_increm=0;
    f16_increm=0;
    if (key == 27) exit(0);
    else if (key == '-' && key>1) *eye_vector=*eye_vector*1.05;
    else if (key == '+' && key<179)*eye_vector=*eye_vector*0.95;
    else if (key == 'a'||key == 'A') toggle1=!toggle1;
    else if (key == 's'||key == 'S') toggle2=!toggle2;
    else if (key == 'd'||key == 'D') toggle3=!toggle3;
    else if (key == 'f'||key == 'F') toggle4=!toggle4;
    else if (key == 'c'||key == 'C')  cam_toggle=(++cam_toggle)%3;
    else if (key == 'q'||key == 'Q')  cube_increm=-5;
    else if (key == 'w'||key == 'W')  cube_increm=+5;
    else if (key == 'e'||key == 'E')  f16_increm=-5;
    else if (key == 'r'||key == 'R')  f16_increm=+5;
    else if (key == 'z'||key == 'Z')  detach_request=hooked;
    else return;
    (toggle1)?glDisable(GL_LIGHT0):glEnable(GL_LIGHT0);
    (toggle2)?glDisable(GL_LIGHT1):glEnable(GL_LIGHT1);
    (toggle3)?glDisable(GL_LIGHT2):glEnable(GL_LIGHT2);
    (toggle4)?glDisable(GL_LIGHT3):glEnable(GL_LIGHT3);
    glutPostRedisplay();

}


void Controller::idle_callback(void) {

    SceneNode * cube=model->root->getChildren()[2];
    cube->rotateLocalTransformMatrix(0.04,glm::vec3(0,1,0));
    SceneNode * f16=model->root->getChildren()[5];
  
    cube_counter++;
    f16_counter++;

    if(cube_counter==cube_speed)//marks the end of a period.. i.e cube is at one of the corners of the floor
    {    


            cube_counter=0;
            cube_period=(++cube_period)%4;
            //reset cube position at the corners of the floors
            cube->initTransformationMatrix();
            switch(cube_period){
                case 0:  
                cube->translateLocalTransformMatrix(glm::vec3(-4.0,-3.9,4.0));
                break;
                case 1:   
                cube->translateLocalTransformMatrix(glm::vec3(-4.0,-3.9,-4.0));
                break;
                case 2:   
                cube->translateLocalTransformMatrix(glm::vec3(4.0,-3.9,-4.0));
                break;
                case 3:  
                cube->translateLocalTransformMatrix(glm::vec3(4.0,-3.9,4.0));
                break;
            }

            //speed control code
            if((cube_speed+cube_increm) > 0)
            {
                cube_speed+=cube_increm;
            }

            cube_increm=0;


            //picking/dropping porsche on to the cube
            if(cube_period==detach_period && !detach_request){


                if(hooked){//then detach porsche
                   
                    SceneNode * porsche=cube->getChildren()[3];
                    porsche=cube->detachChild(porsche);
                    porsche->initTransformationMatrix();
                    glm::vec3 detach_location;
                    //finding the floor corner cordinates 
                    switch(detach_period){

                        case 0: detach_location=glm::vec3(-4.0,-4.5,4.0);break;
                        case 1: detach_location=glm::vec3(-4.0,-4.5,-4.0);break;
                        case 2: detach_location=glm::vec3(4.0,-4.5,-4.0);break;
                        case 3: detach_location=glm::vec3(4.0,-4.5,4.0);break;

                    }

                    porsche->translateLocalTransformMatrix(detach_location);
                    
                    model->root->attachChild(porsche);
                    
                }
                else{ //attach porsche to cube

                    SceneNode * porsche=model->root->getChildren()[3];
                    porsche=model->root->detachChild(porsche);
                    glm::vec3 attach_location;
                    //finding the attach cordinate on the cube
                    switch(detach_period){

                        case 0: attach_location=glm::vec3(4.0,6.0,-3.5);break;
                        case 1: attach_location=glm::vec3(4.0,6.0,4.5);break;
                        case 2: attach_location=glm::vec3(-4.0,6.0,4.5);break;
                        case 3: attach_location=glm::vec3(-4.0,6.0,-3.5);break;

                    }

                    porsche->translateLocalTransformMatrix(attach_location);

                    cube->attachChild(porsche);
                    
                }

                hooked=!hooked;
            

            }


            //detaching the porsche on request (iff its hooked) ..!
            //Drop the porsche on the next immediate corner (when the request was made) of the floor.. and we are olredy at that corner now..!!!
            if(detach_request)
            {   

                 SceneNode * porsche=cube->getChildren()[3];
                 porsche=cube->detachChild(porsche);
                 porsche->initTransformationMatrix();
                
                 switch(cube_period){
                    case 0:porsche->translateLocalTransformMatrix(glm::vec3(-4.0,-4.5,4.0));
                    break;
                    case 1:porsche->translateLocalTransformMatrix(glm::vec3(-4.0,-4.5,-4.0));
                    break;
                    case 2:porsche->translateLocalTransformMatrix(glm::vec3(4.0,-4.5,-4.0));
                    break;
                    case 3:porsche->translateLocalTransformMatrix(glm::vec3(4.0,-4.5,4.0));
                    break;

                 }
                    
                

                model->root->attachChild(porsche);
                hooked=!hooked;
                detach_period=cube_period;
                detach_request=false;
            }

            

        }





    //f16 period occured.. its at one corner of the floor... turn its 180 degrees
    if(f16_counter==f16_speed)
    {       f16_counter=0;
            f16_period=(++f16_period)%4;
            if((f16_speed+f16_increm) > 0)
            {
                f16_speed+=f16_increm;
            }

            f16_increm=0;
            switch(f16_period){
            case 0:f16->rotateLocalTransformMatrix(+135,glm::vec3(0,1,0));
            break;
            case 2:f16->rotateLocalTransformMatrix(-135,glm::vec3(0,1,0));
            break;
            }
            
    }





SceneNode *porsche=model->root->getChildren()[3];

          // moving porsche along half diagonal based on its dropped location   
          if(porsche){

                   switch(detach_period){

                        case 0:  
                            if(cube_period%2==0)
                                porsche->translateLocalTransformMatrix(glm::vec3(4.0/cube_speed,0,-4.0/cube_speed));
                            else
                                porsche->translateLocalTransformMatrix(glm::vec3(-4.0/cube_speed,0,4.0/cube_speed));
                        break;

                        case 1:   
                        
                          if(cube_period%2==0)
                                porsche->translateLocalTransformMatrix(glm::vec3(-4.0/cube_speed,0,-4.0/cube_speed));
                          else
                                porsche->translateLocalTransformMatrix(glm::vec3(4.0/cube_speed,0,4.0/cube_speed));
                        
                        break;

                        case 2:   
                          if(cube_period%2==0)
                                porsche->translateLocalTransformMatrix(glm::vec3(-4.0/cube_speed,0,4.0/cube_speed));
                          else
                                porsche->translateLocalTransformMatrix(glm::vec3(4.0/cube_speed,0,-4.0/cube_speed));
                        
                        break;

                        case 3:  
                          if(cube_period%2==0)
                                porsche->translateLocalTransformMatrix(glm::vec3(4.0/cube_speed,0,4.0/cube_speed));
                          else
                                porsche->translateLocalTransformMatrix(glm::vec3(-4.0/cube_speed,0,-4.0/cube_speed));
                                                  
                        break;




                   }
            }

 //forward motion of the cube -- sinusoidal motion
    switch(cube_period){
        case 0:  
        cube->translateLocalTransformMatrix(glm::vec3(0.3*sin(cube_counter*(32.0/cube_speed)),0,-8.0/cube_speed));
        break;
        case 1:   
        cube->translateLocalTransformMatrix(glm::vec3(+8.0/cube_speed,0,0.3*sin(cube_counter*(32.0/cube_speed))));
        break;
        case 2:   
        cube->translateLocalTransformMatrix(glm::vec3(0.3*sin(cube_counter*(32.0/cube_speed)),0,+8.0/cube_speed));
        break;
        case 3:  
        cube->translateLocalTransformMatrix(glm::vec3(-8.0/cube_speed,0,0.3*sin(cube_counter*(32.0/cube_speed))));
        break;
    }

//forward motion of f16-- along the diagonal
    switch(f16_period){
        case 0:f16->translateLocalTransformMatrix(glm::vec3(-4.0/f16_speed,0,-4.0/f16_speed));
        break;
        case 1:f16->translateLocalTransformMatrix(glm::vec3(-4.0/f16_speed,0,-4.0/f16_speed));
        break;
        case 2:f16->translateLocalTransformMatrix(glm::vec3(+4.0/f16_speed,0,+4.0/f16_speed));
        break;
        case 3:f16->translateLocalTransformMatrix(glm::vec3(+4.0/f16_speed,0,+4.0/f16_speed));
        break;
    }


  glutPostRedisplay();

}
