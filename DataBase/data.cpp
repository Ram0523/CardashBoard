#include "data.h"
#include "QTimer"

data::data() {
    base = QSqlDatabase::addDatabase("QSQLITE");
    base.setDatabaseName("base.db");
    if(OpenConnection()){
        CreateTable();
    };
    // QTimer* timer=new QTimer(this);
    // connect(timer, &QTimer::timeout, this, [this]() {
    //     incrementTotalKM(25);
    //     incrementEngineHours(5);
    // });
    // timer->start(1000);
}


data::~data(){
    CloseConnection();
}


bool data::OpenConnection(){
    // Try to open the database
    if (base.open()) {
        qDebug() << "Connection successful";
        return true;
    } else {
        qDebug() << "Connection failed";
        return false;
    }
}


bool data::CloseConnection(){
    if (base.isOpen()) {
        base.close();
        qDebug() << "Database connection closed";
        return true;
    } else {
        qDebug() << "No active database connection to close";
        return false;
    }
}


bool data::CreateTable() {
    // SQL query to create table UserPrefrence if not exists
    QString createUserPrefrenceQuery = "CREATE TABLE IF NOT EXISTS UserPrefrence ("
                                       "username TEXT PRIMARY KEY,"
                                       "Mode_of_driving TEXT,"
                                       "Prefered_color TEXT,"
                                       "Km_travelled INTEGER,"
                                       "EngineHours INTEGER"
                                       ")";

    // SQL query to create table CarInfo if not exists with foreign key constraint
    QString createCarInfoQuery = "CREATE TABLE IF NOT EXISTS CarInfo ("
                                 "username TEXT PRIMARY KEY,"
                                 "Total_KM INTEGER,"
                                 "Total_Engine_Hours INTEGER,"
                                 "Fuel_Level INTEGER,"
                                 "FOREIGN KEY(username) REFERENCES UserPrefrence(username)"
                                 ")";

    // Execute the queries
    QSqlQuery query;
    if (query.exec(createUserPrefrenceQuery) && query.exec(createCarInfoQuery)) {
        qDebug() << "Tables created successfully.";
        return true;
    } else {
        qDebug() << "Error creating tables: " << query.lastError().text();
        return false;
    }
}



int data::DgetTotalKM() {
    QString selectQuery = "SELECT Total_KM FROM CarInfo LIMIT 1";
    QSqlQuery query(selectQuery);
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    } else {
        qDebug() << "Error retrieving Total_KM value from CarInfo: " << query.lastError().text();
        return -1; // Return an error code or handle the error as required
    }
}


bool data::incrementTotalKM(int incrementBy) {
        QSqlDatabase::database().transaction(); // Start a transaction

        // Increment Total_KM in CarInfo table
        QSqlQuery updateCarInfoQuery;
        updateCarInfoQuery.prepare("UPDATE CarInfo SET Total_KM = Total_KM + :incrementBy "
                                   "WHERE username = (SELECT username FROM CarInfo ORDER BY ROWID DESC LIMIT 1)");
        updateCarInfoQuery.bindValue(":incrementBy", incrementBy);
        if (!updateCarInfoQuery.exec()) {
            qDebug() << "Error incrementing Total_KM value in CarInfo: " << updateCarInfoQuery.lastError().text();
            QSqlDatabase::database().rollback(); // Rollback transaction in case of error
            return false;
        }

        // Increment Km_travelled in UserPrefrence table for the first username in CarInfo
        QSqlQuery updateUserDataQuery;
        updateUserDataQuery.prepare("UPDATE UserPrefrence "
                                    "SET Km_travelled = Km_travelled + :incrementBy "
                                    "WHERE username = (SELECT username FROM CarInfo ORDER BY ROWID DESC LIMIT 1)");
        updateUserDataQuery.bindValue(":incrementBy", incrementBy);
        if (!updateUserDataQuery.exec()) {
            qDebug() << "Error incrementing Km_travelled value in UserPrefrence: " << updateUserDataQuery.lastError().text();
            QSqlDatabase::database().rollback(); // Rollback transaction in case of error
            return false;
        }

        QSqlDatabase::database().commit(); // Commit transaction
        qDebug() << "Total incremented successfully by" << incrementBy;

        return true;
    }



