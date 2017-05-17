#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    build_accounts();
    build_cards();

    ui->textLogin->setReadOnly(true);
    ui->textPassword->setReadOnly(true);
    ui->textPassword->setEchoMode(QLineEdit::Password);
    ui->textComment->setReadOnly(true);

    hide_tabs();
    ui->groupAccounts->show();

    connect(ui->toggleAccounts, SIGNAL(clicked(bool)), this, SLOT(toggleAccountsTab()));
    connect(ui->toggleCards, SIGNAL(clicked(bool)), this, SLOT(toggleCardsTab()));
    connect(ui->toggleSettings, SIGNAL(clicked(bool)), this, SLOT(toggleSettingsTab()));

    connect(ui->accountCreate, SIGNAL(clicked(bool)), this, SLOT(add_account()));
    connect(ui->accountEdit, SIGNAL(clicked(bool)), this, SLOT(edit_account()));
    connect(ui->selectAccount, SIGNAL(currentIndexChanged(QString)),this, SLOT(switch_account(QString)));

    connect(ui->cardCreate, SIGNAL(clicked(bool)), this, SLOT(add_card()));
    connect(ui->selectCard, SIGNAL(currentIndexChanged(QString)), this, SLOT(switch_card(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tabWidget_destroyed()
{

}

void MainWindow::build_cards(){
    ui->selectCard->clear();

    for(auto iter = Data::Instance().cardList.begin();
         iter != Data::Instance().cardList.end(); ++iter){
        ui->selectCard->addItem(iter->first.c_str());
    }

    if(ui->selectCard->currentIndex() > -1){
        std::string currentKey = ui->selectCard->currentText().toUtf8().constData();
        select_card(currentKey);
        ui->cardEdit->setEnabled(true);
    }
    else
    {
        ui->cardEdit->setEnabled(false);
    }
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

void MainWindow::select_card(std::string name){
    ui->textNumber->setText(Data::Instance().cardList.find(name.c_str())->second.number.c_str());
    ui->textDate->setText(Data::Instance().cardList.find(name.c_str())->second.date.c_str());
    ui->textCVC->setText(Data::Instance().cardList.find(name.c_str())->second.cvc.c_str());
    ui->textOwner->setText(Data::Instance().cardList.find(name.c_str())->second.owner.c_str());
    ui->textPin->setText(Data::Instance().cardList.find(name.c_str())->second.pin.c_str());
    ui->textSecret->setText(Data::Instance().cardList.find(name.c_str())->second.secret.c_str());
    ui->textSupportPhone->setText(Data::Instance().cardList.find(name.c_str())->second.phone.c_str());
}

void MainWindow::switch_card(QString item){
    if(item != ""){
        select_card(item.toUtf8().constData());
    }else{
        ui->textNumber->clear();
        ui->textDate->clear();
        ui->textCVC->clear();
        ui->textOwner->clear();
        ui->textPin->clear();
        ui->textSecret->clear();
        ui->textSupportPhone->clear();
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

void MainWindow::add_card(){
    accountform *account_form = new accountform;
    account_form->set_form_type("card");
    account_form->exec();
    build_cards();
}

void MainWindow::hide_tabs(){
    ui->groupCards->hide();
    ui->groupSettings->hide();
    ui->groupAccounts->hide();
}

void MainWindow::toggleAccountsTab(){
    hide_tabs();
    ui->groupAccounts->show();
}

void MainWindow::toggleCardsTab(){
    hide_tabs();
    ui->groupCards->show();
}

void MainWindow::toggleSettingsTab(){
    hide_tabs();
    ui->groupSettings->show();
}
