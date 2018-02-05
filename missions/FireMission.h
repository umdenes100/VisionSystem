#ifndef FIREMISSION_H
#define FIREMISSION_H
#include "mission.h"

class FireMission : public Mission
{
public:
    FireMission();

    QString baseObjective(QString string);
    QString bonusObjective(QString string);
};

#endif // FIREMISSION_H
