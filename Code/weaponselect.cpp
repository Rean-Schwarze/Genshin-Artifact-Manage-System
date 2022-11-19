#include "weaponselect.h"
#include "ui_weaponselect.h"

WeaponSelect::WeaponSelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WeaponSelect)
{
    ui->setupUi(this);
    //嵌入父窗口
    setGeometry(0,0,960,540);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    hide();

    ui->verticalScrollBar_3->hide();
    ui->weapArea->setVerticalScrollBar(ui->verticalScrollBar_3);
    ui->verticalScrollBar_2->hide();
    ui->detailArea->setVerticalScrollBar(ui->verticalScrollBar_2);
    ui->level->hide();
    ui->grade->hide();
    ui->ma->hide();
    ui->mav->hide();
    ui->ba->hide();
    ui->bav->hide();

    int k;
    Data::ft.setPointSize(12);
    for(int i=0;i<5;i++)
    {
        typeText[i]=new QLabel(ui->weapon);
        typeText[i]->setFont(Data::ft);
        typeText[i]->resize(200,30);
        typeText[i]->setStyleSheet("color:rgb(59,66,85)");
        if (Data::WeapAmount[i+1] % 4 != 0) n[i] =  Data::WeapAmount[i+1]/ 4 + 1;
        else n[i] = Data::WeapAmount[i+1] / 4;//n为行数
        if(Data::WeapAmount[i+1]==0) n[i]=0;
    }

    int temp, temp1, temp2;

    ui->weapon->resize(QSize(420,10+40*5+130*(n[0]+n[1]+n[2]+n[3]+n[4])));
    bg=new QPushButton*[Data::WeapAmount[0]];
    weapIcon=new QLabel*[Data::WeapAmount[0]];
    weapText=new QLabel*[Data::WeapAmount[0]];
    weapTemp=new QPushButton*[Data::WeapAmount[0]];

    temp1=0;
    temp2=0;
    k=0;

    typeText[0]->move(10,10+40*k);
    typeText[0]->setText("单手剑");
    typeText[0]->show();

    k++;
    for (int i=0; i < n[0]; i++)
    {
        for (int j = 0; j < 4 && i * 4 + j< Data::WeapAmount[1]; j++)
        {
            temp=temp2+i * 4 + j;
            bg[temp]=new QPushButton(ui->weapon);
            bg[temp]->setGeometry(105*j,10+40*k+130*i,101,122);
            if(Data::Weap[temp][0]->Get_Star()==4) bg[temp]->setIcon(QIcon(":/Icon/item4Bg.png"));
            else if(Data::Weap[temp][0]->Get_Star()==5) bg[temp]->setIcon(QIcon(":/Icon/item5Bg.png"));
            else if(Data::Weap[temp][0]->Get_Star()==3) bg[temp]->setIcon(QIcon(":/Icon/item3Bg.png"));
            bg[temp]->setIconSize(QSize(101,122));
            connect(bg[temp],&QPushButton::clicked,bg[temp],[=](){changeBtnCli(bg[temp], j, i, temp);});
            connect(bg[temp],&QPushButton::pressed,bg[temp],[=](){changeBtnPre(bg[temp], j, i, temp);});
            connect(bg[temp],&QPushButton::released,bg[temp],[=](){changeBtnRea(bg[temp], j, i, temp);});
            bg[temp]->show();

            NameChinese=Data::Weap[temp][0]->Get_NameChinese();
            QPixmap tempPix=QPixmap(":/Weapon/Sword/"+NameChinese+"_icon.png");
            QSize size=tempPix.size()*0.36;

            weapIcon[temp]=new QLabel(ui->weapon);
            weapIcon[temp]->setGeometry(105*j+3+(101/2-size.width()/2),10+40+130*i+3,size.width(),93);
            weapIcon[temp]->setStyleSheet("background-color: transparent;""border-image: url(:/Weapon/Sword/"+NameChinese+"_icon.png);");
            weapIcon[temp]->show();

            weapText[temp]=new QLabel(ui->weapon);
            weapText[temp]->setGeometry(105*j+3,10+40*k+130*i+98,96,21);
            Data::ft.setPointSize(10);
            weapText[temp]->setFont(Data::ft);
            weapText[temp]->setAlignment(Qt::AlignCenter);
            weapText[temp]->setStyleSheet("color:rgb(73,83,102)");
            weapText[temp]->setText(NameChinese);
            weapText[temp]->show();

            weapTemp[temp]=new QPushButton(ui->weapon);
            weapTemp[temp]->setGeometry(105*j,10+40*k+130*i,101,122);
            if(Data::Weap[temp][0]->Get_Star()==4) weapTemp[temp]->setIcon(QIcon(":/Icon/item4Bg_star.png"));
            else if(Data::Weap[temp][0]->Get_Star()==5) weapTemp[temp]->setIcon(QIcon(":/Icon/item5Bg_star.png"));
            else if(Data::Weap[temp][0]->Get_Star()==3) weapTemp[temp]->setIcon(QIcon(":/Icon/item3Bg_star.png"));
            weapTemp[temp]->setIconSize(QSize(101,122));
            connect(weapTemp[temp],&QPushButton::clicked,bg[temp],&QPushButton::clicked);
            connect(weapTemp[temp],&QPushButton::pressed,bg[temp],&QPushButton::pressed);
            connect(weapTemp[temp],&QPushButton::released,bg[temp],&QPushButton::released);
            weapTemp[temp]->show();
        }
    }

    temp1+=n[0];
    temp2+=Data::WeapAmount[1];

    typeText[1]->move(10,10+40*k+130*temp1);
    typeText[1]->setText("双手剑");
    typeText[1]->show();

    k++;
    for (int i=0; i < n[1]; i++)
    {
        for (int j = 0; j < 4 && i * 4 + j< Data::WeapAmount[2]; j++)
        {
            temp=temp2+i * 4 + j;
            bg[temp]=new QPushButton(ui->weapon);
            bg[temp]->setGeometry(105*j,10+40*k+130*(temp1+i),101,122);
            if(Data::Weap[temp][0]->Get_Star()==4) bg[temp]->setIcon(QIcon(":/Icon/item4Bg.png"));
            else if(Data::Weap[temp][0]->Get_Star()==5) bg[temp]->setIcon(QIcon(":/Icon/item5Bg.png"));
            else if(Data::Weap[temp][0]->Get_Star()==3) bg[temp]->setIcon(QIcon(":/Icon/item3Bg.png"));
            bg[temp]->setIconSize(QSize(101,122));
            connect(bg[temp],&QPushButton::clicked,bg[temp],[=](){changeBtnCli(bg[temp], j, i, temp);});
            connect(bg[temp],&QPushButton::pressed,bg[temp],[=](){changeBtnPre(bg[temp], j, i, temp);});
            connect(bg[temp],&QPushButton::released,bg[temp],[=](){changeBtnRea(bg[temp], j, i, temp);});
            bg[temp]->show();

            NameChinese=Data::Weap[temp][0]->Get_NameChinese();
            QPixmap tempPix=QPixmap(":/Weapon/Claymore/"+NameChinese+"_icon.png");
            QSize size=tempPix.size()*0.36;

            weapIcon[temp]=new QLabel(ui->weapon);
            weapIcon[temp]->setGeometry(105*j+3+(101/2-size.width()/2),10+40*k+130*(temp1+i)+3,size.width(),93);
            weapIcon[temp]->setStyleSheet("background-color: transparent;""border-image: url(:/Weapon/Claymore/"+NameChinese+"_icon.png);");
            weapIcon[temp]->show();

            weapText[temp]=new QLabel(ui->weapon);
            weapText[temp]->setGeometry(105*j+3,10+40*k+130*(temp1+i)+98,96,21);
            Data::ft.setPointSize(10);
            weapText[temp]->setFont(Data::ft);
            weapText[temp]->setAlignment(Qt::AlignCenter);
            weapText[temp]->setStyleSheet("color:rgb(73,83,102)");
            weapText[temp]->setText(NameChinese);
            weapText[temp]->show();

            weapTemp[temp]=new QPushButton(ui->weapon);
            weapTemp[temp]->setGeometry(105*j,10+40*k+130*(temp1+i),101,122);
            if(Data::Weap[temp][0]->Get_Star()==4) weapTemp[temp]->setIcon(QIcon(":/Icon/item4Bg_star.png"));
            else if(Data::Weap[temp][0]->Get_Star()==5) weapTemp[temp]->setIcon(QIcon(":/Icon/item5Bg_star.png"));
            else if(Data::Weap[temp][0]->Get_Star()==3) weapTemp[temp]->setIcon(QIcon(":/Icon/item3Bg_star.png"));
            weapTemp[temp]->setIconSize(QSize(101,122));
            connect(weapTemp[temp],&QPushButton::clicked,bg[temp],&QPushButton::clicked);
            connect(weapTemp[temp],&QPushButton::pressed,bg[temp],&QPushButton::pressed);
            connect(weapTemp[temp],&QPushButton::released,bg[temp],&QPushButton::released);
            weapTemp[temp]->show();
        }
    }

    temp1+=n[1];
    temp2+=Data::WeapAmount[2];

    typeText[2]->move(10,10+40*k+130*temp1);
    typeText[2]->setText("弓");
    typeText[2]->show();

    k++;
    for (int i=0; i < n[2]; i++)
    {
        for (int j = 0; j < 4 && i * 4 + j< Data::WeapAmount[3]; j++)
        {
            temp=temp2+i * 4 + j;
            bg[temp]=new QPushButton(ui->weapon);
            bg[temp]->setGeometry(105*j,10+40*k+130*(temp1+i),101,122);
            if(Data::Weap[temp][0]->Get_Star()==4) bg[temp]->setIcon(QIcon(":/Icon/item4Bg.png"));
            else if(Data::Weap[temp][0]->Get_Star()==5) bg[temp]->setIcon(QIcon(":/Icon/item5Bg.png"));
            else if(Data::Weap[temp][0]->Get_Star()==3) bg[temp]->setIcon(QIcon(":/Icon/item3Bg.png"));
            bg[temp]->setIconSize(QSize(101,122));
            connect(bg[temp],&QPushButton::clicked,bg[temp],[=](){changeBtnCli(bg[temp], j, i, temp);});
            connect(bg[temp],&QPushButton::pressed,bg[temp],[=](){changeBtnPre(bg[temp], j, i, temp);});
            connect(bg[temp],&QPushButton::released,bg[temp],[=](){changeBtnRea(bg[temp], j, i, temp);});
            bg[temp]->show();

            NameChinese=Data::Weap[temp][0]->Get_NameChinese();
            QPixmap tempPix=QPixmap(":/Weapon/Bow/"+NameChinese+"_icon.png");
            QSize size;
            if(NameChinese=="冬极白星") size=tempPix.size()*0.18;
            else size=tempPix.size()*0.36;

            weapIcon[temp]=new QLabel(ui->weapon);
            weapIcon[temp]->setGeometry(105*j+3+(101/2-size.width()/2),10+40*k+130*(temp1+i)+3,size.width(),93);
            weapIcon[temp]->setStyleSheet("background-color: transparent;""border-image: url(:/Weapon/Bow/"+NameChinese+"_icon.png);");
            weapIcon[temp]->show();

            weapText[temp]=new QLabel(ui->weapon);
            weapText[temp]->setGeometry(105*j+3,10+40*k+130*(temp1+i)+98,96,21);
            Data::ft.setPointSize(10);
            weapText[temp]->setFont(Data::ft);
            weapText[temp]->setAlignment(Qt::AlignCenter);
            weapText[temp]->setStyleSheet("color:rgb(73,83,102)");
            weapText[temp]->setText(NameChinese);
            weapText[temp]->show();

            weapTemp[temp]=new QPushButton(ui->weapon);
            weapTemp[temp]->setGeometry(105*j,10+40*k+130*(temp1+i),101,122);
            if(Data::Weap[temp][0]->Get_Star()==4) weapTemp[temp]->setIcon(QIcon(":/Icon/item4Bg_star.png"));
            else if(Data::Weap[temp][0]->Get_Star()==5) weapTemp[temp]->setIcon(QIcon(":/Icon/item5Bg_star.png"));
            else if(Data::Weap[temp][0]->Get_Star()==3) weapTemp[temp]->setIcon(QIcon(":/Icon/item3Bg_star.png"));
            weapTemp[temp]->setIconSize(QSize(101,122));
            connect(weapTemp[temp],&QPushButton::clicked,bg[temp],&QPushButton::clicked);
            connect(weapTemp[temp],&QPushButton::pressed,bg[temp],&QPushButton::pressed);
            connect(weapTemp[temp],&QPushButton::released,bg[temp],&QPushButton::released);
            weapTemp[temp]->show();
        }
    }

    temp1+=n[2];
    temp2+=Data::WeapAmount[3];

    typeText[3]->move(10,10+40*k+130*temp1);
    typeText[3]->setText("法器");
    typeText[3]->show();

    k++;
    for (int i=0; i < n[3]; i++)
    {
        for (int j = 0; j < 4 && i * 4 + j< Data::WeapAmount[4]; j++)
        {
            temp=temp2+i * 4 + j;
            bg[temp]=new QPushButton(ui->weapon);
            bg[temp]->setGeometry(105*j,10+40*k+130*(temp1+i),101,122);
            if(Data::Weap[temp][0]->Get_Star()==4) bg[temp]->setIcon(QIcon(":/Icon/item4Bg.png"));
            else if(Data::Weap[temp][0]->Get_Star()==5) bg[temp]->setIcon(QIcon(":/Icon/item5Bg.png"));
            else if(Data::Weap[temp][0]->Get_Star()==3) bg[temp]->setIcon(QIcon(":/Icon/item3Bg.png"));
            bg[temp]->setIconSize(QSize(101,122));
            connect(bg[temp],&QPushButton::clicked,bg[temp],[=](){changeBtnCli(bg[temp], j, i, temp);});
            connect(bg[temp],&QPushButton::pressed,bg[temp],[=](){changeBtnPre(bg[temp], j, i, temp);});
            connect(bg[temp],&QPushButton::released,bg[temp],[=](){changeBtnRea(bg[temp], j, i, temp);});
            bg[temp]->show();

            NameChinese=Data::Weap[temp][0]->Get_NameChinese();
            QPixmap tempPix=QPixmap(":/Weapon/Catalyst/"+NameChinese+"_icon.png");
            QSize size;
            if(NameChinese=="天空之卷") size=tempPix.size()*0.39;
            else size=tempPix.size()*0.45;

            weapIcon[temp]=new QLabel(ui->weapon);
            weapIcon[temp]->setGeometry(105*j+3+(101/2-size.width()/2),10+40*k+130*(temp1+i)+3+(93/2-size.height()/2),size.width(),size.height());
            weapIcon[temp]->setStyleSheet("background-color: transparent;""border-image: url(:/Weapon/Catalyst/"+NameChinese+"_icon.png);");
            weapIcon[temp]->show();

            weapText[temp]=new QLabel(ui->weapon);
            weapText[temp]->setGeometry(105*j+3,10+40*k+130*(temp1+i)+98,96,21);
            Data::ft.setPointSize(10);
            weapText[temp]->setFont(Data::ft);
            weapText[temp]->setAlignment(Qt::AlignCenter);
            weapText[temp]->setStyleSheet("color:rgb(73,83,102)");
            weapText[temp]->setText(NameChinese);
            weapText[temp]->show();

            weapTemp[temp]=new QPushButton(ui->weapon);
            weapTemp[temp]->setGeometry(105*j,10+40*k+130*(temp1+i),101,122);
            if(Data::Weap[temp][0]->Get_Star()==4) weapTemp[temp]->setIcon(QIcon(":/Icon/item4Bg_star.png"));
            else if(Data::Weap[temp][0]->Get_Star()==5) weapTemp[temp]->setIcon(QIcon(":/Icon/item5Bg_star.png"));
            else if(Data::Weap[temp][0]->Get_Star()==3) weapTemp[temp]->setIcon(QIcon(":/Icon/item3Bg_star.png"));
            weapTemp[temp]->setIconSize(QSize(101,122));
            connect(weapTemp[temp],&QPushButton::clicked,bg[temp],&QPushButton::clicked);
            connect(weapTemp[temp],&QPushButton::pressed,bg[temp],&QPushButton::pressed);
            connect(weapTemp[temp],&QPushButton::released,bg[temp],&QPushButton::released);
            weapTemp[temp]->show();
        }
    }

    temp1+=n[3];
    temp2+=Data::WeapAmount[4];

    typeText[4]->move(10,10+40*k+130*temp1);
    typeText[4]->setText("长柄武器");
    typeText[4]->show();

    k++;
    for (int i=0; i < n[4]; i++)
    {
        for (int j = 0; j < 4 && i * 4 + j< Data::WeapAmount[5]; j++)
        {
            temp=temp2+i * 4 + j;
            bg[temp]=new QPushButton(ui->weapon);
            bg[temp]->setGeometry(105*j,10+40*k+130*(temp1+i),101,122);
            if(Data::Weap[temp][0]->Get_Star()==4) bg[temp]->setIcon(QIcon(":/Icon/item4Bg.png"));
            else if(Data::Weap[temp][0]->Get_Star()==5) bg[temp]->setIcon(QIcon(":/Icon/item5Bg.png"));
            else if(Data::Weap[temp][0]->Get_Star()==3) bg[temp]->setIcon(QIcon(":/Icon/item3Bg.png"));
            bg[temp]->setIconSize(QSize(101,122));
            connect(bg[temp],&QPushButton::clicked,bg[temp],[=](){changeBtnCli(bg[temp], j, i, temp);});
            connect(bg[temp],&QPushButton::pressed,bg[temp],[=](){changeBtnPre(bg[temp], j, i, temp);});
            connect(bg[temp],&QPushButton::released,bg[temp],[=](){changeBtnRea(bg[temp], j, i, temp);});
            bg[temp]->show();

            NameChinese=Data::Weap[temp][0]->Get_NameChinese();
            QPixmap tempPix=QPixmap(":/Weapon/Polearm/"+NameChinese+"_icon.png");
            QSize size=tempPix.size()*0.36;

            weapIcon[temp]=new QLabel(ui->weapon);
            weapIcon[temp]->setGeometry(105*j+3+(101/2-size.width()/2),10+40*k+130*(temp1+i)+3,size.width(),93);
            weapIcon[temp]->setStyleSheet("background-color: transparent;""border-image: url(:/Weapon/Polearm/"+NameChinese+"_icon.png);");
            weapIcon[temp]->show();

            weapText[temp]=new QLabel(ui->weapon);
            weapText[temp]->setGeometry(105*j+3,10+40*k+130*(temp1+i)+98,96,21);
            Data::ft.setPointSize(10);
            weapText[temp]->setFont(Data::ft);
            weapText[temp]->setAlignment(Qt::AlignCenter);
            weapText[temp]->setStyleSheet("color:rgb(73,83,102)");
            weapText[temp]->setText(NameChinese);
            weapText[temp]->show();

            weapTemp[temp]=new QPushButton(ui->weapon);
            weapTemp[temp]->setGeometry(105*j,10+40*k+130*(temp1+i),101,122);
            if(Data::Weap[temp][0]->Get_Star()==4) weapTemp[temp]->setIcon(QIcon(":/Icon/item4Bg_star.png"));
            else if(Data::Weap[temp][0]->Get_Star()==5) weapTemp[temp]->setIcon(QIcon(":/Icon/item5Bg_star.png"));
            else if(Data::Weap[temp][0]->Get_Star()==3) weapTemp[temp]->setIcon(QIcon(":/Icon/item3Bg_star.png"));
            weapTemp[temp]->setIconSize(QSize(101,122));
            connect(weapTemp[temp],&QPushButton::clicked,bg[temp],&QPushButton::clicked);
            connect(weapTemp[temp],&QPushButton::pressed,bg[temp],&QPushButton::pressed);
            connect(weapTemp[temp],&QPushButton::released,bg[temp],&QPushButton::released);
            weapTemp[temp]->show();
        }
    }

    ui->comboBox->addItem("请选择武器等级");
    ui->comboBox->addItem("80级未突破");
    ui->comboBox->addItem("80级已突破");
    ui->comboBox->addItem("90级");
}

