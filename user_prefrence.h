#ifndef USER_PREFRENCE_H
#define USER_PREFRENCE_H

#include <QDialog>
#include "add_user.h"
#include "../Details/details.h"

namespace Ui {
class User_Prefrence;
}

class User_Prefrence : public QDialog
{
    Q_OBJECT

public:
    explicit User_Prefrence(QWidget *parent = nullptr);
    ~User_Prefrence();

public slots:
    void ShowDetails(std::vector<details*> detailList);

private slots:
    void on_Add_User_Button_clicked();
    void PassSignal(QString name);


    void on_Load_Button_clicked();

private:
    Ui::User_Prefrence *ui;
    Add_User* ad;

signals:
    void passnamesignal(QString name);
    void loadsignal(QString username,QString mode,QString theme);
};

#endif // USER_PREFRENCE_H
