#ifndef STATEACCOUNT_H
#define STATEACCOUNT_H
#include <istatebase.h>
#include <accountform.h>
#include <Data.h>

class StateAccount: public IStateBase
{
public:
    StateAccount();
    virtual void create();
    virtual void edit(QString key);
    virtual void del(QString key);
};

#endif // STATEACCOUNT_H
