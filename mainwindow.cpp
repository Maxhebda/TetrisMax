#include "mainwindow.h"
#include "ui_mainwindow.h"

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
}

MainWindow::~MainWindow()
{
    delete image;
    paintOnImage->end();
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
