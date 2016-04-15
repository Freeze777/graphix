
#ifndef plymodel_h
#define plymodel_h
#include "PlyUtility.h"
#include "Vector.h"
#include <stdlib.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glut.h>
class PlyModel{

private:

GLfloat shift[3];

PlyUtility *ply;
Vector *normals_face;
Vector *normals_vertex;

int txtWidth;
int txtHeght;
   
public:
GLfloat scale_factor=1.0;
GLfloat centroid[3]={0.0,0.0 ,0.0}; 
    
    void draw();
    void computeNormal();
    void computeCentroid();
    void computeScaleFactor(float dim);		
    
    PlyModel(PlyUtility *p){
        ply=p;

    }

};

#endif
