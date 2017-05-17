#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "accountform.h"
#include <QMainWindow>
#include <QMessageBox>

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
    void edit_account();
    void switch_account(QString item);

    void add_card();
    void edit_card();
    void switch_card(QString item);

    void toggleAccountsTab();
    void toggleCardsTab();
    void toggleSettingsTab();
private:
    Ui::MainWindow *ui;

    void hide_tabs();
    void build_accounts();
    void build_cards();
    void select_account(std::string name);
    void select_card(std::string name);

};

#endif // MAINWINDOW_H
