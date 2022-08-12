#include "glrenderer.h"

#include <QCoreApplication>
#include <QWindow>

#include "CS1230Lib/shaderloader.h"
#include "examplehelpers.h"


const GLuint DEFAULT_FRAMEBUFFER = 2;

// Public

GLRenderer::GLRenderer(QWidget *parent)
  : QOpenGLWidget(parent),
    m_ka(0.1),
    m_kd(0.8),
    m_ks(1),
    m_angleX(6),
    m_angleY(0),
    m_zoom(2)
{
  rebuildCameraMatrices(this->width(), this->height());
}

void GLRenderer::cleanup()
{
  glDeleteProgram(m_texture_shader);
  glDeleteProgram(m_postprocessing_shader);
  doneCurrent();
}

// Protected

void GLRenderer::initializeGL()
{
  m_devicePixelRatio = this->devicePixelRatio();

  // GLEW is a library which provides an implementation for the OpenGL API
  // Here, we are setting it up
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (err != GLEW_OK) fprintf(stderr, "Error while initializing GLEW: %s\n", glewGetErrorString(err));
  fprintf(stdout, "Successfully initialized GLEW %s\n", glewGetString(GLEW_VERSION));
  
  // Set some default values for the OpenGL context
  glClearColor(0, 0, 0, 1);
  glEnable(GL_DEPTH_TEST);
  
  // Load shaders
  m_texture_shader = ShaderLoader::createShaderProgram("Resources/Shaders/texture.vert", "Resources/Shaders/texture.frag");
  m_phong_shader   = ShaderLoader::createShaderProgram("Resources/Shaders/phong.vert", "Resources/Shaders/phong.frag");
  
  // Prepare example geometry for rendering later
  initializeExampleGeometry();

  // Prepare filepath
  QString kitten_filepath = QString("Resources/Images/kitten.png");

  // TASK 1: obtain image from filepath


  // TASK 2: format image to fit OpenGL

  
  // TASK 3: generate kitten texture


  // TASK 9: set the active texture slot to texture slot 0


  // TASK 4: bind kitten texture


  // TASK 5: load image into kitten texture


  // TASK 6: set min and mag filters' interpolation mode to linear


  // TASK 7: unbind kitten texture


  // TASK 10: set the texture.frag uniform for our texture


  // TASK 11: fix this "fullscreen" quad's vertex data
  // TASK 12: play around with different values
  // TASK 13: add UV coordinates
  std::vector<GLfloat> fullscreen_quad_data =
  { //     POSITIONS     //
      -0.8f,  0.8f, 0.0f,
      -0.8f, -0.8f, 0.0f,
       0.8f, -0.8f, 0.0f,
       0.8f,  0.8f, 0.0f,
      -0.8f,  0.8f, 0.0f,
       0.8f, -0.8f, 0.0f
  };

  // Generate and bind a VBO and a VAO for a fullscreen quad
  glGenBuffers(1, &m_fullscreen_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_fullscreen_vbo);
  glBufferData(GL_ARRAY_BUFFER, fullscreen_quad_data.size()*sizeof(GLfloat), fullscreen_quad_data.data(), GL_STATIC_DRAW);
  glGenVertexArrays(1, &m_fullscreen_vao);
  glBindVertexArray(m_fullscreen_vao);

  // TASK 14: modify the code below to add a second attribute to the vertex attribute array
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);

  // Unbind the fullscreen quad's VBO and VAO
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // ================== FBOs Section

  // TASK 19: generate and bind an empty texture, set its min/mag filter interpolation, then unbind


  // TASK 20: generate and bind a renderbuffer of the right size, set its format, then unbind


  // TASK 18: generate and bind an FBO


  // TASK 21: add our texture as a color attachment, and our renderbuffer as a depth+stencil attachment, to our FBO


  // TASK 22: unbind the FBO


}

