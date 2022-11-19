#include "favorite.h"
#include "ui_favorite.h"

Favorite::Favorite(QWidget *parent, QString s0) :
    QWidget(parent),
    ui(new Ui::Favorite)
{
    s=s0;
    QResource::registerResource(QDir::currentPath() + "/Resources.rcc");
    ui->setupUi(this);
    //嵌入父窗口
    setGeometry(0,0,960,540);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    hide();

    //设置随机背景
    srand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int tempBg =rand()%6;
    QString bgName;
    if(tempBg==0) bgName="Anemo";
    if(tempBg==1) bgName="Cryo";
    if(tempBg==2) bgName="Electro";
    if(tempBg==3) bgName="Geo";
    if(tempBg==4) bgName="Hydro";
    if(tempBg==5) bgName="Pryo";
    ui->bg->setStyleSheet("border-image: url(:/BG/"+bgName+".jpg)");

    //初始化
    favNum=-1;
    //设置时钟为1s
    clock=this->startTimer(1000);
    ui->equip->setDisabled(true);//这个按钮只有在选择了仓库中圣遗物之后才可以按
    ui->verticalScrollBar->hide();
    ui->artifactArea->setVerticalScrollBar(ui->verticalScrollBar);
    ui->verticalScrollBar_2->hide();
    ui->detailArea->setVerticalScrollBar(ui->verticalScrollBar_2);
    ui->verticalScrollBar_3->hide();
    ui->favoriteArea->setVerticalScrollBar(ui->verticalScrollBar_3);
    ui->ma->hide();
    ui->mav->hide();
    ui->level->hide();
    ui->star->hide();

    ui->flower->setIcon(QIcon(":/Icon/flower_selected.png"));
    ui->flower->setIconSize(QSize(55,48));
    ui->feather->setIcon(QIcon(":/Icon/feather.png"));
    ui->feather->setIconSize(QSize(55,48));
    ui->sand->setIcon(QIcon(":/Icon/sand.png"));
    ui->sand->setIconSize(QSize(55,48));
    ui->cup->setIcon(QIcon(":/Icon/cup.png"));
    ui->cup->setIconSize(QSize(55,48));
    ui->head->setIcon(QIcon(":/Icon/head.png"));
    ui->head->setIconSize(QSize(55,48));

    setFilter=new upComboBox(this,2);
    setFilter->setGeometry(30,495,253,30);
    //设置滚动条
    setFilter->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setFilter->setMaximumHeight(440);

    QIcon Icon(":/Icon/art_icon.png");
    setFilter->addItem(Icon,"全部");
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
        setFilter->addItem(icon,setNameChinese);

        setNameChinese.clear();
        flowerName.clear();
    }
    setFilter->show();
    connect(setFilter,&QComboBox::currentTextChanged,this,[=](){upComboBox_currentTextChanged(setFilter,setFilter->currentText());});

    sortPosition();
    posFlag="flower";

    setWidget(0);
    showFav(0);
}

Favorite::~Favorite()
{
    delete ui;
}

