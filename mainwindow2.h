#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <QMainWindow>
#include "myregistry.h"
#include <QLabel>
#include <QVector>
#include <QMessageBox>


namespace Ui {
class MainWindow2;
}

class MainWindow2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow2(QWidget *parent = nullptr);
    ~MainWindow2();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow2 *ui;
    MyRegistry savedScores;     // recorded results in the register
    QLabel * myLabel[30];
};

#endif // MAINWINDOW2_H
