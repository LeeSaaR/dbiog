##########################################################################
#  THIS FILE IS PART OF DBIO MODULE
#
#  AUTHOR:  Lisa ( LeeSaaR )
#  URL:     https://leesaar.de
#  REPO:    https://www.github.com/leesaar/dbio
#
#  ==========================================================
#
#  DATABASE-IO: a database input output system for Qt applications.
#  Copyright (C) 2025  Lisa (LeeSaaR)
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <https://www.gnu.org/licenses/>.
##########################################################################

cmake_minimum_required(VERSION 3.5)

include_directories(${CMAKE_CURRENT_LIST_DIR})
set(DBIO_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/dbio.h
    ${CMAKE_CURRENT_LIST_DIR}/dbioconnector.h
    ${CMAKE_CURRENT_LIST_DIR}/dbioidgenerator.h
    ${CMAKE_CURRENT_LIST_DIR}/dbiomodel.h
    ${CMAKE_CURRENT_LIST_DIR}/datacolumn.h
    ${CMAKE_CURRENT_LIST_DIR}/datarowraw.h
    ${CMAKE_CURRENT_LIST_DIR}/datarowrawlist.h
    ${CMAKE_CURRENT_LIST_DIR}/datarowconverter.h
    ${CMAKE_CURRENT_LIST_DIR}/datarow.h
)
set(DBIO_SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/dbio.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dbioconnector.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dbioidgenerator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dbiomodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/datacolumn.cpp
    ${CMAKE_CURRENT_LIST_DIR}/datarowraw.cpp
    ${CMAKE_CURRENT_LIST_DIR}/datarowrawlist.cpp
    ${CMAKE_CURRENT_LIST_DIR}/datarowconverter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/datarow.cpp
)

set(DBIO ${DBIO_SOURCES} ${DBIO_HEADERS})