WeaponSelect::~WeaponSelect()
{
    delete ui;
    for(int i=0;i<5;i++)
    {
        typeText[i]->close();
        delete[] typeText[i];
    }
    for(int i=0;i<Data::WeapAmount[0];i++)
    {
        bg[i]->close();
        delete[] bg[i];
        weapIcon[i]->close();
        delete[] weapIcon[i];
        weapTemp[i]->close();
        delete[] weapTemp[i];
        weapText[i]->close();
        delete[] weapText[i];
    }
}

void WeaponSelect::on_Back_clicked()
{
    this->close();
}

void WeaponSelect::changeBtnCli(QPushButton* btn, int j, int i, int Num)
{
    Data::selectedWeap=Num;
    QPixmap PixBgWeap;
    QSize PixBgWeapSize;
    if(Data::Weap[Num][0]->Get_WeaponTypeChinese()=="单手剑")
    {
        PixBgWeap=QPixmap(":/Weapon/Sword/"+Data::Weap[Num][0]->Get_NameChinese()+".png");
        PixBgWeapSize = PixBgWeap.size()*0.73;//缩小一下
    }
    else if(Data::Weap[Num][0]->Get_WeaponTypeChinese()=="双手剑")
    {
        PixBgWeap=QPixmap(":/Weapon/Claymore/"+Data::Weap[Num][0]->Get_NameChinese()+".png");
        PixBgWeapSize = PixBgWeap.size()*0.6;//缩小一下
    }
    else if(Data::Weap[Num][0]->Get_WeaponTypeChinese()=="弓")
    {
        PixBgWeap=QPixmap(":/Weapon/Bow/"+Data::Weap[Num][0]->Get_NameChinese()+".png");
        PixBgWeapSize = PixBgWeap.size()*0.59;//缩小一下
    }
    else if(Data::Weap[Num][0]->Get_WeaponTypeChinese()=="法器")
    {
        PixBgWeap=QPixmap(":/Weapon/Catalyst/"+Data::Weap[Num][0]->Get_NameChinese()+".png");
        PixBgWeapSize = PixBgWeap.size();
        ui->bgWeap->setGeometry(960-PixBgWeapSize.width()-100,540/2-PixBgWeapSize.height()/2,PixBgWeapSize.width(),PixBgWeapSize.height());
    }
    else if(Data::Weap[Num][0]->Get_WeaponTypeChinese()=="长柄武器")
    {
        PixBgWeap=QPixmap(":/Weapon/Polearm/"+Data::Weap[Num][0]->Get_NameChinese()+".png");
        PixBgWeapSize = PixBgWeap.size()*0.525;//缩小一下
    }
    if(Data::Weap[Num][0]->Get_WeaponTypeChinese()!="法器") ui->bgWeap->setGeometry(960-100-PixBgWeapSize.width(),50,PixBgWeapSize.width(),PixBgWeapSize.height());
    ui->bgWeap->setScaledContents(true);
    ui->bgWeap->setPixmap(PixBgWeap);
    ui->bgWeap->show();
    ui->comboBox->setCurrentIndex(0);
}

