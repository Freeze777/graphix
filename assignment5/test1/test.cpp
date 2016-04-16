#include "PlyModel.h"
#include "Arcball.h"
#include "SceneNode.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;
void myReshape(int w, int h);
void myKeyBoard(unsigned char key,int x, int y);
void myMouse(int button, int state, int x, int y);
void myDisplay(void);
void specialKeys(int key,int x,int y);
void myMouseMotion(int x, int y) ;

float SCREEN_WIDTH=650;
float SCREEN_HEIGHT=650;

SceneNode * root;

Arcball arcball(SCREEN_WIDTH,SCREEN_HEIGHT,1.5);
int arcball_on=false;
Vector eye_vector(0,0,10.0);

#define speed 40
int indx=0,fwd=1,cnt=0,period=0,hooked=0;

void myIdle(void) {
  
	srand(time(NULL));
	float x = ((rand()%1000+1)-500.0)/20000.0;
	float y = ((rand()%1000+1)-500.0)/20000.0;
	float z = ((rand()%1000+1)-500.0)/20000.0;
	float phi = ((rand()%1000+1)-500.0)/5000.0;



    root->rotateLocalTransformMatrix(0.01,glm::vec3(0,1,0));
    SceneNode * cube=root->getChildren()[2];
	cube->rotateLocalTransformMatrix(0.01,glm::vec3(0,1,0));
	SceneNode * f16=root->getChildren()[5];
	f16->translateLocalTransformMatrix(glm::vec3(x,y,z));
	//f16->rotateLocalTransformMatrix(0.08,glm::vec3(1,0,0));
	f16->rotateLocalTransformMatrix(phi,glm::vec3(1,0,0));
	cnt++;
	if(cnt==speed)
		{	cnt=0;
			period=(++period)%4;
			switch(period){
			case 0://f16->rotateLocalTransformMatrix(+135,glm::vec3(0,1,0));
					//f16->rotateLocalTransformMatrix(phi,glm::vec3(0,1,-1));
			break;
			case 1:
			break;
			case 2://f16->rotateLocalTransformMatrix(-135,glm::vec3(0,1,0));
				//f16->rotateLocalTransformMatrix(phi,glm::vec3(0,-1,1));
			break;
			case 3:
			  if(hooked){
					SceneNode * porsche=cube->getChildren()[3];
					porsche=cube->detachChild(porsche);
					porsche->initTransformationMatrix();
					porsche->translateLocalTransformMatrix(glm::vec3(4.0,-4.5,-4.0));
					root->attachChild(porsche);
					hooked=0;
				}
				else{
					SceneNode * porsche=root->getChildren()[3];
					porsche=root->detachChild(porsche);
					porsche->translateLocalTransformMatrix(glm::vec3(-4.0,6.0,4.5));
					cube->attachChild(porsche);
					hooked=1;
				}
			break;

			}
			
		}
	
	switch(period){
		case 0:cube->translateLocalTransformMatrix(glm::vec3(-8.0/speed,0,0));
			   //f16->translateLocalTransformMatrix(glm::vec3(-4.0/speed,0,-4.0/speed));
		break;
		case 1:cube->translateLocalTransformMatrix(glm::vec3(0,0,-8.0/speed));
			 //f16->translateLocalTransformMatrix(glm::vec3(-4.0/speed,0,-4.0/speed));
		break;
		break;
		case 2:cube->translateLocalTransformMatrix(glm::vec3(+8.0/speed,0,0));
			 //f16->translateLocalTransformMatrix(glm::vec3(4.0/speed,0,4.0/speed));
		break;
		case 3:cube->translateLocalTransformMatrix(glm::vec3(0,0,+8.0/speed));
    		//f16->translateLocalTransformMatrix(glm::vec3(4.0/speed,0,4.0/speed));
		break;
    }
  glutPostRedisplay();
}


void myKeyBoard(unsigned char key,int x,int y)
{
 if (key == 27) exit(0);
 /*else if(key== 'a'||key=='A') 
 	{
 		if(root->getChildren()[3]){
 		SceneNode * porsche=root->detachChild(root->getChildren()[3]);
 		//porsche->rotateLocalTransformMatrix(-45,glm::vec3(0,1,0));
 		porsche->translateLocalTransformMatrix(glm::vec3(-4.0,6.0,4.5));
 		SceneNode * cube=root->getChildren()[2];
 		cube->attachChild(porsche);

 		root->printChildren();
 		cube->printChildren();
 		porsche->printChildren();
 		}
	}
else if(key== 'b'||key=='B')
	{	
		SceneNode * cube=root->getChildren()[2];

		//cube->translateLocalTransformMatrix(glm::vec3(-8,0,0));
		for (int i = 0; i < 10000; ++i)
		{	  
			cube->translateLocalTransformMatrix(glm::vec3(-0.0008,0,-0.0008));
		}
	} */
}