void Favorite::setWidget(int flag)//flag：0为默认，1为刷新
{
    QString Name;
    int level, temp, temp2;

    int n;
    if(flag==1)
    {
        //先清空
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
        if(SetPosId!=NULL)
        {
            delete[] SetPosId;
            SetPosId=NULL;
        }
        if(Amount>0)
        {
            delete[] pBtn;
            delete[] btnLabel;
            delete[] btnLevel;
            delete[] btnStar;
        }
    }
    if(s=="全部"||s.contains("全部",Qt::CaseSensitive))
    {
        if(posFlag=="flower") Amount=Data::PositionAmount[0];
        if(posFlag=="feather") Amount=Data::PositionAmount[1];
        if(posFlag=="sand") Amount=Data::PositionAmount[2];
        if(posFlag=="cup") Amount=Data::PositionAmount[3];
        if(posFlag=="head") Amount=Data::PositionAmount[4];
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
            if(s==setNameChinese||s.contains(setNameChinese,Qt::CaseSensitive))//检测传进来的QString是否包含套装名字（因为传进来的是比如"华馆梦醒形骸记【3】"）
            {
                setId=i;
            }
        }
        for(int i=1;i<=Data::SetAmount[0][0];i++)
        {
            if(setId==Data::SetAmount[i][1])//[i][1]是套装id，[i][0]是该套装下圣遗物数量
            {
                Amount=0;
                for(int j=2;j<=Data::SetAmount[i][0]+1;j++)
                {
                    if(sorted[match(Data::SetAmount[i][j])]->Get_position()==posFlag) Amount++;
                }
                temp2=i;
                if(Amount>0) SetPosId=new int[Amount];
            }
        }
        int setposnum=0;
        for(int j=2;j<=Data::SetAmount[temp2][0]+1;j++)
        {
            if(sorted[match(Data::SetAmount[temp2][j])]->Get_position()==posFlag)
            {
                SetPosId[setposnum]=match(Data::SetAmount[temp2][j]);
                setposnum++;
            }
        }
    }
    if (Amount % 4 != 0) n =  Amount/ 4 + 1;
    else n = Amount / 4;//n为行数
    if(Amount==0) n=0;
    ui->artifact->setGeometry(0,0,300,n*90);
    ui->artifactArea->setWidget(ui->artifact);
    if(n!=0)
    {
        pBtn = new QPushButton*[Amount];
        btnLabel =new QLabel*[Amount];
        btnLevel =new QLabel*[Amount];
        btnStar = new QPushButton*[Amount];

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < 4 && i * 4 + j< Amount; j++)
            {
                temp=i * 4 + j;
                pBtn[temp] = new QPushButton(ui->artifact);
                pBtn[temp]->setGeometry(75*j,90*i,67,81);
                pBtn[temp]->setIcon(QIcon(":/Icon/item5Bg.png"));
                pBtn[temp]->setIconSize(QSize(67,81));
//                if(s=="全部") flag=0;
                connect(pBtn[temp],&QPushButton::clicked,pBtn[temp],[=](){changeBtnCli(pBtn[temp], j, i, temp2, flag);});
                connect(pBtn[temp],&QPushButton::pressed,pBtn[temp],[=](){changeBtnPre(pBtn[temp], j, i, 1);});
                connect(pBtn[temp],&QPushButton::released,pBtn[temp],[=](){changeBtnRea(pBtn[temp], j, i, 1);});
                pBtn[temp]->show();

                //圣遗物图片显示

                if(s=="全部"||s.contains("全部",Qt::CaseSensitive))
                {
                    if(posFlag=="flower")
                    {
                        Name=sorted[temp]->Get_Name();
                        level=sorted[temp]->Get_level();
                    }
                    if(posFlag=="feather")
                    {
                        Name=sorted[temp+Data::PositionAmount[0]]->Get_Name();
                        level=sorted[temp+Data::PositionAmount[0]]->Get_level();
                    }
                    if(posFlag=="sand")
                    {
                        Name=sorted[temp+Data::PositionAmount[0]+Data::PositionAmount[1]]->Get_Name();
                        level=sorted[temp+Data::PositionAmount[0]+Data::PositionAmount[1]]->Get_level();
                    }
                    if(posFlag=="cup")
                    {
                        Name=sorted[temp+Data::PositionAmount[0]+Data::PositionAmount[1]+Data::PositionAmount[2]]->Get_Name();
                        level=sorted[temp+Data::PositionAmount[0]+Data::PositionAmount[1]+Data::PositionAmount[2]]->Get_level();
                    }
                    if(posFlag=="head")
                    {
                        Name=sorted[temp+Data::PositionAmount[0]+Data::PositionAmount[1]+Data::PositionAmount[2]+Data::PositionAmount[3]]->Get_Name();
                        level=sorted[temp+Data::PositionAmount[0]+Data::PositionAmount[1]+Data::PositionAmount[2]+Data::PositionAmount[3]]->Get_level();
                    }
                }
                else
                {
                    Name=sorted[SetPosId[temp]]->Get_Name();
                    level=sorted[SetPosId[temp]]->Get_level();
                }
                btnLabel[temp]=new QLabel(ui->artifact);
                btnLabel[temp]->setGeometry(75*j+4,90*i+4,58,53);
                QPixmap Pix=QPixmap(":/Artifact/"+Name+".png");
                QSize pixSize=Pix.size()*0.25;
                btnLabel[temp]->setGeometry(75*j+4+29-pixSize.width()/2,90*i+4+27-pixSize.height()/2,pixSize.width(),pixSize.height());
                btnLabel[temp]->setStyleSheet("background-color: transparent;""border-image: url(:/Artifact/"+Name+".png);");
                btnLabel[temp]->show();

                //等级
                btnLevel[temp]=new QLabel(ui->artifact);
                btnLevel[temp]->setGeometry(75*j,90*i+65,67,14);
                Data::ft.setPointSize(8);
                btnLevel[temp]->setFont(Data::ft);
                btnLevel[temp]->setAlignment(Qt::AlignCenter);
                btnLevel[temp]->setStyleSheet("color:rgb(73,83,102)");
                btnLevel[temp]->setText("+"+QString::number(level));
                btnLevel[temp]->show();

                btnStar[temp]=new QPushButton(ui->artifact);
                btnStar[temp]->setGeometry(75*j,90*i,67,81);
                btnStar[temp]->setStyleSheet("border-image: url(:/Icon/item5Bg_star.png)");
                btnStar[temp]->show();
                connect(btnStar[temp],&QPushButton::clicked,pBtn[temp],&QPushButton::clicked);//套娃，因为显示在了真正的按钮上面，所以点它=点真正的按钮
                connect(btnStar[temp],&QPushButton::pressed,pBtn[temp],&QPushButton::pressed);
                connect(btnStar[temp],&QPushButton::released,pBtn[temp],&QPushButton::released);
            }
        }
    }
}

