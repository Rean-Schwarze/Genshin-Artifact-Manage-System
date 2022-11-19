#include "Artifact.h"

//默认构造函数
Artifact::Artifact()
{
	level = 0;
	star = 0;
	MainAttributeValue = 0;
	SubAttributeValue1 = 0;
	SubAttributeValue2 = 0;
	SubAttributeValue3 = 0;
	SubAttributeValue4 = 0;
	id = 0;
}

//构造函数
Artifact::Artifact(QString sn, QString po, QString ma, double mav, QString sa1, double sav1, QString sa2, double sav2, QString sa3, double sav3, QString sa4, double sav4, int le, int st, int ArtAmount)
{
	setName = sn;
	position = po;
	MainAttribute = ma;
	MainAttributeValue = mav;
	SubAttribute1 = sa1;
	SubAttributeValue1 = sav1;
	SubAttribute2 = sa2;
	SubAttributeValue2 = sav2;
	SubAttribute3 = sa3;
	SubAttributeValue3 = sav3;
	SubAttribute4 = sa4;
	SubAttributeValue4 = sav4;
	level = le;
	star = st;
	id = ArtAmount;
    CRIT_score = 0;
        if (sa1 == "critical") {
            CRIT_score += sav1 * 2 * 100;
        }
        if (sa1 == "criticalDamage") {
            CRIT_score += sav1 * 100;
        }
        if (sa2 == "critical") {
            CRIT_score += sav2 * 2 * 100;
        }
        if (sa2 == "criticalDamage") {
            CRIT_score += sav2 * 100;
        }
        if (sa3 == "critical") {
            CRIT_score += sav3 * 2 * 100;
        }
        if (sa3 == "criticalDamage") {
            CRIT_score += sav3 * 100;
        }
        if (sa4 == "critical") {
            CRIT_score += sav4 * 2 * 100;
        }
        if (sa4 == "criticalDamage") {
            CRIT_score += sav4 * 100;
        }
}

//修改数据
void Artifact::modify(QString sn, QString po, QString ma, double mav, QString sa1, double sav1, QString sa2, double sav2, QString sa3, double sav3, QString sa4, double sav4, int le, int st)
{
	setName = sn;
	position = po;
	MainAttribute = ma;
	MainAttributeValue = mav;
	SubAttribute1 = sa1;
	SubAttributeValue1 = sav1;
	SubAttribute2 = sa2;
	SubAttributeValue2 = sav2;
	SubAttribute3 = sa3;
	SubAttributeValue3 = sav3;
	SubAttribute4 = sa4;
	SubAttributeValue4 = sav4;
	level = le;
	star = st;
    CRIT_score = 0;
        if (sa1 == "critical") {
            CRIT_score += sav1 * 2 * 100;
        }
        if (sa1 == "criticalDamage") {
            CRIT_score += sav1 * 100;
        }
        if (sa2 == "critical") {
            CRIT_score += sav2 * 2 * 100;
        }
        if (sa2 == "criticalDamage") {
            CRIT_score += sav2 * 100;
        }
        if (sa3 == "critical") {
            CRIT_score += sav3 * 2 * 100;
        }
        if (sa3 == "criticalDamage") {
            CRIT_score += sav3 * 100;
        }
        if (sa4 == "critical") {
            CRIT_score += sav4 * 2 * 100;
        }
        if (sa4 == "criticalDamage") {
            CRIT_score += sav4 * 100;
        }
}

void Artifact::modid(int i)
{
	id += i;
}

//ostream& operator<<(ostream& output, const Artifact& Art)
//{

	//return output;
//}

//获取各种数据
QString Artifact::Get_setName()
{
	return setName;
}

QString Artifact::Get_Name()
{
    QJsonParseError err_rpt;
    QFile fileArt(":/Data/Artifact.json");
    fileArt.open(QIODevice::ReadOnly);
    QJsonDocument  root_Art = QJsonDocument::fromJson(fileArt.readAll(), &err_rpt);
    QJsonObject root_ArtObj = root_Art.object();
    QJsonValue artifact_Value = root_ArtObj.value("Artifact");
    QJsonArray array=artifact_Value.toArray();//转化为QJsonArray
    int size =array.size();
    QString temp;
    for (int i = 0; i < size; i++)
    {
        QJsonObject artifact_Obj = array.at(i).toObject();
        temp = artifact_Obj.value("setName").toString();
        if (setName == temp)
        {
            return artifact_Obj.value(position).toString();
        }
        temp.clear();
    }
}

QString Artifact::Get_position()
{
	return position;
}

int Artifact::Get_level()
{
	return level;
}

int Artifact::Get_star()
{
	return star;
}

QString Artifact::Get_MainAttribute()
{
	return MainAttribute;
}

