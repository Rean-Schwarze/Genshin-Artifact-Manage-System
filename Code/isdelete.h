#ifndef ISDELETE_H
#define ISDELETE_H

#include <QDialog>
#include "data.h"

namespace Ui {
class isDelete;
}

class isDelete : public QDialog
{
    Q_OBJECT

public:
    explicit isDelete(QWidget *parent = nullptr);
    explicit isDelete(QWidget *parent = nullptr, int n=0);
    ~isDelete();

private slots:
    void on_yes_clicked();

private:
    Ui::isDelete *ui;
    int num;
};

#endif // ISDELETE_H
