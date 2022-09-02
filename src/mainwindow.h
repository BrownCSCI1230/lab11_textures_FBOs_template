#pragma once

#include <QMainWindow>

#include "glrenderer.h"

class MainWindow : public QWidget
{
    Q_OBJECT

  public:
    MainWindow();
    void cleanup();

  private:
    GLRenderer *glRenderer;
};
