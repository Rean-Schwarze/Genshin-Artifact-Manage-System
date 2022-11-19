#include "rating.h"
#include "ui_rating.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"

Rating::Rating(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Rating)
{
    ui->setupUi(this);
    //嵌入父窗口
    setGeometry(0,0,960,540);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    hide();

    //设置时钟为1s
    clock=this->startTimer(1000);

    ui->verticalScrollBar_3->hide();
    ui->favoriteArea->setVerticalScrollBar(ui->verticalScrollBar_3);

    favFilter=new upComboBox(this,1);
    //设置滚动条
    favFilter->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    favFilter->setGeometry(600,450,350,31);
    favFilter->setMaximumHeight(400);
    favFilter->addItem("请选择预设套装");
    if(Data::Favorite_size>0) favFilter->setDisabled(false);
    else favFilter->setDisabled(true);

    ui->Save->hide();
    ui->entry1->hide();
    ui->entry2->hide();
    ui->entry3->hide();
    ui->entry4->hide();
    ui->entry5->hide();
    ui->entryBox->hide();
    ui->entryBox2->hide();

    setFav(0);
}

Rating::~Rating()
{
    delete ui;
}

void Rating::on_Back_clicked()
{
    this->hide();
}

void Rating::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == clock)
    {
        if(Data::selectedChar!=-1&&Data::charLevel!=-1)
        {
            QPixmap PixBgChar=QPixmap(":/Character/Avatar_high/"+Data::Char[Data::selectedChar][0]->Get_Name()+".png");
            QSize PixBgCharSize = PixBgChar.size()*0.42;//缩小一下
            ui->bgChar->setText("");
            ui->bgChar->setGeometry(280/2-PixBgCharSize.width()/2,430/2-PixBgCharSize.height()/2,PixBgCharSize.width(),PixBgCharSize.height());
            ui->bgChar->setScaledContents(true);
            ui->bgChar->setPixmap(PixBgChar);
            ui->bgChar->show();
        }
        else
        {
            ui->bgChar->clear();
            ui->bgChar->setGeometry(0,0,280,430);
            ui->bgChar->setText("尚未选择人物");
        }

        if(Data::selectedWeap>-1&&Data::weapLevel>-1)
        {
            if(Data::matchCharWeap())
            {
                QPixmap PixBgWeap=QPixmap(":/Weapon/"+Data::Weap[Data::selectedWeap][0]->Get_WeaponType()+"/"+Data::Weap[Data::selectedWeap][0]->Get_NameChinese()+".png");
                QSize PixBgWeapSize;
                if(Data::Weap[Data::selectedWeap][0]->Get_WeaponType()=="Sword") PixBgWeapSize = PixBgWeap.size()*0.63;//缩小一下
                else if(Data::Weap[Data::selectedWeap][0]->Get_WeaponType()=="Claymore") PixBgWeapSize = PixBgWeap.size()*0.51;//缩小一下
                else if(Data::Weap[Data::selectedWeap][0]->Get_WeaponType()=="Bow") PixBgWeapSize = PixBgWeap.size()*0.51;//缩小一下
                else if(Data::Weap[Data::selectedWeap][0]->Get_WeaponType()=="Catalyst") PixBgWeapSize = PixBgWeap.size()*0.82;//缩小一下
                else if(Data::Weap[Data::selectedWeap][0]->Get_WeaponType()=="Polearm") PixBgWeapSize = PixBgWeap.size()*0.45;//缩小一下
                ui->bgWeap->setText("");
                ui->bgWeap->setGeometry(280/2-PixBgWeapSize.width()/2,430/2-PixBgWeapSize.height()/2,PixBgWeapSize.width(),PixBgWeapSize.height());
                ui->bgWeap->setScaledContents(true);
                ui->bgWeap->setPixmap(PixBgWeap);
                ui->bgWeap->show();
            }
        }
        else
        {
            ui->bgWeap->clear();
            ui->bgWeap->setGeometry(0,0,280,430);
            ui->bgWeap->setText("尚未选择武器");
        }
    }
}

void Rating::upComboBox_currentTextChanged(upComboBox* box, const QString &arg1)
{
    if(arg1!="请选择预设套装")
    {
        for(int i=0;i<Data::Favorite_size;i++)
        {
            if(arg1==Data::Fav[i]->getName())
            {
                Data::selectedFav=i;
                break;
            }
        }
        if(Data::Favorite_size>0) setFav(1);
    }
    ui->entry1->hide();
    ui->entry2->hide();
    ui->entry3->hide();
    ui->entry4->hide();
    ui->entry5->hide();
    ui->entryBox->hide();
    ui->entryBox2->hide();
}