QString Artifact::Get_MainAttributeChinese()
{
	if (MainAttribute == "lifeStatic" || MainAttribute == "lifePercentage") return "生命值";
	if (MainAttribute == "defendStatic" || MainAttribute == "defendPercentage") return "防御力";
	if (MainAttribute == "attackStatic" || MainAttribute == "attackPercentage") return "攻击力";
	if (MainAttribute == "elementalMastery") return "元素精通";
	if (MainAttribute == "recharge") return "元素充能效率";
	if (MainAttribute == "critical") return "暴击率";
	if (MainAttribute == "criticalDamage") return "暴击伤害";
	if (MainAttribute == "cureEffect") return "治疗加成";
	if (MainAttribute == "physicalBonus") return "物理伤害加成";
	if (MainAttribute == "fireBonus") return "火元素伤害加成";
	if (MainAttribute == "waterBonus") return "水元素伤害加成";
    if (MainAttribute == "dendroBounus") return "草元素伤害加成";
	if (MainAttribute == "thunderBonus") return "雷元素伤害加成";
	if (MainAttribute == "windBonus") return "风元素伤害加成";
	if (MainAttribute == "iceBonus") return "冰元素伤害加成";
	if (MainAttribute == "rockBonus") return "岩元素伤害加成";
}

double Artifact::Get_MainAttributeValue()
{
	return MainAttributeValue;
}

QString Artifact::Get_SubAttribute1()
{
	return SubAttribute1;
}

QString Artifact::Get_SubAttributeChinese1()
{
	if (SubAttribute1 == "lifeStatic" || SubAttribute1 == "lifePercentage") return "生命值";
	if (SubAttribute1 == "defendStatic" || SubAttribute1 == "defendPercentage") return "防御力";
	if (SubAttribute1 == "attackStatic" || SubAttribute1 == "attackPercentage") return "攻击力";
	if (SubAttribute1 == "elementalMastery") return "元素精通";
	if (SubAttribute1 == "recharge") return "元素充能效率";
	if (SubAttribute1 == "critical") return "暴击率";
	if (SubAttribute1 == "criticalDamage") return "暴击伤害";
}

double Artifact::Get_SubAttributeValue1()
{
	return SubAttributeValue1;
}

QString Artifact::Get_SubAttribute2()
{
	return SubAttribute2;
}

QString Artifact::Get_SubAttributeChinese2()
{
	if (SubAttribute2 == "lifeStatic" || SubAttribute2 == "lifePercentage") return "生命值";
	if (SubAttribute2 == "defendStatic" || SubAttribute2 == "defendPercentage") return "防御力";
	if (SubAttribute2 == "attackStatic" || SubAttribute2 == "attackPercentage") return "攻击力";
	if (SubAttribute2 == "elementalMastery") return "元素精通";
	if (SubAttribute2 == "recharge") return "元素充能效率";
	if (SubAttribute2 == "critical") return "暴击率";
	if (SubAttribute2 == "criticalDamage") return "暴击伤害";
}

double Artifact::Get_SubAttributeValue2()
{
	return SubAttributeValue2;
}

QString Artifact::Get_SubAttribute3()
{
	return SubAttribute3;
}

QString Artifact::Get_SubAttributeChinese3()
{
	if (SubAttribute3 == "lifeStatic" || SubAttribute3 == "lifePercentage") return "生命值";
	if (SubAttribute3 == "defendStatic" || SubAttribute3 == "defendPercentage") return "防御力";
	if (SubAttribute3 == "attackStatic" || SubAttribute3 == "attackPercentage") return "攻击力";
	if (SubAttribute3 == "elementalMastery") return "元素精通";
	if (SubAttribute3 == "recharge") return "元素充能效率";
	if (SubAttribute3 == "critical") return "暴击率";
	if (SubAttribute3 == "criticalDamage") return "暴击伤害";
}

double Artifact::Get_SubAttributeValue3()
{
	return SubAttributeValue3;
}

QString Artifact::Get_SubAttribute4()
{
	return SubAttribute4;
}

QString Artifact::Get_SubAttributeChinese4()
{
	if (SubAttribute4 == "lifeStatic" || SubAttribute4 == "lifePercentage") return "生命值";
	if (SubAttribute4 == "defendStatic" || SubAttribute4 == "defendPercentage") return "防御力";
	if (SubAttribute4 == "attackStatic" || SubAttribute4 == "attackPercentage") return "攻击力";
	if (SubAttribute4 == "elementalMastery") return "元素精通";
	if (SubAttribute4 == "recharge") return "元素充能效率";
	if (SubAttribute4 == "critical") return "暴击率";
	if (SubAttribute4 == "criticalDamage") return "暴击伤害";
}

double Artifact::Get_SubAttributeValue4()
{
	return SubAttributeValue4;
}

int Artifact::Get_id()
{
	return id;
}

double Artifact::Get_CRIT_score()
{
    return CRIT_score;
}

bool Artifact::confirm_position(int p)//1~5对应五个位置
{
	switch (p) {
	case 1:
		if (position == "flower")	return true;
		else return false;
		break;
	case 2:
		if (position == "feather")	return true;
		else return false;
		break;
	case 3:
		if (position == "sand")	return true;
		else return false;
		break;
	case 4:
		if (position == "cup")	return true;
		else return false;
		break;
	case 5:
		if (position == "head")	return true;
		else return false;
		break;
	}
}
