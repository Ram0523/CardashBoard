#ifndef DETAILS_H
#define DETAILS_H

#include <QObject>

class details:public QObject
{
    Q_OBJECT
private:
    QString username;
    QString Mode_of_driving;
    QString Prefered_color;
    int Km_travelled;
    int EngineHours;
    int Total_KM;
    int  Total_Engine_Hours;
    int Fuel_Level;

public:
    details(QObject *parent = nullptr);

    static std::vector<details*> detailList;
    void addDetailsToList(details* newDetails);


    QString Getusername();
    QString GetMode_of_driving();
    QString GetPrefered_color();
    int GetKm_travelled();
    int GetEngineHours();
    int GetTotal_KM();
    int GetTotal_Engine_Hours();
    int GetFuel_Level();


    void Setusername(const QString& name);
    void SetMode_of_driving(const QString& mode);
    void SetPrefered_color(const QString& color);
    void SetKm_travelled(int km);
    void SetEngineHours(int hours);
    void SetTotal_KM(int totalKm);
    void SetTotal_Engine_Hours(int totalEngineHours);
    void SetFuel_Level(int fuelLevel);




};

#endif // DETAILS_H
