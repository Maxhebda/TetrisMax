#include "scores.h"

Scores::Scores()
{

}

unsigned short int Scores::size()
{
    return score.size();
}

void Scores::add(QString value)
{
    ScoresCell temp(value);
    score.push_back(temp);
}

void Scores::step()
{
    for (auto iter = score.begin(); iter!=score.end(); iter++)
    {
        iter->go();
        if (iter->itsDead())
        {
            score.erase(iter);
        }
    }
}