void Favorite::on_close_clicked()
{
    //当前预设输入完毕才能关闭（
    if(Data::Favorite_size==0||(Data::Favorite_size>0&&!Data::Fav[Data::Favorite_size-1]->isEmpty())) this->hide();
    else QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","当前预设尚未输入完成！");
}

void Favorite::changeBtnCli(QPushButton* btn, int j, int i, int temp2, int flag)//flag=1为仓库的显示，2为套装预设的显示
{
    if(flag==1)
    {
        ui->equip->setDisabled(false);//选中仓库中圣遗物后，可以按
        int temp=i *4 + j;
        if(s=="全部"||s.contains("全部",Qt::CaseSensitive))
        {
            if(posFlag=="flower")
            {
                 selectedNum=temp;
            }
            if(posFlag=="feather")
            {
                selectedNum=temp+Data::PositionAmount[0];
            }
            if(posFlag=="sand")
            {
                selectedNum=temp+Data::PositionAmount[0]+Data::PositionAmount[1];
            }
            if(posFlag=="cup")
            {
                selectedNum=temp+Data::PositionAmount[0]+Data::PositionAmount[1]+Data::PositionAmount[2];
            }
            if(posFlag=="head")
            {
                selectedNum=temp+Data::PositionAmount[0]+Data::PositionAmount[1]+Data::PositionAmount[2]+Data::PositionAmount[3];
            }
        }
        else selectedNum=SetPosId[i * 4 + j];
    }
    else if(flag==0)
    {
        ui->equip->setDisabled(false);//选中仓库中圣遗物后，可以按
        selectedNum=i *4 + j;
    }
    else if(flag==2)
    {
        ui->equip->setDisabled(true);//与此同时，装备这个按钮不可以按
        favNum=i;
        if(j==0) favPos="flower";
        if(j==1) favPos="feather";
        if(j==2) favPos="sand";
        if(j==3) favPos="cup";
        if(j==4) favPos="head";
        selectedNum=match(Data::Fav[i]->getID(j));
    }

    if(selectedNum>-1)
    {
        ui->name->setText(sorted[selectedNum]->Get_Name());
        QString Position;
        if(sorted[selectedNum]->Get_position()=="flower") Position="生之花";
        if(sorted[selectedNum]->Get_position()=="feather") Position="死之羽";
        if(sorted[selectedNum]->Get_position()=="sand") Position="时之沙";
        if(sorted[selectedNum]->Get_position()=="cup") Position="空之杯";
        if(sorted[selectedNum]->Get_position()=="head") Position="理之冠";
        ui->position->setText(Position);

        ui->ma->setText(sorted[selectedNum]->Get_MainAttributeChinese());
        ui->ma->show();
        if(sorted[selectedNum]->Get_MainAttributeValue()>1)
        {
            ui->mav->setText(QString::number(sorted[selectedNum]->Get_MainAttributeValue()));
        }
        else
        {
            ui->mav->setText(QString::number(sorted[selectedNum]->Get_MainAttributeValue()*100)+"%");
        }
        ui->mav->show();

        ui->level->setText("+"+QString::number(sorted[selectedNum]->Get_level()));
        ui->level->show();
        ui->star->show();

        if(sorted[selectedNum]->Get_SubAttributeValue1()>1)
        {
            ui->sa1->setText("·"+sorted[selectedNum]->Get_SubAttributeChinese1()+"+"+QString::number(sorted[selectedNum]->Get_SubAttributeValue1()));
        }
        else
        {
            ui->sa1->setText("·"+sorted[selectedNum]->Get_SubAttributeChinese1()+"+"+QString::number(sorted[selectedNum]->Get_SubAttributeValue1()*100)+"%");
        }
        if(sorted[selectedNum]->Get_SubAttributeValue2()>1)
        {
            ui->sa2->setText("·"+sorted[selectedNum]->Get_SubAttributeChinese2()+"+"+QString::number(sorted[selectedNum]->Get_SubAttributeValue2()));
        }
        else
        {
            ui->sa2->setText("·"+sorted[selectedNum]->Get_SubAttributeChinese2()+"+"+QString::number(sorted[selectedNum]->Get_SubAttributeValue2()*100)+"%");
        }
        if(sorted[selectedNum]->Get_SubAttributeValue3()>1)
        {
            ui->sa3->setText("·"+sorted[selectedNum]->Get_SubAttributeChinese3()+"+"+QString::number(sorted[selectedNum]->Get_SubAttributeValue3()));
        }
        else
        {
            ui->sa3->setText("·"+sorted[selectedNum]->Get_SubAttributeChinese3()+"+"+QString::number(sorted[selectedNum]->Get_SubAttributeValue3()*100)+"%");
        }
        if(sorted[selectedNum]->Get_SubAttribute4()!="none")
        {
            if(sorted[selectedNum]->Get_SubAttributeValue4()>1)
            {
                ui->sa4->setText("·"+sorted[selectedNum]->Get_SubAttributeChinese4()+"+"+QString::number(sorted[selectedNum]->Get_SubAttributeValue4()));
            }
            else
            {
                ui->sa4->setText("·"+sorted[selectedNum]->Get_SubAttributeChinese4()+"+"+QString::number(sorted[selectedNum]->Get_SubAttributeValue4()*100)+"%");
            }
        }
        //获取↓↓↓↓
        QString setname, setNameChinese, twoPieceSet, fourPieceSet, des;
        setname=sorted[selectedNum]->Get_setName();
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
                des=artifact_Obj.value(sorted[selectedNum]->Get_position()+"Des").toString();
            }
            temp.clear();
        }
        ui->setName->setText(setNameChinese+"：");
        ui->twoPieceSet->setText("2件套："+twoPieceSet);
        ui->twoPieceSet->adjustSize();
        ui->fourPieceSet->setGeometry(15,222+ui->twoPieceSet->size().height()+4,175,21);
        ui->fourPieceSet->setText("4件套："+fourPieceSet);
        ui->fourPieceSet->adjustSize();
        ui->description->setText(des);
        ui->description->setGeometry(5,222+ui->twoPieceSet->size().height()+4+ui->fourPieceSet->size().height()+4,185,21);
        ui->description->adjustSize();
        ui->detail->adjustSize();
    }

}

