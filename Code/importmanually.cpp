#include "importmanually.h"
#include "ui_importmanually.h"

ImportManually::ImportManually(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImportManually)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    hide();
    ui->setBox->installEventFilter(this);
    ui->positionBox->installEventFilter(this);
    ui->maBox->installEventFilter(this);
    ui->sa1Box->installEventFilter(this);
    ui->sa2Box->installEventFilter(this);
    ui->sa3Box->installEventFilter(this);
    ui->sa4Box->installEventFilter(this);
}

//修改圣遗物属性
ImportManually::ImportManually(QWidget *parent, int flag, int n) :
    QWidget(parent),
    ui(new Ui::ImportManually)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    hide();

    if(flag==1)
    {
        ui->text->setText("修改圣遗物属性");
        num=n;
        //获取当前圣遗物信息
        setName=Data::Art[num]->Get_setName();
        position=Data::Art[num]->Get_position();
        star=Data::Art[num]->Get_star();
        level=Data::Art[num]->Get_level();
        MainAttribute=Data::Art[num]->Get_MainAttribute();
        MainAttributeValue=Data::Art[num]->Get_MainAttributeValue();
        SubAttribute1=Data::Art[num]->Get_SubAttribute1();
        SubAttributeValue1=Data::Art[num]->Get_SubAttributeValue1();
        SubAttribute2=Data::Art[num]->Get_SubAttribute2();
        SubAttributeValue2=Data::Art[num]->Get_SubAttributeValue2();
        SubAttribute3=Data::Art[num]->Get_SubAttribute3();
        SubAttributeValue3=Data::Art[num]->Get_SubAttributeValue3();
        SubAttribute4=Data::Art[num]->Get_SubAttribute4();
        SubAttributeValue4=Data::Art[num]->Get_SubAttributeValue4();
        id=114514;//区分导入新圣遗物和修改圣遗物（

        //套装初始设置
        ui->setBox->clear();
        QResource::registerResource(QDir::currentPath() + "/Resources.rcc");
        QJsonParseError err_rpt;
        QFile fileArt(":/Data/Artifact.json");
        fileArt.open(QIODevice::ReadOnly);
        QJsonDocument  root_Art = QJsonDocument::fromJson(fileArt.readAll(), &err_rpt);
        QJsonObject root_ArtObj = root_Art.object();
        QJsonValue artifact_Value = root_ArtObj.value("Artifact");
        QJsonArray array=artifact_Value.toArray();//转化为QJsonArray
        int artSize=array.size();
        QString setNameChinese, flowerName;
        for(int i=0;i<artSize;i++)
        {
            QJsonObject artifact_Obj = array.at(i).toObject();
            if(setName==artifact_Obj.value("setName").toString())
            {
                setNameChinese=artifact_Obj.value("setNameChinese").toString();
                flowerName=artifact_Obj.value("flower").toString();
                QPixmap artPix=QPixmap(":/Artifact/"+flowerName+".png");

                QIcon icon(":/Artifact/"+flowerName+".png");
                ui->setBox->addItem(icon,setNameChinese);

                setNameChinese.clear();
                flowerName.clear();
            }
        }

        //部位初始设置
        if(position=="flower") ui->positionBox->addItem("生之花");
        if(position=="feather") ui->positionBox->addItem("死之羽");
        if(position=="sand") ui->positionBox->addItem("时之沙");
        if(position=="cup") ui->positionBox->addItem("空之杯");
        if(position=="head") ui->positionBox->addItem("理之冠");
        //因为禁止修改部位，所以去掉了点击触发combobox刷新

        ui->starEdit->setText(QString::number(star));
        ui->levelEdit->setText(QString::number(level));

        //属性初始设置
        ui->maBox->addItem(Data::Art[num]->Get_MainAttributeChinese());
        ui->mavEdit->setText(QString::number(MainAttributeValue));
        ui->sa1Box->addItem(Data::Art[num]->Get_SubAttributeChinese1());
        ui->sav1Edit->setText(QString::number(SubAttributeValue1));
        ui->sa2Box->addItem(Data::Art[num]->Get_SubAttributeChinese2());
        ui->sav2Edit->setText(QString::number(SubAttributeValue2));
        ui->sa3Box->addItem(Data::Art[num]->Get_SubAttributeChinese3());
        ui->sav3Edit->setText(QString::number(SubAttributeValue3));
        ui->sa4Box->addItem(Data::Art[num]->Get_SubAttributeChinese4());
        ui->sav4Edit->setText(QString::number(SubAttributeValue4));
    }

    ui->setBox->installEventFilter(this);

    if(flag==0) ui->positionBox->installEventFilter(this);

    ui->maBox->installEventFilter(this);

    ui->sa1Box->installEventFilter(this);

    ui->sa2Box->installEventFilter(this);

    ui->sa3Box->installEventFilter(this);

    ui->sa4Box->installEventFilter(this);
}

