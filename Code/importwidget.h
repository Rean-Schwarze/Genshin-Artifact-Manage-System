#ifndef IMPORTWIDGET_H
#define IMPORTWIDGET_H

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
#include "Artifact.h"
#include "Character.h"
#include "Import.h"
#include "ImportCharacter.h"
#include "data.h"
#include "isoverwrite.h"
#include "importmanually.h"

namespace Ui {
class ImportWidget;
}

class ImportWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImportWidget(QWidget *parent = nullptr);
    ~ImportWidget();
    void setPix(QString);
    void sortPosition();//将圣遗物按部位排序

private slots:
    void on_Back_clicked();

    void on_ImportFromScan_clicked();

    void on_ImportManully_clicked();

    void on_Save_clicked();

private:
    Ui::ImportWidget *ui;
    QPixmap Pix;
    QSize Size;
    Artifact* sorted[1500]={};
};

#endif // IMPORTWIDGET_H
