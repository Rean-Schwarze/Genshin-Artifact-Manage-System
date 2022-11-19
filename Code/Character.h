#pragma once
#include <string>
#include <QString>

//using namespace std;

class Character
{
public:
	Character();//默认构造函数
    Character(QString, QString, QString, int, QString, QString, double, double, double, double, QString);//构造函数
    QString Get_Name();
    QString Get_NameChinese();
    QString Get_Element();
    QString Get_ElementChinese();
	int Get_Star();
    QString Get_WeaponType();
    QString Get_WeaponTypeChinese();
    QString Get_BaseAttribute();
    QString Get_BaseAttributeChinese();
	double Get_BaseLife();
	double Get_BaseDefend();
	double Get_BaseAttack();
	double Get_BaseAttributeValue();
    QString Get_Description();
protected:
    QString Name, NameChinese, Element, WeaponType, BaseAttribute, Description;
	int Star;
	double BaseLife, BaseDefend, BaseAttack, BaseAttributeValue;
};