void Favorite::changeBtnPre(QPushButton* btn, int j, int i, int flag)
{
    if(flag==1)
    {
        btn->setGeometry(75*j-3,90*i-3,73,87);
        btn->setIcon(QIcon(":/Icon/item5Bg_selected.png"));
    }
    if(flag==2)
    {
        btn->setGeometry(75*j-3,110*i+25-3,73,87);
        if(Data::Fav[i]->getID(j)>-1) btn->setIcon(QIcon(":/Icon/item5Bg_selected.png"));
        else btn->setIcon(QIcon(":/Artifact/artbg2_selected.png"));
    }

    btn->setIconSize(QSize(73,87));
}

void Favorite::changeBtnRea(QPushButton* btn, int j, int i, int flag)
{
    if(flag==1)
    {
        btn->setGeometry(75*j,90*i,67,81);
        btn->setIcon(QIcon(":/Icon/item5Bg.png"));
    }
    if(flag==2)
    {
        btn->setGeometry(75*j,110*i+25,67,81);
        if(Data::Fav[i]->getID(j)>-1) btn->setIcon(QIcon(":/Icon/item5Bg.png"));
        else btn->setIcon(QIcon(":/Artifact/artbg2.png"));
    }
    btn->setIconSize(QSize(67,81));
}

void Favorite::upComboBox_currentTextChanged(upComboBox* box, const QString &arg1)
{
    s=arg1;
    setWidget(1);
}

int Favorite::match(int id)
{
    int flag=0;
    for(int i=0;i<Data::ArtAmount;i++)
    {
        if(id==sorted[i]->Get_id())
        {
            flag=1;
            return i;
        }
    }
    if(flag!=1) return -1;
}


void Favorite::on_flower_pressed()
{
    ui->flower->setIcon(QIcon(":/Icon/flower_selected.png"));
    ui->flower->setIconSize(QSize(55,48));
    ui->feather->setIcon(QIcon(":/Icon/feather.png"));
    ui->feather->setIconSize(QSize(55,48));
    ui->sand->setIcon(QIcon(":/Icon/sand.png"));
    ui->sand->setIconSize(QSize(55,48));
    ui->cup->setIcon(QIcon(":/Icon/cup.png"));
    ui->cup->setIconSize(QSize(55,48));
    ui->head->setIcon(QIcon(":/Icon/head.png"));
    ui->head->setIconSize(QSize(55,48));
}


