#include "PlyModel.h"
#include "SceneNode.h"
using namespace std;


void myReshape(int w, int h);
void myKeyBoard(unsigned char key,int x, int y);
void myMouse(int button, int state, int x, int y);
void myDisplay(void);
void specialKeys(int key,int x,int y);
void myMouseMotion(int x, int y) ;

SceneNode * root;

float SCREEN_WIDTH=1000;
float SCREEN_HEIGHT=650;

void myIdle(void) {
  
    root->rotateLocalTransformMatrix(0.01,glm::vec3(0,1,0));
    root->getChildren()[0]->rotateLocalTransformMatrix(0.05,glm::vec3(1,0,1));
     root->getChildren()[1]->rotateLocalTransformMatrix(0.05,glm::vec3(1,0,1));
  glutPostRedisplay();
}
void myMouse(int button, int state, int x, int y) {

  
}
void myMouseMotion(int x, int y) {

  

}

void myDisplay() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5,5,5, 0,0,0 , 0,1,0);
    
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

void myKeyBoard(unsigned char key,int x,int y)
{
 if (key == 27) exit(0);

}


int main(int argc, char *argv[]) {
    
    PlyUtility util;
    PlyModel *mesh;
    util.readPlyFile("cube.ply");
    mesh=new PlyModel(&util);
    mesh->computeNormal();
    mesh->computeCentroid();
    root=new SceneNode(mesh,"cube");
    root->initTransformationMatrix();

    PlyUtility util1;
    PlyModel *mesh1;
    util1.readPlyFile("cylinder.ply");
    mesh1=new PlyModel(&util1);
    mesh1->computeNormal();
    mesh1->computeCentroid();
    SceneNode * child1=new SceneNode(mesh1,"cylinder");
    child1->initTransformationMatrix();
    child1->translateLocalTransformMatrix(glm::vec3(0.0,0.0,2.0));
    root->attachChild(child1);
   // cout<< child1->getParent()->getName();
   // root->printChildren();

    PlyUtility util2;
    PlyModel *mesh2;
    util2.readPlyFile("dolphins.ply");
    mesh2=new PlyModel(&util2);
    mesh2->computeNormal();
    mesh2->computeCentroid();
    SceneNode * child2=new SceneNode(mesh2,"dolphins");
    child2->initTransformationMatrix();
    child2->translateLocalTransformMatrix(glm::vec3(0.0,0.0,-2.0));
    root->attachChild(child2);

    PlyUtility util3;
    PlyModel *mesh3;
    util3.readPlyFile("sphere.ply");
    mesh3=new PlyModel(&util3);
    mesh3->computeNormal();
    mesh3->computeCentroid();
    SceneNode * child3=new SceneNode(mesh3,"sphere");
    child3->initTransformationMatrix();
    child3->translateLocalTransformMatrix(glm::vec3(0.0,0.0,2.0));
    child1->attachChild(child3);
 
    glutInit(&argc, argv);


    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Testing phase");
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glColor3f(0.0,1.0,1.0);

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






