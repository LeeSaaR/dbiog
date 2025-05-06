/**
 * THIS FILE WAS GENERATED WITH DBIOG
 * REPO:    https://www.github.com/leesaar/dbiog
**/
#ifndef <INCLUDEGUARD>
#define <INCLUDEGUARD>

#include <QString>
#include <QList>

#include "dbiomodel.h"

class <CLASSNAME> : public DBIOModel
{
private:
    <CLASSNAME>(){}
    ~<CLASSNAME>(){}

protected:
    static <CLASSNAME> *m_instance;

public:
    <CLASSNAME>(<CLASSNAME> &other) = delete;
    void operator=(const <CLASSNAME> &) = delete;
    static <CLASSNAME> *get()
    {
        if (m_instance == nullptr)
            m_instance = new <CLASSNAME>();
        return m_instance;
    }
    virtual const QList<QString> createStatements() const override
    {
        return {
<CREATE_STATEMENT>
        };
    }
    virtual const QList<QString> updateStatements() const override
    {
        return {
        };
    }
};

inline <CLASSNAME>* <CLASSNAME>::m_instance= nullptr;

#endif // <INCLUDEGUARD>
