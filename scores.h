#ifndef SCORES_H
#define SCORES_H
#include <QString>
#include <QVector>
struct oneScore
{
    short int x;
    short int y;
    QString value;
    short int speedX;
    short int speedY;
    unsigned short int gravity;
    unsigned short int lengthLive;
    unsigned short int live;
};

class Scores
{
public:
    Scores();
    void add(short int y, short int x, QString value);
    unsigned short int size();
private:
    QVector <oneScore> score;
};

#endif // SCORES_H
