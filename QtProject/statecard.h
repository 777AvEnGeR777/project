#ifndef STATECARD_H
#define STATECARD_H
#include "statebase.h"
#include "cardform.h"
#include <Data.h>

class StateCard: public StateBase
{
public:
    StateCard();

    virtual void create();
    virtual void edit(QString key);
    virtual void build();
    virtual void del(QString key);
    virtual void save();
};

#endif // STATECARD_H
