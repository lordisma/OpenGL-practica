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

#include <QPushButton>
#include <QGridLayout>
#include <QRadioButton>
#include <QRect>
#include <QSlider>
#include <QSignalMapper>

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
  QVBoxLayout *Newh            = new QVBoxLayout(Central_widget);
  QDesktopWidget * newt          = new QDesktopWidget();

  QGridLayout * Principal = new QGridLayout(Central_widget);
  //QRect  screensize = newt->availableGeometry();

  cout << newt->width()<< "\n\n\n" << newt->height() << endl;
  //Newh->setGeometry(screensize);

  QGridLayout * PushBut = new QGridLayout(Central_widget);
  QGridLayout * Check = new QGridLayout(Central_widget);
  QGridLayout * Check1 = new QGridLayout(Central_widget);
  QGridLayout * Check2 = new QGridLayout(Central_widget);
  QVBoxLayout * Slider = new QVBoxLayout(Central_widget);

  QSlider  * CutNum = new QSlider(Qt::Horizontal,Central_widget);
  CutNum->setMaximumWidth(300);

  QPushButton * prueba = new QPushButton("Lineas",Central_widget);
  prueba->setMaximumWidth(70);
  QPushButton * prueba2 = new QPushButton("Puntos", Central_widget);
  prueba2->setMaximumWidth(70);
  QPushButton * prueba3 = new QPushButton("Ajedrez", Central_widget);
  prueba3->setMaximumWidth(70);


  QRadioButton * radio1 = new QRadioButton(" Cubo ", Central_widget);
  radio1->setMaximumWidth(70);
  QRadioButton * radio2 = new QRadioButton(" Pira ", Central_widget);
  radio1->setMaximumWidth(70);
  QRadioButton * radio3 = new QRadioButton(" Figura ", Central_widget);
  radio1->setMaximumWidth(70);
  QRadioButton * radio4 = new QRadioButton(" Cilindro ", Central_widget);
  radio1->setMaximumWidth(70);

  QRadioButton * radio5 = new QRadioButton(" Tubo ", Central_widget);
  radio1->setMaximumWidth(70);
  QRadioButton * radio6 = new QRadioButton(" Peon ", Central_widget);
  radio1->setMaximumWidth(70);
  QRadioButton * radio7 = new QRadioButton(" Cono ", Central_widget);
  radio1->setMaximumWidth(70);
  QRadioButton * radio8 = new QRadioButton(" Vaso ", Central_widget);
  radio1->setMaximumWidth(70);

  PushBut->setMargin(5);
  PushBut->addWidget(prueba,0,1);
  PushBut->addWidget(prueba2,0,0);
  PushBut->addWidget(prueba3,1,0);

  Check1->setMargin(5);
  Check1->addWidget(radio1,0,0);   Check1->addWidget(radio5,0,1);
  Check1->addWidget(radio2,1,0);   Check1->addWidget(radio6,1,1);

  Check2->setMargin(5);
  Check2->addWidget(radio3,0,0);   Check2->addWidget(radio7,0,1);
  Check2->addWidget(radio4,1,0);   Check2->addWidget(radio8,1,1);

  Slider->setMargin(5);
  Slider->addWidget(CutNum);

  Horizontal_main->addWidget(Framed_widget);
  Check->addLayout(Check1,0,1);
  Check->addLayout(Check2,0,0);

  Principal->addLayout(PushBut,0,0);
  Principal->addLayout(Check,1,0);
  Principal->addLayout(Slider,2,0);
  Newh->addLayout(Principal,20);
  Horizontal_main->addLayout(Newh);

  Central_widget->setLayout(Horizontal_main);
  setCentralWidget(Central_widget);

  // actions
  connect(prueba,SIGNAL(clicked(bool)),GL_widget,SLOT(CheckModl()));
  connect(prueba2,SIGNAL(clicked(bool)),GL_widget,SLOT(CheckModp()));
  connect(prueba3,SIGNAL(clicked(bool)),GL_widget,SLOT(CheckModc()));


  connect(radio1,SIGNAL(clicked(bool)),GL_widget,SLOT(CheckFig1()));
  connect(radio2,SIGNAL(clicked(bool)),GL_widget,SLOT(CheckFig2()));
  connect(radio3,SIGNAL(clicked(bool)),GL_widget,SLOT(CheckFig3()));
  connect(radio4,SIGNAL(clicked(bool)),GL_widget,SLOT(CheckFig4()));
  connect(radio5,SIGNAL(clicked(bool)),GL_widget,SLOT(CheckFig5()));
  connect(radio6,SIGNAL(clicked(bool)),GL_widget,SLOT(CheckFig6()));
  connect(radio7,SIGNAL(clicked(bool)),GL_widget,SLOT(CheckFig7()));
  connect(radio8,SIGNAL(clicked(bool)),GL_widget,SLOT(CheckFig8()));

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


