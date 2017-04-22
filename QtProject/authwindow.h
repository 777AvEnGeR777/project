#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class AuthWindow;
}

class AuthWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AuthWindow(QWidget *parent = 0);
    ~AuthWindow();
    bool GetResult();

private slots:
    void Authentication();
    void CreateMaster();

private:
    Ui::AuthWindow *ui;
    bool authResult;
    int attempts;
};

#endif // AUTHWINDOW_H
