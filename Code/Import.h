#pragma once
#include<iostream>
#include "Artifact.h"
#include "data.h"
//#include "Display.h"

//using namespace std;

class Import :public Artifact
{
public:
    void ImportFromFile(Artifact**, int&, int);//从文件导入
	void ImportManually(Artifact**, int&);//手动输入导入
	void Modify(Artifact**, int&);//手动修改
	void Delete(Artifact**, int&);//手动删除
	void ImportSetName();//手动输入套装名称
	void ImportPosition();//手动输入部位
	void ImportMainAttribute();//手动输入主属性
	void ImportSubAttribute1();//手动输入副属性1
	void ImportSubAttribute2();//手动输入副属性2
	void ImportSubAttribute3();//手动输入副属性3
	void ImportSubAttribute4();//手动输入副属性4
	void get(Artifact**, int);//获取基础数据
	void clear();//重置基础数据
};
