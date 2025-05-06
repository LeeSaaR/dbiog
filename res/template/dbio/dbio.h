/**
 * DBIO IS PART OF DBIO MODULE
 *
 * AUTHOR:  Lisa ( LeeSaaR )
 * URL:     https://leesaar.de
 * REPO:    https://www.github.com/leesaar/dbio
 *
 * ==========================================================
 *
 * DBIO: a database input output system for Qt applications.
 * Copyright (C) 2025  Lisa (LeeSaaR)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
**/
#ifndef DBIO_H
#define DBIO_H

#include "datarowrawlist.h"
#include "datarow.h"
#include "dbioidgenerator.h"
#include <QList>
#include <QString>

class DBIO
{
private:
    inline static QString m_connection = "";
private:
    DBIO(){}
    ~DBIO(){}
protected:
    inline static DBIO *m_instance = nullptr;
public:
    DBIO(DBIO &other) = delete;
    void operator=(const DBIO &) = delete;
    inline static DBIO *get()
    {
        if (m_instance == nullptr)
            m_instance = new DBIO();
        return m_instance;
    }
private:
    QString makeID(DataRow *row);
    void getIDs(DataRow *row, QList<QString> &list_existing_ids);
    void findID(DBIOIDGenerator* id_generator, const QList<QString> &list_existing_ids, const QString &id_format, QString &out_id);
    const QString makeBindValue(const int & i);
public:
    void insert(DataRow *row);
    void update(DataRow *row);
    void update(DataRow *row, DataColumn *target_col);
    void select(DataRow* row);
    void select(DataRow* row, DataRowRawList *outputList, DataColumn *target_col = nullptr);
    void del(DataRow* row);
public:
    inline static QString connection() { return m_connection; }
    inline static void connection(const QString &newConnection) { m_connection = newConnection; }
};

#endif // DBIO_H

