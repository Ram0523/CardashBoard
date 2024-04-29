#include "api.h"

api::api():db(data::instance()) {}

api::~api()
{
    delete db;
}

int api::GetTotalKm(){
    return db->DgetTotalKM();
}

int api::GetEngineHours(){
    return db->DgetEngineHours();
}



void api:: SetTotalKm(int incrementBy){
    db->incrementTotalKM(incrementBy);
}

void api:: SetEngineHours(int incrementBy){
    db->incrementEngineHours(incrementBy);
}


details* api::GetLastUserPrefrence(){
    return db->LastUserData();
}

std::vector<details*> api::GetAllUserData(){
    return db->LoadAllUserData();
}

void api::AddUser(QString name){
    db->addUser(name);
}


void api::reset(){
    db->resetAllUserData();
}


void api::Loaddata(QString username,QString mode,QString theme){
    db->load(username,mode,theme);
}


bool api::UpdateKmEngine(int km,int EngineHr,int Fuel){

    return (db->incrementTotalKM(km) &&
    db->incrementEngineHours(EngineHr) &&
            db->decrementFuelLevel(Fuel));

}
