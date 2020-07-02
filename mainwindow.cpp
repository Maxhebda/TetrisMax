#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <shape.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // --- set form size
    QWidget::setMinimumHeight(650+10+ui->menubar->height());
    QWidget::setMaximumHeight(650+10+ui->menubar->height());
    QWidget::setMinimumWidth(500+10);
    QWidget::setMaximumWidth(500+10);
    // --- background
    image = new QImage(500,650,QImage::Format_RGB16);
    image -> fill(QColor(255,190,190));
    paintOnImage = new QPainter;
    paintOnImage->begin(image);
    // --- add frame
    paintOnImage->drawRect(5,5,10*32,20*32);

    Shape a;
    a.newShape();

//    for (short i=0; i<a.getShape().size();)
//    {
//        if (a.getShape().size()==9)
//        {
//            qDebug() << a.getShape()[i] << a.getShape()[i+1] << a.getShape()[i+2];
//            i+=3;
//        }
//        else
//        {
//            qDebug() << a.getShape()[i] << a.getShape()[i+1] << a.getShape()[i+2] << a.getShape()[i+3];
//            i+=4;
//        }
//    }
//    a.rotateShape();
//    for (short i=0; i<a.getShape().size();)
//    {
//        if (a.getShape().size()==9)
//        {
//            qDebug() << a.getShape()[i] << a.getShape()[i+1] << a.getShape()[i+2];
//            i+=3;
//        }
//        else
//        {
//            qDebug() << a.getShape()[i] << a.getShape()[i+1] << a.getShape()[i+2] << a.getShape()[i+3];
//            i+=4;
//        }
//    }
}
MainWindow::~MainWindow()
{
    paintOnImage->end();
    delete image;
    delete paintOnImage;
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent * e)
{
    QPainter painter;
    painter.begin(this);
    painter.drawImage(5,5 + ui->menubar->height(),*image);
    painter.end();
}
