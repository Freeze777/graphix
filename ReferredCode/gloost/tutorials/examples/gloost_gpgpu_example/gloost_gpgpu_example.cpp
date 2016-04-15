/**

  Last change 09.04.24 by Felix Weißig

  Email: thesleeper@gmx.net
  skype: otacocato
  URL:   http://www.otaco.de

**/

/**
  gloost GPGPU EXAMPLE

  This demo uses two 32 bit textures and one shader to process a wave simulation.
  Another shader is used to visualize the result of the processing with per pixel
  lighting and environment mapping.

  The two textures are used as double buffer: The processing shader is reading value
  from one texture and writes the results to the second one. For the next frame
  the textures are switched;

  The amplitude of the wave are stored in the red value, while the vertical
  speed of one element/pixel is stored in the green value of the texture.


  In this demo you can see how to create a 32 bits/channel component texture and
  use it with the TextureManager.


**/


////////////////////////////////////////////////////////////////////////////////



/// gloost includes
#include <gloost/gl/Texture.h>
#include <gloost/gl/Fbo.h>
#include <gloost/TextureManager.h>
#include <gloost/gl/gloostRenderGoodies.h>


/// cpp includes
#include <GL/glew.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <map>



//////////////////////////////////////////////////////////////////////////////////////////


/// screen size
unsigned int g_screenWidth  = 1280;
unsigned int g_screenHeight = 720;


/// path where the images, shaders and relfection maps are located in
std::string g_dataPath = "../../tutorials/examples/gloost_gpgpu_example/data/";


/// size of the processing buffer
unsigned int g_bufferWidth  = g_screenWidth  * 2.0;
unsigned int g_bufferHeight = g_screenHeight * 2.0;


/// frame counter for some reason
unsigned int g_frameCounter = 0;


// textureManager
gloost::TextureManager* g_texMaster = 0;


/// background picture
unsigned int g_backgroundTexture = 0;


/// double buffer for processing
unsigned int g_doubleBufferIds[2];
bool         g_currentBuffer = 0;


/// shader and uniforms for processing
#include <gloost/gl/ShaderProgram.h>
#include <gloost/gl/UniformSet.h>
gloost::gl::ShaderProgram* g_processingShader = nullptr;
gloost::gl::UniformSet     g_processingUniforms;

/// shader and uniforms for visualsation
gloost::gl::ShaderProgram* g_viewShader   = nullptr;
gloost::gl::UniformSet     g_viewUniforms;


/// fbo holding both processing textures as color attachments
gloost::gl::Fbo* g_fbo = nullptr;


/**
    This little fella renders a little image to a texture. You can set the position,
    rotation, opacity and size of this image within the big texture.

    The texture is used to set the amplidue values (green color) to a defined
    value (pull the water up). Since the texture is black eccept for the spot
    where the little image was drawn to, the values are only manipulated in this
    area.
**/

#include <gloost/Brush.h>
gloost::Brush* g_brush;


// mouse state
bool  g_mouseDown[3] = {false, false, false};

gloost::vec2 g_mouseLoc;
gloost::vec2 g_mouseLocOld;
gloost::vec2 g_mouseSpeed;


/// toggle info text
bool g_toggle_infoText = true;




void reloadShaders();

//////////////////////////////////////////////////////////////////////////////////////////