void Favorite::on_feather_pressed()
{
    ui->flower->setIcon(QIcon(":/Icon/flower.png"));
    ui->flower->setIconSize(QSize(55,48));
    ui->feather->setIcon(QIcon(":/Icon/feather_selected.png"));
    ui->feather->setIconSize(QSize(55,48));
    ui->sand->setIcon(QIcon(":/Icon/sand.png"));
    ui->sand->setIconSize(QSize(55,48));
    ui->cup->setIcon(QIcon(":/Icon/cup.png"));
    ui->cup->setIconSize(QSize(55,48));
    ui->head->setIcon(QIcon(":/Icon/head.png"));
    ui->head->setIconSize(QSize(55,48));
}


void Favorite::on_sand_pressed()
{
    ui->flower->setIcon(QIcon(":/Icon/flower.png"));
    ui->flower->setIconSize(QSize(55,48));
    ui->feather->setIcon(QIcon(":/Icon/feather.png"));
    ui->feather->setIconSize(QSize(55,48));
    ui->sand->setIcon(QIcon(":/Icon/sand_selected.png"));
    ui->sand->setIconSize(QSize(55,48));
    ui->cup->setIcon(QIcon(":/Icon/cup.png"));
    ui->cup->setIconSize(QSize(55,48));
    ui->head->setIcon(QIcon(":/Icon/head.png"));
    ui->head->setIconSize(QSize(55,48));
}


void Favorite::on_cup_pressed()
{
    ui->flower->setIcon(QIcon(":/Icon/flower.png"));
    ui->flower->setIconSize(QSize(55,48));
    ui->feather->setIcon(QIcon(":/Icon/feather.png"));
    ui->feather->setIconSize(QSize(55,48));
    ui->sand->setIcon(QIcon(":/Icon/sand.png"));
    ui->sand->setIconSize(QSize(55,48));
    ui->cup->setIcon(QIcon(":/Icon/cup_selected.png"));
    ui->cup->setIconSize(QSize(55,48));
    ui->head->setIcon(QIcon(":/Icon/head.png"));
    ui->head->setIconSize(QSize(55,48));
}


void Favorite::on_head_pressed()
{
    ui->flower->setIcon(QIcon(":/Icon/flower.png"));
    ui->flower->setIconSize(QSize(55,48));
    ui->feather->setIcon(QIcon(":/Icon/feather.png"));
    ui->feather->setIconSize(QSize(55,48));
    ui->sand->setIcon(QIcon(":/Icon/sand.png"));
    ui->sand->setIconSize(QSize(55,48));
    ui->cup->setIcon(QIcon(":/Icon/cup.png"));
    ui->cup->setIconSize(QSize(55,48));
    ui->head->setIcon(QIcon(":/Icon/head_selected.png"));
    ui->head->setIconSize(QSize(55,48));
}

void Favorite::sortPosition()
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

void Favorite::on_feather_clicked()
{
    posFlag="feather";
    setWidget(1);
}


void Favorite::on_flower_clicked()
{
    posFlag="flower";
    setWidget(1);
}


void Favorite::on_sand_clicked()
{
    posFlag="sand";
    setWidget(1);
}


void Favorite::on_cup_clicked()
{
    posFlag="cup";
    setWidget(1);
}


void Favorite::on_head_clicked()
{
    posFlag="head";
    setWidget(1);
}


void Favorite::on_add_clicked()
{
    int temp;
    //上一个预设输入完毕才能再新增
    if(Data::Favorite_size==0||(Data::Favorite_size>0&&!Data::Fav[Data::Favorite_size-1]->isEmpty()))
    {
        temp=Data::Favorite_size;
        favNum=Data::Favorite_size;//因为connect不能越权访问（网上是这么说的），只能这样了
        //预设名称输入框
        name[Data::Favorite_size]=new QLineEdit(ui->favorite);
        name[Data::Favorite_size]->setGeometry(35,110*Data::Favorite_size,335,21);
        name[Data::Favorite_size]->setStyleSheet("background-color: rgba(255, 255, 255, 127);""font: 10pt \"汉仪文黑-85W\";""color:#38434e;""border-radius:3px;""padding: 1px 1px 1px 10px;");
        name[Data::Favorite_size]->setPlaceholderText("请输入该预设名称（不可重复）");
        name[Data::Favorite_size]->show();
        connect(name[favNum],&QLineEdit::textEdited,name[favNum],[=](){nameEdited(name[favNum]->text(),favNum, name[favNum]);});

        fav[favNum]=new QLabel(ui->favorite);
        fav[favNum]->setGeometry(0,110*Data::Favorite_size,30,21);
        Data::ft.setPointSize(10);
        fav[favNum]->setFont(Data::ft);
        fav[favNum]->setAlignment(Qt::AlignCenter);
        fav[favNum]->setStyleSheet("background-color: rgba(255, 255, 255, 127);""color:#38434e;""border-radius:3px;");
        fav[favNum]->setText(QString::number(favNum+1));
        fav[favNum]->show();

        //按钮初始化
        Art[Data::Favorite_size] = new QPushButton*[5];
        artLabel[Data::Favorite_size] =new QLabel*[5];
        artLevel[Data::Favorite_size] =new QLabel*[5];
        artStar[Data::Favorite_size] = new QPushButton*[5];

        Data::Fav[Data::Favorite_size]=new FavoriteOri();

        for(int i=0;i<5;i++)
        {
            Art[favNum][i]=new QPushButton(ui->favorite);
            Art[favNum][i]->setGeometry(75*i,110*Data::Favorite_size+25,67,81);
            Art[favNum][i]->setIcon(QIcon(":/Artifact/artbg2.png"));
            Art[favNum][i]->setIconSize(QSize(67,81));
            //不知道为什么 connect的时候参数只能用局部变量
            connect(Art[temp][i],&QPushButton::clicked,Art[temp][i],[=](){changeBtnCli(Art[temp][i], i, temp, 0, 2);});
            connect(Art[temp][i],&QPushButton::pressed,Art[temp][i],[=](){changeBtnPre(Art[temp][i], i, temp,2);});
            connect(Art[temp][i],&QPushButton::released,Art[temp][i],[=](){changeBtnRea(Art[temp][i], i, temp,2);});
            Art[favNum][i]->show();
        }
        Data::Favorite_size++;
        ui->add->move(166,Data::Favorite_size*110);
        ui->favorite->resize(QSize(375,Data::Favorite_size*110+42));
    }
    else QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","当前预设尚未输入完成！");
}


