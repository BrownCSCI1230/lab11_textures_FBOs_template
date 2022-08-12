cmake_minimum_required(VERSION 3.16)

project(lab11 LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core          REQUIRED)
find_package(Qt6 COMPONENTS Widgets       REQUIRED)
find_package(Qt6 COMPONENTS OpenGL        REQUIRED)
find_package(Qt6 COMPONENTS OpenGLWidgets REQUIRED)
find_package(Qt6 COMPONENTS Gui           REQUIRED)

add_executable(${PROJECT_NAME}
  main.cpp
  glrenderer.cpp
  mainwindow.cpp

  glrenderer.h
  mainwindow.h
  CS1230Lib/shaderloader.h
  examplehelpers.h
)

include_directories(${projectName}
    PRIVATE glew/include
    )

add_library(myGlew STATIC ${CMAKE_CURRENT_SOURCE_DIR}/glew/src/glew.c)

add_subdirectory(glm)

target_link_libraries(${PROJECT_NAME} PRIVATE
  Qt::Core
  Qt::Widgets
  Qt::OpenGL
  Qt::OpenGLWidgets
  Qt::Gui
  myGlew
  glm
)

if (WIN32)
  add_compile_definitions(GLEW_STATIC)
  target_link_libraries(${PROJECT_NAME} PRIVATE
      opengl32
      glu32
  )
endif()

if (UNIX AND NOT APPLE)
  target_link_libraries(${PROJECT_NAME} PRIVATE
      GLU
  )
endif()