void Rating::setFav(int flag)//0为初始，1为刷新
{
    if(flag==1)
    {
        for(int i=0;i<numTemp;i++)
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
        int i=0;
        numTemp=1;
        fav[i]=new QLabel(ui->favorite);
        fav[i]->setGeometry(0,0,30,21);
        Data::ft.setPointSize(10);
        fav[i]->setFont(Data::ft);
        fav[i]->setAlignment(Qt::AlignCenter);
        fav[i]->setStyleSheet("background-color: rgba(255, 255, 255, 216);""color:#38434e;""border-radius:3px;");
        fav[i]->setText("★");
        fav[i]->show();

        name[i]=new QLabel(ui->favorite);
        name[i]->setGeometry(35,0,315,21);
        name[i]->setFont(Data::ft);
        name[i]->setAlignment(Qt::AlignCenter);
        name[i]->setStyleSheet("background-color: rgba(255, 255, 255, 216);""color:#38434e;""border-radius:3px;");
        name[i]->setText(Data::Fav[Data::selectedFav]->getName());
        name[i]->show();

        Art[i] = new QLabel*[5];
        artLabel[i] =new QLabel*[5];
        artLevel[i] =new QLabel*[5];
        artStar[i] = new QLabel*[5];

        for(int j=0;j<5;j++)
        {
            Art[i][j]=new QLabel(ui->favorite);
            Art[i][j]->setGeometry(70*j,0+25,67,81);
            Art[i][j]->setStyleSheet("border-image: url(:/Icon/item5Bg.png)");
            Art[i][j]->show();

            Name=Data::Fav[Data::selectedFav]->favorite[j]->Get_Name();
            level=Data::Fav[Data::selectedFav]->favorite[j]->Get_level();
            artLabel[i][j]=new QLabel(ui->favorite);
            artLabel[i][j]->setGeometry(70*j+4,0+25+4,58,53);
            QPixmap Pix=QPixmap(":/Artifact/"+Name+".png");
            QSize pixSize=Pix.size()*0.25;
            artLabel[i][j]->setGeometry(70*j+4+29-pixSize.width()/2,0+25+4+27-pixSize.height()/2,pixSize.width(),pixSize.height());
            artLabel[i][j]->setStyleSheet("background-color: transparent;""border-image: url(:/Artifact/"+Name+".png);");
            artLabel[i][j]->show();

            artLevel[i][j]=new QLabel(ui->favorite);
            artLevel[i][j]->setGeometry(70*j,0+25+65,67,14);
            Data::ft.setPointSize(8);
            artLevel[i][j]->setFont(Data::ft);
            artLevel[i][j]->setAlignment(Qt::AlignCenter);
            artLevel[i][j]->setStyleSheet("color:rgb(73,83,102)");
            artLevel[i][j]->setText("+"+QString::number(level));
            artLevel[i][j]->show();

            artStar[i][j]=new QLabel(ui->favorite);
            artStar[i][j]->setGeometry(70*j,0+25,67,81);
            artStar[i][j]->setStyleSheet("border-image: url(:/Icon/item5Bg_star.png)");
            artStar[i][j]->show();
        }
    }
    else if(flag==0)
    {
        if(Data::Favorite_size>0)
        {
            numTemp=Data::Favorite_size;
            //设置widget大小，但有最小高度，否则评分内容可能显示不完全
            if(Data::Favorite_size*110<400)  ui->favorite->resize(QSize(350,400));
            else ui->favorite->resize(QSize(350,Data::Favorite_size*110));
            for(int i=0;i<Data::Favorite_size;i++)
            {
                if(flag==0) favFilter->addItem(Data::Fav[i]->getName());

                fav[i]=new QLabel(ui->favorite);
                fav[i]->setGeometry(0,110*i,30,21);
                Data::ft.setPointSize(10);
                fav[i]->setFont(Data::ft);
                fav[i]->setAlignment(Qt::AlignCenter);
                fav[i]->setStyleSheet("background-color: rgba(255, 255, 255, 216);""color:#38434e;""border-radius:3px;");
                fav[i]->setText(QString::number(i+1));
                fav[i]->show();

                name[i]=new QLabel(ui->favorite);
                name[i]->setGeometry(35,110*i,315,21);
                name[i]->setFont(Data::ft);
                name[i]->setAlignment(Qt::AlignCenter);
                name[i]->setStyleSheet("background-color: rgba(255, 255, 255, 216);""color:#38434e;""border-radius:3px;");
                name[i]->setText(Data::Fav[i]->getName());
                name[i]->show();

                Art[i] = new QLabel*[5];
                artLabel[i] =new QLabel*[5];
                artLevel[i] =new QLabel*[5];
                artStar[i] = new QLabel*[5];

                for(int j=0;j<5;j++)
                {
                    Art[i][j]=new QLabel(ui->favorite);
                    Art[i][j]->setGeometry(70*j,110*i+25,67,81);
                    Art[i][j]->setStyleSheet("border-image: url(:/Icon/item5Bg.png)");
                    Art[i][j]->show();

                    Name=Data::Fav[i]->favorite[j]->Get_Name();
                    level=Data::Fav[i]->favorite[j]->Get_level();
                    artLabel[i][j]=new QLabel(ui->favorite);
                    artLabel[i][j]->setGeometry(70*j+4,110*i+25+4,58,53);
                    QPixmap Pix=QPixmap(":/Artifact/"+Name+".png");
                    QSize pixSize=Pix.size()*0.25;
                    artLabel[i][j]->setGeometry(70*j+4+29-pixSize.width()/2,110*i+25+4+27-pixSize.height()/2,pixSize.width(),pixSize.height());
                    artLabel[i][j]->setStyleSheet("background-color: transparent;""border-image: url(:/Artifact/"+Name+".png);");
                    artLabel[i][j]->show();

                    artLevel[i][j]=new QLabel(ui->favorite);
                    artLevel[i][j]->setGeometry(70*j,110*i+25+65,67,14);
                    Data::ft.setPointSize(8);
                    artLevel[i][j]->setFont(Data::ft);
                    artLevel[i][j]->setAlignment(Qt::AlignCenter);
                    artLevel[i][j]->setStyleSheet("color:rgb(73,83,102)");
                    artLevel[i][j]->setText("+"+QString::number(level));
                    artLevel[i][j]->show();

                    artStar[i][j]=new QLabel(ui->favorite);
                    artStar[i][j]->setGeometry(70*j,110*i+25,67,81);
                    artStar[i][j]->setStyleSheet("border-image: url(:/Icon/item5Bg_star.png)");
                    artStar[i][j]->show();
                }
            }
            favFilter->show();
            connect(favFilter,&QComboBox::currentTextChanged,this,[=](){upComboBox_currentTextChanged(favFilter,favFilter->currentText());});
        }
    }
}


