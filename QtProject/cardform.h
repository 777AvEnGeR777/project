#ifndef CARDFORM_H
#define CARDFORM_H

#include <QDialog>
#include <Data.h>
#include <QMessageBox>
#include <Card.h>

namespace Ui {
class cardform;
}

class cardform : public QDialog
{
    Q_OBJECT

public:
    explicit cardform(QWidget *parent = 0);
    ~cardform();
    void set_card_name(std::string name);

private:
    Ui::cardform *ui;
    std::string account_name;

private slots:
    void save_card();
};

#endif // CARDFORM_H