void GLRenderer::paintGL()
{
//  // TASK 10: set the active texture slot to texture slot 0, then bind the kitten texture

// Clear screen, use program, bind vertex array, draw vertex array
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(m_texture_shader);
  glBindVertexArray(m_fullscreen_vao);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
  glUseProgram(0);

  // TASK 23 (uncomment the following code and todos): rendering to our created FBO

//  // TASK 25: bind our FBO


//  // Draw a sphere to the currently bound framebuffer
//  paintExampleGeometry();

//  // TASK 24: unbind our FBO


//  // TASK 26: set the active texture slot to texture slot 0, then bind the FBO texture


//  // TASK 26: clear screen, use program, bind vertex array, draw vertex array


}

void GLRenderer::resizeGL(int w, int h)
{
  m_proj = glm::perspective(45.0, 1.0 * w / h, 0.01, 100.0);
}

// Private

void GLRenderer::initializeExampleGeometry()
{
  // Create geometry for a sphere

  // Generate and bind the VBO
  glGenBuffers(1, &m_sphere_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_sphere_vbo);

  // Put data into the VBO
  m_sphere_data = generateSphereData(10, 20);
  glBufferData(GL_ARRAY_BUFFER,
               m_sphere_data.size() * sizeof(GLfloat),
               m_sphere_data.data(),
               GL_STATIC_DRAW);

  // Generate and bind the VAO, with our VBO currently bound
  glGenVertexArrays(1, &m_sphere_vao);
  glBindVertexArray(m_sphere_vao);

  // Define VAO attributes
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<void *>(0));

  // Unbind
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLRenderer::paintExampleGeometry()
{
  // Paint the geometry for a sphere

  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(m_phong_shader);

  // Set uniforms for Phong vertex shader
  auto modelLoc = glGetUniformLocation(m_phong_shader, "modelMatrix");
  auto viewLoc  = glGetUniformLocation(m_phong_shader, "viewMatrix");
  auto projLoc  = glGetUniformLocation(m_phong_shader, "projMatrix");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &m_model[0][0]);
  glUniformMatrix4fv(viewLoc,  1, GL_FALSE, &m_view[0][0]);
  glUniformMatrix4fv(projLoc,  1, GL_FALSE, &m_proj[0][0]);

  // Set uniforms for Phong fragment shader
  glUniform4f(glGetUniformLocation(m_phong_shader, "light.position"), 10, 0, 0, 1);
  glUniform3f(glGetUniformLocation(m_phong_shader, "light.color"), 1, 1, 1);
  glUniform1f(glGetUniformLocation(m_phong_shader, "ka"),m_ka);
  glUniform1f(glGetUniformLocation(m_phong_shader, "kd"),m_kd);
  glUniform1f(glGetUniformLocation(m_phong_shader, "ks"),m_ks);

  // Draw
  glBindVertexArray(m_sphere_vao);
  glDrawArrays(GL_TRIANGLES, 0, m_sphere_data.size() / 3);

  // Unbind
  glBindVertexArray(0);
  glUseProgram(0);
}

void GLRenderer::rebuildCameraMatrices(int w, int h)
{
  // Update view matrix by rotating eye vector based on x and y angles

  // Create a new view matrix
  m_view = glm::mat4(1);
  glm::mat4 rot = glm::rotate(-10 * m_angleX,glm::vec3(0,0,1));
  glm::vec3 eye = glm::vec3(2,0,0);
  eye = glm::vec3(rot * glm::vec4(eye, 1));
  
  rot = glm::rotate(-10 * m_angleY,glm::cross(glm::vec3(0,0,1),eye));
  eye = glm::vec3(rot * glm::vec4(eye, 1));
  
  eye = eye * m_zoom;
  
  m_view = glm::lookAt(eye,glm::vec3(0,0,0),glm::vec3(0,0,1));
  
  m_proj = glm::perspective(45.0, 1.0 * w / h, 0.01,100.0);
  
  update();
}
