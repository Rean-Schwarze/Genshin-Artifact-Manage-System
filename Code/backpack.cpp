#include "backpack.h"
#include "ui_backpack.h"

Backpack::Backpack(QWidget *parent, QString s0) :
    QWidget(parent),
    ui(new Ui::Backpack)
{
    s=s0;
    ui->setupUi(this);
    //嵌入父窗口
    setGeometry(0,0,960,540);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    hide();

    QResource::registerResource(QDir::currentPath() + "/Resources.rcc");
    ui->verticalScrollBar->hide();
    ui->artifactArea->setVerticalScrollBar(ui->verticalScrollBar);
    ui->verticalScrollBar_2->hide();
    ui->detailArea->setVerticalScrollBar(ui->verticalScrollBar_2);

    setWidget(0);
}

Backpack::~Backpack()
{
    delete ui;
    for(int i=0;i<Amount;i++)
    {
        pBtn[i]->close();
        delete[] pBtn[i];
        btnLabel[i]->close();
        delete[] btnLabel[i];
        btnLevel[i]->close();
        delete[] btnLevel[i];
        btnStar[i]->close();
        delete[] btnStar[i];
    }
    delete[] pBtn;
    delete[] btnLabel;
    delete[] btnLevel;
    delete[] btnStar;
}

