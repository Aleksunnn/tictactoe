#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "mainwidget.h"
#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void clickedQuit();
private:
    Ui::MainWindow *ui;
    Mainwidget *m_mainwidget;

};

#endif // MAINWINDOW_H
