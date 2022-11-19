#include "importwidget.h"
#include "ui_importwidget.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"


ImportWidget::ImportWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImportWidget)
{
    ui->setupUi(this);
    //嵌入父窗口
    setGeometry(0,0,960,540);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    hide();

    setPix(":/BG/background.png");
    ui->bg->setScaledContents(true);
    ui->bg->setPixmap(Pix);

//    setPix(":/Icon/close.png");
//    ui->Back->setIcon(QIcon(Pix));
//    ui->Back->setIconSize(Size);

//    setPix(":/Icon/save.png");
//    ui->Save->setIcon(QIcon(Pix));
//    ui->Save->setIconSize(Size);
}

ImportWidget::~ImportWidget()
{
    delete ui;
}

void ImportWidget::setPix(QString s)
{
        Pix=QPixmap(s);
        Size = Pix.size()*0.5;//缩小一下
        Pix.scaled(Size,Qt::KeepAspectRatioByExpanding);
}

void ImportWidget::on_Back_clicked()
{
    this->hide();
}


void ImportWidget::on_ImportFromScan_clicked()
{
    if(Data::ArtAmount>0)
    {
        isOverWrite *isoverwrite=new isOverWrite();
        isoverwrite->show();
    }
    else
    {
        Data::fileName = QFileDialog::getOpenFileName(
                this,
                tr("请选择Yas的扫描结果（mona.json）"),
                "QDir::currentPath()",
                tr("files(*.json)"));
        Import import;
        import.ImportFromFile(Data::Art, Data::ArtAmount , 1);
    }
}


void ImportWidget::on_ImportManully_clicked()
{
    ImportManually *importman=new ImportManually(this,0);
    importman->show();
}


//void ImportWidget::on_Back_pressed()
//{
//    setPix(":/Icon/close_selected.png");
//    ui->Back->setIcon(QIcon(Pix));
//    ui->Back->setIconSize(Size);
//}


//void ImportWidget::on_Back_released()
//{
//    setPix(":/Icon/close.png");
//    ui->Back->setIcon(QIcon(Pix));
//    ui->Back->setIconSize(Size);
//}


//void ImportWidget::on_Save_pressed()
//{
//    setPix(":/Icon/save_selected.png");
//    ui->Save->setIcon(QIcon(Pix));
//    ui->Save->setIconSize(Size);
//}


//void ImportWidget::on_Save_released()
//{
//    setPix(":/Icon/save.png");
//    ui->Save->setIcon(QIcon(Pix));
//    ui->Save->setIconSize(Size);
//}

void ImportWidget::sortPosition()
{
    //先清空
    if(Data::PositionAmount!=NULL)
    {
        for(int i=0;i<Data::ArtAmount;i++)
        {
            delete[] sorted[i];
        }
        delete[] Data::PositionAmount;
        Data::PositionAmount=NULL;
    }

    Data::PositionAmount=new int[5];
    for(int i=0;i<5;i++)
    {
        Data::PositionAmount[i]=0;
    }
    for(int i=0;i<Data::ArtAmount;i++)
    {
        if(Data::Art[i]->Get_position()=="flower") Data::PositionAmount[0]++;
        if(Data::Art[i]->Get_position()=="feather") Data::PositionAmount[1]++;
        if(Data::Art[i]->Get_position()=="sand") Data::PositionAmount[2]++;
        if(Data::Art[i]->Get_position()=="cup") Data::PositionAmount[3]++;
        if(Data::Art[i]->Get_position()=="head") Data::PositionAmount[4]++;
    }

    int temp=0;
    for(int i=0;i<Data::ArtAmount;i++)
    {
        if(Data::Art[i]->Get_position()=="flower")
        {
            sorted[temp]=Data::Art[i];
            temp++;
        }
    }
    for(int i=0;i<Data::ArtAmount;i++)
    {
        if(Data::Art[i]->Get_position()=="feather")
        {
            sorted[temp]=Data::Art[i];
            temp++;
        }
    }
    for(int i=0;i<Data::ArtAmount;i++)
    {
        if(Data::Art[i]->Get_position()=="sand")
        {
            sorted[temp]=Data::Art[i];
            temp++;
        }
    }
    for(int i=0;i<Data::ArtAmount;i++)
    {
        if(Data::Art[i]->Get_position()=="cup")
        {
            sorted[temp]=Data::Art[i];
            temp++;
        }
    }
    for(int i=0;i<Data::ArtAmount;i++)
    {
        if(Data::Art[i]->Get_position()=="head")
        {
            sorted[temp]=Data::Art[i];
            temp++;
        }
    }
}

