#include "data.h"

Data::Data()
{

}

QPixmap Data::setBackgroundChar()
{
    srand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int tempChar =rand()%(Data::CharAmount[0]);
    QString tempCharName=Data::Char[tempChar][0]->Get_Name();
    QPixmap PixBgCharTemp=QPixmap(":/Character/Avatar_high/"+tempCharName+".png");

    QSize PixBgCharSize = PixBgCharTemp.size()*0.5;//缩小一下
    PixBgCharTemp.scaled(PixBgCharSize,Qt::KeepAspectRatioByExpanding);

    //设置背景图片透明度
    QPixmap temp(PixBgCharTemp.size());
    temp.fill(Qt::transparent);

    QPainter p1(&temp);
    p1.setCompositionMode(QPainter::CompositionMode_Source);
    p1.drawPixmap(0, 0, PixBgCharTemp);
    p1.setCompositionMode(QPainter::CompositionMode_DestinationIn);

    //根据QColor中第四个参数设置透明度，取值范围是0～255
    p1.fillRect(temp.rect(), QColor(0, 0, 0, 127));
    p1.end();
    PixBgCharTemp = temp;

    return PixBgCharTemp;
}

//void Data::searchPosition()
//{
//    if(Data::PositionAmount!=NULL)
//    {
//        for(int i=0;i<5;i++)//先清空
//        {
//            delete []Data::PositionAmount[i];
//        }
//        delete[]Data::PositionAmount;
//    }

//    int a=0,b=0,c=0,d=0,e=0;
//    Data::PositionAmount=new int*[5];
//    for(int i=0;i<Data::ArtAmount;i++)
//    {
//        if(Data::Art[i]->Get_position()=="flower") a++;
//        if(Data::Art[i]->Get_position()=="feather") b++;
//        if(Data::Art[i]->Get_position()=="sand") c++;
//        if(Data::Art[i]->Get_position()=="cup") d++;
//        if(Data::Art[i]->Get_position()=="head") e++;
//    }
//    Data::PositionAmount[0]=new int[a+1];
//    Data::PositionAmount[0][0]=a;
//    Data::PositionAmount[1]=new int[b+1];
//    Data::PositionAmount[1][0]=b;
//    Data::PositionAmount[2]=new int[c+1];
//    Data::PositionAmount[2][0]=c;
//    Data::PositionAmount[3]=new int[d+1];
//    Data::PositionAmount[3][0]=d;
//    Data::PositionAmount[4]=new int[e+1];
//    Data::PositionAmount[4][0]=e;
//    a=1;b=1;c=1;d=1;e=1;

//    for(int i=0;i<Data::ArtAmount;i++)
//    {
//        if(Data::Art[i]->Get_position()=="flower")
//        {
//            Data::PositionAmount[0][a]=Data::Art[i]->Get_id();
//            a++;
//        }
//        if(Data::Art[i]->Get_position()=="feather")
//        {
//            Data::PositionAmount[1][b]=Data::Art[i]->Get_id();
//            b++;
//        }
//        if(Data::Art[i]->Get_position()=="sand")
//        {
//            Data::PositionAmount[2][c]=Data::Art[i]->Get_id();
//            c++;
//        }
//        if(Data::Art[i]->Get_position()=="cup")
//        {
//            Data::PositionAmount[3][d]=Data::Art[i]->Get_id();
//            d++;
//        }
//        if(Data::Art[i]->Get_position()=="head")
//        {
//            Data::PositionAmount[4][e]=Data::Art[i]->Get_id();
//            e++;
//        }
//    }
//}



void Data::searchSet()
{
    QResource::registerResource(QDir::currentPath() + "/Resources.rcc");
    QJsonParseError err_rpt;
    QFile fileArt(":/Data/Artifact.json");
    fileArt.open(QIODevice::ReadOnly);
    QJsonDocument  root_Art = QJsonDocument::fromJson(fileArt.readAll(), &err_rpt);
    QJsonObject root_ArtObj = root_Art.object();
    QJsonValue artifact_Value = root_ArtObj.value("Artifact");
    QJsonArray array=artifact_Value.toArray();//转化为QJsonArray
    int size =array.size();
    if(Data::SetAmount!=NULL)
    {
        int temp=Data::SetAmount[0][0];
        for(int i=0;i<=temp;i++)
        {
            delete []Data::SetAmount[i];
        }
        delete []Data::SetAmount;
    }

    int* temp=new int[size+1];//用来存放每套的圣遗物数量，0为仓库中有的套装总数，后面分别对应总的每个套装有的圣遗物数量
    for(int i=0;i<=size;i++)//初始化
    {
        temp[i]=0;
    }
    //遍历，获取每套圣遗物的数量
    for(int j=0;j<Data::ArtAmount;j++)
    {
        for(int i=1;i<=size;i++)
        {
            QJsonObject artifact_Obj = array.at(i-1).toObject();//temp[i]对应json中的[i-1]
            if(Data::Art[j]->Get_setName()==artifact_Obj.value("setName").toString())
            {
                temp[i]++;
            }
        }
    }
    for(int i=1;i<=size;i++)
    {
        if(temp[i]!=0) temp[0]++;
    }
    Data::SetAmount=new int*[temp[0]+1];
    Data::SetAmount[0]=new int[1];
    Data::SetAmount[0][0]=temp[0];
    int a=1;
    for(int i=1;i<=size;i++)
    {
        if(temp[i]!=0)
        {
            Data::SetAmount[a]=new int[temp[i]+2];
            Data::SetAmount[a][0]=temp[i];
            Data::SetAmount[a][1]=i-1;
            int k=2;
            for(int j=0;j<Data::ArtAmount;j++)
            {
                QJsonObject artifact_Obj = array.at(i-1).toObject();
                if(Data::Art[j]->Get_setName()==artifact_Obj.value("setName").toString())
                {
                    Data::SetAmount[a][k]=Data::Art[j]->Get_id();
                    k++;
                }
            }
            a++;
        }
    }
}

bool Data::matchCharWeap()
{
    if(Data::selectedChar>-1&&Data::selectedWeap>-1)
    {
        if(Data::Char[Data::selectedChar][0]->Get_WeaponType()==Data::Weap[Data::selectedWeap][0]->Get_WeaponType()) return true;
        else return false;
    }
}

int Data::ArtAmount=0;
int* Data::PositionAmount=NULL;
int** Data::SetAmount=NULL;
int Data::flag=0;
int Data::CharAmount[9]={ 0,0,0,0,0,0,0,0,1 };
int Data::WeapAmount[6]={ 0,0,0,0,0,0 };
int Data::Favorite_size=0;
int Data::favTemp=-1;
int Data::favFlag=0;
Artifact* Data::Art[1500]={};
Character** Data::Char[200]={};
Weapon** Data::Weap[200]={};
FavoriteOri* Data::Fav[200]={};
QFile Data::fileArt=QFile("");
QFile Data::fileChar=QFile("");
QFile Data::fileWeap=QFile("");
QString Data::fileName="";
QFont Data::ft=QFont("汉仪文黑-85W");
int Data::selectedChar=-1;
int Data::charLevel=-1;
int Data::selectedWeap=-1;
int Data::weapLevel=-1;
int Data::selectedFav=-1;
