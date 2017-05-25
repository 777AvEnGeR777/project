#ifndef STATEACCOUNT_H
#define STATEACCOUNT_H
#include <statebase.h>
#include <accountform.h>

class StateAccount: public StateBase
{
public:
    StateAccount();
    virtual void create();
    virtual void edit(QString key);
    virtual void build();
    virtual void del();
    virtual void save();
};

#endif // STATEACCOUNT_H
