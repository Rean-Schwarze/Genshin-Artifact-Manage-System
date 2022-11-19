#ifndef IMPORTMANUALLY_H
#define IMPORTMANUALLY_H

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
#include <QIcon>
#include <QMessageBox>
#include "Artifact.h"
#include "Data.h"

namespace Ui {
class ImportManually;
}

class ImportManually : public QWidget, public Artifact
{
    Q_OBJECT

public:
    explicit ImportManually(QWidget *parent = nullptr);
    explicit ImportManually(QWidget *parent = nullptr, int flag=0,int n=0);//flag=0为手动导入，=1为修改圣遗物属性
    ~ImportManually();
    bool isComplete();
    void clear();

public slots:
    bool eventFilter(QObject *, QEvent *);

private slots:

    void on_back_clicked();

    void on_setBox_currentTextChanged(const QString &arg1);

    void on_positionBox_currentTextChanged(const QString &arg1);

    void on_starEdit_textEdited(const QString &arg1);

    void on_levelEdit_textEdited(const QString &arg1);

    void on_maBox_currentIndexChanged(int index);

    void on_mavEdit_textEdited(const QString &arg1);

    void on_sa1Box_textActivated(const QString &arg1);

    void on_sav1Edit_textEdited(const QString &arg1);

    void on_sa2Box_textActivated(const QString &arg1);

    void on_sav2Edit_textEdited(const QString &arg1);

    void on_sa3Box_textActivated(const QString &arg1);

    void on_sav3Edit_textEdited(const QString &arg1);

    void on_sa4Box_textActivated(const QString &arg1);

    void on_sav4Edit_textEdited(const QString &arg1);

    void on_save_clicked();

private:
    Ui::ImportManually *ui;
    int num;
};

#endif // IMPORTMANUALLY_H
