#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    state = new StateAccount;

    rebuild();

    ui->textLogin->setReadOnly(true);
    ui->textPassword->setReadOnly(true);
    ui->textComment->setReadOnly(true);

    ui->textCVC->setReadOnly(true);
    ui->textNumber->setReadOnly(true);
    ui->textOwner->setReadOnly(true);
    ui->textPin->setReadOnly(true);
    ui->textSecret->setReadOnly(true);
    ui->textSupportPhone->setReadOnly(true);
    ui->textDate->setReadOnly(true);


    ui->groupCards->hide();
    ui->groupSettings->hide();
    currentTab = ACCOUNTS;

    connect(ui->toggleAccounts, SIGNAL(clicked(bool)), this, SLOT(toggleAccountsTab()));
    connect(ui->toggleCards, SIGNAL(clicked(bool)), this, SLOT(toggleCardsTab()));
    connect(ui->toggleSettings, SIGNAL(clicked(bool)), this, SLOT(toggleSettingsTab()));

    connect(ui->recordCreate, SIGNAL(clicked(bool)), this, SLOT(add()));
    connect(ui->recordEdit, SIGNAL(clicked(bool)), this, SLOT(edit()));
    connect(ui->recordDelete, SIGNAL(clicked(bool)), this, SLOT(delete_item()));
    connect(ui->selectAccount, SIGNAL(currentIndexChanged(QString)),this, SLOT(switch_account(QString)));
    connect(ui->selectCard, SIGNAL(currentIndexChanged(QString)), this, SLOT(switch_card(QString)));

    connect(ui->changeMaster, SIGNAL(clicked(bool)), this, SLOT(changeMaster()));
    connect(ui->textNewMaster, SIGNAL(textChanged(QString)), this, SLOT(passwordStrengthWatcher()));

    connect(ui->copyLogin, SIGNAL(clicked(bool)), this, SLOT(copyLogin()));
    connect(ui->copyPassword, SIGNAL(clicked(bool)), this, SLOT(copyPassword()));
    connect(ui->copyNumber, SIGNAL(clicked(bool)), this, SLOT(copyCardNumber()));
    connect(ui->copyOwner, SIGNAL(clicked(bool)), this, SLOT(copyOwner()));
    connect(ui->copyDate, SIGNAL(clicked(bool)), this, SLOT(copyDate()));

    connect(ui->eyePassword, SIGNAL(clicked(bool)), this, SLOT(changePasswordVisibility()));
    connect(ui->eyePin, SIGNAL(clicked(bool)), this, SLOT(changePinVisibility()));
    connect(ui->eyeSecret, SIGNAL(clicked(bool)), this, SLOT(changeSecretVisibility()));
    connect(ui->eyeOldMaster, SIGNAL(clicked(bool)), this, SLOT(changeOldMasterVisibility()));
    connect(ui->eyeNewMaster, SIGNAL(clicked(bool)), this, SLOT(changeNewMasterVisibility()));
    connect(ui->eyeConfirmMaster, SIGNAL(clicked(bool)), this, SLOT(changeConfirmMasterVisibility()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::rebuild(){
    build_accounts();
    build_cards();
}

void MainWindow::delete_item(){
    QString key = ui->selectAccount->currentText();
    if(currentTab == CARDS)
        key = ui->selectCard->currentText();
    if(key == ""){
        QMessageBox::warning(nullptr, "Warning!", "\nNo data to delete\n",
                             QMessageBox::Ok);
        return;
    }
    if(QMessageBox::information(nullptr, "Confirm delete!",
                                "\nAre you sure you want to delete this record?\n",
                                QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes){
        state->del(key);
        rebuild();
    }
}

void MainWindow::edit(){
    QString key = ui->selectAccount->currentText();
    if(currentTab == CARDS)
        key = ui->selectCard->currentText();
    state->edit(key);
    rebuild();
}

void MainWindow::add(){
    state->create();
    rebuild();
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
        ui->recordEdit->setEnabled(true);
    }
    else
    {
        ui->recordEdit->setEnabled(false);
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
        ui->recordEdit->setEnabled(true);
    }
    else
    {
        ui->recordEdit->setEnabled(false);
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

void MainWindow::hide_tab(){
    switch (currentTab) {
    case ACCOUNTS:
        ui->groupAccounts->hide();
        break;
    case CARDS:
        ui->groupCards->hide();
        break;
    case SETTINGS:
        ui->groupSettings->hide();
        ui->groupButtons->show();
        break;
    default:
        break;
    }
}

void MainWindow::toggleAccountsTab(){
    hide_tab();
    state = new StateAccount;
    ui->groupAccounts->show();
    currentTab = ACCOUNTS;
}

void MainWindow::toggleCardsTab(){
    hide_tab();
    ui->groupCards->show();
    state = new StateCard;
    currentTab = CARDS;
}

void MainWindow::toggleSettingsTab(){
    hide_tab();
    ui->groupButtons->hide();
    ui->groupSettings->show();
    currentTab = SETTINGS;
}

void MainWindow::changeMaster(){
    std::string oldMaster = ui->textOldMaster->text().toStdString();
    std::string newMaster = ui->textNewMaster->text().toStdString();
    std::string confirmMaster = ui->textConfirmMaster->text().toStdString();

    if(newMaster.empty()){
        QMessageBox::warning(nullptr, "Empty password!", "\nNew password cannot be empty!\n",
                             QMessageBox::Ok);
        return;
    }
    if(newMaster != confirmMaster){
        QMessageBox::warning(nullptr, "Passwords doesn't match!", "\nPasswords doesn't match!\n",
                             QMessageBox::Ok);
        return;
    }

    if(Encryptor::Instance().Hash(oldMaster) != Data::Instance().masterHash){
        QMessageBox::warning(nullptr, "Wrong password!", "\nWrong password!\n",
                             QMessageBox::Ok);
        return;
    }

    ui->textOldMaster->clear();
    ui->textNewMaster->clear();
    ui->textConfirmMaster->clear();
    Data::Instance().masterHash = Encryptor::Instance().Hash(newMaster);
    Encryptor::Instance().DerieveKey(newMaster);
    Data::Instance().Save();
    QMessageBox::information(nullptr, "Success", "\nMaster password successfully changed!\n",
                             QMessageBox::Ok);
}

void MainWindow::passwordStrengthWatcher(){
    std::string password = ui->textNewMaster->text().toStdString();
    PasswordStrength strength = PasswordStrengthChecker::Instance().CheckPasswordStrength(password);
    QPalette pallete = ui->labelPasswordStrength->palette();
    switch (strength) {
        case NO_PASSWORD:
            ui->labelPasswordStrength->clear();
            break;
        case WEAK:
            ui->labelPasswordStrength->setText("Weak");
            pallete.setColor(ui->labelPasswordStrength->foregroundRole(), Qt::red);
            ui->labelPasswordStrength->setPalette(pallete);
            break;
        case MEDIUM:
            ui->labelPasswordStrength->setText("Medium");
            pallete.setColor(ui->labelPasswordStrength->foregroundRole(), QColor(251, 192, 45));
            ui->labelPasswordStrength->setPalette(pallete);
            break;
        case STRONG:
            ui->labelPasswordStrength->setText("Strong");
            pallete.setColor(ui->labelPasswordStrength->foregroundRole(), QColor(102, 187, 106));
            ui->labelPasswordStrength->setPalette(pallete);
            break;
        case BEST:
            ui->labelPasswordStrength->setText("Best");
            pallete.setColor(ui->labelPasswordStrength->foregroundRole(), Qt::darkGreen);
            ui->labelPasswordStrength->setPalette(pallete);
            break;
        default:
            break;
    }
}

void MainWindow::copyLogin(){
    FieldManager::Instance().copyField(ui->textLogin);
}

void MainWindow::copyPassword()
{
    FieldManager::Instance().copyField(ui->textPassword);
}

void MainWindow::copyCardNumber()
{
    FieldManager::Instance().copyField(ui->textNumber);
}

void MainWindow::copyOwner()
{
    FieldManager::Instance().copyField(ui->textOwner);
}

void MainWindow::copyDate()
{
    FieldManager::Instance().copyField(ui->textDate);
}

void MainWindow::changePasswordVisibility()
{
    if(ui->eyePassword->isChecked())
        FieldManager::Instance().showField(ui->textPassword);
    else
        FieldManager::Instance().hideField(ui->textPassword);
}

void MainWindow::changePinVisibility()
{
    if(ui->eyePin->isChecked())
        FieldManager::Instance().showField(ui->textPin);
    else
        FieldManager::Instance().hideField(ui->textPin);
}

void MainWindow::changeSecretVisibility()
{
    if(ui->eyeSecret->isChecked())
        FieldManager::Instance().showField(ui->textSecret);
    else
        FieldManager::Instance().hideField(ui->textSecret);
}

void MainWindow::changeOldMasterVisibility()
{
    if(ui->eyeOldMaster->isChecked())
        FieldManager::Instance().showField(ui->textOldMaster);
    else
        FieldManager::Instance().hideField(ui->textOldMaster);
}

void MainWindow::changeNewMasterVisibility()
{
    if(ui->eyeNewMaster->isChecked())
        FieldManager::Instance().showField(ui->textNewMaster);
    else
        FieldManager::Instance().hideField(ui->textNewMaster);
}

void MainWindow::changeConfirmMasterVisibility()
{
    if(ui->eyeConfirmMaster->isChecked())
        FieldManager::Instance().showField(ui->textConfirmMaster);
    else
        FieldManager::Instance().hideField(ui->textConfirmMaster);
}
