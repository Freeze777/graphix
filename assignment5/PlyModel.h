
#ifndef plymodel_h
#define plymodel_h
#include "PlyUtility.h"
#include "Vector.h"
#include "Image.h"
#include <GL/glu.h>

#include <GL/gl.h>
#include <GL/glut.h>
class PlyModel{

private:

PlyUtility *ply;
Vector *normals_face;
Vector *normals_vertex;

public:
GLfloat scale_factor=1.0;
GLfloat centroid[3]={0.0,0.0 ,0.0}; 
    Image *texture;
    void draw();
    void computeNormal();
    void readTexture2Buffer(char *filename);
    void freeTextBuffer();
    void computeCentroid();
    void convert2Cylindrical( double x,double y,double z,double *res);
    void convert2Circular( double x,double y,double z,double *res);
    void getUVCoords( double x,double y,double z,double *uv,int mode,int vIndex);
    void computeScaleFactor(float dim);		
    
    PlyModel(PlyUtility *p){
        ply=p;
        texture=new Image();

    }

};

#endif