ImportManually::~ImportManually()
{
    delete ui;
}

bool ImportManually::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        //套装
        if(obj == ui->setBox)
        {
            //处理鼠标点击事件
            QComboBox * setBox = qobject_cast<QComboBox *>(obj);

            QResource::registerResource(QDir::currentPath() + "/Resources.rcc");
            QJsonParseError err_rpt;
            QFile fileArt(":/Data/Artifact.json");
            fileArt.open(QIODevice::ReadOnly);
            QJsonDocument  root_Art = QJsonDocument::fromJson(fileArt.readAll(), &err_rpt);
            QJsonObject root_ArtObj = root_Art.object();
            QJsonValue artifact_Value = root_ArtObj.value("Artifact");
            QJsonArray array=artifact_Value.toArray();//转化为QJsonArray
            int artSize=array.size();
            QString setNameChinese;
            QString flowerName;

            setBox->clear();
            for(int i=0;i<artSize;i++)
            {
                QJsonObject artifact_Obj = array.at(i).toObject();
                setNameChinese=artifact_Obj.value("setNameChinese").toString();
                flowerName=artifact_Obj.value("flower").toString();
                QPixmap artPix=QPixmap(":/Artifact/"+flowerName+".png");

                QIcon icon(":/Artifact/"+flowerName+".png");
                ui->setBox->addItem(icon,setNameChinese);

                setNameChinese.clear();
                flowerName.clear();
            }
        }

        //部位
        if(obj == ui->positionBox)
        {
            QComboBox * positionBox = qobject_cast<QComboBox *>(obj);

            positionBox->clear();
            ui->positionBox->addItem("生之花");
            ui->positionBox->addItem("死之羽");
            ui->positionBox->addItem("时之沙");
            ui->positionBox->addItem("空之杯");
            ui->positionBox->addItem("理之冠");
        }

        //主属性
        if(obj == ui->maBox)
        {
            if(position=="flower"||position=="feather"||position=="sand"||position=="cup"||position=="head")
            {
                QComboBox * maBox = qobject_cast<QComboBox *>(obj);
                maBox->clear();

                if(position=="flower") ui->maBox->addItem("生命值");
                if(position=="feather") ui->maBox->addItem("攻击力");
                if(position=="sand")
                {
                    ui->maBox->addItem("生命值");
                    ui->maBox->addItem("攻击力");
                    ui->maBox->addItem("防御力");
                    ui->maBox->addItem("元素精通");
                    ui->maBox->addItem("元素充能效率");
                }
                if(position=="cup")
                {
                    ui->maBox->addItem("生命值");
                    ui->maBox->addItem("攻击力");
                    ui->maBox->addItem("防御力");
                    ui->maBox->addItem("元素精通");
                    ui->maBox->addItem("物理伤害加成");
                    ui->maBox->addItem("火元素伤害加成");
                    ui->maBox->addItem("水元素伤害加成");
                    ui->maBox->addItem("草元素伤害加成");
                    ui->maBox->addItem("雷元素伤害加成");
                    ui->maBox->addItem("风元素伤害加成");
                    ui->maBox->addItem("冰元素伤害加成");
                    ui->maBox->addItem("岩元素伤害加成");
                }
                if(position=="head")
                {
                    ui->maBox->addItem("生命值");
                    ui->maBox->addItem("攻击力");
                    ui->maBox->addItem("防御力");
                    ui->maBox->addItem("元素精通");
                    ui->maBox->addItem("暴击率");
                    ui->maBox->addItem("暴击伤害");
                    ui->maBox->addItem("治疗加成");
                }
            }
            else
            {
                QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","请先选择部位！");
            }
        }

        //副属性
        if(obj == ui->sa1Box)
        {
            QComboBox * sa1Box = qobject_cast<QComboBox *>(obj);
            sa1Box->clear();

            if(!MainAttribute.isEmpty())
            {
                if(MainAttribute!="lifeStatic") ui->sa1Box->addItem("生命值（小）");
                if(MainAttribute!="lifePercentage") ui->sa1Box->addItem("生命值（大）");
                ui->sa1Box->addItem("防御力（小）");
                if(MainAttribute!="defendPercentage") ui->sa1Box->addItem("防御力（大）");
                if(MainAttribute!="attackStatic") ui->sa1Box->addItem("攻击力（小）");
                if(MainAttribute!="attackPercentage") ui->sa1Box->addItem("攻击力（大）");
                if(MainAttribute!="elementalMastery") ui->sa1Box->addItem("元素精通");
                if(MainAttribute!="recharge") ui->sa1Box->addItem("元素充能效率");
                if(MainAttribute!="critical") ui->sa1Box->addItem("暴击率");
                if(MainAttribute!="criticalDamage") ui->sa1Box->addItem("暴击伤害");
            }
            else QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","请先选择主属性！");
        }
        if(obj == ui->sa2Box)
        {
            QComboBox * sa2Box = qobject_cast<QComboBox *>(obj);
            sa2Box->clear();

            if(!MainAttribute.isEmpty())
            {
                if(MainAttribute!="lifeStatic") ui->sa2Box->addItem("生命值（小）");
                if(MainAttribute!="lifePercentage") ui->sa2Box->addItem("生命值（大）");
                ui->sa2Box->addItem("防御力（小）");
                if(MainAttribute!="defendPercentage") ui->sa2Box->addItem("防御力（大）");
                if(MainAttribute!="attackStatic") ui->sa2Box->addItem("攻击力（小）");
                if(MainAttribute!="attackPercentage") ui->sa2Box->addItem("攻击力（大）");
                if(MainAttribute!="elementalMastery") ui->sa2Box->addItem("元素精通");
                if(MainAttribute!="recharge") ui->sa2Box->addItem("元素充能效率");
                if(MainAttribute!="critical") ui->sa2Box->addItem("暴击率");
                if(MainAttribute!="criticalDamage") ui->sa2Box->addItem("暴击伤害");
            }
            else QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","请先选择主属性！");
        }
        if(obj == ui->sa3Box)
        {
            QComboBox * sa3Box = qobject_cast<QComboBox *>(obj);
            sa3Box->clear();

            if(!MainAttribute.isEmpty())
            {
                if(MainAttribute!="lifeStatic") ui->sa3Box->addItem("生命值（小）");
                if(MainAttribute!="lifePercentage") ui->sa3Box->addItem("生命值（大）");
                ui->sa3Box->addItem("防御力（小）");
                if(MainAttribute!="defendPercentage") ui->sa3Box->addItem("防御力（大）");
                if(MainAttribute!="attackStatic") ui->sa3Box->addItem("攻击力（小）");
                if(MainAttribute!="attackPercentage") ui->sa3Box->addItem("攻击力（大）");
                if(MainAttribute!="elementalMastery") ui->sa3Box->addItem("元素精通");
                if(MainAttribute!="recharge") ui->sa3Box->addItem("元素充能效率");
                if(MainAttribute!="critical") ui->sa3Box->addItem("暴击率");
                if(MainAttribute!="criticalDamage") ui->sa3Box->addItem("暴击伤害");
            }
            else QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","请先选择主属性！");
        }
        if(obj == ui->sa4Box)
        {
            QComboBox * sa4Box = qobject_cast<QComboBox *>(obj);
            sa4Box->clear();

            if(!MainAttribute.isEmpty())
            {
                if(MainAttribute!="lifeStatic") ui->sa4Box->addItem("生命值（小）");
                if(MainAttribute!="lifePercentage") ui->sa4Box->addItem("生命值（大）");
                ui->sa4Box->addItem("防御力（小）");
                if(MainAttribute!="defendPercentage") ui->sa4Box->addItem("防御力（大）");
                if(MainAttribute!="attackStatic") ui->sa4Box->addItem("攻击力（小）");
                if(MainAttribute!="attackPercentage") ui->sa4Box->addItem("攻击力（大）");
                if(MainAttribute!="elementalMastery") ui->sa4Box->addItem("元素精通");
                if(MainAttribute!="recharge") ui->sa4Box->addItem("元素充能效率");
                if(MainAttribute!="critical") ui->sa4Box->addItem("暴击率");
                if(MainAttribute!="criticalDamage") ui->sa4Box->addItem("暴击伤害");
                ui->sa4Box->addItem("无");
            }
            else QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","请先选择主属性！");
        }
    }

    return QWidget::eventFilter(obj, event);
}

