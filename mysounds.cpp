#include "mysounds.h"

MySounds::MySounds()
{
    sClick = new QSound(":/sounds/click.wav");
    sShape = new QSound(":/sounds/shape.wav");
    sSand = new QSound(":/sounds/sand.wav");
    sRow = new QSound(":/sounds/row.wav");
    sRotate = new QSound(":/sounds/rotate.wav");
        sPause = new QSound(":/sounds/pause.wav");
        sGameover = new QSound(":/sounds/gameover.wav");
}

MySounds::~MySounds()
{
    delete sClick;
    delete sShape;
    delete sSand;
    delete sRow;
    delete sRotate;
    delete sPause;
    delete sGameover;
}

void MySounds::click()
{
    sClick->play();
}

void MySounds::shape()
{
    sShape->play();
}

void MySounds::sand()
{
    sSand->play();
}

void MySounds::row()
{
    sRow->play();
}

void MySounds::rotate()
{
    sRotate->play();
}

void MySounds::pause()
{
    sPause->play();
}

void MySounds::gameover()
{
    sGameover->play();
}
