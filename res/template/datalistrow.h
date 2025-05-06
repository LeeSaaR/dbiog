/**
 * THIS FILE WAS GENERATED WITH DBIOG
 * REPO:    https://www.github.com/leesaar/dbiog
**/
#ifndef <INCLUDEGUARD>
#define <INCLUDEGUARD>

#include "<INCLUDE>"
#include "dbio.h"
#include "datarowconverter.h"
#include "datarowrawlist.h"
#include <QList>

class <CLASSNAME>
{
private:
    /*
     *  The current database connection string
     */
    static QString m_connection;
private:
    <CLASS_DATARECORD>* m_target_data = nullptr;
    DataColumn* m_target_col = nullptr;

    // TARGET COLUMNS
<MEMBER_DECLARE>
public:
    <CLASSNAME>() {
        m_target_data = new <CLASS_DATARECORD>();

        // DEFINE TARGET COLUMNS
<MEMBER_DEFINE>
        
        // DEFAULT TARGET COLUMN
        m_target_col = <PRIMARYKEY>;
    }
    ~<CLASSNAME>() { delete m_target_data; }
private:
    static void setConnection(const QString& db_conn) { m_connection = db_conn; }
    static QString getConnection() { return m_connection; }
public:
    static void connection(const QString& db_conn) { setConnection(db_conn); }
public:
    QList<<CLASS_DATARECORD>*> all() {
        DBIO::connection( getConnection() );
        DBIO* db = DBIO::get();
        DataRowRawList* raw_list = new DataRowRawList();
        db->select(m_target_data, raw_list);
        QList<<CLASS_DATARECORD>*> list = DataRowConverter::getType<<CLASS_DATARECORD>>(raw_list);
        delete raw_list;
        return list;
    }
    QList<<CLASS_DATARECORD>*> get() {
        DBIO::connection( getConnection() );
        DBIO* db = DBIO::get();
        DataRowRawList* raw_list = new DataRowRawList();
        db->select(m_target_data, raw_list, m_target_col);
        QList<<CLASS_DATARECORD>*> list = DataRowConverter::getType<<CLASS_DATARECORD>>(raw_list);
        delete raw_list;
        return list;
    }
public:
<SETTERS>
};

inline QString <CLASSNAME>::m_connection;

#endif // <INCLUDEGUARD>