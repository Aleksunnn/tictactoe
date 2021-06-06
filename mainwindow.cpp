#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_mainwidget = new Mainwidget();
    setCentralWidget(m_mainwidget);
    connect(ui->actionPlay_again, SIGNAL(triggered()), m_mainwidget, SLOT(clickedPlayAgain()));
    connect(ui->actionSave, SIGNAL(triggered()), m_mainwidget, SLOT(clickedSave()));
    connect(ui->actionLoad, SIGNAL(triggered()), m_mainwidget, SLOT(clickedLoad()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(clickedQuit()));
    connect(ui->actionPlay_with_bot, SIGNAL(triggered()), m_mainwidget, SLOT(clickedPlayBot()));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clickedQuit()
{
    QCoreApplication::exit(0);
}


