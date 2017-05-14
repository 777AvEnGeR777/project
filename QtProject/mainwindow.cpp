#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    build_accounts();

    ui->textLogin->setReadOnly(true);
    ui->textPassword->setReadOnly(true);
    ui->textPassword->setEchoMode(QLineEdit::Password);
    ui->textComment->setReadOnly(true);
    connect(ui->accountCreate, SIGNAL(clicked(bool)), this, SLOT(add_account()));
    connect(ui->accountEdit, SIGNAL(clicked(bool)), this, SLOT(edit_account()));
    connect(ui->selectAccount, SIGNAL(currentIndexChanged(QString)),this, SLOT(switch_account(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tabWidget_destroyed()
{

}

void MainWindow::build_accounts(){
    ui->selectAccount->clear();

    for(auto iter = Data::Instance().accountList.begin();
         iter != Data::Instance().accountList.end(); ++iter){
        ui->selectAccount->addItem(iter->first.c_str());
    }

    if(ui->selectAccount->currentIndex() > -1){
        std::string currentKey = ui->selectAccount->currentText().toUtf8().constData();
        select_account(currentKey);
        ui->accountEdit->setEnabled(true);
    }
    else
    {
        ui->accountEdit->setEnabled(false);
    }
}

void MainWindow::select_account(std::string name){
    ui->textLogin->setText(Data::Instance().accountList.find(name.c_str())->second.login.c_str());
    ui->textPassword->setText(Data::Instance().accountList.find(name.c_str())->second.password.c_str());
    ui->textComment->setText(Data::Instance().accountList.find(name.c_str())->second.comment.c_str());
}

void MainWindow::switch_account(QString item){
    if(item != ""){
        select_account(item.toUtf8().constData());
    }else{
        ui->textLogin->clear();
        ui->textPassword->clear();
        ui->textComment->clear();
    }
}

void MainWindow::edit_account(){
    accountform *account_form = new accountform;

    account_form->set_account_name(ui->selectAccount->currentText().toUtf8().constData());

    account_form->exec();
    build_accounts();
}

void MainWindow::add_account(){
    accountform *account_form = new accountform;
    account_form->exec();
    build_accounts();
}