int main(int argc, char *argv[]) {
        
    PlyUtility util;
    PlyModel * floor;
    util.readPlyFile("plyfiles/floor.ply");
    floor=new PlyModel(&util,0);
    floor->computeNormal();
    floor->computeCentroid();
    floor->readTexture2Buffer("textures/floor.bmp");
    root=new SceneNode(floor,"floor",1);
    root->initTransformationMatrix();

    PlyUtility util1;
    PlyModel *cube;
    util1.readPlyFile("plyfiles/cube.ply");
    cube=new PlyModel(&util1,2);
    cube->computeNormal();
    cube->computeCentroid();
    cube->readTexture2Buffer("textures/checker.bmp");
    SceneNode * child1=new SceneNode(cube,"cube",2);
    child1->initTransformationMatrix();
    child1->translateLocalTransformMatrix(glm::vec3(4.0,-4.0,4.0));
    root->attachChild(child1);

    PlyUtility util2;
    PlyModel *porsche;
    util2.readPlyFile("plyfiles/porsche.ply");
    porsche=new PlyModel(&util2,1);
    porsche->computeNormal();
    porsche->computeCentroid();
    porsche->readTexture2Buffer("textures/wood_.bmp");
    SceneNode * child2=new SceneNode(porsche,"porsche",3);
    child2->initTransformationMatrix();
    child2->translateLocalTransformMatrix(glm::vec3(4.0,-4.5,-4.0));
    root->attachChild(child2);

    PlyUtility util3;
    PlyModel *car;
    util3.readPlyFile("plyfiles/car.ply");
    car=new PlyModel(&util3,1);
    car->computeNormal();
    car->computeCentroid();
    car->readTexture2Buffer("textures/metal_.bmp");
    SceneNode * child3=new SceneNode(car,"car",4);
    child3->initTransformationMatrix();
    child3->translateLocalTransformMatrix(glm::vec3(-0.1,1.5,-0.5));
    child1->attachChild(child3);

	PlyUtility util4;
    PlyModel *f16;
    util4.readPlyFile("plyfiles/f16.ply");
    f16=new PlyModel(&util4,2);
    f16->computeNormal();
    f16->computeCentroid();
    f16->readTexture2Buffer("textures/apple.bmp");
    SceneNode * child4=new SceneNode(f16,"f16",5);
    child4->initTransformationMatrix();
  //  child4->translateLocalTransformMatrix(glm::vec3(4.0,1.5,4.0));
   // child4->rotateLocalTransformMatrix(-45,glm::vec3(0,1,0));
    root->attachChild(child4);

    root->printChildren();
 
    glutInit(&argc, argv);


    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Testing phase");
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glColor3f(0.0,1.0,1.0);
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
    //register callbacks
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myReshape);

    glutKeyboardFunc(myKeyBoard);
    glutSpecialFunc(specialKeys);

    glutMouseFunc(myMouse);
    glutMotionFunc(myMouseMotion);
   
    glutIdleFunc(myIdle);
   
    glViewport(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,SCREEN_WIDTH/SCREEN_HEIGHT,2,10);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5,5,5, 0,0,0 , 0,1,0);
    
    glClearColor(0.0,0.0,0.0,0.0);
    glEnable(GL_DEPTH_TEST);
    
    glutMainLoop();

    return 0;
}


void myMouse(int button, int state, int x, int y) {

  
}
void myMouseMotion(int x, int y) {

    if (arcball_on) {  // if left button is pressed
        arcball.set_current_xy(x,y);
     }
     glMatrixMode(GL_MODELVIEW);

    //arcball->rotateModelvthMouse(dim);
    arcball.rotateCameravthMouse(2,&eye_vector);
    glutPostRedisplay();
  

}

void myDisplay() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2.5,2.5,2.5, 0,0,0 , 0,1,0);
    
    glMatrixMode(GL_MODELVIEW);
    root->draw();
    glFlush();
}

void myReshape(int w,int h)
{

    SCREEN_WIDTH=w;
    SCREEN_HEIGHT=h;

     glViewport(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,SCREEN_WIDTH/SCREEN_HEIGHT,2,10);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5,5,5, 0,0,0 , 0,1,0);
}

void specialKeys(int key,int x,int y)
{


}




