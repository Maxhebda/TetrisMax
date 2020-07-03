#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // --- set form size
    QWidget::setMinimumHeight(650+40+ui->menubar->height());
    QWidget::setMaximumHeight(650+40+ui->menubar->height());
    QWidget::setMinimumWidth(500+10);
    QWidget::setMaximumWidth(500+10);
    // --- background
    image = new QImage(500,680,QImage::Format_RGB16);
    image -> fill(QColor(255,190,190));
    paintOnImage = new QPainter;
    paintOnImage->begin(image);
    // --- add frame
    paintOnImage->setPen(QColor(100,100,100));
    paintOnImage->drawRect(5,5,10*34-1,20*33+10);
    paintOnImage->drawRect(4,4,10*34+1,20*33+10);
    paintOnImage->fillRect(6,6,10*34-2,20*33+8, QColor(0,0,0));
    Shape a;
    a.newShape();

    for (unsigned short int y=0; y<20 ; y++)
    {
        for (unsigned short int x=0; x<10 ; x++)
        {
            unsigned short int randC = rand()%10;
            if (randC >= 5 && randC <= 8)
                showCell(y,x,1);
            if (randC < 5 )
                showCell(y,x,0);
            if (randC > 8)
                showCell(y,x,2);
        }
    }

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

void MainWindow::showCell(unsigned short y, unsigned short x, unsigned short index)
{
    if (index==0)
    {
        paintOnImage->fillRect(10+33*x,10+33*y,32,32,QColor(0,0,0));
        return;
    }

    // variable gradient
    QRect myRect;
    myRect.setX(13+33*x);
    myRect.setY(13+33*y);
    myRect.setWidth(27);
    myRect.setHeight(27);
    QLinearGradient gradient;

    // frame
    paintOnImage->setPen(QColor(100,100,100));
    paintOnImage->drawRect(10+33*x,10+33*y,32,32);
    paintOnImage->setPen(QColor(200,200,200));
    paintOnImage->drawRect(11+33*x,11+33*y,30,30);
    paintOnImage->setPen(QColor(255,255,255));
    paintOnImage->drawRect(12+33*x,12+33*y,28,28);

    switch (index) {
        case 1 :
        {
            gradient.setStart(myRect.topLeft());
            gradient.setFinalStop(myRect.bottomRight());
            gradient.setColorAt(0, Qt::white);
            gradient.setColorAt(1, Qt::red);
            break;
        }
        case 2 :
        {
            gradient.setStart(myRect.topRight());
            gradient.setFinalStop(myRect.bottomRight());
            gradient.setColorAt(0, Qt::black);
            gradient.setColorAt(1, Qt::darkYellow);
            break;
        }
    }
    paintOnImage->fillRect(myRect, gradient);
}

void MainWindow::setPen(unsigned short int color)
{
    switch (color) {
        case 0 : paintOnImage->setPen(QColor(0,0,255));break;
        case 1 : paintOnImage->setPen(QColor(200,0,100));break;
    }
}
