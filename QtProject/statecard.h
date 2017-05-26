#ifndef STATECARD_H
#define STATECARD_H
#include "istatebase.h"
#include "cardform.h"
#include <Data.h>

class StateCard: public IStateBase
{
public:
    StateCard();

    virtual void create();
    virtual void edit(QString key);
    virtual void del(QString key);
};

#endif // STATECARD_H
