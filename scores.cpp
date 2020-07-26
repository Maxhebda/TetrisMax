#include "scores.h"
#include <ctime>
#include <stdlib.h>

Scores::Scores()
{
    srand(time(NULL));
}

void Scores::add(short int y, short int x, QString value)
{
    oneScore tmp;
    tmp.x = 16+33*x;
    tmp.y = 27+33*y;
    tmp.value = value;
    tmp.speedX = rand()%11+10;          //speedY --> 10..20

    if (x>2 && x<8)
    {
        if (rand()%2==0) tmp.speedX*=-1;
    }
    else
        if (x>=8)
        {
            tmp.speedX*=-1;
        }
    if (tmp.y>7)
    {
        tmp.speedY = rand()%11-20;      //speedY --> -20..-10
    }
    else
    {
        tmp.speedY = rand()%6-10;      //speedY --> -10..-5
    }
    tmp.gravity = (rand()%11+20)/5;    //g --> 4..6
    tmp.live = 0;
    tmp.lengthLive = 10;
    score.push_back(tmp);
}

unsigned short int Scores::size()
{
    return score.size();
}

unsigned short int Scores::getX(unsigned short int index)
{
    if (score.size()==0 || index<0 || index>=score.size())
    {
        return -1;
    }
    return score[index].x;
}

unsigned short int Scores::getY(unsigned short int index)
{
    if (score.size()==0 || index<0 || index>=score.size())
    {
        return -1;
    }
    return score[index].y;
}

QString Scores::getValue(unsigned short int index)
{
    if (score.size()==0 || index<0 || index>=score.size())
    {
        return "";
    }
    return score[index].value;
}

void Scores::go()
{
    QVector <unsigned short int> toDelete;
    for(unsigned short int iter = 0; iter < score.size(); iter++)
    {
        score[iter].live++;
        score[iter].x+=score[iter].speedX;
        if (score[iter].x<=10)
        {
            score[iter].x=10;
            score[iter].speedX*=-1;
        }
        if (score[iter].x>=320)
        {
            score[iter].x=320;
            score[iter].speedX*=-1;
        }
        score[iter].y+=score[iter].speedY;
        if (score[iter].y>660)
        {
            score[iter].y=660;
            score[iter].live = score[iter].lengthLive; //kill
        }
        if (score[iter].y<5)
        {
            score[iter].y=5;
        }
        score[iter].speedY+=score[iter].gravity;
        if (score[iter].live>=score[iter].lengthLive)
        {
            toDelete.push_front(iter);
        }
    }
    if (toDelete.size()==0)
    {
        return;
    }
    for (auto i = toDelete.begin(); i!=toDelete.end(); i++)
    {
        score.remove(*i);
    }
}

void Scores::clear()
{
    score.clear();
}
