#include "details.h"
std::vector<details*> details::detailList;


details::details(QObject *parent) : QObject(parent){}



QString details::Getusername() {
    return username;
}

QString details::GetMode_of_driving() {
    return Mode_of_driving;
}

QString details::GetPrefered_color() {
    return Prefered_color;
}

int details::GetKm_travelled() {
    return Km_travelled;
}

int details::GetEngineHours() {
    return EngineHours;
}

int details::GetTotal_KM() {
    return Total_KM;
}

int details::GetTotal_Engine_Hours() {
    return Total_Engine_Hours;
}

int details::GetFuel_Level() {
    return Fuel_Level;
}

void details::Setusername(const QString& value) {
    username = value;
}

void details::SetMode_of_driving(const QString& value) {
    Mode_of_driving = value;
}

void details::SetPrefered_color(const QString& value) {
    Prefered_color = value;
}

void details::SetKm_travelled(int value) {
    Km_travelled = value;
}

void details::SetEngineHours(int value) {
    EngineHours = value;
}

void details::SetTotal_KM(int value) {
    Total_KM = value;
}

void details::SetTotal_Engine_Hours(int value) {
    Total_Engine_Hours = value;
}

void details::SetFuel_Level(int value) {
    Fuel_Level = value;
}



void details::addDetailsToList(details* newDetails) {
    detailList.push_back(newDetails);

}
