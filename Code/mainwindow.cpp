#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);    // 禁止最大化按钮
    ui->setupUi(this);

    QResource::registerResource(QDir::currentPath() + "/Resources.rcc");

    //设置时钟为1s
    clock=this->startTimer(1000);

    //打开预设json
    Data::fileArt.setFileName(":/Data/Artifact.json");
    Data::fileArt.open(QIODevice::ReadOnly);
    Data::fileChar.setFileName(":/Data/Character.json");
    Data::fileChar.open(QIODevice::ReadOnly);
    Data::fileWeap.setFileName(":/Data/Weapon.json");
    Data::fileWeap.open(QIODevice::ReadOnly);

    QJsonParseError err_rpt;
    QJsonDocument  root_Art = QJsonDocument::fromJson(Data::fileArt.readAll(), &err_rpt);
    QJsonObject root_ArtObj = root_Art.object();
    QJsonValue artVersion_Value = root_ArtObj.value("version");
    QString artVersion=artVersion_Value.toString();

    QJsonDocument  root_Char = QJsonDocument::fromJson(Data::fileChar.readAll(), &err_rpt);
    QJsonObject root_CharObj = root_Char.object();
    QJsonValue charVersion_Value = root_CharObj.value("version");
    QString charVersion=charVersion_Value.toString();

    //读取角色数据
    ImportCharacter importchar;
    importchar.Import(Data::Char, Data::CharAmount);

    //读取武器数据
    ImportWeapon importweap;
    importweap.Import(Data::Weap, Data::WeapAmount);

    QJsonDocument  root_Weap = QJsonDocument::fromJson(Data::fileWeap.readAll(), &err_rpt);
    QJsonObject root_WeapObj = root_Weap.object();
    QJsonValue weapVersion_Value = root_WeapObj.value("version");
    QString weapVersion=weapVersion_Value.toString();

    Import import;
    //检测是否有已保存的文件，如有则读取
    QFileInfo savedFile(QDir::currentPath() +"/savedArt.json");
    if(savedFile.isFile())
    {
        import.ImportFromFile(Data::Art, Data::ArtAmount , 0);
    }
    QFileInfo savedFav(QDir::currentPath() +"/favorite.json");
    if(savedFav.isFile())
    {
        readFavorite();
    }

    QString programVersion="1.1";

    //往状态栏添加信息
    QStatusBar *statusbar = this->statusBar();
    statusbar->setStyleSheet("background-color:white");
    Data::ft.setPointSize(12);
    statusLabelRight=new QLabel("主程序版本：v"+programVersion+"   圣遗物版本：v" + artVersion +"   角色版本：v" + charVersion+"   武器版本：v"+weapVersion);
    statusLabelRight->setFont(Data::ft);
    statusbar->addPermanentWidget(statusLabelRight);
    statusLabel=new QLabel("已导入"+QString ::number(Data::ArtAmount) +"件圣遗物");
    statusLabel->setFont(Data::ft);
    statusbar->addWidget(statusLabel);

    //添加背景图片(随机)
    QPixmap PixBgChar=Data::setBackgroundChar();
    QSize PixBgCharSize;
    if(PixBgChar.size().height()>=1200) PixBgCharSize = PixBgChar.size()*0.45;
    else PixBgCharSize = PixBgChar.size()*0.5;//缩小一下
    ui->centralwidget->setGeometry(0,0,960,540);
    QSize CentralWidgetSize=ui->centralwidget->size();
    ui->backgroundchar->setGeometry(((CentralWidgetSize.width()-PixBgCharSize.width())/2),((CentralWidgetSize.height()-PixBgCharSize.height())/2),PixBgCharSize.width(),PixBgCharSize.height());
    ui->backgroundchar->setScaledContents(true);
    ui->backgroundchar->setPixmap(PixBgChar);
    ui->backgroundchar->show();

//    //设置按钮阴影
//    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect ();
//    effect->setBlurRadius(30); //设置模糊半径为50px
//    effect->setColor(RGB(72,72,72)); //设置阴影颜色
//    effect->setOffset(8,8); //设置水平和垂直方向的偏移量都为10
//    ui->Import->setGraphicsEffect(effect);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Import_clicked()
{
    importWidget=new ImportWidget(this);
    importWidget->show();
}

//每1秒刷新一次状态栏信息
void MainWindow::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == clock)
    {
        statusLabel->setText("已导入"+QString ::number(Data::ArtAmount) +"件圣遗物");

        //如果删除/修改了圣遗物，则仓库窗口刷新
        if(Data::flag!=0)
        {
            refreshBP();
            Data::flag=0;
        }
    }
}

void MainWindow::on_Display_clicked()
{
    backpack=new Backpack(this,"全部");
    backpack->show();
}

void MainWindow::refreshBP()
{
    backpack->close();
    delete[] backpack;
    backpack=new Backpack(this,"全部");
    backpack->show();
}

void MainWindow::on_Favorite_clicked()
{
    favorite=new Favorite(this,"全部");
    favorite->show();
}

void MainWindow::readFavorite()//读入操作（有初始化效果）
{
    int f_size;
    QJsonParseError err_rpt;
    QFile fileFav(QDir::currentPath()+"/favorite.json");
    fileFav.open(QIODevice::ReadOnly);
    QJsonDocument  root_Fav = QJsonDocument::fromJson(fileFav.readAll(), &err_rpt);
    QJsonObject root_FavObj = root_Fav.object();
    QJsonValue fav_Value = root_FavObj.value("favorite");
    QJsonArray array=fav_Value.toArray();//转化为QJsonArray
    int size =array.size();

    for (f_size = 0; f_size < size; f_size++)
    {
        Data::Fav[f_size]=new FavoriteOri();
        QJsonObject fav_Obj=array.at(f_size).toObject();
        Data::Fav[f_size]->f_id[0] = fav_Obj.value("flower").toInt();
        Data::Fav[f_size]->f_id[1] = fav_Obj.value("feather").toInt();
        Data::Fav[f_size]->f_id[2] = fav_Obj.value("sand").toInt();
        Data::Fav[f_size]->f_id[3] = fav_Obj.value("cup").toInt();
        Data::Fav[f_size]->f_id[4] = fav_Obj.value("head").toInt();
        Data::Fav[f_size]->name = fav_Obj.value("name").toString();
        Data::Fav[f_size]->id = fav_Obj.value("id").toInt();
        Data::Fav[f_size]->import(Data::Art, Data::ArtAmount);
        Data::Fav[f_size]->confirm();
    }
    Data::Favorite_size=f_size;
    fileFav.close();
}


void MainWindow::on_Rating_clicked()
{
    rating=new Rating(this);
    rating->show();
}

