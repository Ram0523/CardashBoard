#ifndef ADD_USER_H
#define ADD_USER_H

#include <QDialog>

namespace Ui {
class Add_User;
}

class Add_User : public QDialog
{
    Q_OBJECT

public:
    explicit Add_User(QWidget *parent = nullptr);
    ~Add_User();

signals:
    void namesignal(QString);
private slots:
    void on_Add_Button_clicked();

private:
    Ui::Add_User *ui;
};

#endif // ADD_USER_H
