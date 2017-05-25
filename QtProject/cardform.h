#ifndef CARDFORM_H
#define CARDFORM_H

#include <QDialog>

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
};

#endif // CARDFORM_H