void ImportManually::on_back_clicked()
{
    this->hide();
}


void ImportManually::on_setBox_currentTextChanged(const QString &arg1)
{
    QResource::registerResource(QDir::currentPath() + "/Resources.rcc");
    QJsonParseError err_rpt;
    QFile fileArt(":/Data/Artifact.json");
    fileArt.open(QIODevice::ReadOnly);
    QJsonDocument  root_Art = QJsonDocument::fromJson(fileArt.readAll(), &err_rpt);
    QJsonObject root_ArtObj = root_Art.object();
    QJsonValue artifact_Value = root_ArtObj.value("Artifact");
    QJsonArray array=artifact_Value.toArray();//转化为QJsonArray
    for(int i=0;i<array.size();i++)
    {
        QJsonObject artifact_Obj = array.at(i).toObject();
        if(arg1==artifact_Obj.value("setNameChinese").toString())
        {
            setName=artifact_Obj.value("setName").toString();
        }
    }
}


void ImportManually::on_positionBox_currentTextChanged(const QString &arg1)
{
    QResource::registerResource(QDir::currentPath() + "/Resources.rcc");
    QJsonParseError err_rpt;
    QFile fileArt(":/Data/Artifact.json");
    fileArt.open(QIODevice::ReadOnly);
    QJsonDocument  root_Art = QJsonDocument::fromJson(fileArt.readAll(), &err_rpt);
    QJsonObject root_ArtObj = root_Art.object();
    QJsonValue artifact_Value = root_ArtObj.value("Artifact");
    QJsonArray array=artifact_Value.toArray();//转化为QJsonArray
    int size=array.size();
    QString Name;

    if(arg1=="生之花") position="flower";
    if(arg1=="死之羽") position="feather";
    if(arg1=="时之沙") position="sand";
    if(arg1=="空之杯") position="cup";
    if(arg1=="理之冠") position="head";

    for(int i=0;i<size;i++)
    {
        QJsonObject artifact_Obj = array.at(i).toObject();
        if(setName==artifact_Obj.value("setName").toString())
        {
            Name=artifact_Obj.value(position).toString();
        }
    }

    QPixmap PixArt=QPixmap(":/Artifact/"+Name+".png");

    QSize PixArtSize = PixArt.size()*0.8;//缩小一下
    PixArt.scaled(PixArtSize,Qt::KeepAspectRatioByExpanding);

    //设置背景图片透明度
    QPixmap temp(PixArt.size());
    temp.fill(Qt::transparent);

    QPainter p1(&temp);
    p1.setCompositionMode(QPainter::CompositionMode_Source);
    p1.drawPixmap(0, 0, PixArt);
    p1.setCompositionMode(QPainter::CompositionMode_DestinationIn);

    //根据QColor中第四个参数设置透明度，取值范围是0～255
    p1.fillRect(temp.rect(), QColor(0, 0, 0, 127));
    p1.end();
    PixArt = temp;

    QSize positionSize=ui->position->size();
    ui->bgPic->setGeometry(((positionSize.width()-PixArtSize.width())/2),((positionSize.height()-PixArtSize.height())/2),PixArtSize.width(),PixArtSize.height());
    ui->bgPic->setScaledContents(true);
    ui->bgPic->setPixmap(PixArt);
    ui->bgPic->show();

}


