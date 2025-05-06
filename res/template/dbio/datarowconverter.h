/**
 * DataRowConverter IS PART OF DBIO MODULE
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
#ifndef DATAROWCONVERTER_H
#define DATAROWCONVERTER_H

#include "datarow.h"
#include "datarowrawlist.h"

#include <QString>
#include <QList>

class T;
class DataRowConverter
{
private:
    DataRowConverter();
public:
    template<class T>
    inline static QList<T*> getType(DataRowRawList *list_row_raw)
    {
        QList<T*> rows;
        DataRowRaw* row_raw;
        foreach (row_raw, list_row_raw->list()) {
            T* row = new T();
            DataColumn *col;
            foreach (col, row_raw->columns())
                row->setColumn(col->name(), col->get());
            row->inDB(true);
            rows.append(row);
        }
        return rows;
    }
};

#endif // DATAROWCONVERTER_H
