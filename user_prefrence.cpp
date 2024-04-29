#include "user_prefrence.h"
#include "ui_user_prefrence.h"

User_Prefrence::User_Prefrence(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::User_Prefrence)
{
    ui->setupUi(this);
}

User_Prefrence::~User_Prefrence()
{
    delete ui;
    delete ad;
}

void User_Prefrence::on_Add_User_Button_clicked()
{
    ad=new Add_User();
    connect(ad,&Add_User::namesignal,this,&User_Prefrence::PassSignal);
    ad->show();
}


void User_Prefrence::ShowDetails(std::vector<details *> detailList){
    ui->Select_User->clear();
    ui->Select_Mode->clear();
    ui->Select_Theme->clear();
    for (const auto& detail : detailList) {
        ui->Select_User->addItem(detail->Getusername());
        // ui->Select_Mode->addItem(detail->GetMode_of_driving());
        // ui->Select_Theme->addItem(detail->GetPrefered_color());
        // Add more items to other UI elements as needed
    }
    ui->Select_Mode->addItems({"Sports", "Normal"});
    ui->Select_Theme->addItems({"Dark", "Light"});
    connect(ui->Select_User, &QComboBox::currentTextChanged, this, [this, detailList](const QString& newText) {
        // Find the user details corresponding to the selected username
        details* selectedDetail = nullptr;
        for (const auto& detail : detailList) {
            if (detail->Getusername() == newText) {
                selectedDetail = detail;
                break;
            }
        }

        // Update the mode and theme comboboxes based on the selected user
        if (selectedDetail) {
            ui->Select_Mode->setCurrentText(selectedDetail->GetMode_of_driving());
            ui->Select_Theme->setCurrentText(selectedDetail->GetPrefered_color());
        }
    });

}


void User_Prefrence::PassSignal(QString name)
{
    emit passnamesignal(name);
}

void User_Prefrence::on_Load_Button_clicked()
{
    QString username=ui->Select_User->currentText();
    QString mode=ui->Select_Mode->currentText();
    QString theme=ui->Select_Theme->currentText();

    emit loadsignal(username,mode,theme);
}

