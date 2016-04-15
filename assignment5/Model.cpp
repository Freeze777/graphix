#include "Model.h"
#include <iostream>

Model::Model(char *filename){

ply1=new PlyUtility();
ply2=new PlyUtility();
ply3=new PlyUtility();
plymodel1=new PlyModel(ply1);
plymodel2=new PlyModel(ply2);
plymodel3=new PlyModel(ply3);
walls=new Walls(filename);

}

Model::~Model(){

delete ply1;
delete ply2;
delete ply3;
delete plymodel1;
delete plymodel2;
delete plymodel3;
delete walls;

}

void Model::readModelsFromFile(char *filename1,char *filename2,char *filename3){

    ply1->readPlyFile(filename1);
	plymodel1->computeNormal();
	plymodel1->computeCentroid();
	
    ply2->readPlyFile(filename2);
    plymodel2->computeNormal();
    plymodel2->computeCentroid();


    ply3->readPlyFile(filename3);
    plymodel3->computeNormal();
    plymodel3->computeCentroid();
    


}

void Model::setScaleFactor(float dim){
plymodel1->computeScaleFactor(dim);
plymodel2->computeScaleFactor(dim);
plymodel3->computeScaleFactor(dim);

}
void Model::drawScene(float dim,float dx,float dy,float dz){
	
	
    glPushMatrix(); 
    glTranslatef(0,-7.5,0);
    glStencilFunc(GL_ALWAYS,1, -1);
    plymodel1->draw(0,dx,dy,dz,1);
    glPopMatrix();

    glPushMatrix();   
    glTranslatef(0,-7.5,0);
    glRotatef(90,0,1,0);
    glStencilFunc(GL_ALWAYS,2, -1);
    plymodel2->draw(0,dx,dy,dz,1);
    glPopMatrix();

    glPushMatrix();   
    glTranslatef(0,-7.5,0);
    glRotatef(-90,0,1,0);
    glStencilFunc(GL_ALWAYS,3, -1);
    plymodel3->draw(0,dx,dy,dz,1);
    glPopMatrix();
    
    glStencilFunc(GL_ALWAYS,4, -1);
    walls->draw(5*dim);


}

void Model::drawAxis(float dim){

    glMatrixMode(GL_MODELVIEW);
    glBegin(GL_LINES);
    // draw line for x axis
    glColor3f(1, 0.0, 0.0);
    glVertex3f(dim/2.0,0.0, 0.0);
    glVertex3f(-dim/2.0,0.0, 0.0);

    // draw line for y axis
    glColor3f(0.0,1, 0.0);
    glVertex3f(0.0,dim/2.0, 0.0);
    glVertex3f(0.0,-dim/2.0, 0.0);

    // draw line for z axis
    glColor3f(0.0,0.0,1);
    glVertex3f(0.0,0.0, dim/2.0);
    glVertex3f(0.0,0.0, -dim/2.0);

    glEnd();

    glColor3f(1.0,1.0,1.0);
}



void Model::markPoints(float dim){

        glColor3f(1.0,0.0,0.0);

        glRasterPos3fv(origin);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'O');
        glRasterPos3f(dim/2.0,0.0,0.0);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'X');
        glRasterPos3f(0.0,dim/2.0,0.0);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'Y');
        glRasterPos3f(0.0,0.0,dim/2.0);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'Z');

        glColor3f(1.0,1.0,1.0);
}