void WeaponSelect::changeBtnPre(QPushButton* btn, int j, int i, int temp)
{
    if(Data::Weap[temp][0]->Get_Star()==4) btn->setIcon(QIcon(":/Icon/item4Bg_selected.png"));
    else if(Data::Weap[temp][0]->Get_Star()==5) btn->setIcon(QIcon(":/Icon/item5Bg_selected.png"));
    else if(Data::Weap[temp][0]->Get_Star()==3) btn->setIcon(QIcon(":/Icon/item3Bg_selected.png"));
}

void WeaponSelect::changeBtnRea(QPushButton* btn, int j, int i, int temp)
{
    if(Data::Weap[temp][0]->Get_Star()==4) btn->setIcon(QIcon(":/Icon/item4Bg.png"));
    else if(Data::Weap[temp][0]->Get_Star()==5) btn->setIcon(QIcon(":/Icon/item5Bg.png"));
    else if(Data::Weap[temp][0]->Get_Star()==3) btn->setIcon(QIcon(":/Icon/item3Bg.png"));
}

void WeaponSelect::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1!="请选择武器等级")
    {
        if(Data::selectedWeap>-1)
        {
            ui->name->setText(Data::Weap[Data::selectedWeap][0]->Get_NameChinese());
            ui->type->setText(Data::Weap[Data::selectedWeap][0]->Get_WeaponTypeChinese());
            ui->ba->setText("基础攻击力");
            ui->ba->show();
            ui->ma->setText(Data::Weap[Data::selectedWeap][0]->Get_BaseAttributeChinese());
            ui->ma->show();
            if(Data::Weap[Data::selectedWeap][0]->Get_Star()==3) ui->star->setStyleSheet("border-image: url(:/Icon/3star.png);");
            else if(Data::Weap[Data::selectedWeap][0]->Get_Star()==4) ui->star->setStyleSheet("border-image: url(:/Icon/4star.png);");
            else if(Data::Weap[Data::selectedWeap][0]->Get_Star()==5) ui->star->setStyleSheet("border-image: url(:/Icon/5star.png);");
            ui->star->show();
            ui->grade->show();
            ui->SpecialAbilityName->setText(Data::Weap[Data::selectedWeap][0]->Get_SpecialAbilityName());
            ui->SpecialAbility->setText("    "+Data::Weap[Data::selectedWeap][0]->Get_SpecialAbility());
            ui->SpecialAbility->adjustSize();
            ui->des->setGeometry(5,195+ui->SpecialAbility->size().height()+5,205,21);
            ui->des->setText("    "+Data::Weap[Data::selectedWeap][0]->Get_Description());
            ui->des->adjustSize();
            ui->detail->adjustSize();
            if(arg1=="80级未突破")
            {
                Data::weapLevel=0;
                ui->level->setText("Lv.80/80");
                ui->level->show();
                ui->bav->setText(QString::number(Data::Weap[Data::selectedWeap][Data::weapLevel]->Get_BaseAttack()));
                ui->bav->show();
                if(Data::Weap[Data::selectedWeap][Data::weapLevel]->Get_BaseAttributeValue()>1)
                {
                    ui->mav->setText(QString::number(Data::Weap[Data::selectedWeap][Data::weapLevel]->Get_BaseAttributeValue()));
                }
                else ui->mav->setText(QString::number(Data::Weap[Data::selectedWeap][Data::weapLevel]->Get_BaseAttributeValue()*100)+"%");
                ui->mav->show();
            }
            else if(arg1=="80级已突破")
            {
                Data::weapLevel=1;
                ui->level->setText("Lv.80/90");
                ui->level->show();
                ui->bav->setText(QString::number(Data::Weap[Data::selectedWeap][Data::weapLevel]->Get_BaseAttack()));
                ui->bav->show();
                if(Data::Weap[Data::selectedWeap][Data::weapLevel]->Get_BaseAttributeValue()>1)
                {
                    ui->mav->setText(QString::number(Data::Weap[Data::selectedWeap][Data::weapLevel]->Get_BaseAttributeValue()));
                }
                else ui->mav->setText(QString::number(Data::Weap[Data::selectedWeap][Data::weapLevel]->Get_BaseAttributeValue()*100)+"%");
                ui->mav->show();
            }
            else if(arg1=="90级")
            {
                Data::weapLevel=2;
                ui->level->setText("Lv.90/90");
                ui->level->show();
                ui->bav->setText(QString::number(Data::Weap[Data::selectedWeap][Data::weapLevel]->Get_BaseAttack()));
                ui->bav->show();
                if(Data::Weap[Data::selectedWeap][Data::weapLevel]->Get_BaseAttributeValue()>1)
                {
                    ui->mav->setText(QString::number(Data::Weap[Data::selectedWeap][Data::weapLevel]->Get_BaseAttributeValue()));
                }
                else ui->mav->setText(QString::number(Data::Weap[Data::selectedWeap][Data::weapLevel]->Get_BaseAttributeValue()*100)+"%");
                ui->mav->show();
            }
        }
        else QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","当前尚未选择武器！");
    }
    else
    {
        detailClear();
    }
}

void WeaponSelect::on_confirm_clicked()
{
    if(Data::selectedWeap>-1&&Data::weapLevel>-1)
    {
        if(Data::matchCharWeap()) this->close();
        else
        {
            ui->comboBox->setCurrentIndex(0);
            Data::selectedWeap=-1;
            detailClear();
            ui->bgWeap->hide();
            QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","武器类型错误！");
        }
    }
    else QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","当前尚未选择完毕！");
}

void WeaponSelect::detailClear()
{
    Data::weapLevel=-1;
    ui->name->clear();
    ui->type->clear();
    ui->ba->clear();
    ui->ba->hide();
    ui->bav->clear();
    ui->bav->hide();
    ui->ma->clear();
    ui->ma->hide();
    ui->mav->clear();
    ui->mav->hide();
    ui->star->hide();
    ui->level->clear();
    ui->level->hide();
    ui->grade->hide();
    ui->SpecialAbilityName->clear();
    ui->SpecialAbility->clear();
    ui->des->clear();
    ui->des->adjustSize();
}