void Favorite::on_equip_clicked()
{
    QString Name;
    int level,i;
    if(favNum>-1)
    {
        if(sorted[selectedNum]->Get_position()=="flower") i=0;
        else if(sorted[selectedNum]->Get_position()=="feather") i=1;
        else if(sorted[selectedNum]->Get_position()=="sand") i=2;
        else if(sorted[selectedNum]->Get_position()=="cup") i=3;
        else if(sorted[selectedNum]->Get_position()=="head") i=4;

        Art[favNum][i]->setIcon(QIcon(":/Icon/item5Bg.png"));

        //如果当前预设的对应部位没有，则new
        if(Data::Fav[favNum]->getID(i)==-1)
        {
            Name=sorted[selectedNum]->Get_Name();
            level=sorted[selectedNum]->Get_level();
            artLabel[favNum][i]=new QLabel(ui->favorite);
            artLabel[favNum][i]->setGeometry(75*i+4,110*favNum+25+4,58,53);
            QPixmap Pix=QPixmap(":/Artifact/"+Name+".png");
            QSize pixSize=Pix.size()*0.25;
            artLabel[favNum][i]->setGeometry(75*i+4+29-pixSize.width()/2,110*favNum+25+4+27-pixSize.height()/2,pixSize.width(),pixSize.height());
            artLabel[favNum][i]->setStyleSheet("background-color: transparent;""border-image: url(:/Artifact/"+Name+".png);");
            artLabel[favNum][i]->show();

            artLevel[favNum][i]=new QLabel(ui->favorite);
            artLevel[favNum][i]->setGeometry(75*i,110*favNum+25+65,67,14);
            Data::ft.setPointSize(8);
            artLevel[favNum][i]->setFont(Data::ft);
            artLevel[favNum][i]->setAlignment(Qt::AlignCenter);
            artLevel[favNum][i]->setStyleSheet("color:rgb(73,83,102)");
            artLevel[favNum][i]->setText("+"+QString::number(level));
            artLevel[favNum][i]->show();

            artStar[favNum][i]=new QPushButton(ui->favorite);
            artStar[favNum][i]->setGeometry(75*i,110*favNum+25,67,81);
            artStar[favNum][i]->setStyleSheet("border-image: url(:/Icon/item5Bg_star.png)");
            artStar[favNum][i]->show();
            connect(artStar[favNum][i],&QPushButton::clicked,Art[favNum][i],&QPushButton::clicked);//套娃，因为显示在了真正的按钮上面，所以点它=点真正的按钮
            connect(artStar[favNum][i],&QPushButton::pressed,Art[favNum][i],&QPushButton::pressed);
            connect(artStar[favNum][i],&QPushButton::released,Art[favNum][i],&QPushButton::released);
        }
        else//如果当前预设对应部位已有，则更换图片
        {
            Name=sorted[selectedNum]->Get_Name();
            level=sorted[selectedNum]->Get_level();
            QPixmap Pix=QPixmap(":/Artifact/"+Name+".png");
            QSize pixSize=Pix.size()*0.25;
            artLabel[favNum][i]->setGeometry(75*i+4+29-pixSize.width()/2,110*favNum+25+4+27-pixSize.height()/2,pixSize.width(),pixSize.height());
            artLabel[favNum][i]->setStyleSheet("background-color: transparent;""border-image: url(:/Artifact/"+Name+".png);");
            artLevel[favNum][i]->setText("+"+QString::number(level));
        }

        if(i==0) Data::Fav[favNum]->setFlower(sorted,selectedNum);
        else if(i==1) Data::Fav[favNum]->setFeather(sorted,selectedNum);
        else if(i==2) Data::Fav[favNum]->setSand(sorted,selectedNum);
        else if(i==3) Data::Fav[favNum]->setCup(sorted,selectedNum);
        else if(i==4) Data::Fav[favNum]->setHead(sorted,selectedNum);
    }
    else QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","当前尚未新建预设！");
}

