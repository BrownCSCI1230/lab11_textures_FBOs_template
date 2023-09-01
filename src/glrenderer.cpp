#include "glrenderer.h"

#include <QCoreApplication>
#include <QWindow>

#include "shaderloader.h"
#include "examplehelpers.h"

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

void GLRenderer::finish()
{
  glDeleteProgram(m_texture_shader);
  glDeleteProgram(m_phong_shader);
  glDeleteVertexArrays(1, &m_sphere_vao);
  glDeleteBuffers(1, &m_sphere_vbo);
  glDeleteVertexArrays(1, &m_fullscreen_vao);
  glDeleteBuffers(1, &m_fullscreen_vbo);

  // Task 35: Delete OpenGL memory here

  doneCurrent();
}

// Protected

void GLRenderer::initializeGL()
{
  m_devicePixelRatio = this->devicePixelRatio();

  m_defaultFBO = 0;
  m_screen_width = size().width() * m_devicePixelRatio;
  m_screen_height = size().height() * m_devicePixelRatio;
  m_fbo_width = m_screen_width;
  m_fbo_height = m_screen_height;

  // GLEW is a library which provides an implementation for the OpenGL API
  // Here, we are setting it up
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (err != GLEW_OK) fprintf(stderr, "Error while initializing GLEW: %s\n", glewGetErrorString(err));
  fprintf(stdout, "Successfully initialized GLEW %s\n", glewGetString(GLEW_VERSION));
  
  // Set some default values for the OpenGL context
  glClearColor(0, 0, 0, 1);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  
  // Load shaders
  m_texture_shader = ShaderLoader::createShaderProgram(":/resources/shaders/texture.vert", ":/resources/shaders/texture.frag");
  m_phong_shader   = ShaderLoader::createShaderProgram(":/resources/shaders/phong.vert", ":/resources/shaders/phong.frag");
  
  // Prepare example geometry for rendering later
  initializeExampleGeometry();

  // Prepare filepath
  QString kitten_filepath = QString(":/resources/images/kitten.png");

  // Task 1: Obtain image from filepath

  // Task 2: Format image to fit OpenGL
  
  // Task 3: Generate kitten texture

  // Task 9: Set the active texture slot to texture slot 0

  // Task 4: Bind kitten texture

  // Task 5: Load image into kitten texture

  // Task 6: Set min and mag filters' interpolation mode to linear

  // Task 7: Unbind kitten texture

  // Task 10: Set the texture.frag uniform for our texture
  
  // Task 11: Fix this "fullscreen" quad's vertex data
  // Task 12: Play around with different values!
  // Task 13: Add UV coordinates
  std::vector<GLfloat> fullscreen_quad_data =
  { //     POSITIONS    //
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

  // Task 14: modify the code below to add a second attribute to the vertex attribute array
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);

  // Unbind the fullscreen quad's VBO and VAO
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  makeFBO();
}

void GLRenderer::makeFBO(){
    // Task 19: Generate and bind an empty texture, set its min/mag filter interpolation, then unbind

    // Task 20: Generate and bind a renderbuffer of the right size, set its format, then unbind

    // Task 18: Generate and bind an FBO

    // Task 21: Add our texture as a color attachment, and our renderbuffer as a depth+stencil attachment, to our FBO

    // Task 22: Unbind the FBO

}

void GLRenderer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    paintTexture(m_kitten_texture);

    // Task 23: Uncomment the following code
//    // Task 24: Bind our FBO

//    // Task 28: Call glViewport

//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    paintExampleGeometry();

//    // Task 25: Bind the default framebuffer

//    // Task 26: Clear the color and depth buffers

//    // Task 27: Call paintTexture to draw our FBO color attachment texture | Task 31: Set bool parameter to true

}

// Task 31: Update the paintTexture function signature
void GLRenderer::paintTexture(GLuint texture){
    glUseProgram(m_texture_shader);
    // Task 32: Set your bool uniform on whether or not to filter the texture drawn

    glBindVertexArray(m_fullscreen_vao);
    // Task 10: Bind "texture" to slot 0

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

void GLRenderer::resizeGL(int w, int h){
    // Task 34: Delete Texture, Renderbuffer, and Framebuffer memory

    m_screen_width = size().width() * m_devicePixelRatio;
    m_screen_height = size().height() * m_devicePixelRatio;
    m_fbo_width = m_screen_width;
    m_fbo_height = m_screen_height;
    // Task 34: Regenerate your FBOs

    m_proj = glm::perspective(glm::radians(45.0), 1.0 * w / h, 0.01, 100.0);
}

// ============== DO NOT EDIT PAST THIS LINE ==================== //

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
  glm::mat4 rot = glm::rotate(glm::radians(-10 * m_angleX), glm::vec3(0,0,1));
  glm::vec3 eye = glm::vec3(2,0,0);
  eye = glm::vec3(rot * glm::vec4(eye, 1));
  
  rot = glm::rotate(glm::radians(-10 * m_angleY), glm::cross(glm::vec3(0,0,1),eye));
  eye = glm::vec3(rot * glm::vec4(eye, 1));
  
  eye = eye * m_zoom;
  
  m_view = glm::lookAt(eye,glm::vec3(0,0,0),glm::vec3(0,0,1));
  
  m_proj = glm::perspective(glm::radians(45.0), 1.0 * w / h, 0.01,100.0);
  
  update();
}
