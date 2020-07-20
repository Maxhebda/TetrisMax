#include "mainwindow.h"
#include "ui_mainwindow.h"

// QString mySprintf(format, arguments);
template<typename ... Args>
QString mySprintf(const char * format,Args ... a)
{
    char scream[255];
    sprintf(scream,format,a ...);
    return scream;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // -- set menu connections
    connect(ui->actionNowa_gra,SIGNAL(triggered()), this, SLOT(clickNowaGra()));
    connect(ui->action_Latwa,SIGNAL(triggered()), this, SLOT(clickLatwa()));
    connect(ui->actionTrudnaUP,SIGNAL(triggered()), this, SLOT(clickTrudnaUp()));
    connect(ui->actionTrudnaMove,SIGNAL(triggered()), this, SLOT(clickTrudnaMove()));
    connect(ui->actionUpiorny,SIGNAL(triggered()), this, SLOT(clickUpiorna()));

    // -- set shortCut connections
    shSPACE  = new QShortcut(QKeySequence(Qt::Key_Space),this,SLOT(clickSpace()));
    shRIGHT  = new QShortcut(QKeySequence(Qt::Key_Right),this,SLOT(clickRight()));
    shLEFT   = new QShortcut(QKeySequence(Qt::Key_Left),this,SLOT(clickLeft()));
    shDOWN   = new QShortcut(QKeySequence(Qt::Key_Down),this,SLOT(clickDown()));
    shESC   = new QShortcut(QKeySequence(Qt::Key_Escape),this,SLOT(clickEsc()));

    // -- set timer connections
    connect(&timer,SIGNAL(timeout()),this,SLOT(stepTimer()));
    timer.setInterval(50);
    timerCounter = 0;

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
    shape.newShape();

    // tymczasowe wartosci dla planszy
    board.setBoard(19,0,1);
    board.setBoard(19,1,1);
    board.setBoard(19,2,1);
    board.setBoard(18,2,1);
    board.setBoard(19,5,1);
    board.setBoard(19,6,1);
    board.setBoard(18,6,1);
    board.setBoard(19,7,1);

    isFirstStart = true;
    gameover = false;
    pause = false;
    pointScore = 0;
    difficultyLevel = 0;    //easy
    difficultyLevelCounter = 0;
    showBoard();
    showShape();
}
MainWindow::~MainWindow()
{
    paintOnImage->end();
    delete shSPACE;
    delete shRIGHT;
    delete shLEFT;
    delete shDOWN;
    delete shESC;
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

void MainWindow::showCell(unsigned short y, unsigned short x, unsigned short index, bool blueFrame)
{
    if (index==0)
    {
        paintOnImage->fillRect(10+33*x,10+33*y,33,33,QColor(0,0,0));
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
    if (blueFrame)
    {
        paintOnImage->setPen(Qt::blue);
        paintOnImage->drawRect(10+33*x,10+33*y,32,32);
    }
    else
    {
        paintOnImage->setPen(QColor(100,100,100));
        paintOnImage->drawRect(10+33*x,10+33*y,32,32);
        paintOnImage->setPen(QColor(200,200,200));
    }
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

void MainWindow::showInformation(QString information)
{
    const QRect rectangle = QRect(80, 270, 185, 50);
    paintOnImage->fillRect(rectangle,QColor(055,055,055));
    paintOnImage->setPen(QColor(255,255,255));
    paintOnImage->drawText(rectangle,Qt::AlignCenter, information);
}

void MainWindow::showBoard()
{
    for (unsigned short int y=0; y<20 ; y++)
    {
        for (unsigned short int x=0; x<10 ; x++)
        {
            switch (board.getBoard(y,x)) {
                case 0 :
                {
                    showCell(y,x,0,false);
                    break;
                }
                case 1 :
                {
                    showCell(y,x,1,false);
                    break;
                }
                case 2 :
                {
                    showCell(y,x,2,false);
                    break;
                }
            }
        }
    }
}


void MainWindow::showShape()
{
    for (unsigned short int y=0; y<shape.row() ; y++)
    {
        for (unsigned short int x=0; x<shape.row() ; x++)
        {
            switch (shape.getShapeCell(y,x)) {
                case 0 :
                {
                    // showCell(y + shape.y(),x + shape.x(),0);
                    break;
                }
                case 1 :
                {
                    showCell(y + shape.y(),x + shape.x(),1, true);
                    break;
                }
                case 2 :
                {
                    showCell(y + shape.y(),x + shape.x(),2, true);
                    break;
                }
            }
        }
    }

    if (gameover)
    {
        showInformation("Koniec gry!\nGameOver");
    }

    if (pause)
    {
        showInformation("Pauza\nNaciśnij spację");
    }
}

void MainWindow::showScores()
{
    if (score.size()==0)
    {
        return;
    }
    for(unsigned short int iter = 0; iter<score.size(); iter++)
    {
        paintOnImage->setPen(QColor(255,255,255));
        paintOnImage->drawText(score.getX(iter), score.getY(iter), score.getValue(iter));
    }
    ui->label_2->setText(mySprintf("%d",pointScore));
}

void MainWindow::stepTimer()
{
    timerCounter++;
    calculateScores();
    if (timerCounter%2==0)
    {
        calculate();
    }

    if (timerCounter == 20)
    {
        timerCounter = 0;
        step();
    }
}

void MainWindow::clickNowaGra()
{
    gameover = false;
    pause = false;
    pointScore = 0;
    difficultyLevelCounter = 0;
    board.clearBoard();
    shape.newShape();
    timer.start();
    showBoard();
    showShape();
    showScores();
    repaint();
}

void MainWindow::clickLatwa()
{
    ui->action_Latwa->blockSignals(true);
    ui->action_Latwa->setChecked(true);
    ui->action_Latwa->blockSignals(false);
    ui->actionTrudnaUP->blockSignals(true);
    ui->actionTrudnaUP->setChecked(false);
    ui->actionTrudnaUP->blockSignals(false);
    ui->actionTrudnaMove->blockSignals(true);
    ui->actionTrudnaMove->setChecked(false);
    ui->actionTrudnaMove->blockSignals(false);
    ui->actionUpiorny->blockSignals(true);
    ui->actionUpiorny->setChecked(false);
    ui->actionUpiorny->blockSignals(false);
    difficultyLevel = 0;    //set easy
}

void MainWindow::clickTrudnaUp()
{
    ui->actionTrudnaUP->blockSignals(true);
    ui->actionTrudnaUP->setChecked(true);
    ui->actionTrudnaUP->blockSignals(false);
    ui->action_Latwa->blockSignals(true);
    ui->action_Latwa->setChecked(false);
    ui->action_Latwa->blockSignals(false);
    ui->actionTrudnaMove->blockSignals(true);
    ui->actionTrudnaMove->setChecked(false);
    ui->actionTrudnaMove->blockSignals(false);
    ui->actionUpiorny->blockSignals(true);
    ui->actionUpiorny->setChecked(false);
    ui->actionUpiorny->blockSignals(false);
    difficultyLevel = 1;    //set hard up
}

void MainWindow::clickTrudnaMove()
{
    ui->actionTrudnaMove->blockSignals(true);
    ui->actionTrudnaMove->setChecked(true);
    ui->actionTrudnaMove->blockSignals(false);
    ui->actionTrudnaUP->blockSignals(true);
    ui->actionTrudnaUP->setChecked(false);
    ui->actionTrudnaUP->blockSignals(false);
    ui->action_Latwa->blockSignals(true);
    ui->action_Latwa->setChecked(false);
    ui->action_Latwa->blockSignals(false);
    ui->actionUpiorny->blockSignals(true);
    ui->actionUpiorny->setChecked(false);
    ui->actionUpiorny->blockSignals(false);
    difficultyLevel = 2;    //set hard move
}

void MainWindow::clickUpiorna()
{
    ui->actionUpiorny->blockSignals(true);
    ui->actionUpiorny->setChecked(true);
    ui->actionUpiorny->blockSignals(false);
    ui->actionTrudnaMove->blockSignals(true);
    ui->actionTrudnaMove->setChecked(false);
    ui->actionTrudnaMove->blockSignals(false);
    ui->actionTrudnaUP->blockSignals(true);
    ui->actionTrudnaUP->setChecked(false);
    ui->actionTrudnaUP->blockSignals(false);
    ui->action_Latwa->blockSignals(true);
    ui->action_Latwa->setChecked(false);
    ui->action_Latwa->blockSignals(false);
    difficultyLevel = 3;    //set very hard
}

void MainWindow::step()
{
    if (gameover)
    {
        return;
    }
    bool allowDown = true;
    for (unsigned short int y=0; y<shape.row(); y++)
    {
        for (unsigned short int x=0; x<shape.row(); x++)
        {
            if (shape.getShapeCell(y,x)!=0 && board.getBoard(shape.y()+y+1,shape.x()+x)!=0)
            {
                allowDown = false;
            }
        }
    }
    if (allowDown==false)
    {
        sound.click();
        merge();    // merge the board and shape
        shape.newShape();
        //---- easy / hard change the board
        difficultyLevelCounter++;
        if (difficultyLevelCounter==10)
        {
            difficultyLevelCounter = 0;
            changeTheBoards();
        }

        //---- its gameover?
        for (unsigned short int y=0; y<shape.row(); y++)
        {
            for (unsigned short int x=0; x<shape.row(); x++)
            {
                if (shape.getShapeCell(y,x)!=0 && board.getBoard(shape.y()+y,shape.x()+x)!=0)
                {
                    // gameover
                    gameover = true;
                    sound.gameover();
                }
            }
        }
    }
    else
    {
        sound.shape();
        shape.goDown();
    }

    showBoard();
    showShape();
    showScores();
    repaint();
}

void MainWindow::merge()        // merge the board and shape
{
    for (unsigned short int y=0; y<shape.row(); y++)
    {
        for (unsigned short int x=0; x<shape.row(); x++)
        {
            if (shape.getShapeCell(y,x)!=0)
            {
                board.setBoard(shape.y()+y,shape.x()+x,shape.getShapeCell(y,x));
            }
        }
    }
}

bool MainWindow::isEndOfFalling(unsigned short y, unsigned short x)
{
    for (unsigned short int i = y+1; i<20; i++)
    {
        if (board.getBoard(i,x)==0)
        {
            return false;
        }
        else
            if (board.getBoard(i,x)==1)
            {
                return true;
                break;
            }
    }
    return true;
}

void MainWindow::calculate()
{
    bool isCalculate = false;
    bool isSand = false;
    bool isRow = false;
    //checking individual points
    for (unsigned short int y=18; y>0; y--)
    {
        for (unsigned short int x=0; x<10; x++)
        {
            if (board.getBoard(y,x)==2)     // if is sand
            {
                if (board.getBoard(y+1,x)==0)
                {
                    board.setBoard(y,x,0);
                    board.setBoard(y+1,x,2);
                    if (isEndOfFalling(y+1,x))
                    {
                        score.add(y+1,x,"100");
                        pointScore+=100;
                    }
                    isCalculate = true;
                    isSand = true;
                }
            }
        }
    }

    //checking the rows
    bool isFullRow;
    for (unsigned short int y=19; y>0; y--)
    {
        isFullRow = true;
        for (unsigned short int x=0; x<10; x++)
        {
            if (board.getBoard(y,x)==0 || (board.getBoard(y,x)==2 && isEndOfFalling(y,x)==false))
            {
                isFullRow = false;
            }
        }
        if (isFullRow)
        {
            score.add(y,5,"800");
            pointScore+=800;
            isCalculate = true;
            isRow = true;
            for (unsigned short int y2=y; y2>0; y2--)
            {
                for (unsigned short int x=0; x<10; x++)
                {
                    board.setBoard(y2,x,board.getBoard(y2-1,x));
                }
            }
        }
    }

    if (isCalculate)
    {
        if (isSand)
        {
            sound.sand();
        }
        if (isRow)
        {
            sound.row();
        }
        showBoard();
        showShape();
        showScores();
        repaint();
    }
}

void MainWindow::calculateScores()
{
    score.go();
    showBoard();
    showShape();
    showScores();
    repaint();
}

void MainWindow::clickSpace()
{
    if (timer.isActive()==false)
    {
        timer.start();
        isFirstStart = false;
        pause = false;
        return;
    }

    if (shape.type()==1)                // shape is pionts
    {
        return;
    }

    bool allowRotate = true;
    unsigned short int tempX = shape.x();

    // -- if the shape is out of range then move and check if it can be rotated
    if (shape.x()+shape.row()>10)
    {
        tempX = 10 - shape.row();
    }
    if (shape.x()<0)
    {
        tempX = 0;
    }

    for (unsigned short int y=0; y<shape.row() ; y++)
    {
        for (unsigned short int x=0; x<shape.row() ; x++)
        {
            if (board.getBoard(shape.y()+y, tempX+x)!=0)
            {
                allowRotate=false;
            }
        }
    }
    if (allowRotate==false)
    {
        return;
    }

    sound.rotate();
    shape.setX(tempX);
    shape.rotateShape();
    showBoard();
    showShape();
    showScores();
    repaint();
}

void MainWindow::clickRight()
{
    bool allowRight = true;
    for (unsigned short int y=0; y<shape.row(); y++)
    {
        for (unsigned short int x=0; x<shape.row(); x++)
        {
            if (shape.getShapeCell(y,x)!=0 && board.getBoard(shape.y()+y,shape.x()+x+1)!=0)
            {
                allowRight = false;
            }
        }
    }
    if (allowRight==false)
    {
        return;
    }

    shape.goRight();
    showBoard();
    showShape();
    showScores();
    repaint();
}

void MainWindow::clickLeft()
{
    bool allowLeft = true;
    for (unsigned short int y=0; y<shape.row(); y++)
    {
        for (unsigned short int x=0; x<shape.row(); x++)
        {
            if (shape.getShapeCell(y,x)!=0 && board.getBoard(shape.y()+y,shape.x()+x-1)!=0)
            {
                allowLeft = false;
            }
        }
    }
    if (allowLeft==false)
    {
        return;
    }

    shape.goLeft();
    showBoard();
    showShape();
    showScores();
    repaint();
}

void MainWindow::clickDown()
{
    if (gameover)
    {
        return;
    }
    if (timer.isActive())
    {
        sound.shape();
        step();
    }
    else
    {
        timer.start();
        pause = false;
    }
}

void MainWindow::clickEsc()
{
    if (gameover)
    {
        return;
    }
    if (pause)
    {
        timer.start();
        pause = false;
    }
    else
    {
        timer.stop();
        sound.pause();
        pause = true;
    }
    showBoard();
    showShape();
    showScores();
    repaint();
}

void MainWindow::changeTheBoards()
{

}
