#ifndef ISOVERWRITE_H
#define ISOVERWRITE_H

#include <QDialog>
#include <QFile>
#include <QtGlobal>
#include <QtWidgets>
#include "data.h"
#include "Import.h"

namespace Ui {
class isOverWrite;
}

class isOverWrite : public QDialog
{
    Q_OBJECT

public:
    explicit isOverWrite(QWidget *parent = nullptr);
    ~isOverWrite();

private slots:
    void on_yes_clicked();

private:
    Ui::isOverWrite *ui;
};

#endif // ISOVERWRITE_H
