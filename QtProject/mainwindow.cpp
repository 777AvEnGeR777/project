#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    build_accounts();

    connect(ui->button_addaccount, SIGNAL(clicked(bool)), this, SLOT(add_account()));
    connect(ui->accounts_list, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(edit_account(QListWidgetItem*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tabWidget_destroyed()
{

}

void MainWindow::build_accounts(){
    ui->accounts_list->clear();
    for(auto iter = Data::Instance().accountList.begin();
        iter != Data::Instance().accountList.end(); ++iter){
        ui->accounts_list->addItem(iter->first.c_str());
    }
}

void MainWindow::edit_account(QListWidgetItem* item){
    accountform *account_form = new accountform;

    account_form->set_account_name(item->text().toUtf8().constData());

    account_form->exec();
    build_accounts();
}

void MainWindow::add_account(){
    accountform *account_form = new accountform;
    account_form->exec();
    build_accounts();
}
