#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QCheckBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QCheckBox *checkbox = new QCheckBox("C&ase sensitive", this);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{

    delete ui;
}