int data::DgetEngineHours() {
    QString selectQuery = "SELECT Total_Engine_Hours FROM CarInfo LIMIT 1";
    QSqlQuery query(selectQuery);
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    } else {
        qDebug() << "Error retrieving Engine_Hours value from CarInfo: " << query.lastError().text();
        return -1; // Return an error code or handle the error as required
    }
}

bool data::incrementEngineHours(int incrementBy) {

    QSqlDatabase::database().transaction(); // Start a transaction

    // Increment Total_Engine_Hours in CarInfo table

    QSqlQuery updateCarInfoQuery;

    updateCarInfoQuery.prepare("UPDATE CarInfo SET Total_Engine_Hours = Total_Engine_Hours + :incrementBy "
                               "WHERE username = (SELECT username FROM CarInfo ORDER BY ROWID DESC LIMIT 1)");

    updateCarInfoQuery.bindValue(":incrementBy", incrementBy);

    if (!updateCarInfoQuery.exec()) {

        qDebug() << "Error incrementing Total_Engine_Hours value in CarInfo: " << updateCarInfoQuery.lastError().text();

        QSqlDatabase::database().rollback(); // Rollback transaction in case of error

        return false;

    }

    // Increment EngineHours in UserPrefrence table for the first username in CarInfo

    QSqlQuery updateUserPrefrenceQuery;

    updateUserPrefrenceQuery.prepare("UPDATE UserPrefrence "
                                     "SET EngineHours = EngineHours + :incrementBy "
                                     "WHERE username = (SELECT username FROM CarInfo ORDER BY ROWID DESC LIMIT 1)");

    updateUserPrefrenceQuery.bindValue(":incrementBy", incrementBy);

    if (!updateUserPrefrenceQuery.exec()) {

        qDebug() << "Error incrementing EngineHours value in UserPrefrence: " << updateUserPrefrenceQuery.lastError().text();

        QSqlDatabase::database().rollback(); // Rollback transaction in case of error

        return false;

    }

    QSqlDatabase::database().commit(); // Commit transaction

    qDebug() << "Engine hours incremented successfully by" << incrementBy;

    return true;

}

bool data::decrementFuelLevel(int decrementBy) {
    QSqlDatabase::database().transaction(); // Start a transaction

    // Decrement Fuel_Level in CarInfo table
    QSqlQuery updateCarInfoQuery;
    updateCarInfoQuery.prepare("UPDATE CarInfo SET Fuel_Level = Fuel_Level - :decrementBy "
                               "WHERE username = (SELECT username FROM CarInfo ORDER BY ROWID DESC LIMIT 1)");
    updateCarInfoQuery.bindValue(":decrementBy", decrementBy);

    if (!updateCarInfoQuery.exec()) {
        qDebug() << "Error decrementing Fuel_Level value in CarInfo: " << updateCarInfoQuery.lastError().text();
        QSqlDatabase::database().rollback(); // Rollback transaction in case of error
        return false;
    }

    // If the update in CarInfo succeeds, commit the transaction
    QSqlDatabase::database().commit();
    // qDebug() << "Fuel level decremented successfully by" << decrementBy;

    return true;
}



details* data::LastUserData() {
    details* userData=new details();


    // SQL query to retrieve user data from UserPrefrence table for the first username in CarInfo
    QString selectUserDataQuery = "SELECT UserPrefrence.*, CarInfo.Total_KM, CarInfo.Total_Engine_Hours, CarInfo.Fuel_Level "
                                  "FROM UserPrefrence "
                                  "JOIN CarInfo ON UserPrefrence.username = CarInfo.username "
                                  "ORDER BY CarInfo.ROWID DESC LIMIT 1";

    QSqlQuery userDataQuery(selectUserDataQuery);
    if (!userDataQuery.exec() || !userDataQuery.next()) {
        qDebug() << "Error retrieving user data from UserPrefrence table: " << userDataQuery.lastError().text();
        return userData;
    }

    // Retrieve data from the query result
    userData->Setusername(userDataQuery.value("username").toString());
    userData->SetMode_of_driving(userDataQuery.value("Mode_of_driving").toString());
    userData->SetPrefered_color(userDataQuery.value("Prefered_color").toString());
    userData->SetKm_travelled(userDataQuery.value("Km_travelled").toInt());
    userData->SetEngineHours(userDataQuery.value("EngineHours").toInt());
    userData->SetTotal_KM(userDataQuery.value("Total_KM").toInt());
    userData->SetTotal_Engine_Hours(userDataQuery.value("Total_Engine_Hours").toInt());
    userData->SetFuel_Level(userDataQuery.value("Fuel_Level").toInt());

    return userData;
}



