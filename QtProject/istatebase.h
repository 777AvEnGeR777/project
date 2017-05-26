#ifndef ISTATEBASE_H
#define ISTATEBASE_H
#include <QString>
#include <Data.h>

class IStateBase
{
public:
    IStateBase() {}

    virtual void create() = 0;
    virtual void edit(QString key) = 0;
    virtual void del(QString key) = 0;
};

#endif // ISTATEBASE_H
