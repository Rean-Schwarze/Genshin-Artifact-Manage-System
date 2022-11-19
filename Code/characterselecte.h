#ifndef CHARACTERSELECTE_H
#define CHARACTERSELECTE_H

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
#include "Character.h"
#include "data.h"

namespace Ui {
class CharacterSelecte;
}

class CharacterSelecte : public QWidget
{
    Q_OBJECT

public:
    explicit CharacterSelecte(QWidget *parent = nullptr);
    ~CharacterSelecte();

private slots:
    void on_Back_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_confirm_clicked();

private:
    Ui::CharacterSelecte *ui;
    void changeBtnCli(QPushButton*, int, int, int);
    void changeBtnPre(QPushButton*, int, int, int, int, int);
    void changeBtnRea(QPushButton*, int, int, int, int, int);
    int n[8];
    QLabel** element=new QLabel*[8];
    QLabel** elementText=new QLabel*[8];
    QPushButton** bg;
    QLabel** charIcon;
    QLabel** charText;
    QLabel** charElement;
    QPushButton** charTemp;
    QString Name, NameChinese;
};

#endif // CHARACTERSELECTE_H
