#pragma once
#include <string>
#include <QString>

//using namespace std;

class Weapon
{
public:
	Weapon();//默认构造函数
    Weapon(QString, QString, QString, int, QString, double, double, QString, QString, QString);//构造函数
    QString Get_WeaponType();
    QString Get_WeaponTypeChinese();
    QString Get_Name();
    QString Get_NameChinese();
	int Get_Star();
    QString Get_BaseAttribute();
    QString Get_BaseAttributeChinese();
	double Get_BaseAttack();
	double Get_BaseAttributeValue();
    QString Get_SpecialAbilityName();
    QString Get_SpecialAbility();
    QString Get_Description();
protected:
    QString Name, NameChinese, BaseAttribute, WeaponType, SpecialAbilityName, SpecialAbility, Description;
	int Star;
	double BaseAttack, BaseAttributeValue;
};

