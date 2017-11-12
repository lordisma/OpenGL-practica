//**************************************************************************
//
// Domingo Martin Perandres© 2014-2017
// http://calipso.ugr.es/dmartin
// dmartin@ugr.es
//
// GPL
//**************************************************************************

#include <QApplication>
#include <QMenuBar>
#include <QGroupBox>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>
#include <QSpinBox>
#include <QScrollArea>

#include "window.h"
#include "glwidget.h"

void _window::openfile(){

  QString nombre = QFileDialog::getOpenFileName(this, "Selecciona un archivo .ply para abrir", QDir::currentPath(),tr("Archivo ply (*.ply)"));

  setWindowTitle(tr("Practica 2 - Leido(") + nombre + tr(")"));

  GL_widget->load_ply(nombre.toStdString());

  cout << nombre.toStdString() << endl;

}

_window::_window()
{

  QSizePolicy Q(QSizePolicy::Expanding,QSizePolicy::Expanding);

  QWidget *Central_widget = new QWidget(this);

  QFrame *Framed_widget= new QFrame(Central_widget);
  Framed_widget->setSizePolicy(Q);
  Framed_widget->setFrameStyle(QFrame::Panel);
  Framed_widget->setLineWidth(3);


  GL_widget = new _gl_widget(this);
  GL_widget->setSizePolicy(Q);

  QHBoxLayout *Horizontal_frame = new QHBoxLayout();
  Horizontal_frame->setContentsMargins(1,1,1,1);

  Horizontal_frame->addWidget(GL_widget);
  Framed_widget->setLayout(Horizontal_frame);

  QHBoxLayout *Horizontal_main = new QHBoxLayout(Central_widget);

  Horizontal_main->addWidget(Framed_widget);

  Central_widget->setLayout(Horizontal_main);
  setCentralWidget(Central_widget);

  // actions for file menu
  QAction *Exit = new QAction(QIcon("./icons/exit.png"), tr("&Exit..."), this);
  Exit->setShortcut(tr("Ctrl+Q"));
  Exit->setToolTip(tr("Exit the application"));
  connect(Exit, SIGNAL(triggered()), this, SLOT(close()));

  const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/images/open.png"));
  QAction *Abrir = new QAction(openIcon, tr("&Open..."), this);
  Abrir->setShortcuts(QKeySequence::Open);
  Abrir->setStatusTip(tr("Open an existing file"));
  connect(Abrir, &QAction::triggered, this, &_window::openfile);

  // menus
  QMenu *File_menu=menuBar()->addMenu(tr("Options"));
  File_menu->addAction(Abrir);
  File_menu->addAction(Exit);
  File_menu->setAttribute(Qt::WA_AlwaysShowToolTips);

  setWindowTitle(tr("Practica IG"));

  resize(800,800);
}


