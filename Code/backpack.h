#ifndef BACKPACK_H
#define BACKPACK_H

#include <QWidget>
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
#include <QHBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include "Artifact.h"
#include "data.h"
#include "isdelete.h"
#include "importmanually.h"
#include "upcombobox.h"

namespace Ui {
class Backpack;
}

class Backpack : public QWidget
{
    Q_OBJECT

public:
    explicit Backpack(QWidget *parent = nullptr,QString s0="");
    ~Backpack();
//    void timerEvent(QTimerEvent* event);
    void setWidget(int);
    int match(int);//匹配id，返回对应的[]

//protected:
//        int clock;

private slots:
    void on_close_clicked();

    void on_deleted_clicked();

    void on_modify_clicked();

    void on_filter_clicked();

    void upComboBox_currentTextChanged(upComboBox* box, const QString &arg1);

private:
    Ui::Backpack *ui;
    void changeBtnCli(QPushButton*, int, int, int, int);
    void changeBtnPre(QPushButton*, int, int);
    void changeBtnRea(QPushButton*, int, int);
    int selectedNum, Amount, num;
    QString s;
    QPushButton **pBtn;
    QLabel **btnLabel;
    QLabel **btnLevel;
    QPushButton **btnStar;
};

#endif // BACKPACK_H
