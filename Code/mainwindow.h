#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "importwidget.h"
#include "backpack.h"
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
#include <QTimerEvent>
#include "Artifact.h"
#include "Character.h"
#include "Weapon.h"
#include "Import.h"
#include "ImportCharacter.h"
#include "ImportWeapon.h"
#include "data.h"
#include "favorite.h"
#include "FavoriteOri.h"
#include "rating.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void timerEvent(QTimerEvent* event);
    void refreshBP(); //刷新仓库界面
    void readFavorite();//文件初始化导入收藏类id，然后通过id将目标圣遗物地址赋给收藏指针

protected:
    int clock;

private slots:

    void on_Import_clicked();

    void on_Display_clicked();

    void on_Favorite_clicked();

    void on_Rating_clicked();

private:
    Ui::MainWindow *ui;
    ImportWidget *importWidget=NULL;
    QLabel *statusLabel;
    QLabel *statusLabelRight;
    Backpack *backpack=NULL;
    int saveAmount;
    Favorite* favorite=NULL;
    Rating* rating=NULL;
};
#endif // MAINWINDOW_H