void ImportManually::on_starEdit_textEdited(const QString &arg1)
{
    if(arg1.toInt()==5)
    {
        star=arg1.toInt();
    }
    else
    {
        ui->starEdit->clear();
        QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","输入数据有误！");
    }
}


void ImportManually::on_levelEdit_textEdited(const QString &arg1)
{
    if(arg1.toInt()>-1&&arg1.toInt()<21)
    {
        level=arg1.toInt();
    }
    else
    {
        ui->levelEdit->clear();
        QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","输入数据有误！");
    }
}


void ImportManually::on_maBox_currentIndexChanged(int index)
{
    if(position=="flower")
    {
        MainAttribute = "lifeStatic";
    }
    if(position=="feather")
    {
        MainAttribute = "attackStatic";
    }
    if(position=="sand")
    {
        switch (index)
        {
        case 0:MainAttribute = "lifePercentage"; break;
        case 1:MainAttribute = "attackPercentage"; break;
        case 2:MainAttribute = "defendPercentage"; break;
        case 3:MainAttribute = "elementalMastery"; break;
        case 4:MainAttribute = "recharge"; break;
        }
    }
    if(position=="cup")
    {
        switch (index)
        {
        case 0:MainAttribute = "lifePercentage"; break;
        case 1:MainAttribute = "attackPercentage"; break;
        case 2:MainAttribute = "defendPercentage"; break;
        case 3:MainAttribute = "elementalMastery"; break;
        case 4:MainAttribute = "physicalBonus"; break;
        case 5:MainAttribute = "fireBonus"; break;
        case 6:MainAttribute = "waterBonus"; break;
        case 7:MainAttribute = "dendroBounus"; break;
        case 8:MainAttribute = "thunderBonus"; break;
        case 9:MainAttribute = "windBonus"; break;
        case 10:MainAttribute = "iceBonus"; break;
        case 11:MainAttribute = "rockBonus"; break;
        }
    }
    if(position=="head")
    {
        switch (index)
        {
        case 0:MainAttribute = "lifePercentage"; break;
        case 1:MainAttribute = "attackPercentage"; break;
        case 2:MainAttribute = "defendPercentage"; break;
        case 3:MainAttribute = "elementalMastery"; break;
        case 4:MainAttribute = "critical"; break;
        case 5:MainAttribute = "criticalDamage"; break;
        case 6:MainAttribute = "cureEffect"; break;
        }
    }
}


