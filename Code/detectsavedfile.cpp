#include "detectsavedfile.h"
#include "ui_detectsavedfile.h"

detectSavedFile::detectSavedFile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::detectSavedFile)
{
    ui->setupUi(this);
}

detectSavedFile::~detectSavedFile()
{
    delete ui;
}