void init()
{
  //
  g_texMaster = gloost::TextureManager::getInstance();


  // create a fbo
  g_fbo = new gloost::gl::Fbo();



  // initialise double buffer and attach it to the FBO
  for (unsigned int i=0; i!=2; ++i )
  {

    gloost::gl::Texture* buffer = new gloost::gl::Texture(g_bufferWidth,
        g_bufferHeight,
        8,
        GL_TEXTURE_2D,
        GL_LUMINANCE_ALPHA32F_ARB,
        GL_LUMINANCE_ALPHA,
        GL_FLOAT );

    buffer->setTexParameter(GL_TEXTURE_WRAP_S, GL_CLAMP);
    buffer->setTexParameter(GL_TEXTURE_WRAP_T, GL_CLAMP);

    g_doubleBufferIds[i] = g_texMaster->addTexture(buffer);

    g_fbo->attachTexture(GL_TEXTURE_2D,
        buffer->getTextureHandle(),
        GL_COLOR_ATTACHMENT0_EXT+i);

    gloost::gl::Fbo::unbind();
  }

  /// the background image
  gloost::gl::Texture* background = new gloost::gl::Texture(g_dataPath + "/background/wcip_screenshot.jpg");
  background->setTexParameter(GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  background->setTexParameter(GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  g_backgroundTexture = g_texMaster->addTexture(background);


  // shader and uniforms
  reloadShaders();

  g_viewUniforms.set_sampler("environment_map", g_texMaster->createTexture(std::string("../../data/environments/probe.jpg")));
//  g_viewUniforms.set_sampler2D("environment_map", g_texMaster->createTexture("../../data/environments/bensFrontyard.jpg"));


  // brush to paint
  g_brush = new gloost::Brush(g_dataPath + "/brush/raff.jpg",
      g_bufferWidth,
      g_bufferHeight);
  g_brush->setScale(0.015);
  g_brush->setOpacity(0.9);

}


//////////////////////////////////////////////////////////////////////////////////////////

void reloadShaders()
{

  if (g_processingShader)
  {
    delete g_processingShader;
  }

  g_processingShader = new gloost::gl::ShaderProgram();
  g_processingShader->attachShader(GLOOST_SHADERPROGRAM_VERTEX_SHADER,
      g_dataPath + "/shader/processingShader.vs");
  g_processingShader->attachShader(GLOOST_SHADERPROGRAM_FRAGMENT_SHADER,
      g_dataPath + "/shader/processingShader.fs");


  if (g_viewShader)
  {
    delete g_viewShader;
  }

  g_viewShader = new gloost::gl::ShaderProgram();

  g_viewShader->attachShader(GLOOST_SHADERPROGRAM_VERTEX_SHADER,
      g_dataPath + "/shader/visualizingShader.vs");
  g_viewShader->attachShader(GLOOST_SHADERPROGRAM_FRAGMENT_SHADER,
      g_dataPath + "/shader/visualizingShader.fs");

}




//////////////////////////////////////////////////////////////////////////////////////////


static void resize(int width, int height)
{
  g_screenWidth  = width;
  g_screenHeight = height;

  const float ar = (float) width / (float) height;

  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-ar, ar, -1.0, 1.0, 3.0, 20.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity() ;
}

//////////////////////////////////////////////////////////////////////////////////////////


///

inline void drawQuad()
{
  glBegin(GL_QUADS);
  {
    glTexCoord2f(0.0, 1.0);
    glVertex3f  (0.0, 1.0, 0);

    glTexCoord2f(0.0, 0.0);
    glVertex3f  (0.0, 0.0, 0);

    glTexCoord2f(1.0, 0.0);
    glVertex3f  (1.0, 0.0, 0);

    glTexCoord2f(1.0, 1.0);
    glVertex3f  (1.0, 1.0, 0);
  }
  glEnd();
}


//////////////////////////////////////////////////////////////////////////////////////////

inline void switchToOrtho()
{
  glViewport(0, 0, g_screenWidth, g_screenHeight);



  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, (float) g_screenWidth, 0, (float) g_screenHeight, 0.1, 10.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 5.0,
      0.0, 0.0, 0.0,
      0.0, 1.0, 0.0);
}


//////////////////////////////////////////////////////////////////////////////////////////


void processLiquid()
{

  glPushMatrix();
  {
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    {

      glViewport(0, 0, g_bufferWidth, g_bufferHeight);


      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(0, (float) g_bufferWidth, 0, (float) g_bufferHeight, 0.1, 10.0);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      gluLookAt(0.0, 0.0, 5.0,
          0.0, 0.0, 0.0,
          0.0, 1.0, 0.0);

      glDisable(GL_COLOR_MATERIAL);
      glDisable(GL_DEPTH_TEST);
      glDisable(GL_LIGHTING);

      // color
      glColor3d(1,1,1);


      // switch doubleBuffer
      g_currentBuffer = !g_currentBuffer;


      // configure the uniforms for the next renderpass
      g_processingUniforms.set_sampler("data_map", g_doubleBufferIds[(int)(!g_currentBuffer)]);
      g_processingUniforms.set_sampler("targetTex", g_doubleBufferIds[(int)(g_currentBuffer)]);
      g_processingUniforms.set_sampler("objects_map", g_brush->getTransferTextureId());
      g_processingUniforms.set_float("f_texelWidth", 1.0/g_bufferWidth);
      g_processingUniforms.set_float("f_texelHeight", 1.0/g_bufferHeight);
      g_processingUniforms.set_float("f_reset", 0.0);

      if (g_frameCounter < 3)
      {
        g_processingUniforms.set_float("f_reset", 0.01);
      }


      g_fbo->bind();
      glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT+((int)g_currentBuffer));
      {
        g_processingShader->use();
        g_processingUniforms.applyToShader(g_processingShader->getHandle());
        {
          glPushMatrix();
          glScalef(g_bufferWidth, g_bufferHeight, 1.0);

          drawQuad();

          glPopMatrix();
        }
        g_processingShader->disable();
      }

      gloost::gl::Fbo::unbind();

    }
    glPopAttrib();
  }
  glPopMatrix();

}


