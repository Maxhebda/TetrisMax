#ifndef MYREGISTRY_H
#define MYREGISTRY_H
// write or read variables to the register

#include <QString>
#include <QVector>
#include <QSettings>

struct MyData{
    QString name;
    unsigned int pointScore;
};

class MyRegistry
{
public:
    MyRegistry();
    ~MyRegistry();
    void load();
    void save();
    QString getName(uint8_t index);
    unsigned long int getScore(uint8_t index);
    void set(QString key, QString value);
private:
    QVector<MyData> dataScore;
    QSettings * settings;
};

#endif // MYREGISTRY_H
