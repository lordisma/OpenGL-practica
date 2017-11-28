//**************************************************************************
//
// Domingo Martin Perandres© 2014-2017
// http://calipso.ugr.es/dmartin
// dmartin@ugr.es
//
// GPL
//**************************************************************************

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardPaths>
#include <QFileDialog>
#include <QDialog>
#include <QTimer>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QGuiApplication>
#include <iostream>
#include <QDesktopWidget>

QT_FORWARD_DECLARE_CLASS(QOpenGLWidget)

class _gl_widget;

class _window : public QMainWindow
{
    Q_OBJECT

public:
    _window();
    void openfile();
private:
  _gl_widget *GL_widget;
};

#endif