void Rating::on_change1_clicked()
{
    charSelect=new CharacterSelecte(this);
    charSelect->show();
}


void Rating::on_change2_clicked()
{
    if(Data::selectedChar!=-1&&Data::charLevel!=-1)
    {
        weapSelect=new WeaponSelect(this);
        weapSelect->show();
    }
    else QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","当前尚未选择人物！");
}


void Rating::on_rate_clicked()
{
    if(Data::selectedChar>-1&&Data::charLevel>-1&&Data::selectedWeap>-1&&Data::weapLevel>-1&&Data::selectedFav>-1)
    {
        if(Data::matchCharWeap())
        {

            //圣遗物加成生命=人物生命白值*大生命%+小生命，防御同理，加成攻击=(人物攻击白值+武器攻击白值)*大攻击%+小攻击
            artLife=Data::Char[Data::selectedChar][Data::charLevel]->Get_BaseLife()*Data::Fav[Data::selectedFav]->Get_total_Life()+Data::Fav[Data::selectedFav]->Get_total_life();
            artAttack=(Data::Char[Data::selectedChar][Data::charLevel]->Get_BaseAttack()+Data::Weap[Data::selectedWeap][Data::weapLevel]->Get_BaseAttack())*Data::Fav[Data::selectedFav]->Get_total_Attack()+Data::Fav[Data::selectedFav]->Get_total_attack();
            artDefend=Data::Char[Data::selectedChar][Data::charLevel]->Get_BaseDefend()*Data::Fav[Data::selectedFav]->Get_total_Defend()+Data::Fav[Data::selectedFav]->Get_total_defend();

            lifeEntry=((artLife-4780)/Data::Char[Data::selectedChar][Data::charLevel]->Get_BaseLife()-0.466*Data::Fav[Data::selectedFav]->Get_Num(0))/0.04975;
            attackEntry=(((artAttack-311)/(Data::Char[Data::selectedChar][Data::charLevel]->Get_BaseAttack()+Data::Weap[Data::selectedWeap][Data::weapLevel]->Get_BaseAttack()))-0.466*Data::Fav[Data::selectedFav]->Get_Num(1))/0.04975;
            defendEntry=(artDefend/Data::Char[Data::selectedChar][Data::charLevel]->Get_BaseDefend()-0.583*Data::Fav[Data::selectedFav]->Get_Num(2))/0.062;
            masteryEntry=(Data::Fav[Data::selectedFav]->Get_mastery()-187*Data::Fav[Data::selectedFav]->Get_Num(3))/19.75;
            rechargeEntry=(Data::Fav[Data::selectedFav]->Get_recharge()*100-51.8*Data::Fav[Data::selectedFav]->Get_Num(4))/5.5;
            criticalEntry=(Data::Fav[Data::selectedFav]->Get_total_critical()*100-31.1*Data::Fav[Data::selectedFav]->Get_Num(5))/3.3;
            criDMGEntry=(Data::Fav[Data::selectedFav]->Get_total_criticalDamage()*100-62.2*Data::Fav[Data::selectedFav]->Get_Num(6))/6.6;

            QString temp, tempSand, tempCup, tempHead;
            if(Data::charLevel==0) temp="80级未突破";
            else if(Data::charLevel==1) temp="80级已突破";
            else if(Data::charLevel==2) temp="90级";
            //字体颜色
            if(Data::Char[Data::selectedChar][0]->Get_Element()=="Pryo")
            {
                ui->entry1->setStyleSheet("color:rgb(255,102,64)");
                ui->entry2->setStyleSheet("color:rgb(255,102,64)");
                ui->entry3->setStyleSheet("color:rgb(255,102,64)");
                ui->entry4->setStyleSheet("color:rgb(255,102,64)");
                ui->entry5->setStyleSheet("color:rgb(255,102,64)");
            }
            else if(Data::Char[Data::selectedChar][0]->Get_Element()=="Hydro")
            {
                ui->entry1->setStyleSheet("color:rgb(0,192,255)");
                ui->entry2->setStyleSheet("color:rgb(0,192,255)");
                ui->entry3->setStyleSheet("color:rgb(0,192,255)");
                ui->entry4->setStyleSheet("color:rgb(0,192,255)");
                ui->entry5->setStyleSheet("color:rgb(0,192,255)");
            }
            else if(Data::Char[Data::selectedChar][0]->Get_Element()=="Electro")
            {
                ui->entry1->setStyleSheet("color:rgb(204,128,255)");
                ui->entry2->setStyleSheet("color:rgb(204,128,255)");
                ui->entry3->setStyleSheet("color:rgb(204,128,255)");
                ui->entry4->setStyleSheet("color:rgb(204,128,255)");
                ui->entry5->setStyleSheet("color:rgb(204,128,255)");
            }
            else if(Data::Char[Data::selectedChar][0]->Get_Element()=="Anemo")
            {
                ui->entry1->setStyleSheet("color:rgb(51,215,160)");
                ui->entry2->setStyleSheet("color:rgb(51,215,160)");
                ui->entry3->setStyleSheet("color:rgb(51,215,160)");
                ui->entry4->setStyleSheet("color:rgb(51,215,160)");
                ui->entry5->setStyleSheet("color:rgb(51,215,160)");
            }
            else if(Data::Char[Data::selectedChar][0]->Get_Element()=="Cryo")
            {
                ui->entry1->setStyleSheet("color:rgb(122,242,242)");
                ui->entry2->setStyleSheet("color:rgb(122,242,242)");
                ui->entry3->setStyleSheet("color:rgb(122,242,242)");
                ui->entry4->setStyleSheet("color:rgb(122,242,242)");
                ui->entry5->setStyleSheet("color:rgb(122,242,242)");
            }
            else if(Data::Char[Data::selectedChar][0]->Get_Element()=="Geo")
            {
                ui->entry1->setStyleSheet("color:rgb(255,176,13)");
                ui->entry2->setStyleSheet("color:rgb(255,176,13)");
                ui->entry3->setStyleSheet("color:rgb(255,176,13)");
                ui->entry4->setStyleSheet("color:rgb(255,176,13)");
                ui->entry5->setStyleSheet("color:rgb(255,176,13)");
            }
            else if(Data::Char[Data::selectedChar][0]->Get_Element()=="Dendro")
            {
                ui->entry1->setStyleSheet("color:rgb(100,228,103)");
                ui->entry2->setStyleSheet("color:rgb(100,228,103)");
                ui->entry3->setStyleSheet("color:rgb(100,228,103)");
                ui->entry4->setStyleSheet("color:rgb(100,228,103)");
                ui->entry5->setStyleSheet("color:rgb(100,228,103)");
            }
            else
            {
                ui->entry1->setStyleSheet("color:rgb(59,66,85)");
                ui->entry2->setStyleSheet("color:rgb(59,66,85)");
                ui->entry3->setStyleSheet("color:rgb(59,66,85)");
                ui->entry4->setStyleSheet("color:rgb(59,66,85)");
                ui->entry5->setStyleSheet("color:rgb(59,66,85)");
            }

            if(Data::Fav[Data::selectedFav]->favorite[2]->Get_MainAttributeChinese()=="生命值") tempSand="生";
            else if(Data::Fav[Data::selectedFav]->favorite[2]->Get_MainAttributeChinese()=="防御力") tempSand="防";
            else if(Data::Fav[Data::selectedFav]->favorite[2]->Get_MainAttributeChinese()=="攻击力") tempSand="攻";
            else if(Data::Fav[Data::selectedFav]->favorite[2]->Get_MainAttributeChinese()=="元素精通") tempSand="精";
            else if(Data::Fav[Data::selectedFav]->favorite[2]->Get_MainAttributeChinese()=="元素充能效率") tempSand="充";

            if(Data::Fav[Data::selectedFav]->favorite[3]->Get_MainAttributeChinese()=="生命值") tempCup="生";
            else if(Data::Fav[Data::selectedFav]->favorite[3]->Get_MainAttributeChinese()=="防御力") tempCup="防";
            else if(Data::Fav[Data::selectedFav]->favorite[3]->Get_MainAttributeChinese()=="攻击力") tempCup="攻";
            else if(Data::Fav[Data::selectedFav]->favorite[3]->Get_MainAttributeChinese()=="元素精通") tempCup="精";
            else if(Data::Fav[Data::selectedFav]->favorite[3]->Get_MainAttributeChinese()=="物理伤害加成") tempCup="物";
            else if(Data::Fav[Data::selectedFav]->favorite[3]->Get_MainAttributeChinese()=="火元素伤害加成") tempCup="火";
            else if(Data::Fav[Data::selectedFav]->favorite[3]->Get_MainAttributeChinese()=="水元素伤害加成") tempCup="水";
            else if(Data::Fav[Data::selectedFav]->favorite[3]->Get_MainAttributeChinese()=="雷元素伤害加成") tempCup="雷";
            else if(Data::Fav[Data::selectedFav]->favorite[3]->Get_MainAttributeChinese()=="冰元素伤害加成") tempCup="冰";
            else if(Data::Fav[Data::selectedFav]->favorite[3]->Get_MainAttributeChinese()=="风元素伤害加成") tempCup="风";
            else if(Data::Fav[Data::selectedFav]->favorite[3]->Get_MainAttributeChinese()=="岩元素伤害加成") tempCup="岩";
            else if(Data::Fav[Data::selectedFav]->favorite[3]->Get_MainAttributeChinese()=="草元素伤害加成") tempCup="草";

            if(Data::Fav[Data::selectedFav]->favorite[4]->Get_MainAttributeChinese()=="生命值") tempHead="生";
            else if(Data::Fav[Data::selectedFav]->favorite[4]->Get_MainAttributeChinese()=="防御力") tempHead="防";
            else if(Data::Fav[Data::selectedFav]->favorite[4]->Get_MainAttributeChinese()=="攻击力") tempHead="攻";
            else if(Data::Fav[Data::selectedFav]->favorite[4]->Get_MainAttributeChinese()=="元素精通") tempHead="精";
            else if(Data::Fav[Data::selectedFav]->favorite[4]->Get_MainAttributeChinese()=="治疗加成") tempHead="治";
            else if(Data::Fav[Data::selectedFav]->favorite[4]->Get_MainAttributeChinese()=="暴击率") tempHead="暴";
            else if(Data::Fav[Data::selectedFav]->favorite[4]->Get_MainAttributeChinese()=="暴击伤害") tempHead="爆";

            //双爆分=暴击×2+爆伤
            ui->entry1->setText(temp+Data::Char[Data::selectedChar][0]->Get_NameChinese()+"，主词条"+tempSand+tempCup+tempHead+"\n双爆 "+QString::number(Data::Fav[Data::selectedFav]->Get_total_critical()*200+Data::Fav[Data::selectedFav]->Get_total_criticalDamage()*100,'f',1)+" 分");
            ui->entry1->show();

            //保留一位小数
            ui->entry2->setText("生 "+QString::number(lifeEntry,'f',1)+" | 攻 "+QString::number(attackEntry,'f',1)+" | 防 "+QString::number(defendEntry,'f',1));
            ui->entry2->show();

            ui->entry3->setText("精 "+QString::number(masteryEntry,'f',1)+" | 充 "+QString::number(rechargeEntry,'f',1)+" | 暴 "+QString::number(criticalEntry,'f',1)+" | 爆 "+QString::number(criDMGEntry,'f',1));
            ui->entry3->show();

            ui->entry4->setText("双爆：共 "+QString::number(criticalEntry+criDMGEntry,'f',1)+" 词条");
            ui->entry4->show();

            if(Data::Char[Data::selectedChar][0]->Get_NameChinese()=="胡桃"||Data::Char[Data::selectedChar][0]->Get_NameChinese()=="诺艾尔"||Data::Char[Data::selectedChar][0]->Get_NameChinese()=="荒泷一斗"||Data::Char[Data::selectedChar][0]->Get_NameChinese()=="珊瑚宫心海")
            {
                ui->entry5->setText("攻击按0.4折算");
                ui->entry5->show();
            }
            else if(Data::Char[Data::selectedChar][0]->Get_NameChinese()=="神里绫人")
            {
                ui->entry5->setText("生命按0.5折算");
                ui->entry5->show();
            }
            else ui->entry5->hide();

            ui->entryBox->show();
            ui->entryBox2->show();
        }
        else QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","当前武器类型错误！");
    }
    else QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","尚未选择完毕！");
}


