#ifndef DATA_H
#define DATA_H

#include <QMainWindow>
#include <QObject>
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
#include "Artifact.h"
#include "Character.h"
#include "Weapon.h"
#include "FavoriteOri.h"

class Data
{
public:
    Data();
    static int ArtAmount;//圣遗物的数量
    static int* PositionAmount;//分别对应五个部位//，[x][0]为总数，[x][1,2,……]为id
    static int** SetAmount;//分别对应不同套装，[0][0]为总套装数，[x][0]为一个套装的总数，[x][1]为套装id，[x][2,3,...]为圣遗物id
    static int flag;//用来检测是否应该刷新仓库界面
    static int CharAmount[9];//导入角色的数量，012345678分别为总、火、水、雷、风、冰、岩、草元素、玩家人物的数量
    static int WeapAmount[6];//导入武器的数量，012345分别为总、单手剑、双手剑、弓、法器、长柄武器的数量
    static int Favorite_size;
    static int favTemp, favFlag;//删除、修改预设用,flag=1为删除，2为修改
    static Artifact* Art[1500];
    static Character** Char[200];
    static Weapon** Weap[200];
    static FavoriteOri* Fav[200];
    static QFile fileArt;
    static QFile fileChar;
    static QFile fileWeap;
    static QPixmap setBackgroundChar();//添加背景图片(随机)
    static QString fileName;
    static QFont ft;
    static void searchSet();//遍历，写入id
    static int selectedChar, charLevel ,selectedWeap, weapLevel, selectedFav;
    static bool matchCharWeap();//判断选择的人物和武器是否搭配
};

#endif // DATA_H
