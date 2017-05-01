#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->button_addaccount, SIGNAL(clicked(bool)), this, SLOT(add_account()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tabWidget_destroyed()
{

}

void MainWindow::add_account(){
    accountform *account_form = new accountform;
//    account_form->set_account_name("a");
    account_form->exec();
}
