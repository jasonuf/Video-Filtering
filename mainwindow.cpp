#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "videoplayer.h"


#include <QMenuBar>
#include <QMenu>
#include <QDebug>
#include <QVBoxLayout>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(960,540);



    qInfo() << "Main Window Created";


}

MainWindow::~MainWindow()
{


    delete ui;
}

void MainWindow::actionTest()
{
    qInfo() << "Action was completed";
}

void MainWindow::createMenus()
{


}



void MainWindow::on_actionOpen_File_triggered()
{
    videoOpen = new QString(QFileDialog::getOpenFileName(this,
        tr("Open Video"), "/", tr("Video Files (*.mp4)")));
    qInfo() << "The property videoOpen is set to: " << *videoOpen;
}

