#include "isoverwrite.h"
#include "ui_isoverwrite.h"

isOverWrite::isOverWrite(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::isOverWrite)
{
    ui->setupUi(this);

}

isOverWrite::~isOverWrite()
{
    delete ui;
}

void isOverWrite::on_yes_clicked()
{
    this->close();
    Data::fileName = QFileDialog::getOpenFileName(
            this,
            tr("请选择Yas的扫描结果（mona.json）"),
            "QDir::currentPath()",
            tr("files(*.json)"));
    for(int i=0;i<Data::ArtAmount;i++)
    {
        delete Data::Art[i];
    }
    Data::ArtAmount=0;
    Import import;
    import.ImportFromFile(Data::Art, Data::ArtAmount , 1);
    for(int i=0;i<Data::Favorite_size;i++)
    {
        delete Data::Fav[i];
    }
    Data::Favorite_size=0;
}

