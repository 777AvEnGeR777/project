#include "fieldmanager.h"

void FieldManager::showField(QLineEdit* lineEdit){
    lineEdit->setEchoMode(QLineEdit::Normal);
}

void FieldManager::hideField(QLineEdit* lineEdit){
    lineEdit->setEchoMode(QLineEdit::Password);
}

void FieldManager::copyField(QLineEdit* lineEdit){
    if(QClipboard* c = QApplication::clipboard()){
        c->setText(lineEdit->text());
    }
    else {
        QMessageBox::critical(nullptr, "Error!", "\nError caused by clipboard!\n", QMessageBox::Ok);
    }
}

FieldManager &FieldManager::Instance(){
    static FieldManager instance;
    return instance;
}
