#include "authwindow.h"
#include "ui_authwindow.h"
#include "Data.h"

AuthWindow::AuthWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthWindow)
{
    ui->setupUi(this);

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