std::vector<details*> data::LoadAllUserData() {
    std::vector<details*> userDataList;

    QString selectAllUserDataQuery = "SELECT * FROM UserPrefrence";
    QSqlQuery allUserDataQuery(selectAllUserDataQuery);
    while (allUserDataQuery.next()) {
        details* userData = new details();

        // Retrieve data from the query result
        userData->Setusername(allUserDataQuery.value("username").toString());
        userData->SetMode_of_driving(allUserDataQuery.value("Mode_of_driving").toString());
        userData->SetPrefered_color(allUserDataQuery.value("Prefered_color").toString());
    // Add the userData to userDataList
        userDataList.push_back(userData);
    }

    return userDataList;
}


void data::addUser(QString name) {
    // SQL query to insert a new user with default values
    QString insertUserQuery = "INSERT INTO UserPrefrence (username, Mode_of_driving, Prefered_color, Km_travelled, EngineHours) "
                              "VALUES (:username, 'normal', 'light', 0, 0)";

    // Prepare the query
    QSqlQuery query;
    query.prepare(insertUserQuery);

    // Bind values to the placeholders
    query.bindValue(":username", name);

    // Execute the query
    if (query.exec()) {
        qDebug() << "User added successfully.";
    } else {
        qDebug() << "Error adding user: " << query.lastError().text();
    }
}


void data::resetAllUserData() {
    // Reset values in UserPrefrence table
    QString resetUserPrefQuery = "UPDATE UserPrefrence SET Km_travelled = 0, EngineHours = 0";
    QSqlQuery userPrefQuery;
    if (!userPrefQuery.exec(resetUserPrefQuery)) {
        qDebug() << "Error resetting user data in UserPrefrence table: " << userPrefQuery.lastError().text();
        return;
    }

    // Reset values in CarInfo table
    QString resetCarInfoQuery = "UPDATE CarInfo SET Total_KM = 0, Total_Engine_Hours = 0, Fuel_Level = 100";
    QSqlQuery carInfoQuery;
    if (!carInfoQuery.exec(resetCarInfoQuery)) {
        qDebug() << "Error resetting user data in CarInfo table: " << carInfoQuery.lastError().text();
        return;
    }

    qDebug() << "All user data reset successfully.";
}



void data::load(QString username, QString mode, QString theme) {
    // Start a transaction for data consistency
    QSqlDatabase::database().transaction();

    // 1. Update UserPrefrence table (assuming username already exists)
    QSqlQuery updateUserPrefQuery;
    updateUserPrefQuery.prepare("UPDATE UserPrefrence "
                                "SET Mode_of_driving = :mode, Prefered_color = :theme "
                                "WHERE username = :username");
    updateUserPrefQuery.bindValue(":username", username);
    updateUserPrefQuery.bindValue(":mode", mode);
    updateUserPrefQuery.bindValue(":theme", theme);

    if (!updateUserPrefQuery.exec()) {
        qDebug() << "Error updating UserPrefrence: " << updateUserPrefQuery.lastError().text();
        QSqlDatabase::database().rollback(); // Rollback transaction if update fails
        return;
    }

    // 2. Update CarInfo table (replace username)
    QSqlQuery updateCarInfoQuery;
    updateCarInfoQuery.prepare("UPDATE CarInfo "
                               "SET username = :username "  // Only update username
                               "WHERE username != :username");  // Avoid updating existing row with same username
    updateCarInfoQuery.bindValue(":username", username);

    if (!updateCarInfoQuery.exec()) {
        qDebug() << "Error updating CarInfo: " << updateCarInfoQuery.lastError().text();
        QSqlDatabase::database().rollback(); // Rollback transaction if update fails
        return;
    }

    // If both updates succeed, commit the transaction
    QSqlDatabase::database().commit();
    qDebug() << "Data loaded successfully for username:" << username;
}


