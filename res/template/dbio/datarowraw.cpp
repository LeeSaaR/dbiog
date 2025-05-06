/**
 * DataRowRaw IS PART OF DBIO MODULE
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
#include "datarowraw.h"

DataRowRaw::DataRowRaw() { }
DataRowRaw::~DataRowRaw()
{
    while (!m_columns.isEmpty()) {
        DataColumn* col = m_columns.last();
        m_columns.removeLast();
        delete col;
    }
}

DataColumn* DataRowRaw::add(const QString &name, const QString &val)
{
    m_columns.append( new DataColumn(name, val) );
    return m_columns.last();
}

QList<DataColumn*> DataRowRaw::columns() 
{
    return m_columns;
}
