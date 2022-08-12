#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include <QOpenGLFunctions_3_1>
#include <QOpenGLVersionFunctionsFactory>
#include <QFile>
#include <iostream>

// TODO: update with the newest one

class ShaderLoader : protected QOpenGLFunctions_3_1 {
  public:
    ShaderLoader();
    static GLuint createShaderProgram(const char * vertex_file_path,const char * fragment_file_path){
      QOpenGLFunctions_3_1 *f = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_3_1>(QOpenGLContext::currentContext());
      // Create and compile the shaders.
      GLuint vertexShaderID = createShader(GL_VERTEX_SHADER, vertex_file_path);
      GLuint fragmentShaderID = createShader(GL_FRAGMENT_SHADER, fragment_file_path);

      // Link the shader program.
      GLuint programId = f->glCreateProgram();
      f->glAttachShader(programId, vertexShaderID);
      f->glAttachShader(programId, fragmentShaderID);
      f->glLinkProgram(programId);

      // Print the info log.
      GLint result = GL_FALSE;
      int infoLogLength;
      f->glGetProgramiv(programId, GL_LINK_STATUS, &result);
      f->glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
      if (infoLogLength > 0) {
        std::vector<char> infoLog(std::max(infoLogLength, int(1)));
        f->glGetProgramInfoLog(programId, infoLogLength, NULL, &infoLog[0]);
        fprintf(stdout, "%s\n", &infoLog[0]);
      }

      f->glDeleteShader(vertexShaderID);
      f->glDeleteShader(fragmentShaderID);

      return programId;
    }

  private:
    static GLuint createShader(GLenum shaderType, const char *filepath){
      QOpenGLFunctions_3_1 *f = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_3_1>(QOpenGLContext::currentContext());
      GLuint shaderID = f->glCreateShader(shaderType);

      // Read shader file.
      std::string code;
      QString filepathStr = QString(filepath);
      QFile file(filepathStr);
      if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        code = stream.readAll().toStdString();
      }

      // Compile shader code.
      printf("Compiling shader: %s\n", filepath);
      std::cout<<code<<std::endl;
      const char *codePtr = code.c_str();
      f->glShaderSource(shaderID, 1, &codePtr, NULL);
      f->glCompileShader(shaderID);

      // Print info log.
      GLint result = GL_FALSE;
      int infoLogLength;
      f->glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
      f->glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
      if (infoLogLength > 0) {
        std::vector<char> infoLog(infoLogLength);
        f->glGetShaderInfoLog(shaderID, infoLogLength, NULL, &infoLog[0]);
        fprintf(stdout, "%s\n", &infoLog[0]);
      }

      return shaderID;
    }
};

#endif // SHADERLOADER_H
