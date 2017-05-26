#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "accountform.h"
#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include "enums.h"
#include "passwordstrengthchecker.h"
#include "stateaccount.h"
#include "istatebase.h"
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
    void add();
    void edit();
    void delete_item();
    void switch_account(QString item);


    void switch_card(QString item);

    void toggleAccountsTab();
    void toggleCardsTab();
    void toggleSettingsTab();

    void changeMaster();
    void passwordStrengthWatcher();

    void copyLogin();
    void copyPassword();
    void copyCardNumber();
    void copyOwner();
    void copyDate();

    void changePasswordVisibility();
    void changePinVisibility();
    void changeSecretVisibility();
    void changeOldMasterVisibility();
    void changeNewMasterVisibility();
    void changeConfirmMasterVisibility();
private:
    IStateBase *state;
    Ui::MainWindow *ui;

    TabTypes currentTab;

    void hide_tab();
    void rebuild();
    void build_accounts();
    void build_cards();

    void select_account(std::string name);
    void select_card(std::string name);

};

#endif // MAINWINDOW_H