void Backpack::setWidget(int flag)//0为默认，1为刷新
{
    QString Name;
    int level, temp2;

    int n;
    if(flag==1)
    {
        for(int i=0;i<Amount;i++)
        {
            pBtn[i]->close();
            delete[] pBtn[i];
            btnLabel[i]->close();
            delete[] btnLabel[i];
            btnLevel[i]->close();
            delete[] btnLevel[i];
            btnStar[i]->close();
            delete[] btnStar[i];
        }
        delete[] pBtn;
        delete[] btnLabel;
        delete[] btnLevel;
        delete[] btnStar;
    }
    if(s=="全部"||s.contains("全部",Qt::CaseSensitive))
    {
        Amount=Data::ArtAmount;
    }
    else
    {
        QJsonParseError err_rpt;
        QFile fileArt(":/Data/Artifact.json");
        fileArt.open(QIODevice::ReadOnly);
        QJsonDocument  root_Art = QJsonDocument::fromJson(fileArt.readAll(), &err_rpt);
        QJsonObject root_ArtObj = root_Art.object();
        QJsonValue artifact_Value = root_ArtObj.value("Artifact");
        QJsonArray array=artifact_Value.toArray();//转化为QJsonArray
        int size =array.size();
        QString setNameChinese;
        int setId=0;
        for (int i = 0; i < size; i++)
        {
            QJsonObject artifact_Obj = array.at(i).toObject();
            setNameChinese = artifact_Obj.value("setNameChinese").toString();
            if(s.contains(setNameChinese,Qt::CaseSensitive))//检测传进来的QString是否包含套装名字（因为传进来的是比如"华馆梦醒形骸记【3】"）
            {
                setId=i;
            }
        }
        for(int i=1;i<=Data::SetAmount[0][0];i++)
        {
            if(setId==Data::SetAmount[i][1])
            {
                Amount=Data::SetAmount[i][0];//[i][1]是套装id，[i][0]是该套装下圣遗物数量
                temp2=i;
            }
        }
    }
    if (Amount % 8 != 0) n =  Amount/ 8 + 1;
    else n = Amount / 8;//n为行数
    ui->artifact->setGeometry(0,0,610,n*90);
    ui->artifactArea->setWidget(ui->artifact);
    if(n!=0)
    {
        pBtn = new QPushButton*[Amount];
        btnLabel =new QLabel*[Amount];
        btnLevel =new QLabel*[Amount];
        btnStar = new QPushButton*[Amount];

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < 8 && i * 8 + j< Amount; j++)
            {
                pBtn[i * 8 + j] = new QPushButton(ui->artifact);
                pBtn[i * 8 + j]->setGeometry(75*j,90*i,67,81);
                pBtn[i * 8 + j]->setIcon(QIcon(":/Icon/item5Bg.png"));
                pBtn[i * 8 + j]->setIconSize(QSize(67,81));
                if(s=="全部"||s.contains("全部",Qt::CaseSensitive)) flag=0;
                connect(pBtn[i * 8 + j],&QPushButton::clicked,pBtn[i * 8 + j],[=](){changeBtnCli(pBtn[i * 8 + j], j, i, temp2, flag);});
                connect(pBtn[i * 8 + j],&QPushButton::pressed,pBtn[i * 8 + j],[=](){changeBtnPre(pBtn[i * 8 + j], j, i);});
                connect(pBtn[i * 8 + j],&QPushButton::released,pBtn[i * 8 + j],[=](){changeBtnRea(pBtn[i * 8 + j], j, i);});
                pBtn[i * 8 + j]->show();

                //圣遗物图片显示
                if(s=="全部"||s.contains("全部",Qt::CaseSensitive))
                {
                    Name=Data::Art[i * 8 + j]->Get_Name();
                    level=Data::Art[i * 8 + j]->Get_level();
                }
                else
                {
                    Name=Data::Art[match(Data::SetAmount[temp2][i * 8 + j+2])]->Get_Name();
                    level=Data::Art[match(Data::SetAmount[temp2][i * 8 + j+2])]->Get_level();
                }
                btnLabel[i * 8 + j]=new QLabel(ui->artifact);
                btnLabel[i * 8 + j]->setGeometry(75*j+4,90*i+4,58,53);
                QPixmap Pix=QPixmap(":/Artifact/"+Name+".png");
                QSize pixSize=Pix.size()*0.25;
                btnLabel[i * 8 + j]->setGeometry(75*j+4+29-pixSize.width()/2,90*i+4+27-pixSize.height()/2,pixSize.width(),pixSize.height());
                btnLabel[i * 8 + j]->setStyleSheet("background-color: transparent;""border-image: url(:/Artifact/"+Name+".png);");
                btnLabel[i * 8 + j]->show();

                //等级
                btnLevel[i * 8 + j]=new QLabel(ui->artifact);
                btnLevel[i * 8 + j]->setGeometry(75*j,90*i+65,67,14);
                Data::ft.setPointSize(8);
                btnLevel[i * 8 + j]->setFont(Data::ft);
                btnLevel[i * 8 + j]->setAlignment(Qt::AlignCenter);
                btnLevel[i * 8 + j]->setStyleSheet("color:rgb(73,83,102)");
                btnLevel[i * 8 + j]->setText("+"+QString::number(level));
                btnLevel[i * 8 + j]->show();

                btnStar[i * 8 + j]=new QPushButton(ui->artifact);
                btnStar[i * 8 + j]->setGeometry(75*j,90*i,67,81);
                btnStar[i * 8 + j]->setStyleSheet("border-image: url(:/Icon/item5Bg_star.png)");
                btnStar[i * 8 + j]->show();
                connect(btnStar[i * 8 + j],&QPushButton::clicked,pBtn[i * 8 + j],&QPushButton::clicked);//套娃，因为显示在了真正的按钮上面，所以点它=点真正的按钮
                connect(btnStar[i * 8 + j],&QPushButton::pressed,pBtn[i * 8 + j],&QPushButton::pressed);
                connect(btnStar[i * 8 + j],&QPushButton::released,pBtn[i * 8 + j],&QPushButton::released);
            }
        }
    }
}

void Backpack::on_close_clicked()
{
    this->close();
}

