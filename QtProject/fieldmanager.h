#ifndef FIELDMANAGER_H
#define FIELDMANAGER_H
#include <QApplication>
#include <QLineEdit>
#include <QClipboard>
#include <QMessageBox>

class FieldManager
{
public:
    void showField(QLineEdit* lineEdit);
    void hideField(QLineEdit* lineEdit);
    void copyField(QLineEdit* lineEdit);
    static FieldManager& Instance();
private:
    FieldManager() {}
    FieldManager(const FieldManager&);
    FieldManager& operator=(FieldManager&);
};

#endif // FIELDMANAGER_H