void ImportManually::on_mavEdit_textEdited(const QString &arg1)
{
    if((arg1.toDouble()>0||arg1.toDouble()==0)&&arg1.toDouble()<5000) MainAttributeValue=arg1.toDouble();
    else
    {
        ui->mavEdit->clear();
        QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","输入数据有误！");
    }
}


void ImportManually::on_sa1Box_textActivated(const QString &arg1)
{
    if(arg1=="生命值（小）") SubAttribute1="lifeStatic";
    if(arg1=="生命值（大）") SubAttribute1="lifePercentage";
    if(arg1=="防御力（小）") SubAttribute1="defendStatic";
    if(arg1=="防御力（大）") SubAttribute1="defendPercentage";
    if(arg1=="攻击力（小）") SubAttribute1="attackStatic";
    if(arg1=="攻击力（大）") SubAttribute1="attackPercentage";
    if(arg1=="元素精通") SubAttribute1="elementalMastery";
    if(arg1=="元素充能效率") SubAttribute1="recharge";
    if(arg1=="暴击率") SubAttribute1="critical";
    if(arg1=="暴击伤害") SubAttribute1="criticalDamage";
    if(SubAttribute1==SubAttribute2||SubAttribute1==SubAttribute3||SubAttribute1==SubAttribute4)
    {
        ui->sa1Box->clear();
        SubAttribute1.clear();
        QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","副属性重复！");
    }
}


