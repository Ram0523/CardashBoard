#ifndef API_H
#define API_H

#include <QObject>
#include "../DataBase/data.h"

class api: public QObject
{
    Q_OBJECT
public:
    api();
    ~api();
    int GetTotalKm();
    int GetEngineHours();
    details* GetLastUserPrefrence();
    std::vector<details*> GetAllUserData();
    void AddUser(QString name);
    void reset();
    void SetTotalKm(int incrementBy);
    void SetEngineHours(int incrementBy);
    void Loaddata(QString username,QString mode,QString theme);
    bool UpdateKmEngine(int km,int EngineHr,int Fuel);


private:
    data*  db;
};

#endif // API_H
