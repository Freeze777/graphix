#include "Controller.h"
using namespace std;
#define num_sample_points 100

class Point {
public:
    float x, y;
    void setxy(float x2, float y2)
    {
        x = x2; y = y2;
    }
    //operator overloading for '=' sign
    const Point & operator=(const Point &rPoint)
    {
        x = rPoint.x;
        y = rPoint.y;
        return *this;
    }
 //operator overloading for '+' sign
    Point operator+(const Point &b)
    {
        Point sum;
        sum.x = this->x+ b.x;
        sum.y = this->y+ b.y;

        return sum;
    }

}samples[num_sample_points],points[3];

void myReshape(int w, int h);
void myKeyBoard(unsigned char key,int x, int y);
void myMouse(int button, int state, int x, int y);
void myDisplay(void);
void specialKeys(int key,int x,int y);
void myMouseMotion(int x, int y) ;

Controller *controller=NULL;
Model * model=NULL;
View *view=NULL;
float SCREEN_WIDTH=1000;
float SCREEN_HEIGHT=650;
int indx=0;
int fwd=1;
int factor=10000; // factor the animation is slowed down by
float binomial_coff(float n,float k) {
    if(k == 0)
        return 1;
    if(k > n/2)
        return binomial_coff(n,n-k);
    return (n * binomial_coff(n-1,k-1)) / k;
}

Point bezierHelper(Point p[],int size,float t) {
    Point P;
    P.x = 0; P.y = 0;
    for (int i = 0; i<size; i++)
    {
        P.x = P.x + binomial_coff((float)(size - 1), (float)i) * pow(t, (float)i) * pow((1 - t), (size - 1 - i)) * p[i].x;
        P.y = P.y + binomial_coff((float)(size - 1), (float)i) * pow(t, (float)i) * pow((1 - t), (size - 1 - i)) * p[i].y;
    }

    return P;
}
void computeBezierCurvePoints(Point p[],int size)
{


    /* Draw each segment of the curve.Make t increment in smaller amounts for a more detailed curve.*/
    int i=1;
    samples[0]=p[0];
    float step= 1.0/num_sample_points;
    for(float t = 0.0;t < 1.0; t += step)
    {
        Point p2 = bezierHelper(p,size,t);
        samples[i++]=p2;
    }

    samples[num_sample_points-1]=p[size-1];




}
/*
void animate(double speed);

static double ftime(void) {
    struct timeval t;
    gettimeofday(&t, NULL);

    double tmp=2*(1.0*t.tv_sec + 1e-6*t.tv_usec);

    return (30*sin(tmp));
}

static double last_T;

void animate(double t) {
  
    controller->dx = t;
    controller->dz =6*sin(controller->dx/400);
     
  glutPostRedisplay();
}

*/
void myIdle(void) {
  //const double now_T = ftime();
  //const double delta_T = now_T - last_T;
  //last_T = now_T;

  //const double speed = (delta_T) * 60;

  //animate(now_T);

   /* controller->dx =samples[indx].x ;
    controller->dz =samples[indx].y ;

    if(indx == num_sample_points-1)
        fwd=0;
    else if(indx == 0)
        fwd=1;
    if(fwd)indx++;
    else indx--;*/
    if(model)
    model->root->rotateLocalTransformMatrix(0.01,glm::vec3(0,1,0));

  glutPostRedisplay();
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
    
    points[0].setxy(-7.5,-7.5);
    points[1].setxy(-7.5,7.5);
    points[2].setxy(7.5,7.5);
    computeBezierCurvePoints(points,3);

  /*  if(argc!=7)
    {
        printf("Insufficient arguments..!!\n");
        exit(0);
    }
*/
    model=new Model();
    PlyUtility util;
    PlyModel *mesh;
    util.readPlyFile("plyfiles/cube.ply");
    mesh=new PlyModel(&util);
    mesh->computeNormal();
    mesh->computeCentroid();
    mesh->readTexture2Buffer("textures/checker.bmp");
    SceneNode * root=new SceneNode(mesh,"cube");
    root->initTransformationMatrix();

    PlyUtility util1;
    PlyModel *mesh1;
    util1.readPlyFile("plyfiles/sphere.ply");
    mesh1=new PlyModel(&util1);
    mesh1->computeNormal();
    mesh1->computeCentroid();
    mesh1->readTexture2Buffer("textures/apple.bmp");
    SceneNode * child1=new SceneNode(mesh1,"sphere");
    child1->initTransformationMatrix();
    child1->translateLocalTransformMatrix(glm::vec3(0.0,0.0,2.0));
    root->attachChild(child1);
 
    PlyUtility util2;
    PlyModel *mesh2;
    util2.readPlyFile("plyfiles/cylinder.ply");
    mesh2=new PlyModel(&util2);
    mesh2->computeNormal();
    mesh2->computeCentroid();
    mesh2->readTexture2Buffer("textures/metal_.bmp");
    SceneNode * child2=new SceneNode(mesh2,"cylinder");
    child2->initTransformationMatrix();
    child2->translateLocalTransformMatrix(glm::vec3(0.0,0.0,-2.0));
    root->attachChild(child2);
    
    model->root=root;    
    //root->printChildren();
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
   
    glutIdleFunc(myIdle);
   
    view->initialize(controller->dim,controller->fov);
    glutMainLoop();

    return 0;
}






