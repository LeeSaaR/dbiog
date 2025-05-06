/**
 * DataTable IS PART OF DBIOG
 *
 * AUTHOR:  Lisa ( LeeSaaR )
 * URL:     https://leesaar.de
 * REPO:    https://www.github.com/leesaar/dbiog
 *
 * ==========================================================
 *
 * DBIOG: a generator for DBIO Qt applications.
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
#ifndef DATATABLE_H
#define DATATABLE_H

#include <QString>
#include <QList>
struct Column;
class DataTable
{
public:
    QString prefix;
    QString name;
    QString id_format;
    QString primary_column;
    QList<Column> columns;
    QList<Column> deps;
public:
    DataTable();
    void setName(const QString& value);
    void setPrefix(const QString& value);
    void setFormatID(const QString& value);
    void setPrimaryColumn(const Column& col);
    void addColumn(const Column& col);
    void addDependency(const Column& dependency);
public:
    const QString getName();
    const QString getFormatID();
    const QString getPrimaryColumn();
    QString makeCreateStatement();
    QString makeCreateColumnPrimary();
    QString makeCreateColumn(const QString& col);

    QString fileNameData();
    QString includeGuardData();
    QString classNameData();
    QString classNameData(QString name);
    QString members();
    QString makeMemberData(const QString& col);
    QString memberDefine();
    QString defineMemberData(const QString& col);
    QString columnAppends();
    QString makeColumnAppend(const QString& col);
    QString getterData();
    QString makeGetterData(const Column& col);
    QString setterData();
    QString makeSetterData(const Column& col);
    QString getterColumn();
    QString makeGetterColumn(const QString& col);

    QString fileNameList();
    QString includeGuardList();
    // QString includeRecord();
    QString classNameList();
    QString classNameList(QString value);
    QString memberDefineList();
    QString makeMemberList(const QString& col);
    QString setterList();
    QString makeSetterList(const QString& col);

    QString memberName(const QString& col);

    QString factoryInclude();
    QString factoryIncludeList();
    QString depIncludeList(const QString name);
    QString factoryGetter();
    QString factoryGetterList();
    QString factoryConnection();
    QString factoryConnectionList();

    QString dependenciesIncludes();
    QString makeDependencies();
    QString makeDependency(const Column& dep);

    QString makeCmakeData();
    QString makeCmakeList();
private:
    QString toCamel(const QString& value);
};
struct Column
{
    QString name;
    QString type;
    Column(){}
    Column(const QString& name,const QString& type) : name(name), type(type) {}
};

#endif // DATATABLE_H
