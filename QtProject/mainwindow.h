#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "accountform.h"
#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include "enums.h"
#include "passwordstrengthchecker.h"
#include "stateaccount.h"
#include "statebase.h"
#include "statecard.h"


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

    void add();
    void edit();
    void switch_account(QString item);

//    void add_card();
//    void edit_card();
    void switch_card(QString item);

    void toggleAccountsTab();
    void toggleCardsTab();
    void toggleSettingsTab();

    void changeMaster();
    void passwordStrengthWatcher();

private:
    class StateBase *state;
    Ui::MainWindow *ui;

    TabTypes currentTab;

    void hide_tab();
    void build_accounts();
    void build_cards();

    void select_account(std::string name);
    void select_card(std::string name);

};

#endif // MAINWINDOW_H