//////////////////////////////////////////////////////////////////////////////////////////


void visualize()
{

  glPushMatrix();
  {
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    {
      switchToOrtho();

      // clear the framebuffer
      glClearColor(0.7, 0.6, 0.3, 1.0);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


      glDisable(GL_COLOR_MATERIAL);
      glDisable(GL_DEPTH_TEST);
      glDisable(GL_LIGHTING);
      glEnable(GL_LINE_SMOOTH);

      // color
      glColor3d(1,1,1);


      g_viewUniforms.set_sampler("color_map", g_backgroundTexture);
      g_viewUniforms.set_sampler("data_map", g_doubleBufferIds[(int)(!g_currentBuffer)]);
      g_viewUniforms.set_float("f_bufferWidth", g_bufferWidth);
      g_viewUniforms.set_float("f_bufferHeight", g_bufferHeight);

      g_viewShader->use();
      g_viewUniforms.applyToShader(g_viewShader->getHandle());
      {
        glPushMatrix();
        glScalef(g_screenWidth, g_screenHeight, 1.0);
        gloost::gl::drawQuad();
        glPopMatrix();
      }
      g_viewShader->disable();


      if (g_toggle_infoText)
      {
        g_brush->getTransferTexture()->bind();
        glPushMatrix();
        glScalef(g_screenWidth/5.0, g_screenHeight/5.0, 1.0);
        gloost::gl::drawQuad();
        glPopMatrix();
        g_brush->getTransferTexture()->unbind();


        g_texMaster->getTextureWithoutRefcount(g_doubleBufferIds[(int)(!g_currentBuffer)])->bind();
        glPushMatrix();
        glTranslatef(g_screenWidth/5.0, 0.0, 0.0);
        glScalef(g_screenWidth/5.0, g_screenHeight/5.0, 1.0);
        gloost::gl::drawQuad();
        glPopMatrix();
        g_texMaster->getTextureWithoutRefcount(g_doubleBufferIds[(int)(!g_currentBuffer)])->unbind();
      }


    }
    glPopAttrib();
  }
  glPopMatrix();

}


//////////////////////////////////////////////////////////////////////////////////////////