void Favorite::showFav(int flag)//0为初始，1为删除后的刷新，2为重新打开窗口的刷新
{
    QString Name;
    int level, temp;
    if(flag==1)
    {
        for(int i=0;i<Data::Favorite_size+1;i++)
        {
            for(int j=0;j<5;j++)
            {
                Art[i][j]->close();
                delete[] Art[i][j];
                artLabel[i][j]->close();
                delete[] artLabel[i][j];
                artLevel[i][j]->close();
                delete[] artLevel[i][j];
                artStar[i][j]->close();
                delete[] artStar[i][j];
            }
            name[i]->close();
            delete[] name[i];
            fav[i]->close();
            delete[] fav[i];
        }
    }

    ui->add->move(166,110*Data::Favorite_size);
    ui->favorite->resize(QSize(375,Data::Favorite_size*110+42));
    if(Data::Favorite_size>0)
    {
        for(int i=0;i<Data::Favorite_size;i++)
        {
            temp=i;
            favNum=i;//因为connect不能越权访问（网上是这么说的），只能这样了
            //预设名称输入框
            name[favNum]=new QLineEdit(ui->favorite);
            name[favNum]->setGeometry(35,110*favNum,335,21);
            name[favNum]->setStyleSheet("background-color: rgba(255, 255, 255, 127);""font: 10pt \"汉仪文黑-85W\";""color:#38434e;""border-radius:3px;""padding: 1px 1px 1px 10px;");
            name[favNum]->setText(Data::Fav[favNum]->getName());
            name[favNum]->show();
            connect(name[favNum],&QLineEdit::textEdited,name[favNum],[=](){Data::Fav[favNum]->setName(name[favNum]->text());});

            fav[favNum]=new QLabel(ui->favorite);
            fav[favNum]->setGeometry(0,110*favNum,30,21);
            Data::ft.setPointSize(10);
            fav[favNum]->setFont(Data::ft);
            fav[favNum]->setAlignment(Qt::AlignCenter);
            fav[favNum]->setStyleSheet("background-color: rgba(255, 255, 255, 127);""color:#38434e;""border-radius:3px;");
            fav[favNum]->setText(QString::number(favNum+1));
            fav[favNum]->show();

            //按钮初始化
            Art[favNum] = new QPushButton*[5];
            artLabel[favNum] =new QLabel*[5];
            artLevel[favNum] =new QLabel*[5];
            artStar[favNum] = new QPushButton*[5];

            for(int j=0;j<5;j++)
            {
                Art[favNum][j]=new QPushButton(ui->favorite);
                Art[favNum][j]->setGeometry(75*j,110*favNum+25,67,81);
                Art[favNum][j]->setIcon(QIcon(":/Icon/item5Bg.png"));
                Art[favNum][j]->setIconSize(QSize(67,81));
                connect(Art[temp][j],&QPushButton::clicked,Art[temp][j],[=](){changeBtnCli(Art[temp][j], j, temp, 0, 2);});
                connect(Art[temp][j],&QPushButton::pressed,Art[temp][j],[=](){changeBtnPre(Art[temp][j], j, temp,2);});
                connect(Art[temp][j],&QPushButton::released,Art[temp][j],[=](){changeBtnRea(Art[temp][j], j, temp,2);});
                Art[favNum][j]->show();

                Name=Data::Fav[favNum]->favorite[j]->Get_Name();
                level=Data::Fav[favNum]->favorite[j]->Get_level();
                artLabel[favNum][j]=new QLabel(ui->favorite);
                artLabel[favNum][j]->setGeometry(75*j+4,110*favNum+25+4,58,53);
                QPixmap Pix=QPixmap(":/Artifact/"+Name+".png");
                QSize pixSize=Pix.size()*0.25;
                artLabel[favNum][j]->setGeometry(75*j+4+29-pixSize.width()/2,110*favNum+25+4+27-pixSize.height()/2,pixSize.width(),pixSize.height());
                artLabel[favNum][j]->setStyleSheet("background-color: transparent;""border-image: url(:/Artifact/"+Name+".png);");
                artLabel[favNum][j]->show();

                artLevel[favNum][j]=new QLabel(ui->favorite);
                artLevel[favNum][j]->setGeometry(75*j,110*favNum+25+65,67,14);
                Data::ft.setPointSize(8);
                artLevel[favNum][j]->setFont(Data::ft);
                artLevel[favNum][j]->setAlignment(Qt::AlignCenter);
                artLevel[favNum][j]->setStyleSheet("color:rgb(73,83,102)");
                artLevel[favNum][j]->setText("+"+QString::number(level));
                artLevel[favNum][j]->show();

                artStar[favNum][j]=new QPushButton(ui->favorite);
                artStar[favNum][j]->setGeometry(75*j,110*favNum+25,67,81);
                artStar[favNum][j]->setStyleSheet("border-image: url(:/Icon/item5Bg_star.png)");
                artStar[favNum][j]->show();
                connect(artStar[temp][j],&QPushButton::clicked,Art[temp][j],&QPushButton::clicked);//套娃，因为显示在了真正的按钮上面，所以点它=点真正的按钮
                connect(artStar[temp][j],&QPushButton::pressed,Art[temp][j],&QPushButton::pressed);
                connect(artStar[temp][j],&QPushButton::released,Art[temp][j],&QPushButton::released);
            }
        }
    }
}

