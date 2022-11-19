#pragma once
#include <iostream>
#include <QString>
#include <QDir>
#include "Artifact.h"
#include "Character.h"
#include "Weapon.h"

class FavoriteOri :public Artifact{
public:
	Character* character = NULL;
	Weapon* weapon = NULL;
	int charlevel, weaplevel;
    Artifact* favorite[5];
    int f_id[5]={-1,-1,-1,-1,-1};
    QString name = "";
    int id;
    int Num[7]={0,0,0,0,0,0,0};//0~6分别对应生命、攻击、防御、精通、充能、暴击、爆伤圣遗物数量
    QString sandTemp;
    QString cupTemp;
    QString headTemp;
protected:
	bool importState = 0;

public:
	double CRIT_score = 0;
	double total_critical = 0;
	double total_criticalDamage = 0;
	double total_recharge = 0;
	double total_elementalMastery = 0;
	double total_attack = 0;
	double total_Attack = 0;
	double total_defend = 0;
	double total_Defend = 0;
	double total_life = 0;
	double total_Life = 0;
	double total_cure = 0;
	double total_physicalBonus = 0;
	double total_fireBonus = 0;
	double total_waterBonus = 0;
	double total_grassBonus = 0;
	double total_thunderBonus = 0;
	double total_windBonus = 0;
	double total_iceBonus = 0;
	double total_rockBonus = 0;
    QString set_two1 = "", set_two2 = "", set_four = "";
//    bool state[6] = {};  //各部位输入状态
public:
	Artifact* operator[](int);
    friend void setFavorite(Artifact**, const int, FavoriteOri*, int&);
    friend void Display_Fav(FavoriteOri*, const int&);
    friend void ViewFunction(FavoriteOri*, const int&, Character***, int*, Weapon***, int*);
    QString getName();
    void import(Artifact**, const int&);  //通过id将目标圣遗物地址赋给收藏指针，同时加上双暴分
    void confirm(); //识别套装，计算总属性
    int getID(int i);
    void setName(QString);  //设置对象名称
    void setName(int i);  //未设置名称默认为id号，即序号
    void setFlower(Artifact**,int);//传进来selectedNum即可
    void setFeather(Artifact**,int);
    void setSand(Artifact**,int);
    void setCup(Artifact**,int);
    void setHead(Artifact**,int);
    void addEffect(QString,double);  //通过属性名将分散的属性求和（位于append_total内）
    void append_total(); //遍历各属性，相加计算总属性（位于confirm内）
    void judge_set();  //判断套装（位于confirm内）
    void clear();
    void setCharWeap(Character***,int* ,Weapon***, int*); //设置角色+武器
    bool CW_isNULL(); //判断角色+武器是否为空
    bool isEmpty();//判断该预设是否输入完毕
    double Get_total_life();
    double Get_total_Life();
    double Get_total_attack();
    double Get_total_Attack();
    double Get_total_defend();
    double Get_total_Defend();
    double Get_mastery();
    double Get_recharge();
    double Get_total_critical();
    double Get_total_criticalDamage();
    int Get_Num(int);
    double Get_cScore();
};
//class View {
//public:
//	View(Favorite&);
//	void append(QString, double);
//	void show_View();
//protected:
//	QString character, weapon;
//	int charlevel, weaplevel;
//	double attack = 0, defend = 0, life = 0;
//	double base_attack = 0,
//		base_defend = 0,
//		base_life = 0;
//	double percent_attack = 0,
//		percent_defend = 0,
//		percent_life = 0;
//	double critical = 0,
//		criticalDamage = 0;
//	double recharge = 0,
//		elementalMastery = 0;
//	double cure = 0,
//		physicalBonus = 0,
//		fireBonus = 0,
//		waterBonus = 0,
//		grassBonus = 0,
//		thunderBonus = 0,
//		windBonus = 0,
//		iceBonus = 0,
//		rockBonus = 0;
//};



