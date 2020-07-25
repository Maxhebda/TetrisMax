#include "mainwindow2.h"
#include "ui_mainwindow2.h"

// QString mySprintf(format, arguments);
template<typename ... Args>
QString mySprintf(const char * format,Args ... a)
{
    char scream[255];
    sprintf(scream,format,a ...);
    return scream;
}

MainWindow2::MainWindow2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow2)
{
    ui->setupUi(this);
    //load scores from registry
    savedScores.load();

    //create labels pointer
    for (uint8_t i=0;i<10;i++)
    {
        myLabel[i] = new QLabel(this);
        myLabel[i]->setText(mySprintf("%02d.",i+1));
        myLabel[i]->setGeometry(10,20*i+10,30,20);

        myLabel[i+10] = new QLabel(this);
        myLabel[i+10]->setText(savedScores.getName(i));
        myLabel[i+10]->setGeometry(40,20*i+10,120,20);
        myLabel[i+10]->setAlignment(Qt::AlignRight);

        myLabel[i+20] = new QLabel(this);
        myLabel[i+20]->setText(mySprintf("% 9llu",savedScores.getScore(i)));    // %llu - unsigned long long
        myLabel[i+20]->setGeometry(170,20*i+10,100,20);
        myLabel[i+20]->setAlignment(Qt::AlignRight);
    }
}

MainWindow2::~MainWindow2()
{
    for (uint8_t i=0;i<30;i++)
    {
        delete myLabel[i];
    }
    delete ui;
}


void MainWindow2::on_pushButton_2_clicked()
{
    close();
}

void MainWindow2::on_pushButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Czy na pewno chcesz wyczyścić wszystkie zapisane rekordy?");
    msgBox.setStandardButtons(QMessageBox::Reset | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);

    // reset all scores and save in registry
    if (msgBox.exec()==QMessageBox::Reset)
    {
        savedScores.resetScores();
        for (uint8_t i=0;i<10;i++)
        {
            myLabel[i+10]->setText(savedScores.getName(i));
            myLabel[i+20]->setText(mySprintf("% 9llu",savedScores.getScore(i)));    // %llu - unsigned long long
        }
    }
}
