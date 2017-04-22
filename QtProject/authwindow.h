#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include "enums.h"
#include "Data.h"
#include "passwordstrengthchecker.h"

namespace Ui {
class AuthWindow;
}

class AuthWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AuthWindow(QWidget *parent = 0);
    ~AuthWindow();
    bool GetResult() { return authResult; }

protected:
    bool eventFilter(QObject *, QEvent *);

private slots:
    void Authentication();
    void CreateMaster();

private:
    Ui::AuthWindow *ui;
    bool authResult;
    int attempts;
};

#endif // AUTHWINDOW_H
