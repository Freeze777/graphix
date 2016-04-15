#include "Walls.h"
#include <iostream>

Walls::Walls(char *filename){
//std::cout<< "called";
img=new Image();
img=img->loadTexture(filename);
  
}
void Walls::readNewTexture(char *filename){

delete img;
img=new Image();
img=img->loadTexture(filename);

}

void Walls::draw(float dim)
{
dim=15;

  GLuint txture;
  glGenTextures(1,&txture);
  glBindTexture(GL_TEXTURE_2D, txture);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //scale linearly when image bigger than texture
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //scale linearly when image smalled than texture
  glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, img->sizeX, img->sizeY,1,GL_RGB, GL_UNSIGNED_BYTE, img->data);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
floor_mid[0]=dim/2;
floor_mid[1]=-dim/2;
floor_mid[2]=dim/2;

glBegin(GL_QUADS);
/* Walls */
/*Floor*/
glNormal3d(0,1,0);
glTexCoord2f(0,0);
glVertex3f(-dim/2,-dim/2,-dim/2);
glTexCoord2f(0,8);
glVertex3f(-dim/2,-dim/2,dim/2);
glTexCoord2f(8,8);
glVertex3f(dim/2,-dim/2,dim/2);
 glTexCoord2f(8,0);
glVertex3f(dim/2,-dim/2,-dim/2);
/* Ceiling */
/*glNormal3d(0,-1,0);
glTexCoord2f(0,0);
glVertex3f(-dim/2,dim/2,-dim/2);
glTexCoord2f(0,2);
glVertex3f(dim/2,dim/2,-dim/2);
glTexCoord2f(2,2);
glVertex3f(dim/2,dim/2,dim/2);
 glTexCoord2f(2,0);
glVertex3f(-dim/2,dim/2,dim/2);*/
    /* Walls */
/*Front wall*/
/* 
 glTexCoord2f(0,0);
glVertex3f(-dim/2,-dim/2,dim/2);
 glTexCoord2f(0,2);
glVertex3f(dim/2,-dim/2,dim/2);
 glTexCoord2f(2,2);
glVertex3f(dim/2,dim/2,dim/2);
 glTexCoord2f(2,0);
glVertex3f(-dim/2,dim/2,dim/2);
*/
/*Back wall*/
/*glNormal3d(0,0,1);
glTexCoord2f(0,0);
glVertex3f(-dim/2,-dim/2,-dim/2);
glTexCoord2f(0,2);
glVertex3f(dim/2,-dim/2,-dim/2);
glTexCoord2f(2,2);
glVertex3f(dim/2,dim/2,-dim/2);
glTexCoord2f(2,0);
glVertex3f(-dim/2,dim/2,-dim/2);*

/*Right wall*/

/*glNormal3d(-1,0,0);
glTexCoord2f(0,0);
glVertex3f(dim/2,dim/2,dim/2);
glTexCoord2f(0,2);
glVertex3f(dim/2,-dim/2,dim/2);
glTexCoord2f(2,2);
glVertex3f(dim/2,-dim/2,-dim/2);
glTexCoord2f(2,0);
glVertex3f(dim/2,dim/2,-dim/2);*/

/*Left wall*/
/*glNormal3d(1,0,0);
glTexCoord2f(0,0);
glVertex3f(-dim/2,dim/2,dim/2);
glTexCoord2f(0,2);
glVertex3f(-dim/2,-dim/2,dim/2);
glTexCoord2f(2,2);
glVertex3f(-dim/2,-dim/2,-dim/2);
glTexCoord2f(2,0);
glVertex3f(-dim/2,dim/2,-dim/2);
*/
glEnd();
//glPopMatrix();



}

