#include "characterselecte.h"
#include "ui_characterselecte.h"

CharacterSelecte::CharacterSelecte(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CharacterSelecte)
{
    ui->setupUi(this);
    //嵌入父窗口
    setGeometry(0,0,960,540);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    hide();

    ui->verticalScrollBar_3->hide();
    ui->charArea->setVerticalScrollBar(ui->verticalScrollBar_3);
    ui->verticalScrollBar_4->hide();
    ui->levelArea->setVerticalScrollBar(ui->verticalScrollBar_4);

    int i, k, n1, temp, temp1;
    Data::ft.setPointSize(12);
    for(i=0;i<8;i++)
    {
        element[i]=new QLabel(ui->character);
        element[i]->resize(QSize(30,30));
        element[i]->hide();
        elementText[i]=new QLabel(ui->character);
        elementText[i]->resize(QSize(200,30));
        elementText[i]->setFont(Data::ft);
        elementText[i]->hide();
        if (Data::CharAmount[i+1] % 4 != 0) n[i] =  Data::CharAmount[i+1]/ 4 + 1;
        else n[i] = Data::CharAmount[i+1] / 4;//n为行数
        if(Data::CharAmount[i+1]==0) n[i]=0;
    }

    n1=n[0]+n[1]+n[2]+n[3]+n[4]+n[5]+n[6]+n[7];
    ui->character->resize(QSize(420,10+40*8+130*n1));
    bg=new QPushButton*[Data::CharAmount[0]];
    charIcon=new QLabel*[Data::CharAmount[0]];
    charText=new QLabel*[Data::CharAmount[0]];
    charElement=new QLabel*[Data::CharAmount[0]];
    charTemp=new QPushButton*[Data::CharAmount[0]];

    temp1=0;
    k=0;

    element[0]->move(10,10+40*k);
    element[0]->setStyleSheet("border-image: url(:/Icon/Pryo.png)");
    element[0]->show();
    elementText[0]->move(45,10+40*k);
    elementText[0]->setStyleSheet("color:rgb(255,102,64)");
    elementText[0]->setText("火元素");
    elementText[0]->show();

    k++;
    if(n[0]!=0)
    {
        for (i=0; i < n[0]; i++)
        {
            for (int j = 0; j < 4 && i * 4 + j< Data::CharAmount[1]; j++)
            {
                temp=i * 4 + j;
                bg[temp]=new QPushButton(ui->character);
                bg[temp]->setGeometry(105*j,10+40*k+130*i,101,122);
                if(Data::Char[temp][0]->Get_Star()==4) bg[temp]->setIcon(QIcon(":/Icon/item4Bg.png"));
                else if(Data::Char[temp][0]->Get_Star()==5) bg[temp]->setIcon(QIcon(":/Icon/item5Bg.png"));
                bg[temp]->setIconSize(QSize(101,122));
                connect(bg[temp],&QPushButton::clicked,bg[temp],[=](){changeBtnCli(bg[temp], j, i, temp);});
                connect(bg[temp],&QPushButton::pressed,bg[temp],[=](){changeBtnPre(bg[temp], j, i, temp, temp1 ,k);});
                connect(bg[temp],&QPushButton::released,bg[temp],[=](){changeBtnRea(bg[temp], j, i, temp, temp1 ,k);});
                bg[temp]->show();

                Name=Data::Char[temp][0]->Get_Name();
                NameChinese=Data::Char[temp][0]->Get_NameChinese();

                charIcon[temp]=new QLabel(ui->character);
                charIcon[temp]->setGeometry(105*j+3,10+40*k+130*i+3,93,93);
                charIcon[temp]->setStyleSheet("background-color: transparent;""border-image: url(:/Character/Icon/"+Name+"_icon.png);");
                charIcon[temp]->show();

                charElement[temp]=new QLabel(ui->character);
                charElement[temp]->setGeometry(105*j+3,10+40*k+130*i+3,30,30);
                charElement[temp]->setStyleSheet("background-color: transparent;""border-image: url(:/Icon/Pryo.png);");
                charElement[temp]->show();

                charTemp[temp]=new QPushButton(ui->character);
                charTemp[temp]->setGeometry(105*j,10+40*k+130*i,101,122);
                if(Data::Char[temp][0]->Get_Star()==4) charTemp[temp]->setIcon(QIcon(":/Icon/item4Bg_cover.png"));
                else if(Data::Char[temp][0]->Get_Star()==5) charTemp[temp]->setIcon(QIcon(":/Icon/item5Bg_cover.png"));
                charTemp[temp]->setIconSize(QSize(101,122));
                connect(charTemp[temp],&QPushButton::clicked,bg[temp],&QPushButton::clicked);
                connect(charTemp[temp],&QPushButton::pressed,bg[temp],&QPushButton::pressed);
                connect(charTemp[temp],&QPushButton::released,bg[temp],&QPushButton::released);
                charTemp[temp]->show();

                charText[temp]=new QLabel(ui->character);
                charText[temp]->setGeometry(105*j+3,10+40*k+130*i+96,96,21);
                Data::ft.setPointSize(12);
                charText[temp]->setFont(Data::ft);
                charText[temp]->setAlignment(Qt::AlignCenter);
                charText[temp]->setStyleSheet("color:rgb(73,83,102)");
                charText[temp]->setText(NameChinese);
                charText[temp]->show();
            }
        }
    }
    temp1+=n[0];

    element[1]->move(10,10+40*k+130*n[0]);
    element[1]->setStyleSheet("border-image: url(:/Icon/Hydro.png)");
    element[1]->show();
    elementText[1]->move(45,10+40*k+130*n[0]);
    elementText[1]->setStyleSheet("color:rgb(0,192,255)");
    elementText[1]->setText("水元素");
    elementText[1]->show();

    k++;
    if(n[1]!=0)
    {
        for (i=0; i < n[1]; i++)
        {
            for (int j = 0; j < 4 && i * 4 + j< Data::CharAmount[2]; j++)
            {
                temp=Data::CharAmount[1]+i * 4 + j;
                bg[temp]=new QPushButton(ui->character);
                bg[temp]->setGeometry(105*j,10+40*k+130*(temp1+i),101,122);
                if(Data::Char[temp][0]->Get_Star()==4) bg[temp]->setIcon(QIcon(":/Icon/item4Bg.png"));
                else if(Data::Char[temp][0]->Get_Star()==5) bg[temp]->setIcon(QIcon(":/Icon/item5Bg.png"));
                bg[temp]->setIconSize(QSize(101,122));
                connect(bg[temp],&QPushButton::clicked,bg[temp],[=](){changeBtnCli(bg[temp], j, i, temp);});
                connect(bg[temp],&QPushButton::pressed,bg[temp],[=](){changeBtnPre(bg[temp], j, i, temp, temp1, k);});
                connect(bg[temp],&QPushButton::released,bg[temp],[=](){changeBtnRea(bg[temp], j, i, temp, temp1, k);});
                bg[temp]->show();

                Name=Data::Char[temp][0]->Get_Name();
                NameChinese=Data::Char[temp][0]->Get_NameChinese();

                charIcon[temp]=new QLabel(ui->character);
                charIcon[temp]->setGeometry(105*j+3,10+40*k+130*(temp1+i)+3,93,93);
                charIcon[temp]->setStyleSheet("background-color: transparent;""border-image: url(:/Character/Icon/"+Name+"_icon.png);");
                charIcon[temp]->show();

                charElement[temp]=new QLabel(ui->character);
                charElement[temp]->setGeometry(105*j+3,10+40*k+130*(temp1+i)+3,30,30);
                charElement[temp]->setStyleSheet("background-color: transparent;""border-image: url(:/Icon/Hydro.png);");
                charElement[temp]->show();

                charTemp[temp]=new QPushButton(ui->character);
                charTemp[temp]->setGeometry(105*j,10+40*k+130*(temp1+i),101,122);
                if(Data::Char[temp][0]->Get_Star()==4) charTemp[temp]->setIcon(QIcon(":/Icon/item4Bg_cover.png"));
                else if(Data::Char[temp][0]->Get_Star()==5) charTemp[temp]->setIcon(QIcon(":/Icon/item5Bg_cover.png"));
                charTemp[temp]->setIconSize(QSize(101,122));
                connect(charTemp[temp],&QPushButton::clicked,bg[temp],&QPushButton::clicked);
                connect(charTemp[temp],&QPushButton::pressed,bg[temp],&QPushButton::pressed);
                connect(charTemp[temp],&QPushButton::released,bg[temp],&QPushButton::released);
                charTemp[temp]->show();

                charText[temp]=new QLabel(ui->character);
                charText[temp]->setGeometry(105*j+3,10+40*k+130*(temp1+i)+96,96,21);
                Data::ft.setPointSize(12);
                charText[temp]->setFont(Data::ft);
                charText[temp]->setAlignment(Qt::AlignCenter);
                charText[temp]->setStyleSheet("color:rgb(73,83,102)");
                charText[temp]->setText(NameChinese);
                charText[temp]->show();
            }
        }
    }

    temp1+=n[1];

    element[2]->move(10,10+40*k+130*temp1);
    element[2]->setStyleSheet("border-image: url(:/Icon/Electro.png)");
    element[2]->show();
    elementText[2]->move(45,10+40*k+130*temp1);
    elementText[2]->setStyleSheet("color:rgb(204,128,255)");
    elementText[2]->setText("雷元素");
    elementText[2]->show();

    k++;
    if(n[2]!=0)
    {
        for (i=0; i < n[2]; i++)
        {
            for (int j = 0; j < 4 && i * 4 + j< Data::CharAmount[3]; j++)
            {
                temp=Data::CharAmount[1]+Data::CharAmount[2]+i * 4 + j;
                bg[temp]=new QPushButton(ui->character);
                bg[temp]->setGeometry(105*j,10+40*k+130*(temp1+i),101,122);
                if(Data::Char[temp][0]->Get_Star()==4) bg[temp]->setIcon(QIcon(":/Icon/item4Bg.png"));
                else if(Data::Char[temp][0]->Get_Star()==5) bg[temp]->setIcon(QIcon(":/Icon/item5Bg.png"));
                bg[temp]->setIconSize(QSize(101,122));
                connect(bg[temp],&QPushButton::clicked,bg[temp],[=](){changeBtnCli(bg[temp], j, i, temp);});
                connect(bg[temp],&QPushButton::pressed,bg[temp],[=](){changeBtnPre(bg[temp], j, i, temp, temp1, k);});
                connect(bg[temp],&QPushButton::released,bg[temp],[=](){changeBtnRea(bg[temp], j, i, temp, temp1, k);});
                bg[temp]->show();

                Name=Data::Char[temp][0]->Get_Name();
                NameChinese=Data::Char[temp][0]->Get_NameChinese();

                charIcon[temp]=new QLabel(ui->character);
                charIcon[temp]->setGeometry(105*j+3,10+40*k+130*(temp1+i)+3,93,93);
                charIcon[temp]->setStyleSheet("background-color: transparent;""border-image: url(:/Character/Icon/"+Name+"_icon.png);");
                charIcon[temp]->show();

                charElement[temp]=new QLabel(ui->character);
                charElement[temp]->setGeometry(105*j+3,10+40*k+130*(temp1+i)+3,30,30);
                charElement[temp]->setStyleSheet("background-color: transparent;""border-image: url(:/Icon/Electro.png);");
                charElement[temp]->show();

                charTemp[temp]=new QPushButton(ui->character);
                charTemp[temp]->setGeometry(105*j,10+40*k+130*(temp1+i),101,122);
                if(Data::Char[temp][0]->Get_Star()==4) charTemp[temp]->setIcon(QIcon(":/Icon/item4Bg_cover.png"));
                else if(Data::Char[temp][0]->Get_Star()==5) charTemp[temp]->setIcon(QIcon(":/Icon/item5Bg_cover.png"));
                charTemp[temp]->setIconSize(QSize(101,122));
                connect(charTemp[temp],&QPushButton::clicked,bg[temp],&QPushButton::clicked);
                connect(charTemp[temp],&QPushButton::pressed,bg[temp],&QPushButton::pressed);
                connect(charTemp[temp],&QPushButton::released,bg[temp],&QPushButton::released);
                charTemp[temp]->show();

                charText[temp]=new QLabel(ui->character);
                charText[temp]->setGeometry(105*j+3,10+40*k+130*(temp1+i)+96,96,21);
                Data::ft.setPointSize(12);
                charText[temp]->setFont(Data::ft);
                charText[temp]->setAlignment(Qt::AlignCenter);
                charText[temp]->setStyleSheet("color:rgb(73,83,102)");
                charText[temp]->setText(NameChinese);
                charText[temp]->show();
            }
        }
    }

    temp1+=n[2];

    element[3]->move(10,10+40*k+130*temp1);
    element[3]->setStyleSheet("border-image: url(:/Icon/Anemo.png)");
    element[3]->show();
    elementText[3]->move(45,10+40*k+130*temp1);
    elementText[3]->setStyleSheet("color:rgb(51,215,160)");
    elementText[3]->setText("风元素");
    elementText[3]->show();

    k++;
    if(n[3]!=0)
    {
        for (i=0; i < n[3]; i++)
        {
            for (int j = 0; j < 4 && i * 4 + j< Data::CharAmount[4]; j++)
            {
                temp=Data::CharAmount[1]+Data::CharAmount[2]+Data::CharAmount[3]+i * 4 + j;
                bg[temp]=new QPushButton(ui->character);
                bg[temp]->setGeometry(105*j,10+40*k+130*(temp1+i),101,122);
                if(Data::Char[temp][0]->Get_Star()==4) bg[temp]->setIcon(QIcon(":/Icon/item4Bg.png"));
                else if(Data::Char[temp][0]->Get_Star()==5) bg[temp]->setIcon(QIcon(":/Icon/item5Bg.png"));
                bg[temp]->setIconSize(QSize(101,122));
                connect(bg[temp],&QPushButton::clicked,bg[temp],[=](){changeBtnCli(bg[temp], j, i, temp);});
                connect(bg[temp],&QPushButton::pressed,bg[temp],[=](){changeBtnPre(bg[temp], j, i, temp, temp1, k);});
                connect(bg[temp],&QPushButton::released,bg[temp],[=](){changeBtnRea(bg[temp], j, i, temp, temp1, k);});
                bg[temp]->show();

                Name=Data::Char[temp][0]->Get_Name();
                NameChinese=Data::Char[temp][0]->Get_NameChinese();

                charIcon[temp]=new QLabel(ui->character);
                charIcon[temp]->setGeometry(105*j+3,10+40*k+130*(temp1+i)+3,93,93);
                charIcon[temp]->setStyleSheet("background-color: transparent;""border-image: url(:/Character/Icon/"+Name+"_icon.png);");
                charIcon[temp]->show();

                charElement[temp]=new QLabel(ui->character);
                charElement[temp]->setGeometry(105*j+3,10+40*k+130*(temp1+i)+3,30,30);
                charElement[temp]->setStyleSheet("background-color: transparent;""border-image: url(:/Icon/Anemo.png);");
                charElement[temp]->show();

                charTemp[temp]=new QPushButton(ui->character);
                charTemp[temp]->setGeometry(105*j,10+40*k+130*(temp1+i),101,122);
                if(Data::Char[temp][0]->Get_Star()==4) charTemp[temp]->setIcon(QIcon(":/Icon/item4Bg_cover.png"));
                else if(Data::Char[temp][0]->Get_Star()==5) charTemp[temp]->setIcon(QIcon(":/Icon/item5Bg_cover.png"));
                charTemp[temp]->setIconSize(QSize(101,122));
                connect(charTemp[temp],&QPushButton::clicked,bg[temp],&QPushButton::clicked);
                connect(charTemp[temp],&QPushButton::pressed,bg[temp],&QPushButton::pressed);
                connect(charTemp[temp],&QPushButton::released,bg[temp],&QPushButton::released);
                charTemp[temp]->show();

                charText[temp]=new QLabel(ui->character);
                charText[temp]->setGeometry(105*j+3,10+40*k+130*(temp1+i)+96,96,21);
                Data::ft.setPointSize(12);
                charText[temp]->setFont(Data::ft);
                charText[temp]->setAlignment(Qt::AlignCenter);
                charText[temp]->setStyleSheet("color:rgb(73,83,102)");
                charText[temp]->setText(NameChinese);
                charText[temp]->show();
            }
        }
    }

    temp1+=n[3];

    element[4]->move(10,10+40*k+130*temp1);
    element[4]->setStyleSheet("border-image: url(:/Icon/Cryo.png)");
    element[4]->show();
    elementText[4]->move(45,10+40*k+130*temp1);
    elementText[4]->setStyleSheet("color:rgb(122,242,242)");
    elementText[4]->setText("冰元素");
    elementText[4]->show();

    k++;
    if(n[4]!=0)
    {
        for (i=0; i < n[4]; i++)
        {
            for (int j = 0; j < 4 && i * 4 + j< Data::CharAmount[5]; j++)
            {
                temp=Data::CharAmount[1]+Data::CharAmount[2]+Data::CharAmount[3]+Data::CharAmount[4]+i * 4 + j;
                bg[temp]=new QPushButton(ui->character);
                bg[temp]->setGeometry(105*j,10+40*k+130*(temp1+i),101,122);
                if(Data::Char[temp][0]->Get_Star()==4) bg[temp]->setIcon(QIcon(":/Icon/item4Bg.png"));
                else if(Data::Char[temp][0]->Get_Star()==5) bg[temp]->setIcon(QIcon(":/Icon/item5Bg.png"));
                bg[temp]->setIconSize(QSize(101,122));
                connect(bg[temp],&QPushButton::clicked,bg[temp],[=](){changeBtnCli(bg[temp], j, i, temp);});
                connect(bg[temp],&QPushButton::pressed,bg[temp],[=](){changeBtnPre(bg[temp], j, i, temp, temp1, k);});
                connect(bg[temp],&QPushButton::released,bg[temp],[=](){changeBtnRea(bg[temp], j, i, temp, temp1, k);});
                bg[temp]->show();

                Name=Data::Char[temp][0]->Get_Name();
                NameChinese=Data::Char[temp][0]->Get_NameChinese();

                charIcon[temp]=new QLabel(ui->character);
                charIcon[temp]->setGeometry(105*j+3,10+40*k+130*(temp1+i)+3,93,93);
                charIcon[temp]->setStyleSheet("background-color: transparent;""border-image: url(:/Character/Icon/"+Name+"_icon.png);");
                charIcon[temp]->show();

                charElement[temp]=new QLabel(ui->character);
                charElement[temp]->setGeometry(105*j+3,10+40*k+130*(temp1+i)+3,30,30);
                charElement[temp]->setStyleSheet("background-color: transparent;""border-image: url(:/Icon/Cryo.png);");
                charElement[temp]->show();

                charTemp[temp]=new QPushButton(ui->character);
                charTemp[temp]->setGeometry(105*j,10+40*k+130*(temp1+i),101,122);
                if(Data::Char[temp][0]->Get_Star()==4) charTemp[temp]->setIcon(QIcon(":/Icon/item4Bg_cover.png"));
                else if(Data::Char[temp][0]->Get_Star()==5) charTemp[temp]->setIcon(QIcon(":/Icon/item5Bg_cover.png"));
                charTemp[temp]->setIconSize(QSize(101,122));
                connect(charTemp[temp],&QPushButton::clicked,bg[temp],&QPushButton::clicked);
                connect(charTemp[temp],&QPushButton::pressed,bg[temp],&QPushButton::pressed);
                connect(charTemp[temp],&QPushButton::released,bg[temp],&QPushButton::released);
                charTemp[temp]->show();

                charText[temp]=new QLabel(ui->character);
                charText[temp]->setGeometry(105*j+3,10+40*k+130*(temp1+i)+96,96,21);
                Data::ft.setPointSize(12);
                charText[temp]->setFont(Data::ft);
                charText[temp]->setAlignment(Qt::AlignCenter);
                charText[temp]->setStyleSheet("color:rgb(73,83,102)");
                charText[temp]->setText(NameChinese);
                charText[temp]->show();
            }
        }
    }

    temp1+=n[4];

    element[5]->move(10,10+40*k+130*temp1);
    element[5]->setStyleSheet("border-image: url(:/Icon/Geo.png)");
    element[5]->show();
    elementText[5]->move(45,10+40*k+130*temp1);
    elementText[5]->setStyleSheet("color:rgb(255,176,13)");
    elementText[5]->setText("岩元素");
    elementText[5]->show();

    k++;
    if(n[5]!=0)
    {
        for (i=0; i < n[5]; i++)
        {
            for (int j = 0; j < 4 && i * 4 + j< Data::CharAmount[6]; j++)
            {
                temp=Data::CharAmount[1]+Data::CharAmount[2]+Data::CharAmount[3]+Data::CharAmount[4]+Data::CharAmount[5]+i * 4 + j;
                bg[temp]=new QPushButton(ui->character);
                bg[temp]->setGeometry(105*j,10+40*k+130*(temp1+i),101,122);
                if(Data::Char[temp][0]->Get_Star()==4) bg[temp]->setIcon(QIcon(":/Icon/item4Bg.png"));
                else if(Data::Char[temp][0]->Get_Star()==5) bg[temp]->setIcon(QIcon(":/Icon/item5Bg.png"));
                bg[temp]->setIconSize(QSize(101,122));
                connect(bg[temp],&QPushButton::clicked,bg[temp],[=](){changeBtnCli(bg[temp], j, i, temp);});
                connect(bg[temp],&QPushButton::pressed,bg[temp],[=](){changeBtnPre(bg[temp], j, i, temp, temp1, k);});
                connect(bg[temp],&QPushButton::released,bg[temp],[=](){changeBtnRea(bg[temp], j, i, temp, temp1, k);});
                bg[temp]->show();

                Name=Data::Char[temp][0]->Get_Name();
                NameChinese=Data::Char[temp][0]->Get_NameChinese();

                charIcon[temp]=new QLabel(ui->character);
                charIcon[temp]->setGeometry(105*j+3,10+40*k+130*(temp1+i)+3,93,93);
                charIcon[temp]->setStyleSheet("background-color: transparent;""border-image: url(:/Character/Icon/"+Name+"_icon.png);");
                charIcon[temp]->show();

                charElement[temp]=new QLabel(ui->character);
                charElement[temp]->setGeometry(105*j+3,10+40*k+130*(temp1+i)+3,30,30);
                charElement[temp]->setStyleSheet("background-color: transparent;""border-image: url(:/Icon/Geo.png);");
                charElement[temp]->show();

                charTemp[temp]=new QPushButton(ui->character);
                charTemp[temp]->setGeometry(105*j,10+40*k+130*(temp1+i),101,122);
                if(Data::Char[temp][0]->Get_Star()==4) charTemp[temp]->setIcon(QIcon(":/Icon/item4Bg_cover.png"));
                else if(Data::Char[temp][0]->Get_Star()==5) charTemp[temp]->setIcon(QIcon(":/Icon/item5Bg_cover.png"));
                charTemp[temp]->setIconSize(QSize(101,122));
                connect(charTemp[temp],&QPushButton::clicked,bg[temp],&QPushButton::clicked);
                connect(charTemp[temp],&QPushButton::pressed,bg[temp],&QPushButton::pressed);
                connect(charTemp[temp],&QPushButton::released,bg[temp],&QPushButton::released);
                charTemp[temp]->show();

                charText[temp]=new QLabel(ui->character);
                charText[temp]->setGeometry(105*j+3,10+40*k+130*(temp1+i)+96,96,21);
                Data::ft.setPointSize(12);
                charText[temp]->setFont(Data::ft);
                charText[temp]->setAlignment(Qt::AlignCenter);
                charText[temp]->setStyleSheet("color:rgb(73,83,102)");
                charText[temp]->setText(NameChinese);
                charText[temp]->show();
            }
        }
    }

    temp1+=n[5];

    element[6]->move(10,10+40*k+130*temp1);
    element[6]->setStyleSheet("border-image: url(:/Icon/Dendro.png)");
    element[6]->show();
    elementText[6]->move(45,10+40*k+130*temp1);
    elementText[6]->setStyleSheet("color:rgb(155,229,61)");
    elementText[6]->setText("草元素");
    elementText[6]->show();

    k++;
    if(n[6]!=0)
    {
        for (i=0; i < n[6]; i++)
        {
            for (int j = 0; j < 4 && i * 4 + j< Data::CharAmount[7]; j++)
            {
                temp=Data::CharAmount[1]+Data::CharAmount[2]+Data::CharAmount[3]+Data::CharAmount[4]+Data::CharAmount[5]+Data::CharAmount[6]+i * 4 + j;
                bg[temp]=new QPushButton(ui->character);
                bg[temp]->setGeometry(105*j,10+40*k+130*(temp1+i),101,122);
                if(Data::Char[temp][0]->Get_Star()==4) bg[temp]->setIcon(QIcon(":/Icon/item4Bg.png"));
                else if(Data::Char[temp][0]->Get_Star()==5) bg[temp]->setIcon(QIcon(":/Icon/item5Bg.png"));
                bg[temp]->setIconSize(QSize(101,122));
                connect(bg[temp],&QPushButton::clicked,bg[temp],[=](){changeBtnCli(bg[temp], j, i, temp);});
                connect(bg[temp],&QPushButton::pressed,bg[temp],[=](){changeBtnPre(bg[temp], j, i, temp, temp1, k);});
                connect(bg[temp],&QPushButton::released,bg[temp],[=](){changeBtnRea(bg[temp], j, i, temp, temp1, k);});
                bg[temp]->show();

                Name=Data::Char[temp][0]->Get_Name();
                NameChinese=Data::Char[temp][0]->Get_NameChinese();

                charIcon[temp]=new QLabel(ui->character);
                charIcon[temp]->setGeometry(105*j+3,10+40*k+130*(temp1+i)+3,93,93);
                charIcon[temp]->setStyleSheet("background-color: transparent;""border-image: url(:/Character/Icon/"+Name+"_icon.png);");
                charIcon[temp]->show();

                charElement[temp]=new QLabel(ui->character);
                charElement[temp]->setGeometry(105*j+3,10+40*k+130*(temp1+i)+3,30,30);
                charElement[temp]->setStyleSheet("background-color: transparent;""border-image: url(:/Icon/Dendro.png);");
                charElement[temp]->show();

                charTemp[temp]=new QPushButton(ui->character);
                charTemp[temp]->setGeometry(105*j,10+40*k+130*(temp1+i),101,122);
                if(Data::Char[temp][0]->Get_Star()==4) charTemp[temp]->setIcon(QIcon(":/Icon/item4Bg_cover.png"));
                else if(Data::Char[temp][0]->Get_Star()==5) charTemp[temp]->setIcon(QIcon(":/Icon/item5Bg_cover.png"));
                charTemp[temp]->setIconSize(QSize(101,122));
                connect(charTemp[temp],&QPushButton::clicked,bg[temp],&QPushButton::clicked);
                connect(charTemp[temp],&QPushButton::pressed,bg[temp],&QPushButton::pressed);
                connect(charTemp[temp],&QPushButton::released,bg[temp],&QPushButton::released);
                charTemp[temp]->show();

                charText[temp]=new QLabel(ui->character);
                charText[temp]->setGeometry(105*j+3,10+40*k+130*(temp1+i)+96,96,21);
                Data::ft.setPointSize(12);
                charText[temp]->setFont(Data::ft);
                charText[temp]->setAlignment(Qt::AlignCenter);
                charText[temp]->setStyleSheet("color:rgb(73,83,102)");
                charText[temp]->setText(NameChinese);
                charText[temp]->show();
            }
        }
    }

    temp1+=n[6];

    elementText[7]->move(10,10+40*k+130*temp1);
    elementText[7]->setStyleSheet("color:rgb(59,66,85)");
    elementText[7]->setText("旅行者");
    elementText[7]->show();

    k++;
    if(n[7]!=0)
    {
        for (i=0; i < n[7]; i++)
        {
            for (int j = 0; j < 4 && i * 4 + j< Data::CharAmount[8]; j++)
            {
                temp=Data::CharAmount[1]+Data::CharAmount[2]+Data::CharAmount[3]+Data::CharAmount[4]+Data::CharAmount[5]+Data::CharAmount[6]+Data::CharAmount[7]+i * 4 + j;
                bg[temp]=new QPushButton(ui->character);
                bg[temp]->setGeometry(105*j,10+40*k+130*(temp1+i),101,122);
                if(Data::Char[temp][0]->Get_Star()==4) bg[temp]->setIcon(QIcon(":/Icon/item4Bg.png"));
                else if(Data::Char[temp][0]->Get_Star()==5) bg[temp]->setIcon(QIcon(":/Icon/item5Bg.png"));
                bg[temp]->setIconSize(QSize(101,122));
                connect(bg[temp],&QPushButton::clicked,bg[temp],[=](){changeBtnCli(bg[temp], j, i, temp);});
                connect(bg[temp],&QPushButton::pressed,bg[temp],[=](){changeBtnPre(bg[temp], j, i, temp, temp1, k);});
                connect(bg[temp],&QPushButton::released,bg[temp],[=](){changeBtnRea(bg[temp], j, i, temp, temp1, k);});
                bg[temp]->show();

                Name=Data::Char[temp][0]->Get_Name();
                NameChinese=Data::Char[temp][0]->Get_NameChinese();

                charIcon[temp]=new QLabel(ui->character);
                charIcon[temp]->setGeometry(105*j+3,10+40*k+130*(temp1+i)+3,93,93);
                charIcon[temp]->setStyleSheet("background-color: transparent;""border-image: url(:/Character/Icon/"+Name+"_icon.png);");
                charIcon[temp]->show();

                charTemp[temp]=new QPushButton(ui->character);
                charTemp[temp]->setGeometry(105*j,10+40*k+130*(temp1+i),101,122);
                if(Data::Char[temp][0]->Get_Star()==4) charTemp[temp]->setIcon(QIcon(":/Icon/item4Bg_cover.png"));
                else if(Data::Char[temp][0]->Get_Star()==5) charTemp[temp]->setIcon(QIcon(":/Icon/item5Bg_cover.png"));
                charTemp[temp]->setIconSize(QSize(101,122));
                connect(charTemp[temp],&QPushButton::clicked,bg[temp],&QPushButton::clicked);
                connect(charTemp[temp],&QPushButton::pressed,bg[temp],&QPushButton::pressed);
                connect(charTemp[temp],&QPushButton::released,bg[temp],&QPushButton::released);
                charTemp[temp]->show();

                charText[temp]=new QLabel(ui->character);
                charText[temp]->setGeometry(105*j+3,10+40*k+130*(temp1+i)+96,96,21);
                Data::ft.setPointSize(12);
                charText[temp]->setFont(Data::ft);
                charText[temp]->setAlignment(Qt::AlignCenter);
                charText[temp]->setStyleSheet("color:rgb(73,83,102)");
                charText[temp]->setText("空/荧");
                charText[temp]->show();
            }
        }
    }
    ui->comboBox->addItem("请选择人物等级");
    ui->comboBox->addItem("80级未突破");
    ui->comboBox->addItem("80级已突破");
    ui->comboBox->addItem("90级");
}

