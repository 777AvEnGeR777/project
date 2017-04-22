#include "authwindow.h"
#include "ui_authwindow.h"
#include "Data.h"


AuthWindow::AuthWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthWindow)
{
    ui->setupUi(this);
    authResult = false;
    attempts = 3;

    connect(ui->buttonLogin, SIGNAL(clicked(bool)), this, SLOT(Authentication()));
    connect(ui->buttonCreateMaster, SIGNAL(clicked(bool)), this, SLOT(CreateMaster()));

    std::string masterHash = Data::Instance()->masterHash;
    if(masterHash.empty())
        ui->groupLogin->hide();
    else
        ui->groupCreateMaster->hide();
}

AuthWindow::~AuthWindow()
{
    delete ui;
}

void AuthWindow::Authentication()
{
    std::string password = ui->editMaster->text().toStdString();
    std::string passwordHash = Encryptor::Instance()->Hash(password);

    if(passwordHash == Data::Instance()->masterHash)
    {
        authResult = true;
        attempts = 3;
        close();
    }
    else {
        attempts--;
        if(attempts == 0)
        {
            QMessageBox::critical(0,"Error!","\nПревышено количество попыток входа!\n",QMessageBox::Ok);
            exit(-1);
        }
        QMessageBox::critical(0,"Error!","\nAuthentication error!\n",QMessageBox::Ok);
    }
}

void AuthWindow::CreateMaster()
{

}
