#include "isdelete.h"
#include "ui_isdelete.h"

isDelete::isDelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::isDelete)
{
    ui->setupUi(this);
}

isDelete::isDelete(QWidget *parent, int n) :
    QDialog(parent),
    ui(new Ui::isDelete)
{
    ui->setupUi(this);
    num=n;
}

isDelete::~isDelete()
{
    delete ui;
}

void isDelete::on_yes_clicked()
{
    for (int j = num; j < Data::ArtAmount; j++)
    {
        Data::Art[j - 1] = Data::Art[j];
    }
    Data::ArtAmount--;
    Data::flag=1;
    this->close();
}

