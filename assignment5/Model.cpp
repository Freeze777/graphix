#include "Model.h"
#include <iostream>

Model::Model(){

}

Model::~Model(){

}


void Model::draw(){
	
	
  root->draw();



}
void Model::drawAxis(){

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0.0,0.5,0.0);
    glBegin(GL_LINES);
    // draw line for x axis
    glColor3f(1, 0.0, 0.0);
    glVertex3f(0.5,0.0, 0.0);
    glVertex3f(-0.5,0.0, 0.0);

    // draw line for y axis
    glColor3f(0.0,1, 0.0);
    glVertex3f(0.0,0.5, 0.0);
    glVertex3f(0.0,-0.5, 0.0);

    // draw line for z axis
    glColor3f(0.0,0.0,1);
    glVertex3f(0.0,0.0, 0.5);
    glVertex3f(0.0,0.0, -0.5);

    glEnd();
    glPopMatrix();
    glColor3f(1.0,1.0,1.0);
}
SceneNode * Model::createSceneGraph(){
    PlyUtility * util=new PlyUtility();
    PlyModel * floor;
    util->readPlyFile("plyfiles/floor.ply");
    floor=new PlyModel(util,0);
    floor->computeNormal();
    floor->computeCentroid();
    floor->readTexture2Buffer("textures/checker_.bmp");
    root=new SceneNode(floor,"floor",1);
    root->initTransformationMatrix();

    PlyUtility * util1=new PlyUtility();
    PlyModel *cube;
    util1->readPlyFile("plyfiles/cube.ply");
    cube=new PlyModel(util1,2);
    cube->computeNormal();
    cube->computeCentroid();
    cube->readTexture2Buffer("textures/goldhair.bmp");
    SceneNode * child1=new SceneNode(cube,"cube",2);
    child1->initTransformationMatrix();
   // child1->translateLocalTransformMatrix(glm::vec3(4.0,-3.9,4.0));
     child1->translateLocalTransformMatrix(glm::vec3(-4.0,-3.9,4.0));
    root->attachChild(child1);

    PlyUtility * util2=new PlyUtility();
    PlyModel *porsche;
    util2->readPlyFile("plyfiles/porsche.ply");
    porsche=new PlyModel(util2,1);
    porsche->computeNormal();
    porsche->computeCentroid();
    porsche->readTexture2Buffer("textures/blood.bmp");
    SceneNode * child2=new SceneNode(porsche,"porsche",3);
    child2->initTransformationMatrix();
    child2->translateLocalTransformMatrix(glm::vec3(-4.0,-4.5,4.0));
    root->attachChild(child2);

    PlyUtility * util3=new PlyUtility();
    PlyModel *car;
    util3->readPlyFile("plyfiles/car.ply");
    car=new PlyModel(util3,1);
    car->computeNormal();
    car->computeCentroid();
    car->readTexture2Buffer("textures/bubbles.bmp");
    SceneNode * child3=new SceneNode(car,"car",4);
    child3->initTransformationMatrix();
    child3->translateLocalTransformMatrix(glm::vec3(-0.1,1.5,-0.5));
    child1->attachChild(child3);

    PlyUtility * util4=new PlyUtility();
    PlyModel *f16;
    util4->readPlyFile("plyfiles/f16.ply");
    f16=new PlyModel(util4,2);
    f16->computeNormal();
    f16->computeCentroid();
    f16->readTexture2Buffer("textures/redhair.bmp");
    SceneNode * child4=new SceneNode(f16,"f16",5);
    child4->initTransformationMatrix();
    child4->translateLocalTransformMatrix(glm::vec3(4.0,1.5,4.0));
    child4->rotateLocalTransformMatrix(-45,glm::vec3(0,1,0));
    root->attachChild(child4);

return root;
}
