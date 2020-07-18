#ifndef SCORES_H
#define SCORES_H
#include <scorescell.h>
#include <QVector>
#include <QString>

class Scores
{
public:
    Scores();
    unsigned short int size();
    void add(QString value);
    void step();
private:
    QVector<ScoresCell> score;
};

#endif // SCORES_H
