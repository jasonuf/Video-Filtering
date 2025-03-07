#include "mainwindow.h"

#include <QApplication>

#include <QCheckBox>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QWidget window;
    w.setWindowTitle("Example Name: HI!");

    QPushButton *button = new QPushButton(
        QApplication::translate("childwidget", "Press me"), &w);
    button->move(100, 100);
    button->show();

    QCheckBox *checkbox = new QCheckBox("C&ase sensitive", &w);
    checkbox->show();

    QLabel *label = new QLabel(QApplication::translate("windowlayout", "Name:"));
    QLineEdit *lineEdit = new QLineEdit();

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(label);
    layout->addWidget(lineEdit);
    window.setLayout(layout);


    w.show();

    return a.exec();

}
