#include "PlyModel.h"

void PlyModel::draw()
{

  /*glMatrixMode(GL_MODELVIEW);
 

  glScalef(scale_factor,scale_factor,scale_factor);

  glTranslatef(-centroid[0],-centroid[1],-centroid[2]);*/

  int fcount=ply->getFaceCount();
  PlyUtility::Face ** fl=ply->getFaceList();
  PlyUtility::Vertex ** vl=ply->getVertexList();

  for (int var = 0; var < fcount ; var++) {

    glBegin(GL_POLYGON);
    for (int t = 0; t < fl[var]->nverts; t++)
    {
      int vIndex=fl[var]->verts[t];
      glNormal3d(normals_vertex[vIndex].x(),normals_vertex[vIndex].y(),normals_vertex[vIndex].z());
      glVertex3f(vl[vIndex]->x,vl[vIndex]->y,vl[vIndex]->z);
    }

    glEnd();
  }



  /*glPopMatrix();*/



}
void PlyModel::computeNormal(){


  int fcount=ply->getFaceCount();
  int vcount=ply->getVertexCount();
  PlyUtility::Face ** fl=ply->getFaceList();
  PlyUtility::Vertex ** vl=ply->getVertexList();

//  normals_face=(Vector *)malloc(sizeof(Vector)*fcount);
  normals_vertex=(Vector *)calloc(vcount,sizeof(Vector));

  for (int var = 0; var < fcount; ++var) {
    int v1_index=fl[var]->verts[0];
    int v2_index=fl[var]->verts[1];
    int v3_index=fl[var]->verts[2];
    int v4_index;
    PlyUtility:: Vertex v1=*vl[fl[var]->verts[0]];
PlyUtility::Vertex v2=*vl[fl[var]->verts[1]];//automatic storage i.e stack..! since new() is not used
PlyUtility:: Vertex v3=*vl[fl[var]->verts[2]];
PlyUtility:: Vertex v4;
if(fl[var]->nverts==4)
{
  v4=*vl[fl[var]->verts[3]];
  v4_index=fl[var]->verts[3];
}
Vector vec21(v2.x-v1.x,v2.y-v1.y,v2.z-v1.z);
Vector normv;
if(fl[var]->nverts==3){
  Vector vec32(v3.x-v2.x,v3.y-v2.y,v3.z-v2.z);
  normv=cross(vec21,vec32);
  normals_vertex[v1_index]+=normv;
  normals_vertex[v2_index]+=normv;
  normals_vertex[v3_index]+=normv;
}else if(fl[var]->nverts==4){
  Vector vec41(v4.x-v1.x,v4.y-v1.y,v4.z-v1.z);
  normv=cross(vec21,vec41);
  normals_vertex[v1_index]+=normv;
  normals_vertex[v2_index]+=normv;
  normals_vertex[v3_index]+=normv;
  normals_vertex[v4_index]+=normv;

}



}
}
void PlyModel::computeCentroid(){

  centroid[0]=(ply->vx_max+ply->vx_min)/2.0;
  centroid[1]=(ply->vy_max+ply->vy_min)/2.0;
  centroid[2]=(ply->vz_max+ply->vz_min)/2.0;


}
void PlyModel::computeScaleFactor(float dim){
  float maxDiff=0.0;
  float dx=ply->vx_max-ply->vx_min;
  float dy=ply->vy_max-ply->vy_min;
  float dz=ply->vz_max-ply->vz_min;
  if(dx>dy)
  {
    if(dx>dz)
      maxDiff=dx;
    else
      maxDiff=dz;

  }else{

    if(dy>dz)
      maxDiff=dy;
    else
      maxDiff=dz;

  }

  scale_factor=dim/maxDiff;

}
