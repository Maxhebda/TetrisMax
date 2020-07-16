#ifndef MYSOUNDS_H
#define MYSOUNDS_H
#include <QtMultimedia/QSound>

class MySounds
{
public:
    MySounds();
    ~MySounds();
    void click();
    void shape();
    void sand();
    void row();
    void rotate();
    void pause();
    void gameover();

private:
    QSound * sClick;
    QSound * sShape;
    QSound * sSand;
    QSound * sRow;
    QSound * sRotate;
    QSound * sPause;
    QSound * sGameover;
};

#endif // MYSOUNDS_H