void ImportManually::on_sav1Edit_textEdited(const QString &arg1)
{
    if((arg1.toDouble()>0||arg1.toDouble()==0)&&arg1.toDouble()<5000) SubAttributeValue1=arg1.toDouble();
    else
    {
        ui->sav1Edit->clear();
        QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","输入数据有误！");
    }
}

void ImportManually::on_sa2Box_textActivated(const QString &arg1)
{
    if(arg1=="生命值（小）") SubAttribute2="lifeStatic";
    if(arg1=="生命值（大）") SubAttribute2="lifePercentage";
    if(arg1=="防御力（小）") SubAttribute2="defendStatic";
    if(arg1=="防御力（大）") SubAttribute2="defendPercentage";
    if(arg1=="攻击力（小）") SubAttribute2="attackStatic";
    if(arg1=="攻击力（大）") SubAttribute2="attackPercentage";
    if(arg1=="元素精通") SubAttribute2="elementalMastery";
    if(arg1=="元素充能效率") SubAttribute2="recharge";
    if(arg1=="暴击率") SubAttribute2="critical";
    if(arg1=="暴击伤害") SubAttribute2="criticalDamage";
    if(SubAttribute2==SubAttribute1||SubAttribute2==SubAttribute3||SubAttribute2==SubAttribute4)
    {
        ui->sa2Box->clear();
        SubAttribute2.clear();
        QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","副属性重复！");
    }
}


void ImportManually::on_sav2Edit_textEdited(const QString &arg1)
{
    if((arg1.toDouble()>0||arg1.toDouble()==0)&&arg1.toDouble()<5000) SubAttributeValue2=arg1.toDouble();
    else
    {
        ui->sav2Edit->clear();
        QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","输入数据有误！");
    }
}

void ImportManually::on_sa3Box_textActivated(const QString &arg1)
{
    if(arg1=="生命值（小）") SubAttribute3="lifeStatic";
    if(arg1=="生命值（大）") SubAttribute3="lifePercentage";
    if(arg1=="防御力（小）") SubAttribute3="defendStatic";
    if(arg1=="防御力（大）") SubAttribute3="defendPercentage";
    if(arg1=="攻击力（小）") SubAttribute3="attackStatic";
    if(arg1=="攻击力（大）") SubAttribute3="attackPercentage";
    if(arg1=="元素精通") SubAttribute3="elementalMastery";
    if(arg1=="元素充能效率") SubAttribute3="recharge";
    if(arg1=="暴击率") SubAttribute3="critical";
    if(arg1=="暴击伤害") SubAttribute3="criticalDamage";
    if(SubAttribute3==SubAttribute1||SubAttribute3==SubAttribute2||SubAttribute3==SubAttribute4)
    {
        ui->sa3Box->clear();
        SubAttribute3.clear();
        QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","副属性重复！");
    }
}


void ImportManually::on_sav3Edit_textEdited(const QString &arg1)
{
    if((arg1.toDouble()>0||arg1.toDouble()==0)&&arg1.toDouble()<5000) SubAttributeValue3=arg1.toDouble();
    else
    {
        ui->sav3Edit->clear();
        QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","输入数据有误！");
    }
}

void ImportManually::on_sa4Box_textActivated(const QString &arg1)
{
    if(arg1=="生命值（小）") SubAttribute4="lifeStatic";
    if(arg1=="生命值（大）") SubAttribute4="lifePercentage";
    if(arg1=="防御力（小）") SubAttribute4="defendStatic";
    if(arg1=="防御力（大）") SubAttribute4="defendPercentage";
    if(arg1=="攻击力（小）") SubAttribute4="attackStatic";
    if(arg1=="攻击力（大）") SubAttribute4="attackPercentage";
    if(arg1=="元素精通") SubAttribute4="elementalMastery";
    if(arg1=="元素充能效率") SubAttribute4="recharge";
    if(arg1=="暴击率") SubAttribute4="critical";
    if(arg1=="暴击伤害") SubAttribute4="criticalDamage";
    if(arg1=="无")
    {
        SubAttribute4="none";
        SubAttributeValue4=0;
    }
    if(SubAttribute4==SubAttribute1||SubAttribute4==SubAttribute2||SubAttribute4==SubAttribute3)
    {
        ui->sa4Box->clear();
        SubAttribute4.clear();
        QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","副属性重复！");
    }
}


