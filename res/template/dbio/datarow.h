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
#ifndef DATAROW_H
#define DATAROW_H
/*
 * DataRow is the base class of all derived DataRow classes.
 * DatabaseIO doesn't know how to process a derived DataRow,
 * so the derived class is implicitly casted to the DataRow base class.
 *
 * For each table in the database you create a class
 * that derives from DataRow, with DatabaseIO-Generator (dbiog):
 * To use DatabaseIO-Generator see: https://www.github.com/leesaar/dbio-generator
**/

#include "datacolumn.h"

#include <QString>
#include <QMap>

class DataRow
{
private:
    /*
     * The name of the table.
     */
    QString m_table;

    /*
     * ID Format of the table's primary key.
     * C gets one of the characters defined in IDGenerator's m_id_characters
     * N gets one of the numbers defined in IDGenerator's m_id_characters
     * Other characters are not replaced
     * example formats:
     * "CCNN" could generate -> iB90 or Ta73 etc.
     * "CN-CN" could generate -> h5-e3 or Z1-g8 etc.
     * the primary key id is generated automaticly in DatabaseIO
     * before inserting to database.
    */
    QString m_id_format;

protected:
    /*
     * All DataFields of the specific DataRecord as a list
    */
    QList<DataColumn*> m_columns;
public:
    DataRow();
    virtual ~DataRow();
public:
    friend class DBIO;
    friend class DataRowConverter;
    friend class DBF;
protected:
    bool m_in_db = false;
    void inDB(const bool& in_db);
public:
    const bool inDB();
protected:
    QString m_id_tmp;
public:
    const QString id_tmp() const;
    void id_tmp(const QString& val);
protected:
    const QString fromBool(const bool& val);
    const QString fromInt(const int& val);
    const QString fromDouble(const double& val);
    const QString fromDate(const QString& val);
protected:
    const bool toBool(const QString& val);
    const int toInt(const QString& val);
    const double toDouble(const QString& val);
    const QString toDate(const QString& val);
protected:
    /*
     * ID() is a pointer to the primary key DataField:
     * When you derive from DataRecord e.g. DataRecordUsers
     * and the primary key is:
     * DataField *id = new DataField("ID");
     *
     * be sure to override this like:
     *
     * DataField* ID() override { return id; }
    */
    virtual DataColumn* ID();

    /*
     * Method for development purposes
     * prints the DataFields' Names and Values
    */
private:
    /*
     * This is used when we need to transfer data from
     * existing DataField to specific DataRecords' DataField.
     */
    void setColumn(const QString &name, const QString &value);

protected:
    void table(const QString &val);
protected:
    // GETTER & SETTER
    QString table() const;
    void addCol(DataColumn * col);
    QList<DataColumn *> columns();
public:
    const QString id_format() const;
    void id_format(const QString& val);
};

#endif // DATAROW_H
