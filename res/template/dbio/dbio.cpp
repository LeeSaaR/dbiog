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

#include "dbio.h"
#include "dbioidgenerator.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlField>
#include <QMap>

QString DBIO::makeID(DataRow *row)
{
    QList<QString> existing_ids;
    getIDs(row, existing_ids);

    QString out_id;
    findID(DBIOIDGenerator::get(), existing_ids, row->id_format(), out_id);
    return out_id;
}

void DBIO::getIDs(DataRow *row, QList<QString> &list_existing_ids)
{
    QSqlQuery query(QSqlDatabase::database(connection()));
    query.exec("SELECT "+ row->ID()->name() +" FROM "+ row->table());
    // qDebug() << query.lastError();

    query.previous();
    if (!query.next()) return;

    // set data
    query.first(); query.previous();
    while (query.next())
        list_existing_ids.append(query.value(row->ID()->name()).toString());

    query.finish();
}

void DBIO::findID(DBIOIDGenerator* id_generator, const QList<QString> &list_existing_ids, const QString &id_format, QString &out_id)
{
    /**
     *  recursive call
     *  if id exists this method calls itself again
    */
    out_id = id_generator->generate(id_format);
    if (list_existing_ids.contains(out_id))
        findID(id_generator, list_existing_ids, id_format, out_id);
}

const QString DBIO::makeBindValue(const int &i)
{
    /**
     * Assuming there are less than 99 columns in the table,
     * we hardcode the value to 10.
    */

    const QString value = (i < 10) ? ":val0"+ QString::number(i) : ":val"+ QString::number(i);
    return value;
}

void DBIO::insert(DataRow *row)
{
    QSqlQuery query(QSqlDatabase::database(connection()));

    // generate ID
    row->ID()->set(makeID(row));

    QStringList keys;
    QStringList values;

    DataColumn *col;
    foreach (col, row->columns()) {
        keys.append(col->name());
        values.append(col->getQuoted());
    }

    const QString query_string = "INSERT INTO "+ row->table() +" ("+ keys.join(", ") +") VALUES ("+ values.join(", ") +")";
    query.exec(query_string);
    // qDebug() << query.lastError();
    query.finish();
}

void DBIO::update(DataRow *row)
{
    QSqlQuery query(QSqlDatabase::database(connection()));

    QStringList query_records;
    QMap<QString, QString> bind_values;

    int i = 0;
    DataColumn *col;
    foreach (col, row->columns()) {
        // generate bind value
        const QString value = makeBindValue(i);

        /**
         * Create a map for bind values that looks like:
        * bind_map[":val00"] = "value0"
        * bind_map[":val01"] = "value1" etc.
        */

        bind_values[value] = col->get();
        /**
         * Create a StringList for SET section like
         * "keyname0" = :val00
         * "keyname1" = :val01
        */

        query_records.append(col->name() +" = "+ value);
        i++;
    }

    // consolidate prepare
    const QString prepare_part_1  = "UPDATE "+ row->table() +" SET ";
    const QString prepare_part_2 = query_records.join(", ");
    QString prepare_part_3;
    prepare_part_3 = " WHERE "+ row->ID()->name() +" = "+row->ID()->getQuoted();

    const QString prepare = prepare_part_1 + prepare_part_2 + prepare_part_3;
    query.prepare(prepare);
    //qDebug() << query.lastError();

    // bind the values
    QMapIterator<QString, QString> bind_map(bind_values);
    while (bind_map.hasNext()) {
        bind_map.next();
        query.bindValue(bind_map.key(), bind_map.value());
    }

    query.exec();
    //qDebug() << query.lastError();
    query.finish();
}

void DBIO::update(DataRow *row, DataColumn *target_col)
{
    QSqlQuery query(QSqlDatabase::database(connection()));
    const QString prepare_set = "SET "+target_col->name() +" = :val";

    QString prepare_where = "WHERE "+row->ID()->name() +" = "+ row->ID()->getQuoted();

    const QString prepare = "UPDATE "+ row->table() +" "+ prepare_set +" "+ prepare_where;
    query.prepare(prepare);
    // qDebug() << query.lastError();
    query.bindValue(":val", target_col->get());
    query.exec();
    // qDebug() << query.lastError();
    query.finish();
}

void DBIO::select(DataRow* row)
{
    QSqlQuery query(QSqlDatabase::database(connection()));
    QString query_string;
    query_string = "SELECT * FROM "+row->table()+" WHERE "+row->ID()->name()+" = "+row->ID()->getQuoted();

    query.exec(query_string);
    // qDebug() << query.lastError();
    query.previous();
    if (!query.next()) return;

    // set data
    query.first();
    for (int i = 0; i < query.record().count(); i++)
        row->setColumn(query.record().fieldName(i),query.value(i).toString());

    query.finish();
    // qDebug() << query.lastError();
}

void DBIO::select(DataRow *row, DataRowRawList *output_list, DataColumn *target_col)
{
    QSqlQuery query(QSqlDatabase::database(connection()));
    QString query_string;
    if (target_col == nullptr) {
        query_string = "SELECT * FROM "+row->table();
    }
    else {
        query_string = "SELECT * FROM "+ row->table() +" WHERE "+ target_col->name() +" = "+ target_col->getQuoted();
    }

    query.exec(query_string);
    // qDebug() << query.lastError();

    query.previous();
    if (!query.next()) return;

    query.first(); query.previous();

    // set data
    while (query.next()) {
        DataRowRaw *raw_row = output_list->add();
        for (int i = 0; i < query.record().count(); i++){
            const QString name  = query.record().fieldName(i);
            const QString value = query.value(i).toString();
            raw_row->add(name, value);
        }
    }
    query.finish();
    // qDebug() << query.lastError();
}

void DBIO::del(DataRow *row)
{
    QSqlQuery query(QSqlDatabase::database(connection()));
    QString query_string = "DELETE FROM "+ row->table() +" WHERE "+ row->ID()->name() +" = "+row->ID()->getQuoted();

    query.exec(query_string);
    // qDebug() << query.lastError();
    query.finish();
}

