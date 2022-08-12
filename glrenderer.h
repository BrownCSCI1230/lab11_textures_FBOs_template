#pragma once

#include "GL/glew.h"
#include <QOpenGLWidget>

#include "glm/gtc/constants.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/glm.hpp"

class GLRenderer : public QOpenGLWidget
{
public:
    GLRenderer(QWidget *parent = nullptr);

    void cleanup();

protected:
    void initializeGL()         override; // Called once before the first call to paintGL() or resizeGL()
    void paintGL()              override; // Called whenever the widget needs to be painted
    void resizeGL(int w, int h) override; // Called whenever widget has been resized

private:
    void initializeExampleGeometry();
    void paintExampleGeometry();

    void rebuildCameraMatrices(int w, int h);

    int m_devicePixelRatio;

    GLuint m_texture_shader;
    GLuint m_postprocessing_shader;
    GLuint m_fullscreen_vbo;
    GLuint m_fullscreen_vao;
    QImage m_image;
    GLuint m_kitten_texture;
    GLuint m_fbo;
    GLuint m_fbo_texture;
    GLuint m_rbo;

    GLuint m_phong_shader;
    std::vector<float> m_sphere_data;
    GLuint m_sphere_vbo;
    GLuint m_sphere_vao;

    glm::mat4 m_model;
    glm::mat4 m_view;
    glm::mat4 m_proj;
    float m_ka;
    float m_kd;
    float m_ks;
    float m_angleX;
    float m_angleY;
    float m_zoom;
};
