#ifndef RATING_H
#define RATING_H

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
#include "Artifact.h"
#include "Character.h"
#include "Weapon.h"
#include "data.h"
#include "favorite.h"
#include "FavoriteOri.h"
#include "characterselecte.h"
#include "weaponselect.h"

namespace Ui {
class Rating;
}

class Rating : public QWidget
{
    Q_OBJECT

public:
    explicit Rating(QWidget *parent = nullptr);
    ~Rating();
    void timerEvent(QTimerEvent* event);
    void setFav(int);//0为初始，1为刷新
    void setChar();
    void setWeap();

protected:
    int clock;

private slots:
    void on_Back_clicked();

    void upComboBox_currentTextChanged(upComboBox* box, const QString &arg1);

    void on_change1_clicked();

    void on_change2_clicked();

    void on_rate_clicked();

    void on_entryBox_currentTextChanged(const QString &arg1);

    double addEntry(QString e);

    void on_entryBox2_currentTextChanged(const QString &arg1);

private:
    Ui::Rating *ui;
    upComboBox *favFilter;
    QLabel ***Art=new QLabel**[200];
    QLabel ***artLabel=new QLabel**[200];
    QLabel ***artLevel=new QLabel**[200];
    QLabel ***artStar=new QLabel**[200];
    QLabel **fav=new QLabel*[200];
    QLabel **name=new QLabel*[200];
    QString Name, entryTemp1, entryTemp2;
    int level, numTemp;
    CharacterSelecte* charSelect=NULL;
    WeaponSelect* weapSelect=NULL;
    double artLife, artAttack, artDefend, lifeEntry, attackEntry, defendEntry, masteryEntry, rechargeEntry, criticalEntry, criDMGEntry, entryTemp;
};

#endif // RATING_H
