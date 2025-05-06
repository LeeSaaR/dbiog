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
#include "dbioconnector.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDebug>

DBIOConnector::DBIOConnector(){}
DBIOConnector::~DBIOConnector(){}

bool DBIOConnector::createDatabase(const QString &filename, const QString &connection, DBIOModel *model)
{
    qDebug() << "Creating..." << filename;
    qDebug() << "database filename  :" << filename;
    qDebug() << "database connection:" << connection;

    // create database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connection);
    db.setDatabaseName(filename);

    if (!db.open()) {
        qDebug() << db.lastError().text();
        return false;
    }

    QSqlQuery query(db);

    // create tables
    for (const QString &statement : model->createStatements())
        query.exec(statement);

    query.finish();

    return true;
}

void DBIOConnector::updateDatabase(const QString &connection, DBIOModel *model)
{
    qDebug() << "Update..." << connection;
    qDebug() << "database connection:" << connection;
    QSqlQuery query(QSqlDatabase::database(connection));
    for (const QString &statement : model->updateStatements())
    {
        query.exec(statement);
        qDebug() << query.lastError();
    }
}

bool DBIOConnector::connectDatabase(const QString &filename, const QString &connection)
{
    qDebug() << "Connecting..." << filename;
    qDebug() << "database filename  :" << filename;
    qDebug() << "database connection:" << connection;
    if (!QFile::exists(filename)) {
        qDebug() << "ERROR: no such file:" << filename;
        return false;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connection);
    db.setDatabaseName(filename);
    if (!db.open()) {
        qDebug() << db.lastError().text();
        return false;
    }
    return true;
}

bool DBIOConnector::disconnectDatabase(const QString &connection)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connection);
    db.close();
    db.removeDatabase(connection);
    return true;
}