CharacterSelecte::~CharacterSelecte()
{
    delete ui;
    for(int i=0;i<7;i++)
    {
        element[i]->close();
        delete[] element[i];
        elementText[i]->close();
        delete[] elementText[i];
    }
    elementText[7]->close();
    delete[] elementText[7];

    for(int i=0;i<Data::CharAmount[0];i++)
    {
        bg[i]->close();
        delete[] bg[i];
        charIcon[i]->close();
        delete[] charIcon[i];
        charTemp[i]->close();
        delete[] charTemp[i];
        charText[i]->close();
        delete[] charText[i];
        if(i!=Data::CharAmount[0]-1)
        {
            charElement[i]->close();
            delete[] charElement[i];
        }
    }
}

void CharacterSelecte::on_Back_clicked()
{
    this->close();
}

void CharacterSelecte::changeBtnCli(QPushButton* btn, int j, int i, int Num)
{
    Data::selectedChar=Num;
    QPixmap PixBgChar=QPixmap(":/Character/Avatar_high/"+Data::Char[Num][0]->Get_Name()+".png");
    QSize PixBgCharSize;
    if(PixBgChar.size().height()>=1200)  PixBgCharSize= PixBgChar.size()*0.41;
    else PixBgCharSize = PixBgChar.size()*0.48;//缩小一下
    ui->bgChar->setGeometry(960-PixBgCharSize.width(),540-PixBgCharSize.height(),PixBgCharSize.width(),PixBgCharSize.height());
    ui->bgChar->setScaledContents(true);
    ui->bgChar->setPixmap(PixBgChar);
    ui->comboBox->setCurrentIndex(0);
}

