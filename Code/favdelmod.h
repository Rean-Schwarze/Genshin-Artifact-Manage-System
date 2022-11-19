#ifndef FAVDELMOD_H
#define FAVDELMOD_H

#include <QDialog>
#include "data.h"

namespace Ui {
class FavDelMod;
}

class FavDelMod : public QDialog
{
    Q_OBJECT

public:
    explicit FavDelMod(QWidget *parent = nullptr);
    ~FavDelMod();

private slots:
    void on_no_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_yes_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::FavDelMod *ui;
    int temp,flag;
};

#endif // FAVDELMOD_H
