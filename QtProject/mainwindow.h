#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "accountform.h"
#include <QMainWindow>
#include <QMessageBox>
#include "enums.h"
#include "passwordstrengthchecker.h"

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

    void changeMaster();
    void passwordStrengthWatcher();

private:
    Ui::MainWindow *ui;

    TabTypes currentTab;

    void hide_tab();
    void build_accounts();
    void build_cards();

    void select_account(std::string name);
    void select_card(std::string name);

};

#endif // MAINWINDOW_H
