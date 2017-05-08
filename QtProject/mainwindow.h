#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "accountform.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_tabWidget_destroyed();

    void add_account();
    void edit_account(QListWidgetItem* item);

private:
    Ui::MainWindow *ui;

    void build_accounts();

};

#endif // MAINWINDOW_H
