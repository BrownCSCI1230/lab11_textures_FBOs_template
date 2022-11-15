#include "mainwindow.h"

#include <QHBoxLayout>
#include <QWindow>
#include <iostream>

MainWindow::MainWindow()
{
  glRenderer = new GLRenderer{};

  QHBoxLayout *container = new QHBoxLayout{};
  container->addWidget(glRenderer);

  this->setLayout(container);
}

void MainWindow::finish()
{
  glRenderer->finish();
}


