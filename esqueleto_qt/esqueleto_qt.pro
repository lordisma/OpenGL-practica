HEADERS += \
  glwidget.h \
  window.h \
    vertex.h \
    objetos.h \
    _file_ply.h \
    obj3drev.h \
    f_watt.h

SOURCES += \
  main.cc \
  glwidget.cc \
  window.cc \
    objetos.cpp \
    _file_ply.cpp \
    obj3drev.cpp \
    f_watt.cpp

INCLUDEPATH += /casa/dmartin/codigo/funciontecas/glew/include

LIBS += -L/usr/X11R6/lib64 -lGL \
        -L/casa/dmartin/codigo/funciontecas/glew/lib -lGLEW

CONFIG += c++11
QT += widgets

DISTFILES += \
    ant.ply \
    beethoven.ply \
    big_dodge.ply \
    Cilinder.ply
