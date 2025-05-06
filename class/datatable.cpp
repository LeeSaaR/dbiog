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
#include "datatable.h"

DataTable::DataTable() {}

void DataTable::setName(const QString &value)
{
    name = value;
}

void DataTable::setPrefix(const QString &value)
{
    prefix = value;
}

void DataTable::setFormatID(const QString &value)
{
    id_format = value;
}

void DataTable::setPrimaryColumn(const Column& col/*const QString &value*/)
{
    primary_column = col.name;
    addColumn(col);
}

void DataTable::addColumn(const Column& col/*const QString &col*/)
{
    columns.append(col);
}

void DataTable::addDependency(const Column &dependency)
{
    deps.append(dependency);
}

const QString DataTable::getName()
{
    return name;
}

const QString DataTable::getFormatID()
{
    return id_format;
}

const QString DataTable::getPrimaryColumn()
{
    return "m_"+primary_column;
}

QString DataTable::makeCreateStatement()
{
    QString out = "        \"CREATE TABLE "+name+" ( \"\n";
    out += makeCreateColumnPrimary();
    Column col;
    foreach (col, columns) {
        if (col.name == columns.first().name) continue;
        out += makeCreateColumn(col.name);
        if (col.name != columns.last().name)
            out += ", \"\n";
        else
            out += " )\"";
    }
    return out;
}

QString DataTable::makeCreateColumnPrimary()
{
    return "        \""+primary_column+" TEXT PRIMARY KEY UNIQUE, \"\n";
}

QString DataTable::makeCreateColumn(const QString &col)
{
    return "        \""+col+" TEXT";
}

QString DataTable::fileNameData()
{
    return prefix.toLower()+"_"+name.toLower()+".h";
}

QString DataTable::includeGuardData()
{
    return prefix.toUpper()+name.toUpper()+"_H";
}

QString DataTable::classNameData()
{
    return toCamel(prefix)+toCamel(name);
}

QString DataTable::classNameData(QString name)
{
    return toCamel(prefix)+toCamel(name);
}

QString DataTable::members()
{
    QStringList out;
    Column col;
    foreach (col, columns) {
        if (col.name != columns.last().name)
            out += makeMemberData(col.name)+"\n";
        else
            out += makeMemberData(col.name);
    }
    return out.join("");
}

QString DataTable::makeMemberData(const QString &col)
{
    return "    DataColumn* "+memberName(col)+";";
}

QString DataTable::memberDefine()
{
    QStringList out;
    Column col;
    foreach (col, columns) {
        if (col.name != columns.last().name)
            out += defineMemberData(col.name)+"\n";
        else
            out += defineMemberData(col.name);
    }
    return out.join("");
}

QString DataTable::defineMemberData(const QString &col)
{
    return "        "+memberName(col)+" = new DataColumn(\""+col+"\"); addCol( "+memberName(col)+" );";
}

/*QString DataTable::columnAppends()
{
    QStringList out;
    Column col;
    foreach (col, columns) {
        if (col.name != columns.last().name)
            out += makeColumnAppend(col.name)+"\n";
        else
            out += makeColumnAppend(col.name);
    }
    return out.join("");
}*/

QString DataTable::makeColumnAppend(const QString &col)
{
    return "        m_columns.append("+memberName(col)+");";
}

QString DataTable::getterData()
{
    QStringList out;
    Column col;
    foreach (col, columns) {
        if (col.name != columns.last().name)
            out += makeGetterData(col)+"\n";
        else
            out += makeGetterData(col);
    }
    return out.join("");
}

QString DataTable::makeGetterData(const Column &col)
{
    if (col.type == "BOOL")
        return "    const bool "+col.name+"() { return toBool( "+memberName(col.name)+"->get() ); }";
    if (col.type == "DOUBLE")
        return "    const double "+col.name+"() { return toDouble( "+memberName(col.name)+"->get() ); }";
    if (col.type == "INT")
        return "    const int "+col.name+"() { return toInt( "+memberName(col.name)+"->get() ); }";
    if (col.type == "DATE")
        return "    const QString "+col.name+"() { return toDate( "+memberName(col.name)+"->get() ); }";
    else if (col.type == "TEXT")
        return "    const QString "+col.name+"() { return "+memberName(col.name)+"->get(); }";
    return "ERROR: makeGetterData()";
}

QString DataTable::setterData()
{
    QStringList out;
    Column col;
    foreach (col, columns) {
        if (col.name != columns.last().name)
            out += makeSetterData(col)+"\n";
        else
            out += makeSetterData(col);
    }
    return out.join("");
}

