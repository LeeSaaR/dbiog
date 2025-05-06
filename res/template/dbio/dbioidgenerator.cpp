/**
 * DBIOIDGenerator IS PART OF DBIO MODULE
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
#include "dbioidgenerator.h"
#include <QRandomGenerator>

DBIOIDGenerator* DBIOIDGenerator::m_instance = nullptr;

DBIOIDGenerator *DBIOIDGenerator::get()
{
    if(m_instance == nullptr)
        m_instance = new DBIOIDGenerator();

    return m_instance;
}

DBIOIDGenerator::~DBIOIDGenerator() { }

QString DBIOIDGenerator::generate(const QString &id_format)
{
    // this method generates an id
    QString id;
    for (int i = 0; i < id_format.size(); i++) {
        if (id_format.at(i) == 'C') {
            id.append(randomChar());
        }
        else if (id_format.at(i) == 'N') {
            id.append(randomNumber());
        }
        else {
            id.append(id_format.at(i));
        }
    }
    return id;
}

QString DBIOIDGenerator::randomChar()
{
    // returns a random charakter from m_id_characters
    return QString(m_id_characters.at(QRandomGenerator::global()->bounded(0, m_id_characters.size())));
}

QString DBIOIDGenerator::randomNumber()
{
    // returns a random number m_id_numbers
    return QString(m_id_numbers.at(QRandomGenerator::global()->bounded(0, m_id_numbers.size())));
}
