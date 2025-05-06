/**
 * THIS FILE WAS GENERATED WITH DBIOG
 * REPO:    https://www.github.com/leesaar/dbiog
**/
#ifndef <INCLUDEGUARD>
#define <INCLUDEGUARD>

#include "datarow.h"
#include "dbio.h"
<INCLUDE_DEPS>

class <CLASSNAME> : public DataRow
{
private:
    /*
     *  The current database connection string
     */
    static QString m_connection;
    
<MEMBER_DECLARE>
public:
    <CLASSNAME>() {
        // set base class members
        table("<TABLENAME>");
        id_format("<IDFORMAT>");

        // define data
<MEMBER_DEFINE>
    }
    ~<CLASSNAME>() {}
    friend class <CLASSNAMEDATALIST>;
private:
    void deleteDependencies()
    {
<DEPENDENCIES>
    }
protected:
    virtual DataColumn* ID() override { return <PRIMARYKEY>; }
private:
    static void setConnection(const QString& db_conn) { m_connection = db_conn; }
    static QString getConnection() { return m_connection; }
public:
    static void connection(const QString& db_conn) { setConnection(db_conn); }
public:
    void insert(){ DBIO::connection( getConnection() ); DBIO::get()->insert(this); inDB(true); }
    void select(){ DBIO::connection( getConnection() ); DBIO::get()->select(this); inDB(true); }
    void update(){ DBIO::connection( getConnection() ); DBIO::get()->update(this); }
    void del()   { deleteDependencies(); DBIO::connection( getConnection() ); DBIO::get()->del(this); }
private:
    void update(DataColumn* col){ DBIO::connection( getConnection() ); DBIO::get()->update(this, col); }
public:
<GETTERS>
public:
<SETTERS>
private:
<GETTER_COLUMNS>
};

inline QString <CLASSNAME>::m_connection;

#endif // <INCLUDEGUARD>