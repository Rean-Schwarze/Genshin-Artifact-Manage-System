#include "Character.h"

Character::Character()
{
	Star = 0;
	BaseAttack = 0;
	BaseDefend = 0;
	BaseLife = 0;
	BaseAttributeValue = 0;
}

Character::Character(QString na, QString nac, QString el, int st, QString wt, QString bat, double bl, double bd, double ba, double bav, QString des)
{
	Name = na;
	NameChinese = nac;
	Element = el;
	Star = st;
	WeaponType = wt;
	BaseAttribute = bat;
	BaseLife = bl;
	BaseDefend = bd;
	BaseAttack = ba;
	BaseAttributeValue = bav;
    Description=des;
}

QString Character::Get_Name()
{
	return Name;
}

QString Character::Get_NameChinese()
{
	return NameChinese;
}

QString Character::Get_Element()
{
	return Element;
}

QString Character::Get_ElementChinese()
{
	if (Element == "Anemo") return "风";
	if (Element == "Pryo") return "火";
	if (Element == "Hydro") return "水";
	if (Element == "Electro") return "雷";
	if (Element == "Cryo") return "冰";
	if (Element == "Dendro") return "草";
	if (Element == "Geo") return "岩";
	if (Element == "All") return "全";
}

int Character::Get_Star()
{
	return Star;
}

QString Character::Get_WeaponType()
{
	return WeaponType;
}

QString Character::Get_WeaponTypeChinese()
{
	if (WeaponType == "Sword") return "单手剑";
	if (WeaponType == "Claymore") return "双手剑";
	if (WeaponType == "Bow") return "弓";
	if (WeaponType == "Catalyst") return "法器";
	if (WeaponType == "Polearm") return "长柄武器";
}

QString Character::Get_BaseAttribute()
{
	return BaseAttribute;
}

QString Character::Get_BaseAttributeChinese()
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
	if (BaseAttribute == "fireBonus") return "火元素伤害加成";
	if (BaseAttribute == "waterBonus") return "水元素伤害加成";
    if (BaseAttribute == "dendroBounus") return "草元素伤害加成";
	if (BaseAttribute == "thunderBonus") return "雷元素伤害加成";
    if (BaseAttribute == "windBonus") return "风元素伤害加成";
	if (BaseAttribute == "iceBonus") return "冰元素伤害加成";
	if (BaseAttribute == "rockBonus") return "岩元素伤害加成";
}

double Character::Get_BaseLife()
{
	return BaseLife;
}

double Character::Get_BaseDefend()
{
	return BaseDefend;
}

double Character::Get_BaseAttack()
{
	return BaseAttack;
}

double Character::Get_BaseAttributeValue()
{
	return BaseAttributeValue;
}

QString Character::Get_Description()
{
    return Description;
}
