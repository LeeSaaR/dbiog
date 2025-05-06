# DBIO

DBIO (Database Input Output) acts as a wrapper around the QtSql Module and is a small input-output system for SQLite3 databases in Qt applications. 
Its goals is simplify database manipulation and the project's database more scaleable and maintainable. It goes hand in hand with [DBIOG - Database Input Output Generator](https://www.github.com/leesaar/dbiog), that generates specialized classes for your project.

## DBIO Capabilities
DBIO provides query methods like ```insert()```, ```select()```, ```update()``` and ```del()``` to do manipulate your database. It handels ```DataRow```. A ```DataRow``` maps to the row of a table in your database. It basically consists of ```DataColumns``` the columns of the table. The ```DBIOModel``` is used to create the database. To use DBIO you need specialized ```DataRows``` and a spezialized ```DBIOModel```. DBIOG (Database Input Output Generator) is a tool that generates specialized ```DataRow``` and ```DataListRow``` classes ```DBIOModels``` and ```DBF``` (a database factory class) from a .json input file, for you.

> See:  
> [DBIOG - Database Input Output Generator](https://www.github.com/leesaar/dbiog)

## Documentation
> Coming Soon

## DBIO files:
<pre>
├── datacolumn.cpp  
├── datacolumn.h  
├── datarow.cpp  
├── datarow.h  
├── datarowconverter.cpp  
├── datarowconverter.h  
├── datarowraw.cpp  
├── datarowraw.h  
├── datarowrawlist.cpp  
├── datarowrawlist.h  
├── dbio.cmake  
├── dbio.cpp  
├── dbio.h  
├── dbioconnector.cpp  
├── dbioconnector.h  
├── dbioidgenerator.cpp  
├── dbioidgenerator.h  
├── dbiomodel.cpp  
└── dbiomodel.h  
</pre>

## LICENSE
GNU General Public License v3.0