#ifndef BLACKBOXMISSION_H
#define BLACKBOXMISSION_H
#include "mission.h"
#include <QString>

class BlackBoxMission : public Mission
{
public:
    BlackBoxMission();

    QString baseObjective(QString string);
    QString bonusObjective(QString string);
};

#endif // BLACKBOXMISSION_H