void CharacterSelecte::changeBtnPre(QPushButton* btn, int j, int i, int temp,  int temp1, int temp2)
{
    btn->setGeometry(105*j,10+40*temp2+130*(temp1+i),101,122);
    if(Data::Char[temp][0]->Get_Star()==4) btn->setIcon(QIcon(":/Icon/item4Bg_selected.png"));
    else if(Data::Char[temp][0]->Get_Star()==5) btn->setIcon(QIcon(":/Icon/item5Bg_selected.png"));
    btn->setIconSize(QSize(101,122));
}

void CharacterSelecte::changeBtnRea(QPushButton* btn, int j, int i, int temp,  int temp1, int temp2)
{
    btn->setGeometry(105*j,10+40*temp2+130*(temp1+i),101,122);
    if(Data::Char[temp][0]->Get_Star()==4) btn->setIcon(QIcon(":/Icon/item4Bg.png"));
    else if(Data::Char[temp][0]->Get_Star()==5) btn->setIcon(QIcon(":/Icon/item5Bg.png"));
    btn->setIconSize(QSize(101,122));
}


void CharacterSelecte::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1!="请选择人物等级")
    {
        if(Data::selectedChar>-1)
        {
            if(arg1=="80级未突破")
            {
                Data::charLevel=0;
                ui->baseLife->setText("·基础生命值："+QString::number(Data::Char[Data::selectedChar][0]->Get_BaseLife()));
                ui->baseAttack->setText("·基础攻击力："+QString::number(Data::Char[Data::selectedChar][0]->Get_BaseAttack()));
                ui->baseDefend->setText("·基础防御力："+QString::number(Data::Char[Data::selectedChar][0]->Get_BaseDefend()));
                if(Data::Char[Data::selectedChar][0]->Get_BaseAttributeValue()>1)
                {
                    ui->attribute->setText("·"+Data::Char[Data::selectedChar][0]->Get_BaseAttributeChinese()+"：+"+QString::number(Data::Char[Data::selectedChar][0]->Get_BaseAttributeValue()));
                }
                else ui->attribute->setText("·"+Data::Char[Data::selectedChar][0]->Get_BaseAttributeChinese()+"：+"+QString::number(Data::Char[Data::selectedChar][0]->Get_BaseAttributeValue()*100)+"%");
                ui->des->setText(Data::Char[Data::selectedChar][0]->Get_Description());
                ui->des->adjustSize();
                ui->level->adjustSize();
            }
            else if(arg1=="80级已突破")
            {
                Data::charLevel=1;
                ui->baseLife->setText("·基础生命值："+QString::number(Data::Char[Data::selectedChar][1]->Get_BaseLife()));
                ui->baseAttack->setText("·基础攻击力："+QString::number(Data::Char[Data::selectedChar][1]->Get_BaseAttack()));
                ui->baseDefend->setText("·基础防御力："+QString::number(Data::Char[Data::selectedChar][1]->Get_BaseDefend()));
                if(Data::Char[Data::selectedChar][1]->Get_BaseAttributeValue()>1)
                {
                    ui->attribute->setText("·"+Data::Char[Data::selectedChar][1]->Get_BaseAttributeChinese()+"：+"+QString::number(Data::Char[Data::selectedChar][1]->Get_BaseAttributeValue()));
                }
                else ui->attribute->setText("·"+Data::Char[Data::selectedChar][1]->Get_BaseAttributeChinese()+"：+"+QString::number(Data::Char[Data::selectedChar][1]->Get_BaseAttributeValue()*100)+"%");
                ui->des->setText(Data::Char[Data::selectedChar][1]->Get_Description());
                ui->des->adjustSize();
                ui->level->adjustSize();
            }
            else if(arg1=="90级")
            {
                Data::charLevel=2;
                ui->baseLife->setText("·基础生命值："+QString::number(Data::Char[Data::selectedChar][2]->Get_BaseLife()));
                ui->baseAttack->setText("·基础攻击力："+QString::number(Data::Char[Data::selectedChar][2]->Get_BaseAttack()));
                ui->baseDefend->setText("·基础防御力："+QString::number(Data::Char[Data::selectedChar][2]->Get_BaseDefend()));
                if(Data::Char[Data::selectedChar][2]->Get_BaseAttributeValue()>1)
                {
                    ui->attribute->setText("·"+Data::Char[Data::selectedChar][2]->Get_BaseAttributeChinese()+"：+"+QString::number(Data::Char[Data::selectedChar][2]->Get_BaseAttributeValue()));
                }
                else ui->attribute->setText("·"+Data::Char[Data::selectedChar][2]->Get_BaseAttributeChinese()+"：+"+QString::number(Data::Char[Data::selectedChar][2]->Get_BaseAttributeValue()*100)+"%");
                ui->des->setText(Data::Char[Data::selectedChar][2]->Get_Description());
                ui->des->adjustSize();
                ui->level->adjustSize();
            }
        }
        else QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","当前尚未选择人物！");
    }
    else
    {
        Data::charLevel=-1;
        ui->baseLife->clear();
        ui->baseAttack->clear();
        ui->baseDefend->clear();
        ui->attribute->clear();
        ui->des->clear();
        ui->des->adjustSize();
        ui->level->adjustSize();
    }
}


void CharacterSelecte::on_confirm_clicked()
{
    if(Data::selectedChar!=-1&&Data::charLevel!=-1)
    {
        this->close();
    }
    else QMessageBox::StandardButton result=QMessageBox::warning(this, "警告","当前尚未选择完毕！");
}

