#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <api.h>
#include "dashboard.h"
#include "user_prefrence.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Start_Button_clicked();
    void on_User_Prefrence_clicked();
    void AddName(QString name);
    void load(QString username,QString mode,QString theme);
    void on_Reset_Button_clicked();
    void updateKmEngine(int Km,int EngineHr,int Fuel);

signals:
    void LastUserSignal(details*);
    void AllUserSignal(vector<details*>);
    void loadclicked();
private:
    Ui::MainWindow *ui=nullptr;
    api* ap=nullptr;
    DashBoard* da=nullptr;
    User_Prefrence* up=nullptr;
};
#endif // MAINWINDOW_H
