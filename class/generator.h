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
#ifndef GENERATOR_H
#define GENERATOR_H

#include "datatable.h"
#include <QDir>
#include <QList>
#include <QString>

class Generator
{

private:
    QList<DataTable*> list_tables;
    QList<QString> json_files;
    QString dir_source;
    QString model_class_name;
    QString model_file_name;
    QStringList list_files_dbio;
    QString current_path;
public:
    Generator();
    ~Generator();
private:
    void init();
    void resetListTables();
private:
    QString getTemplate(const QString &file_name);
    QString toCamel(QString file_name);
    QString model_class_file(const QString& json_file);
private:
    void readJsonModel(const QString& json_file);
    void writeFile(const QString &file_name, const QString &file_content);
    void writeDatabaseModel(const QString &json_file);
    void writeData();
    void writeDataList();
    void writeFactory(QString& header_content, const QString& json_file, const bool& is_last = false);
    void writeCmake(QStringList& cmake_files);
private:
    bool hasModJsonFiles();
    void getDBModelJsonFiles();
public:
    void setDirSource(const QString& dir);
    bool isValidDir();
    void make_data();
    void make_pack();
    void make_example();
};

#endif // GENERATOR_H
