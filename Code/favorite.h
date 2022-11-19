#ifndef FAVORITE_H
#define FAVORITE_H

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
#include <QMouseEvent>
#include "Artifact.h"
#include "data.h"
#include "upcombobox.h"
#include "FavoriteOri.h"
#include "favdelmod.h"

namespace Ui {
class Favorite;
}

class Favorite : public QWidget
{
    Q_OBJECT

public:
    explicit Favorite(QWidget *parent = nullptr,QString s0="");
    ~Favorite();
    void setWidget(int);
    int match(int);//匹配id，返回对应的[]
    void sortPosition();//将圣遗物按部位排序
    void showFav(int);//显示预设
    void timerEvent(QTimerEvent* event);
    void nameEdited(QString, int, QLineEdit *);//判断预设名称有没有重复，再写入

protected:
    int clock;

private slots:
    void on_close_clicked();

    void upComboBox_currentTextChanged(upComboBox* box, const QString &arg1);

    void on_flower_pressed();

    void on_feather_pressed();

    void on_sand_pressed();

    void on_cup_pressed();

    void on_head_pressed();

    void on_feather_clicked();

    void on_flower_clicked();

    void on_sand_clicked();

    void on_cup_clicked();

    void on_head_clicked();

    void on_add_clicked();

    void on_equip_clicked();

    void on_delete_2_clicked();

    void on_Save_clicked();

private:
    Ui::Favorite *ui;
    void changeBtnCli(QPushButton*, int, int, int, int);
    void changeBtnPre(QPushButton*, int, int, int);
    void changeBtnRea(QPushButton*, int, int, int);
    int selectedNum, Amount, num, favNum;
    int* SetPosId=NULL;
    QString s;
    QString posFlag;
    QString favPos;
    QPushButton **pBtn;
    QLabel **btnLabel;
    QLabel **btnLevel;
    QPushButton **btnStar;
    upComboBox *setFilter;
    Artifact* sorted[1500]={};
    QLineEdit **name=new QLineEdit*[200];
    QPushButton ***Art=new QPushButton**[200];
    QLabel ***artLabel=new QLabel**[200];
    QLabel ***artLevel=new QLabel**[200];
    QLabel **fav=new QLabel*[200];
    QPushButton ***artStar=new QPushButton**[200];
    FavDelMod* favdm;
};

#endif // FAVORITE_H