void ImportManually::on_sav4Edit_textEdited(const QString &arg1)
{
    if((arg1.toDouble()>0||arg1.toDouble()==0)&&arg1.toDouble()<5000) SubAttributeValue4=arg1.toDouble();
    else
    {
        ui->sav4Edit->clear();
        QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","输入数据有误！");
    }
}

void ImportManually::on_save_clicked()
{
    if(!SubAttribute1.isEmpty()&&!SubAttribute2.isEmpty()&&!SubAttribute3.isEmpty()&&!SubAttribute4.isEmpty())
    {
        if(SubAttribute4!="none")
        {
            if(SubAttributeValue1!=0&&SubAttributeValue2!=0&&SubAttributeValue3!=0&&SubAttributeValue4!=0)
            {
                if(id!=114514)//手动导入
                {
                    int temp=0;
                    for(int i=0;i<Data::ArtAmount;i++)//把现有圣遗物中id最大的赋给temp
                    {
                        if(Data::Art[i]->Get_id()>temp) temp=Data::Art[i]->Get_id();
                    }
                    temp++;//避免如果有圣遗物被删除或排过序后导致手动导入的圣遗物出现id重复的情况
                    Data::Art[Data::ArtAmount]=new Artifact(setName, position, MainAttribute, MainAttributeValue, SubAttribute1, SubAttributeValue1, SubAttribute2, SubAttributeValue2, SubAttribute3, SubAttributeValue3, SubAttribute4, SubAttributeValue4, level, star, temp);
                    Data::ArtAmount++;
                    clear();
                }
                else
                {
                    Data::Art[num]->modify(setName, position, MainAttribute, MainAttributeValue, SubAttribute1, SubAttributeValue1, SubAttribute2, SubAttributeValue2, SubAttribute3, SubAttributeValue3, SubAttribute4, SubAttributeValue4, level, star);
                    clear();
                    Data::flag=1;
                }
            }
            else QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","尚未输入完成！");
        }
        else
        {
            if(SubAttributeValue1!=0&&SubAttributeValue2!=0&&SubAttributeValue3!=0)
            {
                if(id!=114514)
                {
                    int temp=0;
                    for(int i=0;i<Data::ArtAmount;i++)//把现有圣遗物中id最大的赋给temp
                    {
                        if(Data::Art[i]->Get_id()>temp) temp=Data::Art[i]->Get_id();
                    }
                    temp++;//避免如果有圣遗物被删除或排过序后导致手动导入的圣遗物出现id重复的情况
                    Data::Art[Data::ArtAmount]=new Artifact(setName, position, MainAttribute, MainAttributeValue, SubAttribute1, SubAttributeValue1, SubAttribute2, SubAttributeValue2, SubAttribute3, SubAttributeValue3, SubAttribute4, 0, level, star, temp);
                    Data::ArtAmount++;
                    clear();
                }
                else
                {
                    Data::Art[num]->modify(setName, position, MainAttribute, MainAttributeValue, SubAttribute1, SubAttributeValue1, SubAttribute2, SubAttributeValue2, SubAttribute3, SubAttributeValue3, SubAttribute4, 0, level, star);
                    clear();
                    Data::flag=1;
                }
            }
            else QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","尚未输入完成！");
        }
    }
    else QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","尚未输入完成！");
}

void ImportManually::clear()
{
    setName.clear();
    position.clear();
    MainAttribute.clear();
    MainAttributeValue = 0;
    SubAttribute1.clear();
    SubAttributeValue1 = 0;
    SubAttribute2.clear();
    SubAttributeValue2 = 0;
    SubAttribute3.clear();
    SubAttributeValue3 = 0;
    SubAttribute4.clear();
    SubAttributeValue4 = 0;
    level = 0;
    star = 0;
}