static void display(void)
{
  ++g_frameCounter;

  // clear the framebuffer
  glClearColor(0.7, 0.6, 0.3, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity ();



  // clear framebuffer from uv render pass
  glClearColor(0.7, 0.6, 0.3, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  // draw
  g_brush->clearBrushTexture();
  if(g_mouseDown[0])
  {
    g_brush->renderBrushToTransferTexture(g_mouseLoc.u, g_mouseLoc.v);
  }
  else if(g_mouseDown[1])
  {
    g_brush->renderBrushToTransferTexture(gloost::math::frand(), gloost::math::frand());
  }
  else if(g_mouseDown[2])
  {
    g_brush->renderBrushToTransferTexture(sin(g_frameCounter*0.06)*0.09 + g_mouseLoc.u,
        cos(g_frameCounter*0.06)*0.09 + g_mouseLoc.v);
  }
  {
    processLiquid();
  }
  visualize();


  glutSwapBuffers();
}


//////////////////////////////////////////////////////////////////////////////////////////


void motionFunc(int mouse_h, int mouse_v)
{

  g_mouseLoc.u = float(mouse_h) / float(g_screenWidth);
  g_mouseLoc.v = float(mouse_v) / float(g_screenHeight);

  g_mouseSpeed.u = g_mouseLoc.u-g_mouseLocOld.u;
  g_mouseSpeed.v = g_mouseLoc.v-g_mouseLocOld.v;

  g_mouseLocOld.u = g_mouseLoc.u;
  g_mouseLocOld.v = g_mouseLoc.v;
}


//////////////////////////////////////////////////////////////////////////////////////////


void mouseFunc(int button, int state, int mouse_h, int mouse_v)
{

  if (button == GLUT_LEFT_BUTTON)
  {
    if (state == GLUT_DOWN)
    {
      g_mouseDown[0] = true;
    }
    else if (state == GLUT_UP)
    {
      g_mouseDown[0]  = false;
    }
  }
  else if (button == GLUT_RIGHT_BUTTON)
  {
    if (state == GLUT_DOWN)
    {
      g_mouseDown[1] = true;
    }
    else
    {
      g_mouseDown[1] = false;
    }
    glutPostRedisplay();
  }
  else if (button == GLUT_MIDDLE_BUTTON)
  {
    if (state == GLUT_DOWN)
    {
      g_mouseDown[2] = true;
    }
    else
    {
      g_mouseDown[2] = false;
    }
    glutPostRedisplay();
  }
}


//////////////////////////////////////////////////////////////////////////////////////////


static void key(unsigned char key, int x, int y)
{
  switch (key)
  {
  // quit
  case 27 :
    exit(0);
    break;

  // reset brush texture
  case 'n' :
    g_brush->clearBrushTexture();
    break;

  case ' ' :
    g_frameCounter = 0;
    break;

  // show textures
  case 'h' :
    g_toggle_infoText = !g_toggle_infoText;
    break;

  // fullscreen
  case 'f' :
    glutFullScreen();
    break;

  // quit
  case 'r' :
    reloadShaders();
    break;
  }

  glutPostRedisplay();
}


//////////////////////////////////////////////////////////////////////////////////////////


static void idle(void)
{
  glutPostRedisplay();
}


//////////////////////////////////////////////////////////////////////////////////////////


int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitWindowSize(g_screenWidth,g_screenHeight);
  glutInitWindowPosition(80,20);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

  glutCreateWindow("gloost_gpgpu_example");

  glutReshapeFunc(resize);
  glutDisplayFunc(display);
  glutKeyboardFunc(key);
  glutIdleFunc(idle);
  glutMotionFunc(motionFunc);
  glutPassiveMotionFunc(motionFunc);
  glutMouseFunc(mouseFunc);

  if (GLEW_OK != glewInit())
  {
    std::cerr << "'glewInit()' failed." << std::endl;
    exit(0);
  }
  glClearColor(0.7, 0.6, 0.3, 1.0);

//  glEnable(GL_CULL_FACE);
//  glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_TEXTURE_2D);



  //glutFullScreen();


  ////////////////////////////////////////////////////////////////////////////////////////
  // Test
  ////////////////////////////////////////////////////////////////////////////////////////


  /// load stuff
  init();



  glutMainLoop();

  return EXIT_SUCCESS;
}


//////////////////////////////////////////////////////////////////////////////////////////



