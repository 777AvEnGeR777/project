#include "mainwindow.h"
#include "authwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AuthWindow* authWnd = new AuthWindow();
    authWnd->exec();
    if(authWnd->GetResult() == false) {
        delete authWnd;
        return -1;
    }
    delete authWnd;

    MainWindow mainWnd;
    mainWnd.show();

    return a.exec();
}
