#include "scores.h"
#include "QtDebug"

Scores::Scores()
{

}

void Scores::add(short int y, short int x, QString value)
{
    oneScore tmp;
    tmp.x = x;
    tmp.y = y;
    tmp.value = value;
    tmp.speedX = 10;
    tmp.speedY = 10;
    tmp.gravity = 5;
    tmp.live = 0;
    tmp.lengthLive = 20;
    score.push_back(tmp);
    qDebug() << "dodano " << x << ", " << y << "razem=" << score.size();
}

unsigned short int Scores::size()
{
    return score.size();
}
