#ifndef SCORES_H
#define SCORES_H
#include <QString>
#include <QVector>
struct oneScore
{
    double x;
    double y;
    QString value;
    double speedX;
    double speedY;
    double gravity;
    unsigned short int lengthLive;
    unsigned short int live;
};

class Scores
{
public:
    Scores();
    void add(short int y, short int x, QString value);
    unsigned short int size();
    void go();
    void clear();

    unsigned short int getX(unsigned short int index);
    unsigned short int getY(unsigned short int index);
    QString getValue(unsigned short int index);
private:
    QVector <oneScore> score;
};

#endif // SCORES_H
