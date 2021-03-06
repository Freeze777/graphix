#ifndef arc_ball
#define arc_ball



#include "Vector.h"
#include "Quaternion.h"
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glut.h>

class Arcball {
private:
    float windowWidth;
    float windowHeight;

    GLfloat rollSpeed;
    int cur_mx,last_mx,cur_my,last_my;
     
public:
    Arcball( float SCREEN_WIDTH, float SCREEN_HEIGHT, GLfloat roll_speed) ;
    Arcball (const Arcball&);
    void rotateModelvthMouse(float dim);
    void rotateCameravthMouse(float dim,Vector * eye_vector);
    Vector get_arcball_vector(int x, int y,float dim);
    void set_current_xy(int x,int y);
    void set_last_xy(int x,int y);
    void set_width_height(float SCREEN_WIDTH,float SCREEN_HEIGHT);
};

#endif