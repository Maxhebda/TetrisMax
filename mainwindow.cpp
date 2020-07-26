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
    bestResultsWindows = new MainWindow2(this);
    bestResultsWindows->setWindowFlag(Qt::WindowFullscreenButtonHint);
    savedScores.load();         // refresh hight score from registry
    writeNameIfYouWin(false);   // reset write name window

    // -- set menu connections
    connect(ui->actionNowa_gra,SIGNAL(triggered()), this, SLOT(clickNowaGra()));
    connect(ui->action_Latwa,SIGNAL(triggered()), this, SLOT(clickLatwa()));
    connect(ui->actionTrudnaUP,SIGNAL(triggered()), this, SLOT(clickTrudnaUp()));
    connect(ui->actionTrudnaMove,SIGNAL(triggered()), this, SLOT(clickTrudnaMove()));
    connect(ui->actionUpiorny,SIGNAL(triggered()), this, SLOT(clickUpiorna()));
    connect(ui->actionO_aplikacji,SIGNAL(triggered()), this, SLOT(clickOAplikacji()));
    connect(ui->actionNajlepsze_wyniki,SIGNAL(triggered()), this, SLOT(clickWyniki()));

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
    delete bestResultsWindows;
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
    if (blockAppforWriteName)
    {
        return;
    }
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
    blockAppforWriteName = false;
    gameover = false;
    pause = false;
    pointScore = 0;
    ui->label_2->setText("0");
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
    ui->label_4->setText("łatwy");
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
    ui->label_4->setText("trudny up (+1500)");
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
    ui->label_4->setText("trudny left (+1000)");
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
    ui->label_4->setText("upiorny (+3200)");
}

void MainWindow::step()
{
    if (gameover || blockAppforWriteName)
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
            switch (difficultyLevel) {
                case 1 : {
                    score.add(19,4,"500");
                    score.add(19,5,"500");
                    score.add(19,6,"500");
                    pointScore+=1500;
                    break;
                }
                case 2 : {
                    score.add(19,4,"500");
                    score.add(19,5,"500");
                    pointScore+=1000;
                    break;
                }
                case 3 : {
                    score.add(19,3,"800");
                    score.add(19,4,"800");
                    score.add(19,5,"800");
                    score.add(19,6,"800");
                    pointScore+=3200;
                    break;
                }
            }
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
    if (gameover)
    {
        writeNameIfYouWin(true);
        blockAppforWriteName = true;
    }
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

void MainWindow::writeNameIfYouWin(bool show)
{
    if (show==false)
    {
        blockAppforWriteName = false;
        ui->label_5->setStyleSheet("QLabel { color : white; }");
        ui->label_5->setVisible(false);
        ui->pushButton->setVisible(false);
        ui->pushButton_2->setVisible(false);
        ui->lineEdit->setVisible(false);
        ui->lineEdit->setEnabled(false);
        return;
    }

    for (uint8_t var = 0; var < 10; var++) {
        if (pointScore>savedScores.getScore(var))
        {
            // if is new best scores
            const QRect rectangle = QRect(75, 355, 207, 120);
            paintOnImage->fillRect(rectangle,QColor(055,055,055));
            ui->lineEdit->setText("gracz");
            ui->lineEdit->setSelection(0,5);
            ui->label_5->setVisible(true);
            ui->label_5->setText(mySprintf("Brawo! %d miejsce. Wpisz imię :", var+1));
            ui->pushButton->setVisible(true);
            ui->pushButton_2->setVisible(true);
            ui->lineEdit->setVisible(true);
            ui->lineEdit->setEnabled(true);
            ui->lineEdit->selectionChanged();
            break;
        }
    }
}

void MainWindow::clickSpace()
{
    if (gameover || blockAppforWriteName)
    {
        return;
    }

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
    if (gameover || blockAppforWriteName)
    {
        return;
    }

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
    if (gameover || blockAppforWriteName)
    {
        return;
    }
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
    if (gameover || blockAppforWriteName)
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
    if (gameover || blockAppforWriteName)
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

void MainWindow::clickOAplikacji()
{

}

void MainWindow::clickWyniki()
{
    bestResultsWindows->refresh();
    bestResultsWindows->show();
    savedScores.load();
}

void MainWindow::changeTheBoards()
{
    // -- go up when difficultyLevel = TrudnyUp or Upiorny
    if (difficultyLevel==1 || difficultyLevel==3)
    {
        for (unsigned short int y=0; y<19 ; y++)
        {
            for (unsigned short int x=0; x<10 ; x++)
            {
                board.setBoard(y,x,board.getBoard(y+1,x));
            }
        }
        bool noZero=true;
        uint8_t random;
        while (noZero)
        {
            for (unsigned short int x=0; x<10 ; x++)
            {
                random = rand()%5==0?0:rand()%2+1;
                if (random==0)
                {
                    noZero = false;
                }
                board.setBoard(19,x,random);
            }
        }
    }

    // -- go up when difficultyLevel = TrudnyMove or Upiorny
    if (difficultyLevel==2 || difficultyLevel==3)
    {
        unsigned short int tmp;
        for (unsigned short int y=0; y<20 ; y++)
        {
            tmp = board.getBoard(y,0);
            for (unsigned short int x=0; x<9 ; x++)
            {
                board.setBoard(y,x,board.getBoard(y,x+1));
            }
            board.setBoard(y,9,tmp);
        }
    }
}

void MainWindow::on_pushButton_2_clicked()  // click Anuluj in "write name windows"
{
    writeNameIfYouWin(false);
    score.clear();
    timer.stop();

    showBoard();
    showShape();
    showScores();
    repaint();
}

void MainWindow::on_pushButton_clicked()    // click Zapisz in "write name windows"
{
    savedScores.add(pointScore,ui->lineEdit->text());
    writeNameIfYouWin(false);
    score.clear();
    timer.stop();

    showBoard();
    showShape();
    showScores();
    repaint();
}