void Backpack::changeBtnCli(QPushButton* btn, int j, int i, int temp2, int flag)
{
    if(flag==1)
    {
        selectedNum=match(Data::SetAmount[temp2][i * 8 + j+2]);
    }
    else selectedNum=i *8 + j;
    ui->name->setText(Data::Art[selectedNum]->Get_Name());
    QString Position;
    if(Data::Art[selectedNum]->Get_position()=="flower") Position="生之花";
    if(Data::Art[selectedNum]->Get_position()=="feather") Position="死之羽";
    if(Data::Art[selectedNum]->Get_position()=="sand") Position="时之沙";
    if(Data::Art[selectedNum]->Get_position()=="cup") Position="空之杯";
    if(Data::Art[selectedNum]->Get_position()=="head") Position="理之冠";
    ui->position->setText(Position);

    ui->ma->setText(Data::Art[selectedNum]->Get_MainAttributeChinese());
    if(Data::Art[selectedNum]->Get_MainAttributeValue()>1)
    {
        ui->mav->setText(QString::number(Data::Art[selectedNum]->Get_MainAttributeValue()));
    }
    else
    {
        ui->mav->setText(QString::number(Data::Art[selectedNum]->Get_MainAttributeValue()*100)+"%");
    }

    QString Name=Data::Art[selectedNum]->Get_Name();
    QPixmap Pix=QPixmap(":/Artifact/"+Name+".png");
    QSize pixSize=Pix.size()*0.42;
    ui->artPic->setGeometry(129+105/2-pixSize.width()/2,33+98/2-pixSize.height()/2,pixSize.width(),pixSize.height());
    ui->artPic->setStyleSheet("background-color: transparent;""border-image: url(:/Artifact/"+Name+".png);");
    ui->artPic->show();

    ui->level->setText("+"+QString::number(Data::Art[selectedNum]->Get_level()));

    if(Data::Art[selectedNum]->Get_SubAttributeValue1()>1)
    {
        ui->sa1->setText("·"+Data::Art[selectedNum]->Get_SubAttributeChinese1()+"+"+QString::number(Data::Art[selectedNum]->Get_SubAttributeValue1()));
    }
    else
    {
        ui->sa1->setText("·"+Data::Art[selectedNum]->Get_SubAttributeChinese1()+"+"+QString::number(Data::Art[selectedNum]->Get_SubAttributeValue1()*100)+"%");
    }
    if(Data::Art[selectedNum]->Get_SubAttributeValue2()>1)
    {
        ui->sa2->setText("·"+Data::Art[selectedNum]->Get_SubAttributeChinese2()+"+"+QString::number(Data::Art[selectedNum]->Get_SubAttributeValue2()));
    }
    else
    {
        ui->sa2->setText("·"+Data::Data::Art[selectedNum]->Get_SubAttributeChinese2()+"+"+QString::number(Data::Art[selectedNum]->Get_SubAttributeValue2()*100)+"%");
    }
    if(Data::Art[selectedNum]->Get_SubAttributeValue3()>1)
    {
        ui->sa3->setText("·"+Data::Art[selectedNum]->Get_SubAttributeChinese3()+"+"+QString::number(Data::Art[selectedNum]->Get_SubAttributeValue3()));
    }
    else
    {
        ui->sa3->setText("·"+Data::Art[selectedNum]->Get_SubAttributeChinese3()+"+"+QString::number(Data::Art[selectedNum]->Get_SubAttributeValue3()*100)+"%");
    }
    if(Data::Art[selectedNum]->Get_SubAttribute4()!="none")
    {
        if(Data::Art[selectedNum]->Get_SubAttributeValue4()>1)
        {
            ui->sa4->setText("·"+Data::Art[selectedNum]->Get_SubAttributeChinese4()+"+"+QString::number(Data::Art[selectedNum]->Get_SubAttributeValue4()));
        }
        else
        {
            ui->sa4->setText("·"+Data::Art[selectedNum]->Get_SubAttributeChinese4()+"+"+QString::number(Data::Art[selectedNum]->Get_SubAttributeValue4()*100)+"%");
        }
    }
    //获取↓↓↓↓
    QString setname, setNameChinese, twoPieceSet, fourPieceSet;
    setname=Data::Art[selectedNum]->Get_setName();
    QJsonParseError err_rpt;
    QFile fileArt(":/Data/Artifact.json");
    fileArt.open(QIODevice::ReadOnly);
    QJsonDocument  root_Art = QJsonDocument::fromJson(fileArt.readAll(), &err_rpt);
    QJsonObject root_ArtObj = root_Art.object();
    QJsonValue artifact_Value = root_ArtObj.value("Artifact");
    QJsonArray array=artifact_Value.toArray();//转化为QJsonArray
    int size =array.size();
    QString temp;
    for (int i = 0; i < size; i++)
    {
        QJsonObject artifact_Obj = array.at(i).toObject();
        temp = artifact_Obj.value("setName").toString();
        if (setname == temp)
        {
            setNameChinese = artifact_Obj.value("setNameChinese").toString();
            twoPieceSet = artifact_Obj.value("2PieceSet").toString();
            fourPieceSet = artifact_Obj.value("4PieceSet").toString();
        }
        temp.clear();
    }
    ui->setName->setText(setNameChinese+"：");
    ui->twoPieceSet->setText("   2件套："+twoPieceSet);
    ui->twoPieceSet->adjustSize();
    ui->fourPieceSet->setGeometry(13,282+ui->twoPieceSet->size().height()+4,218,21);
    ui->fourPieceSet->setText("   4件套："+fourPieceSet);
    ui->fourPieceSet->adjustSize();
    ui->detail_bg2->setGeometry(0,174,246,21*5+ui->twoPieceSet->size().height()+ui->fourPieceSet->size().height()+10);
    ui->detail_bg3->setGeometry(0,174+ui->detail_bg2->size().height(),246,3);
    ui->detail->adjustSize();
}