void Rating::on_entryBox_currentTextChanged(const QString &arg1)
{
    if(arg1!=" ")
    {
        entryTemp1=arg1;
        entryTemp=0;
        if(entryTemp1!=entryTemp2)
        {
            entryTemp=addEntry(entryTemp1)+addEntry(entryTemp2);
            ui->entry4->setText("双爆：共 "+QString::number(entryTemp+criticalEntry+criDMGEntry,'f',1)+" 词条");
        }
        else
        {
            ui->entryBox->setCurrentIndex(0);
            QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","词条重复！");
        }
    }
}

double Rating::addEntry(QString e)
{
    if(Data::Char[Data::selectedChar][0]->Get_NameChinese()=="胡桃"||Data::Char[Data::selectedChar][0]->Get_NameChinese()=="诺艾尔"||Data::Char[Data::selectedChar][0]->Get_NameChinese()=="荒泷一斗"||Data::Char[Data::selectedChar][0]->Get_NameChinese()=="珊瑚宫心海")
    {
        if(e=="生") return lifeEntry;
        else if(e=="攻") return attackEntry*0.4;
        else if(e=="防") return defendEntry;
        else if(e=="精") return masteryEntry;
        else if(e=="充") return rechargeEntry;
        else return 0;
    }
    else if(Data::Char[Data::selectedChar][0]->Get_NameChinese()=="神里绫人")
    {
        if(e=="生") return lifeEntry*0.5;
        else if(e=="攻") return attackEntry;
        else if(e=="防") return defendEntry;
        else if(e=="精") return masteryEntry;
        else if(e=="充") return rechargeEntry;
        else return 0;
    }
    else
    {
        if(e=="生") return lifeEntry;
        else if(e=="攻") return attackEntry;
        else if(e=="防") return defendEntry;
        else if(e=="精") return masteryEntry;
        else if(e=="充") return rechargeEntry;
        else return 0;
    }
}

void Rating::on_entryBox2_currentTextChanged(const QString &arg1)
{
    if(arg1!=" ")
    {
        entryTemp2=arg1;
        entryTemp=0;
        if(entryTemp1!=entryTemp2)
        {
            entryTemp=addEntry(entryTemp1)+addEntry(entryTemp2);
            ui->entry4->setText("双爆：共 "+QString::number(entryTemp+criticalEntry+criDMGEntry,'f',1)+" 词条");
        }
        else
        {
            ui->entryBox2->setCurrentIndex(0);
            QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","词条重复！");
        }
    }
}

