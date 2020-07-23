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
#include <mysounds.h>
#include <scores.h>
#include <myregistry.h>

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
    bool pause;
    Board board;
    Shape shape;
    MySounds sound;
    Scores score;
    MyRegistry savedScores;     // recorded results in the register, saving and reading
    unsigned int pointScore;
    uint8_t difficultyLevel;            // 0-easy 1-hardUP 2-hardMove
    uint8_t difficultyLevelCounter;     // if 10 shape then go
    void showCell(unsigned short y, unsigned short x, unsigned short index, bool blueFrame);
    void showBoard();
    void showShape();
    void showScores();
    void showInformation(QString information);
    void setPen(unsigned short int color);
    void step();
    void merge();       // merge the board and shape
    void calculate();   // calculate the board. whether the sand is to fall and when there are whole rows.
    void calculateScores(); // calculate the scores (show 100 etc)
    bool isEndOfFalling(unsigned short y, unsigned short x);
    void changeTheBoards();

protected:
    void paintEvent(QPaintEvent *);

private slots:
    // -- menu
    void clickNowaGra();
    void clickLatwa();
    void clickTrudnaUp();
    void clickTrudnaMove();
    void clickUpiorna();
    void clickOAplikacji();

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
