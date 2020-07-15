#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QtGui>
#include <QtCore>
#include <shape.h>
#include <board.h>
#include <QTimer>
#include <QShortcut>

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

    // -- timer
    QTimer timer;
    uint8_t timerCounter;

    // -- shortCut
    QShortcut * shSPACE;
    QShortcut * shRIGHT;
    QShortcut * shLEFT;
    QShortcut * shDOWN;
    QShortcut * shESC;

    bool isFirstStart;  // whether running for the first time
    bool gameover;
    Board board;
    Shape shape;
    void showCell(unsigned short y, unsigned short x, unsigned short index, bool blueFrame);
    void showBoard();
    void showShape();
    void setPen(unsigned short int color);
    void step();
    void merge();       // merge the board and shape

protected:
    void paintEvent(QPaintEvent *);

private slots:
    // -- menu
    void clickNowaGra();

    // - timer
    void stepTimer();

    // -- shortCut
    void clickSpace();  // click key - rotate
    void clickRight();
    void clickLeft();
    void clickDown();
    void clickEsc();    // pause
};
#endif // MAINWINDOW_H
