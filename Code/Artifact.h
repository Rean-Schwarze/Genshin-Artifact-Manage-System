#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QString>
#include <QFile>
#include <QDir>

//using namespace std;

class Artifact//圣遗物类
{
public:
	Artifact();//默认构造函数
    Artifact(QString, QString, QString, double, QString, double, QString, double, QString, double, QString, double, int, int, int);
    void modify(QString, QString, QString, double, QString, double, QString, double, QString, double, QString, double, int, int);
	void modid(int);
	//friend ostream& operator<<(ostream&, const Artifact&);
    QString Get_setName();
    QString Get_Name();
    QString Get_position();
	int Get_level();
	int Get_star();
    QString Get_MainAttribute();
    QString Get_MainAttributeChinese();
	double Get_MainAttributeValue();
    QString Get_SubAttribute1();
    QString Get_SubAttributeChinese1();
	double Get_SubAttributeValue1();
    QString Get_SubAttribute2();
    QString Get_SubAttributeChinese2();
	double Get_SubAttributeValue2();
    QString Get_SubAttribute3();
    QString Get_SubAttributeChinese3();
	double Get_SubAttributeValue3();
    QString Get_SubAttribute4();
    QString Get_SubAttributeChinese4();
	double Get_SubAttributeValue4();
    double Get_CRIT_score();
	int Get_id();
	bool confirm_position(int position);//1~5对应五个位置
protected:
    QString setName, position;//套装名称、部位
	int level, star;//等级（0~20）、星级（1~5）
    QString MainAttribute, SubAttribute1, SubAttribute2, SubAttribute3, SubAttribute4;//主属性、副属性名称
	double MainAttributeValue, SubAttributeValue1, SubAttributeValue2, SubAttributeValue3, SubAttributeValue4;//主属性、副属性数值
	int id;
    double CRIT_score;
};


