/**
 * Generator IS PART OF DBIOG
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
#include "generator.h"

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

Generator::Generator()
{
    init();
}

Generator::~Generator()
{
    resetListTables();
}

void Generator::init()
{
    list_files_dbio
        << "dbio.h"
        << "dbio.cpp"
        << "dbioconnector.h"
        << "dbioconnector.cpp"
        << "dbioidgenerator.h"
        << "dbioidgenerator.cpp"
        << "dbiomodel.h"
        << "dbiomodel.cpp"
        << "datacolumn.h"
        << "datacolumn.cpp"
        << "datarow.h"
        << "datarow.cpp"
        << "datarowconverter.h"
        << "datarowconverter.cpp"
        << "datarowraw.h"
        << "datarowraw.cpp"
        << "datarowrawlist.h"
        << "datarowrawlist.cpp"
        << "dbio.cmake"
        << "LICENSE.txt"
        << "README.md"
        ;
}

void Generator::resetListTables()
{
    while (!list_tables.isEmpty()) {
        auto table = list_tables.last();
        list_tables.removeLast();
        delete table;
    }
}

void Generator::setDirSource(const QString &dir)
{
    dir_source = dir;
}

QString Generator::getTemplate(const QString &file_name)
{
    QFile file(file_name);

    if (!file.open(QTextStream::ReadOnly | QTextStream::Text)) {
        qDebug() << "can't open file";
        return "";
    }

    const QString template_content = file.readAll();
    file.close();
    return template_content;
}

QString Generator::toCamel(QString file_name)
{
    QStringList parts = file_name.split("_");
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

QString Generator::model_class_file(const QString &json_file)
{
    QString classname = "DBModel"+toCamel(QFileInfo(json_file).baseName());
    classname.remove("-mod");
    return "    ${CMAKE_CURRENT_LIST_DIR}/"+classname.toLower()+".h";
}

void Generator::readJsonModel(const QString &json_file)
{
    if (!QFile::exists(json_file)) return;
    QFile file(json_file);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QString raw_json = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(raw_json.toUtf8());
    QJsonObject obj = doc.object();
    QStringList l_tables = obj.keys();
    QString name_table;
    foreach (name_table, l_tables) {
        DataTable* table = new DataTable();
        QJsonObject obj_table = obj.value(name_table).toObject();

        table->setName(name_table);
        table->setPrefix("Data");
        table->setFormatID(obj_table.value("id_form").toString());

        QJsonObject p_key = obj_table.value("primary_key").toObject();
        QString key;
        foreach (key, p_key.keys())
            table->setPrimaryColumn( Column(key, p_key.value(key).toString()) );

        QJsonArray columns = obj_table.value("columns").toArray();
        QJsonValue c;
        foreach (c, columns) {
            QJsonObject col = c.toObject();
            foreach (key, col.keys())
                table->addColumn( Column(key, col.value(key).toString()) );
        }

        QJsonArray deps = obj_table.value("dependencies").toArray();
        QJsonValue d;
        foreach (d, deps) {
            QJsonObject col = d.toObject();
            foreach (key, col.keys())
                table->addDependency( Column(key, col.value(key).toString()) );
        }

        list_tables.append(table);
    }
}

void Generator::writeDatabaseModel(const QString& json_file)
{
    QString file_name = QFileInfo(json_file).baseName();
    file_name.remove("-mod");
    model_class_name = "DBModel"+toCamel(file_name);
    model_file_name = model_class_name.toLower();

    QString classname = model_class_name;
    const QString include_guard = classname.toUpper()+"_H";

    QString header = getTemplate(":/template/databasemodel.h");

    header.replace("<INCLUDEGUARD>", include_guard);
    header.replace("<CLASSNAME>", classname);

    QString create_statements;
    DataTable* table;
    foreach (table, list_tables) {
        create_statements += table->makeCreateStatement();
        if (table != list_tables.last())
            create_statements += ",\n\n";
    }

    header.replace("<CREATE_STATEMENT>", create_statements);

    const QString header_name = classname.toLower()+".h";
    writeFile(header_name, header);
}

void Generator::writeFile(const QString &file_name, const QString &file_content)
{
    if (dir_source.isEmpty()) return;
    QFile file(dir_source+"/dbiog/"+file_name);

    if (!file.open(QTextStream::WriteOnly | QTextStream::Text)) {
        qDebug() << "can't open file";
        return;
    }

    QTextStream out(&file);
    out << file_content;
    file.flush();
    file.close();
}

void Generator::writeDataList()
{
    const QString header_template_file_content = getTemplate(":/template/datalistrow.h");
    DataTable *table;
    foreach (table, list_tables) {
        QString header = header_template_file_content;

        header.replace("<INCLUDEGUARD>", table->includeGuardList());
        header.replace("<INCLUDE>", table->fileNameData());
        header.replace("<CLASSNAME>", table->classNameList());
        header.replace("<CLASS_DATARECORD>", table->classNameData());
        header.replace("<MEMBER_DECLARE>", table->members());

        header.replace("<MEMBER_DEFINE>", table->memberDefineList());
        header.replace("<SETTERS>", table->setterList());
        header.replace("<PRIMARYKEY>", table->getPrimaryColumn());

        writeFile(table->fileNameList(), header);
    }
}

void Generator::writeData()
{
    const QString header_template_file_content = getTemplate(":/template/datarow.h");
    DataTable *table;
    foreach (table, list_tables) {

        QString header = header_template_file_content;
        header.replace("<INCLUDEGUARD>", table->includeGuardData());
        header.replace("<INCLUDE_DEPS>", table->dependenciesIncludes());
        header.replace("<CLASSNAME>", table->classNameData());
        header.replace("<CLASSNAMEDATALIST>", table->classNameList());
        header.replace("<MEMBER_DECLARE>", table->members());

        // source
        header.replace("<TABLENAME>", table->getName());
        header.replace("<IDFORMAT>", table->getFormatID());
        header.replace("<MEMBER_DEFINE>", table->memberDefine());
        header.replace("<PRIMARYKEY>", table->getPrimaryColumn());
        header.replace("<GETTERS>", table->getterData());
        header.replace("<SETTERS>", table->setterData());
        header.replace("<GETTER_COLUMNS>", table->getterColumn());
        header.replace("<DEPENDENCIES>", table->makeDependencies());

        writeFile(table->fileNameData(), header);
    }
}

void Generator::writeFactory(QString& header_content, const QString& json_file, const bool& is_last)
{
    QString file_name = QFileInfo(json_file).baseName();
    file_name.remove("-mod");
    const QString model_conn_setter_name = toCamel(file_name);
    QString connection_setter = "    static void setConnection"+model_conn_setter_name+"(const QString& db_conn)\n    {\n<CONNECTIONS>";

    DataTable *table;
    QStringList includes;
    QStringList includes_list;
    QStringList getter;
    QStringList getter_list;
    QStringList conn_setters;
    foreach (table, list_tables) {
        includes.append( table->factoryInclude() );
        includes_list.append( table->factoryIncludeList() );
        getter.append( table->factoryGetter() );
        getter_list.append( table->factoryGetterList() );
        conn_setters.append( table->factoryConnection()+"\n" );
        conn_setters.append( table->factoryConnectionList() );
        includes.append( "\n" );
        includes_list.append( "\n" );
        getter.append( "\n" );
        getter_list.append( "\n" );
        conn_setters.append( "\n" );

    }

    // remove last new line
    includes.removeLast();
    includes_list.removeLast();
    getter.removeLast();
    getter_list.removeLast();
    conn_setters.removeLast();

    if (!is_last)
    {
        header_content.replace("<INCLUDES>", includes.join("")+"\n<INCLUDES>");
        header_content.replace("<INCLUDES_LIST>", includes_list.join("")+"\n<INCLUDES_LIST>");
        header_content.replace("<GETTER>", getter.join("")+"\n<GETTER>");
        header_content.replace("<GETTER_LIST>", getter_list.join("")+"\n<GETTER_LIST>");
        header_content.replace("<CONNECTION>", connection_setter.replace("<CONNECTIONS>", conn_setters.join("")+"\n    }\n<CONNECTION>"));
    }
    else
    {
        header_content.replace("<INCLUDES>", includes.join(""));
        header_content.replace("<INCLUDES_LIST>", includes_list.join(""));
        header_content.replace("<GETTER>", getter.join(""));
        header_content.replace("<GETTER_LIST>", getter_list.join(""));
        header_content.replace("<CONNECTION>", connection_setter.replace("<CONNECTIONS>", conn_setters.join("")+"\n    }"));
    }
}

void Generator::writeCmake(QStringList& cmake_files)
{
    qDebug() << __FUNCTION__;
    if (dir_source.isEmpty()) return;
    QString cmake_template = getTemplate(":/template/module-database.cmake");

    // DatabaseModel
    cmake_files.append("    ${CMAKE_CURRENT_LIST_DIR}/dbfactory.h");

    DataTable* table;
    // Data
    foreach (table, list_tables)
        cmake_files.append( table->makeCmakeData() );
    // DataList
    foreach (table, list_tables)
        cmake_files.append( table->makeCmakeList() );

    cmake_template.replace("<DATARECORD_FILES>", cmake_files.join("\n"));

    writeFile("dbiog.cmake", cmake_template);
}

bool Generator::hasModJsonFiles()
{
    resetListTables();
    getDBModelJsonFiles();
    return !json_files.isEmpty();
}

void Generator::getDBModelJsonFiles()
{
    QDir dir(dir_source);
    QStringList files = dir.entryList();
    QString file;
    foreach (file, files) {
        if (file.endsWith("-mod.json"))
        {
            json_files.append(dir_source+"/"+file);
        }
    }
}

bool Generator::isValidDir()
{
    QDir dir(dir_source);
    return dir.exists();
}

void Generator::make_data()
{
    if (!hasModJsonFiles()) return;

    QDir dir(dir_source+"/dbiog");
    if (!dir.exists())
        dir.mkdir(dir_source+"/dbiog");

    QString header_factory = getTemplate(":/template/dbfactory.h");
    QString json_file;
    foreach (json_file, json_files) {
        readJsonModel(json_file);
        writeDatabaseModel(json_file);
        writeFactory(header_factory, json_file, json_file == json_files.last());
        resetListTables();
    }
    writeFile("dbfactory.h", header_factory);

    QStringList cmake_files;
    foreach (json_file, json_files) {
        readJsonModel(json_file);
        cmake_files.append(model_class_file(json_file));
    }

    writeCmake(cmake_files);
    writeData();
    writeDataList();
}

void Generator::make_pack()
{
    QDir dir(dir_source+"/dbio");
    if (!dir.exists())
        dir.mkdir(dir_source+"/dbio");

    QString file;
    foreach (file, list_files_dbio) {
        QFile f(":/template/dbio/"+file);
        f.open(QIODevice::ReadOnly | QIODevice::Text);
        QFile out(dir_source+"/dbio/"+file);
        out.open(QIODevice::WriteOnly | QIODevice::Text);
        out.write( f.readAll() );
        f.close();
        out.flush();
        out.close();
    }
}

void Generator::make_example()
{
    QFile f(":/template/example-mod.json");
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    QFile out(dir_source+"/example-mod.json");
    out.open(QIODevice::WriteOnly | QIODevice::Text);
    out.write( f.readAll() );
    f.close();
    out.flush();
    out.close();
}
