#include "Weapon.h"

Weapon::Weapon()
{
	Star = 0;
	BaseAttack = 0;
	BaseAttributeValue = 0;
}

Weapon::Weapon(QString wt, QString na, QString nac, int st, QString bat, double ba, double bav, QString sn, QString s, QString des)
{
	WeaponType = wt;
	Name = na;
	NameChinese = nac;
	Star = st;
	BaseAttribute = bat;
	BaseAttack = ba;
	BaseAttributeValue = bav;
    SpecialAbilityName=sn;
    SpecialAbility=s;
    Description=des;
}

QString Weapon::Get_WeaponType()
{
	return WeaponType;
}

QString Weapon::Get_WeaponTypeChinese()
{
	if (WeaponType == "Sword") return "单手剑";
	if (WeaponType == "Claymore") return "双手剑";
	if (WeaponType == "Bow") return "弓";
	if (WeaponType == "Catalyst") return "法器";
	if (WeaponType == "Polearm") return "长柄武器";
}

QString Weapon::Get_Name()
{
	return Name;
}

QString Weapon::Get_NameChinese()
{
	return NameChinese;
}

int Weapon::Get_Star()
{
	return Star;
}

QString Weapon::Get_BaseAttribute()
{
	return BaseAttribute;
}

QString Weapon::Get_BaseAttributeChinese()
{
	if (BaseAttribute == "lifePercentage") return "生命值";
	if (BaseAttribute == "defendPercentage") return "防御力";
	if (BaseAttribute == "attackPercentage") return "攻击力";
	if (BaseAttribute == "elementalMastery") return "元素精通";
	if (BaseAttribute == "recharge") return "元素充能效率";
	if (BaseAttribute == "critical") return "暴击率";
	if (BaseAttribute == "criticalDamage") return "暴击伤害";
	if (BaseAttribute == "cureEffect") return "治疗加成";
	if (BaseAttribute == "physicalBonus") return "物理伤害加成";
}

double Weapon::Get_BaseAttack()
{
	return BaseAttack;
}

double Weapon::Get_BaseAttributeValue()
{
	return BaseAttributeValue;
}

QString Weapon::Get_Description()
{
    return Description;
}

QString Weapon::Get_SpecialAbilityName()
{
    return SpecialAbilityName;
}

QString Weapon::Get_SpecialAbility()
{
    return SpecialAbility;
}