void Favorite::on_delete_2_clicked()
{
    if(Data::Favorite_size>0)
    {
        if(!Data::Fav[Data::Favorite_size-1]->isEmpty())
        {
            favdm=new FavDelMod(this);
            favdm->show();
        }
        else QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","当前预设尚未输入完成！");
    }
    else QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","当前尚未新建预设！");
}

void Favorite::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == clock)
    {
        if(Data::favFlag==1)
        {
            if(Data::favTemp>-1)
            {
                favNum=Data::favTemp;
                for(int i=favNum;i<Data::Favorite_size;i++)
                {
                    Data::Fav[i]=Data::Fav[i+1];
                }
                Data::Favorite_size--;
                showFav(Data::favFlag);
                Data::favTemp=-1;
                Data::favFlag=0;
            }
        }
        if(Data::favFlag==2)
        {
            if(Data::favTemp>-1)
            {
                favNum=Data::favTemp;
                Data::favTemp=-1;
                Data::favFlag=0;
            }
        }
    }
}

void Favorite::on_Save_clicked()
{
    if(Data::Favorite_size>0)
    {
        if(!Data::Fav[Data::Favorite_size-1]->isEmpty())
        {
            // 以读写方式打开.json文件，若该文件不存在则会自动创建
            QFile fileFav(QDir::currentPath()+"/favorite.json");
            fileFav.open(QIODevice::ReadWrite);
            // 清空文件中的原有内容
            fileFav.resize(0);

            // 使用QJsonArray添加值，并写入文件
            QJsonArray array;
            for(int i = 0; i < Data::Favorite_size; i++)
            {
                Data::Fav[i]->confirm();
                // 定义 { } 对象
                QJsonObject fav_Obj;
                fav_Obj.insert("name",Data::Fav[i]->getName());
                fav_Obj.insert("id",i+1);
                fav_Obj.insert("flower",Data::Fav[i]->getID(0));
                fav_Obj.insert("feather",Data::Fav[i]->getID(1));
                fav_Obj.insert("sand",Data::Fav[i]->getID(2));
                fav_Obj.insert("cup",Data::Fav[i]->getID(3));
                fav_Obj.insert("head",Data::Fav[i]->getID(4));

                // 定义 [ ] 对象
                array.append(fav_Obj);
            }
            // 定义根节点	也即是最外层 { }
            QJsonObject rootObject;
            // 插入元素
            rootObject.insert("favorite",array);
            // 将json对象里的数据转换为字符串
            QJsonDocument doc;
            // 将object设置为本文档的主要对象
            doc.setObject(rootObject);

            fileFav.write(doc.toJson());
            fileFav.close();
            QMessageBox::StandardButton result=QMessageBox::information(this,"保存成功","套装预设已保存到文件！");
        }
        else QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","当前预设尚未输入完成！");
    }
    else QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","当前尚未新建预设！");
}

void Favorite::nameEdited(QString n, int fn, QLineEdit *name)
{
    int temp=0;
    for(int i=0;i<Data::Favorite_size;i++)
    {
        if(n!=Data::Fav[i]->getName()) temp++;
    }
    if(temp==Data::Favorite_size)
    {
        Data::Fav[fn]->setName(n);
    }
    else
    {
        name->clear();
        QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","名称重复！");
    }
}
