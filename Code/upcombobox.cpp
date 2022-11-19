#include "upcombobox.h"

upComboBox::upComboBox(QWidget *parent, int flag)
    : QComboBox(parent)
{
    setView(new QListView);
    if(flag==1) qss.setFileName(":/Data/setFilter.qss");
    else if (flag==2) qss.setFileName(":/Data/setFilter2.qss");
    qss.open(QFile::ReadOnly);
    setStyleSheet(qss.readAll());
    qss.close();
//    Data::ft.setPointSize(12);
//    setFont(Data::ft);
    //setStyleSheet("QComboBox{color:#666666;font: 12pt \"汉仪文黑-85W\";padding: 1px 15px 1px 3px;border:1px solid rgba(228,228,228,1);border-radius:5px 5px 0px 0px;}""QComboBox::drop-down {background-color: transparent;}""QComboBox QAbstractItemView{background:rgba(255,255,255,1);border:1px solid rgba(228,228,228,1);border-radius:0px 0px 5px 5px;outline: 0px;}""QComboBox QAbstractItemView::item{height:36px;color:#666666;padding-left:9px;background-color:#FFFFFF;}""QComboBox QAbstractItemView::item:hover{background-color:#409CE1;color:#ffffff;}""QComboBox QAbstractItemView::item:selected{background-color:#409CE1;color:#ffffff;}");
}

void upComboBox::showPopup()
{
    if(Data::Favorite_size>2||Data::SetAmount[0][0]>4)
    {
        QComboBox::showPopup();
        QWidget *popup = this->findChild<QFrame*>();
        popup->move(popup->x(),popup->y());//x轴不变，y轴向上移动 list的高+combox的高
    }
    else
    {
        QComboBox::showPopup();
        QWidget *popup = this->findChild<QFrame*>();
        popup->move(popup->x(),popup->y()-this->height()-popup->height());//x轴不变，y轴向上移动 list的高+combox的高
    }
}
