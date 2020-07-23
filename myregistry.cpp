#include "myregistry.h"

// QString mySprintf(format, arguments);
template<typename ... Args>
QString mySprintf(const char * format,Args ... a)
{
    char scream[255];
    sprintf(scream,format,a ...);
    return scream;
}

MyRegistry::MyRegistry()
{
    settings = new QSettings("MaxHebda", "TertisMax");
    if (dataScore.isEmpty())
    {
        MyData tmp;
        for (uint8_t i=0; i<10 ; i++)
        {
            tmp.name = "---";
            tmp.pointScore = 0;
            dataScore.push_back(tmp);
        }
    }
}

MyRegistry::~MyRegistry()
{
    delete settings;
}

void MyRegistry::load()
{
    dataScore.clear();
    MyData tmp;
    for (uint8_t i=0; i<10 ; i++)
    {
        tmp.name = settings->value(mySprintf("wyniki/%d/name",i+1),"---").toString();
        tmp.pointScore = settings->value(mySprintf("wyniki/%d/score",i+1),0).toUInt();
        dataScore.push_back(tmp);
    }
}

void MyRegistry::save()
{
    for (uint8_t i=0; i<10 ; i++)
    {
        settings->setValue(mySprintf("wyniki/%d/name",i+1),dataScore[i].name);
        settings->setValue(mySprintf("wyniki/%d/score",i+1),dataScore[i].pointScore);
    }
    settings->sync();
}

QString MyRegistry::getName(uint8_t index)
{
    if (index<dataScore.size())
    {
        return dataScore[index].name;
    }
    else
        return "---";
}

unsigned long int MyRegistry::getScore(uint8_t index)
{
    if (index<dataScore.size())
    {
        return dataScore[index].pointScore;
    }
    else
        return 0;
}