QString DataTable::makeSetterData(const Column &col)
{
    if (col.type == "BOOL")
        return "    void "+col.name+"(const bool& val, const bool& mkup = false) { "+memberName(col.name)+"->set( fromBool(val) ); if (mkup && inDB()) update( "+memberName(col.name)+" ); }";
    if (col.type == "DOUBLE")
        return "    void "+col.name+"(const double& val, const bool& mkup = false) { "+memberName(col.name)+"->set( fromDouble(val) ); if (mkup && inDB()) update( "+memberName(col.name)+" ); }";
    if (col.type == "INT")
        return "    void "+col.name+"(const int& val, const bool& mkup = false) { "+memberName(col.name)+"->set( fromInt(val) ); if (mkup && inDB()) update( "+memberName(col.name)+" ); }";
    if (col.type == "DATE")
        return "    void "+col.name+"(const QString& val, const bool& mkup = false) { "+memberName(col.name)+"->set( fromDate(val) ); if (mkup && inDB()) update( "+memberName(col.name)+" ); }";
    else if (col.type == "TEXT")
        return "    void "+col.name+"(const QString& val, const bool& mkup = false) { "+memberName(col.name)+"->set( val ); if (mkup && inDB()) update( "+memberName(col.name)+" ); }";
    return "ERROR: makeSetterData()";
}

QString DataTable::getterColumn()
{
    QStringList out;
    Column col;
    foreach (col, columns) {
        if (col.name != columns.last().name)
            out += makeGetterColumn(col.name)+"\n";
        else
            out += makeGetterColumn(col.name);
    }
    return out.join("");
}

QString DataTable::makeGetterColumn(const QString &col)
{
    return "    DataColumn* get_"+col+"() { return "+memberName(col)+"; }";
}

QString DataTable::fileNameList()
{
    return prefix.toLower()+"list_"+name.toLower()+".h";
}

QString DataTable::includeGuardList()
{
    return prefix.toUpper()+"LIST"+name.toUpper()+"_H";
}

QString DataTable::classNameList()
{
    return toCamel(prefix)+"List"+toCamel(name);
}

QString DataTable::classNameList(QString value)
{
    return toCamel(prefix)+"List"+toCamel(value);
}

QString DataTable::memberDefineList()
{
    QStringList out;
    Column col;
    foreach (col, columns) {
        if (col.name != columns.last().name)
            out += makeMemberList(col.name)+"\n";
        else
            out += makeMemberList(col.name);
    }
    return out.join("");
}

QString DataTable::makeMemberList(const QString &col)
{
    return "        "+memberName(col)+" = m_target_data->get_"+col+"();";
}

QString DataTable::setterList()
{
    QStringList out;
    Column col;
    foreach (col, columns) {
        if (col.name != columns.last().name)
            out += makeSetterList(col.name)+"\n";
        else
            out += makeSetterList(col.name);
    }
    return out.join("");
}

QString DataTable::makeSetterList(const QString &col)
{
    return "    void "+col+"(const QString& value) { m_target_col->set(\"\"); "+memberName(col)+"->set(value); m_target_col = "+memberName(col)+"; }";
}

// QString DataTable::includeRecord()
// {
//     return fileNameData();
// }

QString DataTable::memberName(const QString &col)
{
    return "m_"+col;
}

QString DataTable::factoryInclude()
{
    return "#include \""+fileNameData()+"\"";
}

QString DataTable::factoryIncludeList()
{
    return "#include \"datalist_"+name+".h\"";
}


QString DataTable::factoryGetter()
{
    return "    static "+classNameData()+"* "+name+"() { return new "+classNameData()+"(); }";
}

QString DataTable::factoryGetterList()
{
    return "    static "+classNameList()+"* "+name+"_list() { return new "+classNameList()+"(); }";
}

QString DataTable::factoryConnection()
{
    return "        "+classNameData()+"::connection(db_conn);";
}

QString DataTable::factoryConnectionList()
{
    return "        "+classNameList()+"::connection(db_conn);";
}

QString DataTable::depIncludeList(const QString name)
{
    return "#include \"datalist_"+name+".h\"";
}

QString DataTable::dependenciesIncludes()
{
    QStringList out;
    Column dep;
    foreach (dep, deps) {
        if (dep.name != deps.last().name)
            out += depIncludeList(dep.name)+"\n";
        else
            out += depIncludeList(dep.name);
    }
    return out.join("");
}

QString DataTable::makeDependencies()
{
    QStringList out;
    Column dep;
    foreach (dep, deps) {
        if (dep.name != deps.last().name)
            out += makeDependency(dep)+"\n";
        else
            out += makeDependency(dep);
    }
    return out.join("");
}

QString DataTable::makeDependency(const Column &dep)
{
    return
    "        {\n"
    "            "+classNameList(dep.name)+"* list = new "+classNameList(dep.name)+"();\n"
    "            list->"+dep.type+"( "+ getPrimaryColumn() +"->get() );\n"
    "            "+classNameData(dep.name)+"* data;\n"
    "            foreach (data, list->get()) data->del();\n"
    "            delete list;\n"
    "        }"
    ;
}

QString DataTable::makeCmakeData()
{
    return "    ${CMAKE_CURRENT_LIST_DIR}/"+fileNameData();
}

QString DataTable::makeCmakeList()
{
    return "    ${CMAKE_CURRENT_LIST_DIR}/"+fileNameList();
}

QString DataTable::toCamel(const QString &value)
{
    QStringList parts = value.split("_");
    for (QString &part : parts) {
        QString new_part;
        for (int i = 0; i < part.size(); i++) {
            if (i == 0)
                new_part += part[0].toUpper();
            else
                new_part += part[i].toLower();
        }
        part = new_part;
    }
    return parts.join("");
}
