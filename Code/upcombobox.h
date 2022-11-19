#ifndef UPCOMBOBOX_H
#define UPCOMBOBOX_H

#include <QObject>
#include <QWidget>
#include <QComboBox>
#include <QFile>
#include "data.h"

class upComboBox: public QComboBox
{
    Q_OBJECT
public:
    upComboBox(QWidget *parent = nullptr, int flag=0);//12分别代表不同的box

protected:
    void showPopup() override;
    QFile qss;
};

#endif // UPCOMBOBOX_H
