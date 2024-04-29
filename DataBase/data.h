#ifndef DATA_H
#define DATA_H

#include <QObject>
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include "../Details/details.h"


class data: public QObject
{
    Q_OBJECT
private:
    data();
    data(data& other)=delete;
    data& operator=(data& other)=delete;

public:
     ~data();
   static data* instance(){

          static  data* _instance=new data;

        return _instance;
    }

    bool OpenConnection();
    bool CloseConnection();
    bool CreateTable();
    // bool InsertData();
    int DgetTotalKM();
    int DgetEngineHours();
    bool incrementTotalKM(int incrementBy);
    bool incrementEngineHours(int incrementBy);
    bool decrementFuelLevel(int decrementBy);
    details* LastUserData();
    std::vector<details*> LoadAllUserData();
    void load(QString username,QString mode,QString theme);
    void addUser(QString name);
    void resetAllUserData();

private:
    QSqlDatabase base;
};

#endif // DATA_H
