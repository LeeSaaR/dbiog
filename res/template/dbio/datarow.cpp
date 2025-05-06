/**
 * DataRow IS PART OF DBIO MODULE
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
#include "datarow.h"
#include <QDate>

DataRow::DataRow() { }
DataRow::~DataRow()
{
    while (!m_columns.isEmpty()) 
    {
        DataColumn* col = m_columns.last();
        m_columns.removeLast();
        delete col;
    }
}
void DataRow::inDB(const bool& in_db) 
{ 
    m_in_db = in_db; 
}

const bool DataRow::inDB() 
{ 
    return m_in_db; 
}

const QString DataRow::id_tmp() const 
{ 
    return m_id_tmp; 
}

void DataRow::id_tmp(const QString& val) 
{ 
    m_id_tmp = val; 
}

const QString DataRow::fromBool(const bool& val) 
{ 
    return QString::number( (int)val ); 
}

const QString DataRow::fromInt(const int& val) 
{ 
    return QString::number( val ); 
}

const QString DataRow::fromDouble(const double& val) 
{ 
    return QString::number( val, 'f', 2 ); 
}

const QString DataRow::fromDate(const QString &val)
{
    return QDate::fromString( val, "dd.MM.yyyy" ).toString("yyyy-MM-dd");
}

const bool DataRow::toBool(const QString& val) 
{ 
    return (bool)val.toInt(); 
}

const int DataRow::toInt(const QString& val) 
{ 
    return val.toInt(); 
}

const double DataRow::toDouble(const QString& val)  
{ 
    return val.toDouble(); 
}

const QString DataRow::toDate(const QString &val)
{
    return QDate::fromString( val, "yyyy-MM-dd" ).toString("dd.MM.yyyy");
}

DataColumn* DataRow::ID() 
{
    return nullptr;
}

void DataRow::setColumn(const QString &name, const QString &value)
{
    DataColumn *col;
    foreach (col, m_columns) {
        if (col->name() == name) {
            col->set(value);
            return;
        }
    }
}

void DataRow::table(const QString &val) 
{ 
    m_table = val; 
}

QString DataRow::table() const 
{ 
    return m_table; 
}

void DataRow::addCol(DataColumn * col)
{ 
    m_columns.append(col); 
}

QList<DataColumn *> DataRow::columns()
{ 
    return m_columns; 
}

const QString DataRow::id_format() const 
{ 
    return m_id_format; 
}

void DataRow::id_format(const QString& val) 
{ 
    m_id_format = val; 
}