void Backpack::changeBtnPre(QPushButton* btn, int j, int i)
{
    btn->setGeometry(75*j-3,90*i-3,73,87);
    btn->setIcon(QIcon(":/Icon/item5Bg_selected.png"));
    btn->setIconSize(QSize(73,87));
}

void Backpack::changeBtnRea(QPushButton* btn, int j, int i)
{
    btn->setGeometry(75*j,90*i,67,81);
    btn->setIcon(QIcon(":/Icon/item5Bg.png"));
    btn->setIconSize(QSize(67,81));
}

void Backpack::on_deleted_clicked()
{
    isDelete *isdelete=new isDelete(this,selectedNum);
    isdelete->show();
}



void Backpack::on_modify_clicked()
{
    ImportManually *importman=new ImportManually(this,1,selectedNum);
    importman->show();
}


void Backpack::on_filter_clicked()
{
    upComboBox *setFilter=new upComboBox(this,1);
    //设置滚动条
    setFilter->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    setFilter->setGeometry(80,488-31,226,31);
    setFilter->setMaximumHeight(440);
    QIcon Icon(":/Icon/art_icon.png");
    setFilter->addItem(Icon,"全部【"+QString::number(Data::ArtAmount)+"】");

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

    Data::searchSet();

    for(int j=1;j<=Data::SetAmount[0][0];j++)
    {
        QJsonObject artifact_Obj = array.at(Data::SetAmount[j][1]).toObject();
        setNameChinese=artifact_Obj.value("setNameChinese").toString();
        flowerName=artifact_Obj.value("flower").toString();

        QIcon icon(":/Artifact/"+flowerName+".png");
        setFilter->addItem(icon,setNameChinese+"【"+QString::number(Data::SetAmount[j][0])+"】");

        setNameChinese.clear();
        flowerName.clear();
    }
    setFilter->show();
    connect(setFilter,&QComboBox::currentTextChanged,this,[=](){upComboBox_currentTextChanged(setFilter,setFilter->currentText());});
}

void Backpack::upComboBox_currentTextChanged(upComboBox* box, const QString &arg1)
{
    if(arg1.contains("全部",Qt::CaseSensitive)) box->hide();
    s=arg1;
    setWidget(1);
}

int Backpack::match(int id)
{
    for(int i=0;i<Data::ArtAmount;i++)
    {
        if(id==Data::Art[i]->Get_id()) return i;
    }
}

