#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QDialog>
#include "../Details/details.h"
using namespace std;

namespace Ui {
class DashBoard;
}

class DashBoard : public QDialog
{
    Q_OBJECT

public:
    explicit DashBoard(QWidget *parent = nullptr);
    ~DashBoard();
    void change(QString color);
    void cal();

signals:
    void lastsignal(int,int,int);

protected :
    void closeEvent(QCloseEvent *event)override;

private slots:
    void Speedometer();
    void on_Left_Signal_clicked();
    void on_Right_Signal_clicked();

    void LeftIndicator();
    void RightIndicator();

public slots:
    void ShowDetails(details* userData);
    void LoadButtonClicked();


private:
    Ui::DashBoard *ui;
    QTimer* timer;
    QTimer* Ltimer=nullptr;
    QTimer* Rtimer=nullptr;
    int rpm;
    int speed=0;
    QString name;
    QString mode;
    int Total_km;
    int Total_Engine_hour;
    int fuel_level;
    int DTotal_km;
    int DTotal_Engine_hour;
    int Dfuel_level;
};

#endif // DASHBOARD_H
