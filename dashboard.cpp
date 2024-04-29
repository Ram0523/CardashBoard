#include "dashboard.h"
#include "ui_dashboard.h"
#include "QTimer"
#include "QStyle"

DashBoard::DashBoard(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DashBoard)
{
    ui->setupUi(this);
    ui->label_LeftSIgnal->setVisible(false);
    ui->label_RightSignal->setVisible(false);
    timer=new QTimer;
    connect(timer,&QTimer::timeout,this,&DashBoard::Speedometer);
   timer->start(1000);
}

DashBoard::~DashBoard()
{
    qDebug()<<"destructor called";
    // cal();
    // emit lastsignal(DTotal_km,DTotal_Engine_hour,Dfuel_level);
    delete ui;
}

void DashBoard::cal(){
    DTotal_km=Total_km-DTotal_km;
    DTotal_Engine_hour=Total_Engine_hour-DTotal_Engine_hour;
    Dfuel_level= Dfuel_level-fuel_level;
    qDebug()<<DTotal_km<<DTotal_Engine_hour<<Dfuel_level;
}
void DashBoard:: ShowDetails(details* userData){
    // qDebug() << "Username:" << userData->Getusername();
    qDebug() << "Mode of driving:" << userData->GetMode_of_driving();
    qDebug() << "Preferred color:" << userData->GetPrefered_color();
    // qDebug() << "Km travelled:" << userData->GetKm_travelled();
    // qDebug() << "Engine hours:" << userData->GetEngineHours();
    // qDebug() << "Total KM:" << userData->GetTotal_KM();
    // qDebug() << "Total engine hours:" << userData->GetTotal_Engine_Hours();
    // qDebug() << "Fuel level:" << userData->GetFuel_Level();

    name=userData->Getusername();
    mode=userData->GetMode_of_driving();
    Total_km=userData->GetTotal_KM();
    Total_Engine_hour=userData->GetTotal_Engine_Hours();
    fuel_level=userData->GetFuel_Level();
    DTotal_km=Total_km;
    DTotal_Engine_hour=Total_Engine_hour;
    Dfuel_level=userData->GetFuel_Level();;
    if(mode=="Sports"){
        rpm=6000;
    }
    else rpm=3000;
    ui->lcd_Engine->display(Total_Engine_hour);
    ui->lcd_Km->display(Total_km);
    ui->progressBar_Fuel->setValue(fuel_level);

    change(userData->GetPrefered_color());

}

void DashBoard::Speedometer(){
    if(fuel_level>0){
    if(speed>=140){
        qDebug()<<"Max limit reached";
        //timer->stop();
    }
    ui->dial->setValue(speed);
    if(mode=="Sports"){
    speed+=20;
    }
    else speed+=10;

    Total_Engine_hour+=1;
    Total_km+=(rpm*speed)/63360;
    fuel_level-=1;
    ui->lcd_Engine->display(Total_Engine_hour);
    ui->lcd_Km->display(Total_km);
    ui->progressBar_Fuel->setValue(fuel_level);

    }
    else {
        qDebug()<<"Low Fuel";
    }
}


void DashBoard::change(QString color) {
    if (color == "Dark") {
        this->setStyleSheet("background-color: '#121212'; color: '#FFFFFF';"); // Add semicolon here
    } else {
        this->setStyleSheet("background-color: 'white'; color: 'black';"); // Add semicolon here
    }
}


void DashBoard::LoadButtonClicked(){
    cal();
    emit lastsignal(DTotal_km,DTotal_Engine_hour,Dfuel_level);
}



void DashBoard::on_Left_Signal_clicked()
{
    if (Ltimer && Ltimer->isActive()) {
        Ltimer->stop(); // If left timer is running, stop it
        ui->label_LeftSIgnal->setVisible(false);
    } else {
        // Stop the right timer if it's running
        if (Rtimer && Rtimer->isActive()) {
            Rtimer->stop();
            ui->label_RightSignal->setVisible(false);
        }

        Ltimer = new QTimer(this);
        connect(Ltimer, &QTimer::timeout, this, &DashBoard::LeftIndicator);
        Ltimer->setInterval(500);
        Ltimer->start(); // Start the left timer
    }
}

void DashBoard::on_Right_Signal_clicked()
{
    if (Rtimer && Rtimer->isActive()) {
        Rtimer->stop(); // If right timer is running, stop it
        ui->label_RightSignal->setVisible(false);
    } else {
        // Stop the left timer if it's running
        if (Ltimer && Ltimer->isActive()) {
            Ltimer->stop();
            ui->label_LeftSIgnal->setVisible(false);
        }

        Rtimer = new QTimer(this);
        connect(Rtimer, &QTimer::timeout, this, &DashBoard::RightIndicator);
        Rtimer->setInterval(500);
        Rtimer->start(); // Start the right timer
    }
}

void DashBoard::LeftIndicator()
{
    ui->label_LeftSIgnal->setVisible(!ui->label_LeftSIgnal->isVisible());
}

void DashBoard::RightIndicator()
{
    ui->label_RightSignal->setVisible(!ui->label_RightSignal->isVisible());
}


void DashBoard::closeEvent(QCloseEvent *event){
    QWidget::closeEvent(event);
    qDebug()<<"close event";
    cal();
    emit lastsignal(DTotal_km,DTotal_Engine_hour,Dfuel_level);
}
