#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QtGui>
#include <QtCore>
#include <shape.h>
#include <board.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QImage * image;
    QPainter * paintOnImage;
    Board board;
    Shape shape;
    void showCell(unsigned short y, unsigned short x, unsigned short index);
    void showBoard();
    void showShape();
    void setPen(unsigned short int color);

protected:
    void paintEvent(QPaintEvent *);
};
#endif // MAINWINDOW_H
