#include "favdelmod.h"
#include "ui_favdelmod.h"

FavDelMod::FavDelMod(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FavDelMod)
{
    ui->setupUi(this);
    ui->comboBox->addItem("删除");
    ui->comboBox->addItem("修改");
}

FavDelMod::~FavDelMod()
{
    delete ui;
}

void FavDelMod::on_no_clicked()
{
    this->close();
    Data::favTemp=-1;
}


void FavDelMod::on_lineEdit_textEdited(const QString &arg1)
{
    temp=arg1.toInt();
    if(temp>0&&temp<201)
    {
        Data::favTemp=temp-1;
    }
    else
    {
        ui->lineEdit->clear();
        QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","输入数据有误！");
    }
}


void FavDelMod::on_yes_clicked()
{
    if(flag==2) QMessageBox::StandardButton result=QMessageBox::information(this,"设置成功","点击左边圣遗物装备即可修改！");
    if(temp>0&&temp<201)
    {
        this->close();
        Data::favFlag=flag;
    }
    else QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","尚未输入序号！");
}


void FavDelMod::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1=="删除") flag=1;
    else if(arg1=="修改") flag=2;
}

