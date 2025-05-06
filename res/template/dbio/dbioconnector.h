/**
 * DBIOConnector IS PART OF DBIO MODULE
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
#ifndef DBIOCONNECTOR_H
#define DBIOCONNECTOR_H

#include "dbiomodel.h"

class DBIOConnector
{

private:
    DBIOConnector();
protected:
    inline static DBIOConnector *m_instance = nullptr;
public:
    DBIOConnector(DBIOConnector &other) = delete;
    void operator=(const DBIOConnector &other) = delete;
    inline static DBIOConnector *get()
    {
        if (m_instance == nullptr)
            m_instance = new DBIOConnector();
        return m_instance;
    }
    ~DBIOConnector();
public:
    bool createDatabase(const QString & filename, const QString &connection, DBIOModel *model);
    void updateDatabase(const QString &connection, DBIOModel *model);
    bool connectDatabase(const QString & filename, const QString &connection);
    bool disconnectDatabase(const QString &connection);
};

#endif // DBIOCONNECTOR_H
