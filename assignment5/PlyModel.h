
#ifndef plymodel_h
#define plymodel_h
#include "PlyUtility.h"
#include "Image.h"
#include "Vector.h"
#include <stdlib.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glut.h>
class PlyModel{

private:

GLfloat shift[3];
Image *img;
PlyUtility *ply;
Vector *normals_face;
Vector *normals_vertex;
int txtMode;  
public:
GLfloat scale_factor=1.0;
GLfloat centroid[3]={0.0,0.0 ,0.0}; 
    
    void draw();
    void computeNormal();
    void computeCentroid();
    void computeScaleFactor(float dim);		
    void readTexture2Buffer(char *filename);
    void freeTextBuffer();
    void getUVCoords( double x,double y,double z,double *uv);
    void convert2Cylindrical( double x,double y,double z,double *res);
    PlyModel(PlyUtility *p,int mode){
        ply=p;
        txtMode=mode;
        img=new Image();

    }

};

#endif
