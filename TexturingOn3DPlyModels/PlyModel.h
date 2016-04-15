
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
//GLfloat centroid[3]={0.02,-0.09 ,-0.015};
GLfloat centroid[3]={0.0,0.0 ,0.0};
GLfloat shift[3];


Vector *normals_face;
Vector *normals_vertex;

int txtWidth;
int txtHeght;
   
public:
GLfloat scale_factor=1.0;
    PlyUtility *ply;
    Image *texture;
    void draw(int txtMode,float dx,float dy,float dz,int trans_flag);
    void computeNormal();
    void readTexture2Buffer(char *filename,int width,int height);
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
