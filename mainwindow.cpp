#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qdebug.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Car DashBoard System");
    ap=new api;
    // ap->SetTotalKm(25);
    // ap->SetEngineHours(10);
    qDebug()<< ap->GetEngineHours();
    qDebug()<< ap->GetTotalKm();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ap;
    delete da;
    delete up;
}



void MainWindow::on_Start_Button_clicked()
{
    // da=new DashBoard(this);
    da=new DashBoard();
    connect(this,&MainWindow::LastUserSignal,da,&DashBoard::ShowDetails);
    emit LastUserSignal(ap->GetLastUserPrefrence());
    da->show();
    connect(da,&DashBoard::lastsignal,this,&MainWindow::updateKmEngine);
    connect(this,&MainWindow::loadclicked,da,&DashBoard::LoadButtonClicked);
}


void MainWindow::on_User_Prefrence_clicked()
{
    up=new User_Prefrence();
    connect(this,&MainWindow::AllUserSignal,up,&User_Prefrence::ShowDetails);
    emit AllUserSignal(ap->GetAllUserData());
    up->show();
    connect(up,&User_Prefrence::passnamesignal,this,&MainWindow::AddName);
    connect(up,&User_Prefrence::loadsignal,this,&MainWindow::load);
}


void MainWindow::AddName(QString name)
{
    ap->AddUser(name);
    emit AllUserSignal(ap->GetAllUserData());
}

void MainWindow::on_Reset_Button_clicked()
{
    ap->reset();
    if(da!=nullptr){
        //get vaues from dashboard
        emit LastUserSignal(ap->GetLastUserPrefrence());
    }
}

void MainWindow::load(QString username,QString mode,QString theme){
    emit loadclicked();
    ap->Loaddata(username,mode,theme);
    if(da!=nullptr){
        //get vaues from dashboard
        emit LastUserSignal(ap->GetLastUserPrefrence());
    }
    emit AllUserSignal(ap->GetAllUserData());
}

void MainWindow::updateKmEngine(int Km,int EngineHr,int Fuel){
    ap->UpdateKmEngine(Km,EngineHr,Fuel);
}
