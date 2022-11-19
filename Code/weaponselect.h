#ifndef WEAPONSELECT_H
#define WEAPONSELECT_H

#include <QWidget>
#include <QWidget>
#include <QLabel>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QString>
#include <QFile>
#include <QDir>
#include <QResource>
#include <QPixmap>
#include <QPainter>
#include <QtGlobal>
#include <QtWidgets>
#include <QPainter>
#include <QDialog>
#include "Weapon.h"
#include "data.h"

namespace Ui {
class WeaponSelect;
}

class WeaponSelect : public QWidget
{
    Q_OBJECT

public:
    explicit WeaponSelect(QWidget *parent = nullptr);
    ~WeaponSelect();
    void detailClear();

private slots:
    void on_Back_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_confirm_clicked();

private:
    Ui::WeaponSelect *ui;
    void changeBtnCli(QPushButton*, int, int, int);
    void changeBtnPre(QPushButton*, int, int, int);
    void changeBtnRea(QPushButton*, int, int, int);
    int n[5], Amount;
    QLabel** typeText=new QLabel*[5];
    QPushButton** bg;
    QLabel** weapIcon;
    QLabel** weapText;
    QPushButton** weapTemp;
    QString Name, NameChinese, typeChinese;
};

#endif // WEAPONSELECT_H