void ImportWidget::on_Save_clicked()
{
    int i=0;
    if(Data::ArtAmount>0)
    {
        sortPosition();
        // 以读写方式打开.json文件，若该文件不存在则会自动创建
        QFile fileSavedArt(QDir::currentPath()+"/savedArt.json");
        fileSavedArt.open(QIODevice::ReadWrite);
        // 清空文件中的原有内容
        fileSavedArt.resize(0);

        // 使用QJsonArray添加值，并写入文件
        QJsonArray flowerArray;
        for(i; i < Data::PositionAmount[0]; i++)
        {
            // 定义 { } 对象
            QJsonObject flowerObject ;
            flowerObject.insert("setName",sorted[i]->Get_setName());
            flowerObject.insert("position",sorted[i]->Get_position());
            //{ {} }
            QJsonObject mainTagObject;
            mainTagObject.insert("name",sorted[i]->Get_MainAttribute());
            mainTagObject.insert("value",sorted[i]->Get_MainAttributeValue());
            flowerObject.insert("mainTag",mainTagObject);
            //[ {} ]
            QJsonArray normalTagsArray;
            QJsonObject normalTagsObject1;
            normalTagsObject1.insert("name",sorted[i]->Get_SubAttribute1());
            normalTagsObject1.insert("value",sorted[i]->Get_SubAttributeValue1());
            normalTagsArray.append(normalTagsObject1);
            QJsonObject normalTagsObject2;
            normalTagsObject2.insert("name",sorted[i]->Get_SubAttribute2());
            normalTagsObject2.insert("value",sorted[i]->Get_SubAttributeValue2());
            normalTagsArray.append(normalTagsObject2);
            QJsonObject normalTagsObject3;
            normalTagsObject3.insert("name",sorted[i]->Get_SubAttribute3());
            normalTagsObject3.insert("value",sorted[i]->Get_SubAttributeValue3());
            normalTagsArray.append(normalTagsObject3);
            QJsonObject normalTagsObject4;
            normalTagsObject4.insert("name",sorted[i]->Get_SubAttribute4());
            normalTagsObject4.insert("value",sorted[i]->Get_SubAttributeValue4());
            normalTagsArray.append(normalTagsObject4);
            flowerObject.insert("normalTags",normalTagsArray);

            flowerObject.insert("level",sorted[i]->Get_level());
            flowerObject.insert("star",sorted[i]->Get_star());
            flowerObject.insert("id",sorted[i]->Get_id());

            // 定义 [ ] 对象
            flowerArray.append(flowerObject);
        }

        QJsonArray featherArray;
        for(i; i < Data::PositionAmount[0]+Data::PositionAmount[1]; i++)
        {
            // 定义 { } 对象
            QJsonObject featherObject ;
            featherObject.insert("setName",sorted[i]->Get_setName());
            featherObject.insert("position",sorted[i]->Get_position());
            //{ {} }
            QJsonObject mainTagObject;
            mainTagObject.insert("name",sorted[i]->Get_MainAttribute());
            mainTagObject.insert("value",sorted[i]->Get_MainAttributeValue());
            featherObject.insert("mainTag",mainTagObject);
            //[ {} ]
            QJsonArray normalTagsArray;
            QJsonObject normalTagsObject1;
            normalTagsObject1.insert("name",sorted[i]->Get_SubAttribute1());
            normalTagsObject1.insert("value",sorted[i]->Get_SubAttributeValue1());
            normalTagsArray.append(normalTagsObject1);
            QJsonObject normalTagsObject2;
            normalTagsObject2.insert("name",sorted[i]->Get_SubAttribute2());
            normalTagsObject2.insert("value",sorted[i]->Get_SubAttributeValue2());
            normalTagsArray.append(normalTagsObject2);
            QJsonObject normalTagsObject3;
            normalTagsObject3.insert("name",sorted[i]->Get_SubAttribute3());
            normalTagsObject3.insert("value",sorted[i]->Get_SubAttributeValue3());
            normalTagsArray.append(normalTagsObject3);
            QJsonObject normalTagsObject4;
            normalTagsObject4.insert("name",sorted[i]->Get_SubAttribute4());
            normalTagsObject4.insert("value",sorted[i]->Get_SubAttributeValue4());
            normalTagsArray.append(normalTagsObject4);
            featherObject.insert("normalTags",normalTagsArray);

            featherObject.insert("level",sorted[i]->Get_level());
            featherObject.insert("star",sorted[i]->Get_star());
            featherObject.insert("id",sorted[i]->Get_id());

            // 定义 [ ] 对象
            featherArray.append(featherObject);
        }

        QJsonArray sandArray;
        for(i; i < Data::PositionAmount[0]+Data::PositionAmount[1]+Data::PositionAmount[2]; i++)
        {
            // 定义 { } 对象
            QJsonObject sandObject ;
            sandObject.insert("setName",sorted[i]->Get_setName());
            sandObject.insert("position",sorted[i]->Get_position());
            //{ {} }
            QJsonObject mainTagObject;
            mainTagObject.insert("name",sorted[i]->Get_MainAttribute());
            mainTagObject.insert("value",sorted[i]->Get_MainAttributeValue());
            sandObject.insert("mainTag",mainTagObject);
            //[ {} ]
            QJsonArray normalTagsArray;
            QJsonObject normalTagsObject1;
            normalTagsObject1.insert("name",sorted[i]->Get_SubAttribute1());
            normalTagsObject1.insert("value",sorted[i]->Get_SubAttributeValue1());
            normalTagsArray.append(normalTagsObject1);
            QJsonObject normalTagsObject2;
            normalTagsObject2.insert("name",sorted[i]->Get_SubAttribute2());
            normalTagsObject2.insert("value",sorted[i]->Get_SubAttributeValue2());
            normalTagsArray.append(normalTagsObject2);
            QJsonObject normalTagsObject3;
            normalTagsObject3.insert("name",sorted[i]->Get_SubAttribute3());
            normalTagsObject3.insert("value",sorted[i]->Get_SubAttributeValue3());
            normalTagsArray.append(normalTagsObject3);
            QJsonObject normalTagsObject4;
            normalTagsObject4.insert("name",sorted[i]->Get_SubAttribute4());
            normalTagsObject4.insert("value",sorted[i]->Get_SubAttributeValue4());
            normalTagsArray.append(normalTagsObject4);
            sandObject.insert("normalTags",normalTagsArray);

            sandObject.insert("level",sorted[i]->Get_level());
            sandObject.insert("star",sorted[i]->Get_star());
            sandObject.insert("id",sorted[i]->Get_id());

            // 定义 [ ] 对象
            sandArray.append(sandObject);
        }

        QJsonArray cupArray;
        for(i; i < Data::PositionAmount[0]+Data::PositionAmount[1]+Data::PositionAmount[2]+Data::PositionAmount[3]; i++)
        {
            // 定义 { } 对象
            QJsonObject cupObject ;
            cupObject.insert("setName",sorted[i]->Get_setName());
            cupObject.insert("position",sorted[i]->Get_position());
            //{ {} }
            QJsonObject mainTagObject;
            mainTagObject.insert("name",sorted[i]->Get_MainAttribute());
            mainTagObject.insert("value",sorted[i]->Get_MainAttributeValue());
            cupObject.insert("mainTag",mainTagObject);
            //[ {} ]
            QJsonArray normalTagsArray;
            QJsonObject normalTagsObject1;
            normalTagsObject1.insert("name",sorted[i]->Get_SubAttribute1());
            normalTagsObject1.insert("value",sorted[i]->Get_SubAttributeValue1());
            normalTagsArray.append(normalTagsObject1);
            QJsonObject normalTagsObject2;
            normalTagsObject2.insert("name",sorted[i]->Get_SubAttribute2());
            normalTagsObject2.insert("value",sorted[i]->Get_SubAttributeValue2());
            normalTagsArray.append(normalTagsObject2);
            QJsonObject normalTagsObject3;
            normalTagsObject3.insert("name",sorted[i]->Get_SubAttribute3());
            normalTagsObject3.insert("value",sorted[i]->Get_SubAttributeValue3());
            normalTagsArray.append(normalTagsObject3);
            QJsonObject normalTagsObject4;
            normalTagsObject4.insert("name",sorted[i]->Get_SubAttribute4());
            normalTagsObject4.insert("value",sorted[i]->Get_SubAttributeValue4());
            normalTagsArray.append(normalTagsObject4);
            cupObject.insert("normalTags",normalTagsArray);

            cupObject.insert("level",sorted[i]->Get_level());
            cupObject.insert("star",sorted[i]->Get_star());
            cupObject.insert("id",sorted[i]->Get_id());

            // 定义 [ ] 对象
            cupArray.append(cupObject);
        }

        QJsonArray headArray;
        for(i; i < Data::PositionAmount[0]+Data::PositionAmount[1]+Data::PositionAmount[2]+Data::PositionAmount[3]+Data::PositionAmount[4]; i++)
        {
            // 定义 { } 对象
            QJsonObject headObject ;
            headObject.insert("setName",sorted[i]->Get_setName());
            headObject.insert("position",sorted[i]->Get_position());
            //{ {} }
            QJsonObject mainTagObject;
            mainTagObject.insert("name",sorted[i]->Get_MainAttribute());
            mainTagObject.insert("value",sorted[i]->Get_MainAttributeValue());
            headObject.insert("mainTag",mainTagObject);
            //[ {} ]
            QJsonArray normalTagsArray;
            QJsonObject normalTagsObject1;
            normalTagsObject1.insert("name",sorted[i]->Get_SubAttribute1());
            normalTagsObject1.insert("value",sorted[i]->Get_SubAttributeValue1());
            normalTagsArray.append(normalTagsObject1);
            QJsonObject normalTagsObject2;
            normalTagsObject2.insert("name",sorted[i]->Get_SubAttribute2());
            normalTagsObject2.insert("value",sorted[i]->Get_SubAttributeValue2());
            normalTagsArray.append(normalTagsObject2);
            QJsonObject normalTagsObject3;
            normalTagsObject3.insert("name",sorted[i]->Get_SubAttribute3());
            normalTagsObject3.insert("value",sorted[i]->Get_SubAttributeValue3());
            normalTagsArray.append(normalTagsObject3);
            QJsonObject normalTagsObject4;
            normalTagsObject4.insert("name",sorted[i]->Get_SubAttribute4());
            normalTagsObject4.insert("value",sorted[i]->Get_SubAttributeValue4());
            normalTagsArray.append(normalTagsObject4);
            headObject.insert("normalTags",normalTagsArray);

            headObject.insert("level",sorted[i]->Get_level());
            headObject.insert("star",sorted[i]->Get_star());
            headObject.insert("id",sorted[i]->Get_id());

            // 定义 [ ] 对象
            headArray.append(headObject);
        }

        // 定义根节点	也即是最外层 { }
        QJsonObject rootObject;
        // 插入元素
        rootObject.insert("flower",flowerArray);
        rootObject.insert("feather",featherArray);
        rootObject.insert("sand",sandArray);
        rootObject.insert("cup",cupArray);
        rootObject.insert("head",headArray);

        // 将json对象里的数据转换为字符串
        QJsonDocument doc;
        // 将object设置为本文档的主要对象
        doc.setObject(rootObject);

        fileSavedArt.write(doc.toJson());
        fileSavedArt.close();
        QMessageBox::StandardButton result=QMessageBox::information(this,"保存成功","导入圣遗物已保存到文件！");
    }
    else QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","当前尚未导入圣遗物！");
}

