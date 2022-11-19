#include"Import.h"

//从文件导入
void Import::ImportFromFile(Artifact** Art, int& ArtAmount, int flag)
{
    QJsonParseError err_rpt;
    QFile File;
    if(flag==0)//0是读取已保存文件
    {
        QFileInfo savedFile(QDir::currentPath() +"/savedArt.json");
        if(savedFile.isFile())
        {
            File.setFileName(QDir::currentPath() +"/savedArt.json");
        }
    }
    else if(flag==1)//1是打开扫描文件
    {
        File.setFileName(Data::fileName);
    }

    File.open(QIODevice::ReadOnly);
    QJsonDocument  root_Art = QJsonDocument::fromJson(File.readAll(), &err_rpt);
    QJsonObject root_ArtObj = root_Art.object();
    QJsonValue flower_Value = root_ArtObj.value("flower");
    QJsonArray flower_array=flower_Value.toArray();//转化为QJsonArray
    int flower_size = flower_array.size();//获取生之花数量
    QJsonValue feather_Value = root_ArtObj.value("feather");
    QJsonArray feather_array=feather_Value.toArray();//转化为QJsonArray
    int feather_size = feather_array.size();//获取死之羽数量
    QJsonValue sand_Value = root_ArtObj.value("sand");
    QJsonArray sand_array=sand_Value.toArray();//转化为QJsonArray
    int sand_size = sand_array.size();//获取时之沙数量
    QJsonValue cup_Value = root_ArtObj.value("cup");
    QJsonArray cup_array=cup_Value.toArray();//转化为QJsonArray
    int cup_size = cup_array.size();//获取空之杯数量
    QJsonValue head_Value = root_ArtObj.value("head");
    QJsonArray head_array=head_Value.toArray();//转化为QJsonArray
    int head_size = head_array.size();//获取理之冠数量

    //遍历①：生之花
    for (int i = 0; i < flower_size; i++)
    {
        QJsonObject flower_Obj = flower_array.at(i).toObject();
        setName = flower_Obj.value("setName").toString();
        position = flower_Obj.value("position").toString();

        level= flower_Obj.value("level").toInt();//获取等级、星级
        star = flower_Obj.value("star").toInt();

        if(level==20)//只读取20级的圣遗物
        {
            QJsonObject val_mainTag=flower_Obj.value("mainTag").toObject();//获取主属性
            MainAttribute = val_mainTag.value("name").toString();
            MainAttributeValue = val_mainTag.value("value").toDouble();

            QJsonArray normalTags_array=flower_Obj.value("normalTags").toArray();//获取副属性
            QJsonObject normalTags_Obj = normalTags_array.at(0).toObject();
            SubAttribute1 = normalTags_Obj.value("name").toString();
            SubAttributeValue1 = normalTags_Obj.value("value").toDouble();
            normalTags_Obj = normalTags_array.at(1).toObject();
            SubAttribute2 =normalTags_Obj.value("name").toString();
            SubAttributeValue2 = normalTags_Obj.value("value").toDouble();
            normalTags_Obj = normalTags_array.at(2).toObject();
            SubAttribute3 = normalTags_Obj.value("name").toString();
            SubAttributeValue3 = normalTags_Obj.value("value").toDouble();
            normalTags_Obj = normalTags_array.at(3).toObject();
            SubAttribute4 = normalTags_Obj.value("name").toString();
            SubAttributeValue4 = normalTags_Obj.value("value").toDouble();

            if(flag==0)
            {
                id=flower_Obj.value("id").toInt();
                Art[ArtAmount] = new Artifact(setName, position, MainAttribute, MainAttributeValue, SubAttribute1, SubAttributeValue1, SubAttribute2, SubAttributeValue2, SubAttribute3, SubAttributeValue3, SubAttribute4, SubAttributeValue4, level, star, id);
                ArtAmount++;

            }
            else if(flag==1)
            {
                Art[ArtAmount] = new Artifact(setName, position, MainAttribute, MainAttributeValue, SubAttribute1, SubAttributeValue1, SubAttribute2, SubAttributeValue2, SubAttribute3, SubAttributeValue3, SubAttribute4, SubAttributeValue4, level, star, ArtAmount);
                ArtAmount++;
            }
        }

        clear();//重置一下，方便后续读取
    }

    //遍历②：死之羽
    for (int i = 0; i < feather_size; i++)
    {
        QJsonObject feather_Obj = feather_array.at(i).toObject();
        setName = feather_Obj.value("setName").toString();
        position = feather_Obj.value("position").toString();

        level= feather_Obj.value("level").toInt();//获取等级、星级
        star = feather_Obj.value("star").toInt();

        if(level==20)
        {
            QJsonObject val_mainTag=feather_Obj.value("mainTag").toObject();//获取主属性
            MainAttribute = val_mainTag.value("name").toString();
            MainAttributeValue = val_mainTag.value("value").toDouble();

            QJsonArray normalTags_array=feather_Obj.value("normalTags").toArray();//获取副属性
            QJsonObject normalTags_Obj = normalTags_array.at(0).toObject();
            SubAttribute1 = normalTags_Obj.value("name").toString();
            SubAttributeValue1 = normalTags_Obj.value("value").toDouble();
            normalTags_Obj = normalTags_array.at(1).toObject();
            SubAttribute2 =normalTags_Obj.value("name").toString();
            SubAttributeValue2 = normalTags_Obj.value("value").toDouble();
            normalTags_Obj = normalTags_array.at(2).toObject();
            SubAttribute3 = normalTags_Obj.value("name").toString();
            SubAttributeValue3 = normalTags_Obj.value("value").toDouble();
            normalTags_Obj = normalTags_array.at(3).toObject();
            SubAttribute4 = normalTags_Obj.value("name").toString();
            SubAttributeValue4 = normalTags_Obj.value("value").toDouble();

            if(flag==0)
            {
                id=feather_Obj.value("id").toInt();
                Art[ArtAmount] = new Artifact(setName, position, MainAttribute, MainAttributeValue, SubAttribute1, SubAttributeValue1, SubAttribute2, SubAttributeValue2, SubAttribute3, SubAttributeValue3, SubAttribute4, SubAttributeValue4, level, star, id);
                ArtAmount++;
            }
            else if(flag==1)
            {
                Art[ArtAmount] = new Artifact(setName, position, MainAttribute, MainAttributeValue, SubAttribute1, SubAttributeValue1, SubAttribute2, SubAttributeValue2, SubAttribute3, SubAttributeValue3, SubAttribute4, SubAttributeValue4, level, star, ArtAmount);
                ArtAmount++;
            }
        }

        clear();//重置一下，方便后续读取
    }

    //遍历③：时之沙
    for (int i = 0; i < sand_size; i++)
    {
        QJsonObject sand_Obj = sand_array.at(i).toObject();
        setName = sand_Obj.value("setName").toString();
        position = sand_Obj.value("position").toString();

        level= sand_Obj.value("level").toInt();//获取等级、星级
        star = sand_Obj.value("star").toInt();

        if(level==20)
        {
            QJsonObject val_mainTag=sand_Obj.value("mainTag").toObject();//获取主属性
            MainAttribute = val_mainTag.value("name").toString();
            MainAttributeValue = val_mainTag.value("value").toDouble();

            QJsonArray normalTags_array=sand_Obj.value("normalTags").toArray();//获取副属性
            QJsonObject normalTags_Obj = normalTags_array.at(0).toObject();
            SubAttribute1 = normalTags_Obj.value("name").toString();
            SubAttributeValue1 = normalTags_Obj.value("value").toDouble();
            normalTags_Obj = normalTags_array.at(1).toObject();
            SubAttribute2 =normalTags_Obj.value("name").toString();
            SubAttributeValue2 = normalTags_Obj.value("value").toDouble();
            normalTags_Obj = normalTags_array.at(2).toObject();
            SubAttribute3 = normalTags_Obj.value("name").toString();
            SubAttributeValue3 = normalTags_Obj.value("value").toDouble();
            normalTags_Obj = normalTags_array.at(3).toObject();
            SubAttribute4 = normalTags_Obj.value("name").toString();
            SubAttributeValue4 = normalTags_Obj.value("value").toDouble();

            if(flag==0)
            {
                id=sand_Obj.value("id").toInt();
                Art[ArtAmount] = new Artifact(setName, position, MainAttribute, MainAttributeValue, SubAttribute1, SubAttributeValue1, SubAttribute2, SubAttributeValue2, SubAttribute3, SubAttributeValue3, SubAttribute4, SubAttributeValue4, level, star, id);
                ArtAmount++;
            }
            else if(flag==1)
            {
                Art[ArtAmount] = new Artifact(setName, position, MainAttribute, MainAttributeValue, SubAttribute1, SubAttributeValue1, SubAttribute2, SubAttributeValue2, SubAttribute3, SubAttributeValue3, SubAttribute4, SubAttributeValue4, level, star, ArtAmount);
                ArtAmount++;
            }
        }

        clear();//重置一下，方便后续读取
    }

    //遍历④：空之杯
    for (int i = 0; i < cup_size; i++)
    {
        QJsonObject cup_Obj = cup_array.at(i).toObject();
        setName = cup_Obj.value("setName").toString();
        position = cup_Obj.value("position").toString();

        level= cup_Obj.value("level").toInt();//获取等级、星级
        star = cup_Obj.value("star").toInt();

        if(level==20)
        {
            QJsonObject val_mainTag=cup_Obj.value("mainTag").toObject();//获取主属性
            MainAttribute = val_mainTag.value("name").toString();
            MainAttributeValue = val_mainTag.value("value").toDouble();

            QJsonArray normalTags_array=cup_Obj.value("normalTags").toArray();//获取副属性
            QJsonObject normalTags_Obj = normalTags_array.at(0).toObject();
            SubAttribute1 = normalTags_Obj.value("name").toString();
            SubAttributeValue1 = normalTags_Obj.value("value").toDouble();
            normalTags_Obj = normalTags_array.at(1).toObject();
            SubAttribute2 =normalTags_Obj.value("name").toString();
            SubAttributeValue2 = normalTags_Obj.value("value").toDouble();
            normalTags_Obj = normalTags_array.at(2).toObject();
            SubAttribute3 = normalTags_Obj.value("name").toString();
            SubAttributeValue3 = normalTags_Obj.value("value").toDouble();
            normalTags_Obj = normalTags_array.at(3).toObject();
            SubAttribute4 = normalTags_Obj.value("name").toString();
            SubAttributeValue4 = normalTags_Obj.value("value").toDouble();


            if(flag==0)
            {
                id=cup_Obj.value("id").toInt();
                Art[ArtAmount] = new Artifact(setName, position, MainAttribute, MainAttributeValue, SubAttribute1, SubAttributeValue1, SubAttribute2, SubAttributeValue2, SubAttribute3, SubAttributeValue3, SubAttribute4, SubAttributeValue4, level, star, id);
                ArtAmount++;
            }
            else if(flag==1)
            {
                Art[ArtAmount] = new Artifact(setName, position, MainAttribute, MainAttributeValue, SubAttribute1, SubAttributeValue1, SubAttribute2, SubAttributeValue2, SubAttribute3, SubAttributeValue3, SubAttribute4, SubAttributeValue4, level, star, ArtAmount);
                ArtAmount++;
            }
        }

        clear();//重置一下，方便后续读取
    }

    //遍历⑤：理之冠
    for (int i = 0; i < head_size; i++)
    {
        QJsonObject head_Obj = head_array.at(i).toObject();
        setName = head_Obj.value("setName").toString();
        position = head_Obj.value("position").toString();

        level= head_Obj.value("level").toInt();//获取等级、星级
        star = head_Obj.value("star").toInt();

        if(level==20)
        {
            QJsonObject val_mainTag=head_Obj.value("mainTag").toObject();//获取主属性
            MainAttribute = val_mainTag.value("name").toString();
            MainAttributeValue = val_mainTag.value("value").toDouble();

            QJsonArray normalTags_array=head_Obj.value("normalTags").toArray();//获取副属性
            QJsonObject normalTags_Obj = normalTags_array.at(0).toObject();
            SubAttribute1 = normalTags_Obj.value("name").toString();
            SubAttributeValue1 = normalTags_Obj.value("value").toDouble();
            normalTags_Obj = normalTags_array.at(1).toObject();
            SubAttribute2 =normalTags_Obj.value("name").toString();
            SubAttributeValue2 = normalTags_Obj.value("value").toDouble();
            normalTags_Obj = normalTags_array.at(2).toObject();
            SubAttribute3 = normalTags_Obj.value("name").toString();
            SubAttributeValue3 = normalTags_Obj.value("value").toDouble();
            normalTags_Obj = normalTags_array.at(3).toObject();
            SubAttribute4 = normalTags_Obj.value("name").toString();
            SubAttributeValue4 = normalTags_Obj.value("value").toDouble();

            if(flag==0)
            {
                id=head_Obj.value("id").toInt();
                Art[ArtAmount] = new Artifact(setName, position, MainAttribute, MainAttributeValue, SubAttribute1, SubAttributeValue1, SubAttribute2, SubAttributeValue2, SubAttribute3, SubAttributeValue3, SubAttribute4, SubAttributeValue4, level, star, id);
                ArtAmount++;
            }
            else if(flag==1)
            {
                Art[ArtAmount] = new Artifact(setName, position, MainAttribute, MainAttributeValue, SubAttribute1, SubAttributeValue1, SubAttribute2, SubAttributeValue2, SubAttribute3, SubAttributeValue3, SubAttribute4, SubAttributeValue4, level, star, ArtAmount);
                ArtAmount++;
            }
        }

        clear();//重置一下，方便后续读取
    }
}

//手动输入导入
//void Import::ImportManually(Artifact** Art, int& Amount)
//{
//	int n, i, temp;
//	cout << "请输入要导入的圣遗物数量。（输入0返回）" << endl;
//	cin >> n;
//	for (i = 0; i < n; i++)
//	{
//		ImportSetName();

//		ImportPosition();

//		cout << "请输入圣遗物星级" << endl;
//		cin >> star;

//		cout << "请输入圣遗物等级" << endl;
//		cin >> level;

//		ImportMainAttribute();

//		ImportSubAttribute1();
//		ImportSubAttribute2();
//		ImportSubAttribute3();
//		ImportSubAttribute4();

//		Art[Amount] = new Artifact(setName, position, MainAttribute, MainAttributeValue, SubAttribute1, SubAttributeValue1, SubAttribute2, SubAttributeValue2, SubAttribute3, SubAttributeValue3, SubAttribute4, SubAttributeValue4, level, star, Amount);
//		Amount++;

//		clear();//重置一下，方便后续读取
//		temp = 0;
//	}
//}

//void Import::Modify(Artifact** Art, int& Amount)
//{
//	int mod, n, n1;
//    //DisplayAllArtifact(Art, Amount);

//	FLAG1:
//	cout << "请输入欲修改圣遗物的数量。（输入0返回）" << endl;
//	cin >> n;
//	for (int i = 0; i < n; i++)
//	{
//		FLAG2:
//		cout << "请输入欲修改圣遗物的序号。（输入0返回）" << endl;
//		cin >> mod;
//		if (mod == 0) goto FLAG1;
//		else
//		{
//			get(Art, mod - 1);

//			FLAG3:
//			cout << "请选择要修改的数据。（记得保存！）" << endl;
//			cout << "【1】套装名称" << endl;
//			cout << "【2】等级" << '\t' << "【3】星级" << endl;
//			cout << "【4】主属性及数值" << endl;
//			cout << "【5】副属性1及数值" << endl;
//			cout << "【6】副属性2及数值" << endl;
//			cout << "【7】副属性3及数值" << endl;
//			cout << "【8】副属性4及数值" << endl;
//			cout << "【9】保存所做修改并返回" << endl;
//			cout << "【0】返回" << endl;

//			while (cin >> n1)
//			{
//				if (n1 == 0) goto FLAG2;
//				else
//				{
//					if (n1 != 10) cout << "请输入修改后的数据。" << endl;
//					switch (n1)
//					{
//					case 1:
//					{
//						setName.clear();
//						ImportSetName();
//						goto FLAG3;
//					}; break;
//					case 2:
//					{
//						cin >> level;
//						goto FLAG3;
//					}; break;
//					case 3:
//					{
//						cin >> star;
//						goto FLAG3;
//					}; break;
//					case 4:
//					{
//						MainAttribute.clear();
//						ImportMainAttribute();
//						goto FLAG3;
//					}; break;
//					case 5:
//					{
//						SubAttribute1.clear();
//						ImportSubAttribute1();
//						goto FLAG3;
//					}; break;
//					case 6:
//					{
//						SubAttribute2.clear();
//						ImportSubAttribute2();
//						goto FLAG3;
//					}; break;
//					case 7:
//					{
//						SubAttribute3.clear();
//						ImportSubAttribute3();
//						goto FLAG3;
//					}; break;
//					case 8:
//					{
//						SubAttribute4.clear();
//						ImportSubAttribute4();
//						goto FLAG3;
//					}; break;
//					case 9:
//					{
//						Art[mod-1]->modify(setName, position, MainAttribute, MainAttributeValue, SubAttribute1, SubAttributeValue1, SubAttribute2, SubAttributeValue2, SubAttribute3, SubAttributeValue3, SubAttribute4, SubAttributeValue4, level, star);
//						clear();
//						goto FLAG2;
//					}; break;
//					}
//				}
//			}
//		}
//	}
//}

//void Import::Delete(Artifact** Art, int& Amount)
//{
//	int del, n;
//    //DisplayAllArtifact(Art, Amount);
//	cout << "请输入欲删除圣遗物的数量。（输入0返回）" << endl;
//	cin >> n;
//	cout << "请输入欲删除圣遗物的序号。" << endl;
//	for (int i = 0; i < n; i++)
//	{
//		cin >> del;
//		for (int j = del; j < Amount; j++)
//		{
//			Art[j - 1] = Art[j];
//		}
//		Amount--;
//	}
//}

////手动输入套装名称
//void Import::ImportSetName()
//{
//    int n;
//    QJsonParseError err_rpt;
//    QFile fileArt(":/Data/Artifact.json");
//    fileArt.open(QIODevice::ReadOnly);
//    QJsonDocument  root_Art = QJsonDocument::fromJson(fileArt.readAll(), &err_rpt);
//    QJsonObject root_ArtObj = root_Art.object();
//    QJsonValue artifact_Value = root_ArtObj.value("Artifact");
//    QJsonArray array=artifact_Value.toArray();//转化为QJsonArray

//    if (fileArt.open(QIODevice::ReadOnly))
//	{
//        int size =array.size();
//		cout << "请选择圣遗物套装（目前仅支持含五星的套装）" << endl;
//		for (int i = 0; i < size; i++)
//		{
//            QJsonObject artifact_Obj = array.at(i).toObject();
//            qDebug() << "【" << i + 1 << "】" << artifact_Obj.value("setNameChinese").toString();
//		}
//		cin >> n;
//		if (n > 0 && n < size + 1)
//		{
//            QJsonObject artifact_Obj = array.at(n).toObject();
//            setName = artifact_Obj.value("setName").toString();
//		}
//	}
//}

////手动输入部位
//void Import::ImportPosition()
//{
//	int temp;
//	cout << "请选择圣遗物部位" << endl;
//	cout << "【1】生之花" << endl;
//	cout << "【2】死之羽" << endl;
//	cout << "【3】时之沙" << endl;
//	cout << "【4】空之杯" << endl;
//	cout << "【5】理之冠" << endl;
//	cin >> temp;
//	switch (temp)
//	{
//	case 1:position = "flower"; break;
//	case 2:position = "feather"; break;
//	case 3:position = "sand"; break;
//	case 4:position = "cup"; break;
//	case 5:position = "head"; break;
//	}
//}

////手动输入主属性
//void Import::ImportMainAttribute()
//{
//	int n;
//	if (position == "flower")
//	{
//		MainAttribute = "lifeStatic";
//		cout << "请输入主属性数值" << endl;
//		cin >> MainAttributeValue;
//	}
//	if (position == "feather")
//	{
//		MainAttribute = "attackStatic";
//		cout << "请输入主属性数值" << endl;
//		cin >> MainAttributeValue;
//	}
//	if (position == "sand")
//	{
//		cout << "请选择主属性" << endl;
//		cout << "【1】生命值" << endl;
//		cout << "【2】防御力" << endl;
//		cout << "【3】攻击力" << endl;
//		cout << "【4】元素精通" << endl;
//		cout << "【5】元素充能效率" << endl;
//		cin >> n;
//		switch (n)
//		{
//		case 1:MainAttribute = "lifePercentage"; break;
//		case 2:MainAttribute = "defendPercentage"; break;
//		case 3:MainAttribute = "attackPercentage"; break;
//		case 4:MainAttribute = "elementalMastery"; break;
//		case 5:MainAttribute = "recharge"; break;
//		}
//		cout << "请输入数值（百分比请转换为小数，例2.7%→0.027）" << endl;
//		cin >> MainAttributeValue;
//	}
//	if (position == "cup")
//	{
//		cout << "请选择主属性" << endl;
//		cout << "【1】生命值" << endl;
//		cout << "【2】防御力" << endl;
//		cout << "【3】攻击力" << endl;
//		cout << "【4】元素精通" << endl;
//		cout << "【5】物理伤害加成" << endl;
//		cout << "【6】火元素伤害加成" << endl;
//		cout << "【7】水元素伤害加成" << endl;
//		cout << "【8】草元素伤害加成" << endl;
//		cout << "【9】雷元素伤害加成" << endl;
//		cout << "【10】风元素伤害加成" << endl;
//		cout << "【11】冰元素伤害加成" << endl;
//		cout << "【12】岩元素伤害加成" << endl;
//		cin >> n;
//		switch (n)
//		{
//		case 1:MainAttribute = "lifePercentage"; break;
//		case 2:MainAttribute = "defendPercentage"; break;
//		case 3:MainAttribute = "attackPercentage"; break;
//		case 4:MainAttribute = "elementalMastery"; break;
//		case 5:MainAttribute = "physicalBonus"; break;
//		case 6:MainAttribute = "fireBonus"; break;
//		case 7:MainAttribute = "waterBonus"; break;
//		case 8:MainAttribute = "dendroBounus"; break;
//		case 9:MainAttribute = "thunderBonus"; break;
//		case 10:MainAttribute = "windBonus"; break;
//		case 11:MainAttribute = "iceBonus"; break;
//		case 12:MainAttribute = "rockBonus"; break;
//		}
//		cout << "请输入数值（百分比请转换为小数，例2.7%→0.027）" << endl;
//		cin >> MainAttributeValue;
//	}
//	if (position == "head")
//	{
//		cout << "请选择主属性" << endl;
//		cout << "【1】生命值" << endl;
//		cout << "【2】防御力" << endl;
//		cout << "【3】攻击力" << endl;
//		cout << "【4】元素精通" << endl;
//		cout << "【5】暴击率" << endl;
//		cout << "【6】暴击伤害" << endl;
//		cout << "【7】治疗加成" << endl;
//		cin >> n;
//		switch (n)
//		{
//		case 1:MainAttribute = "lifePercentage"; break;
//		case 2:MainAttribute = "defendPercentage"; break;
//		case 3:MainAttribute = "attackPercentage"; break;
//		case 4:MainAttribute = "elementalMastery"; break;
//		case 5:MainAttribute = "critical"; break;
//		case 6:MainAttribute = "criticalDamage"; break;
//		case 7:MainAttribute = "cureEffect"; break;
//		}
//		cout << "请输入数值（百分比请转换为小数，例2.7%→0.027）" << endl;
//		cin >> MainAttributeValue;
//	}
//}

////手动输入副属性1
//void Import::ImportSubAttribute1()
//{
//	int n;
//	cout << "请选择第一个副属性" << endl;
//	cout << "【1】生命值（小）" << endl;
//	cout << "【2】生命值（大）" << endl;
//	cout << "【3】防御力（小）" << endl;
//	cout << "【4】防御力（大）" << endl;
//	cout << "【5】攻击力（小）" << endl;
//	cout << "【6】攻击力（大）" << endl;
//	cout << "【7】元素精通" << endl;
//	cout << "【8】元素充能效率" << endl;
//	cout << "【9】暴击率" << endl;
//	cout << "【10】暴击伤害" << endl;
//	cin >> n;
//	switch (n)
//	{
//	case 1:SubAttribute1 = "lifeStatic"; break;
//	case 2:SubAttribute1 = "lifePercentage"; break;
//	case 3:SubAttribute1 = "defendStatic"; break;
//	case 4:SubAttribute1 = "defendPercentage"; break;
//	case 5:SubAttribute1 = "attackStatic"; break;
//	case 6:SubAttribute1 = "attackPercentage"; break;
//	case 7:SubAttribute1 = "elementalMastery"; break;
//	case 8:SubAttribute1 = "recharge"; break;
//	case 9:SubAttribute1 = "critical"; break;
//	case 10:SubAttribute1 = "criticalDamage"; break;
//	}
//	cout << "请输入数值（百分比请转换为小数，例2.7%→0.027）" << endl;
//	cin >> SubAttributeValue1;
//}

//void Import::ImportSubAttribute2()
//{
//	int n;
//	cout << "请选择第二个副属性" << endl;
//	cout << "【1】生命值（小）" << endl;
//	cout << "【2】生命值（大）" << endl;
//	cout << "【3】防御力（小）" << endl;
//	cout << "【4】防御力（大）" << endl;
//	cout << "【5】攻击力（小）" << endl;
//	cout << "【6】攻击力（大）" << endl;
//	cout << "【7】元素精通" << endl;
//	cout << "【8】元素充能效率" << endl;
//	cout << "【9】暴击率" << endl;
//	cout << "【10】暴击伤害" << endl;
//	cin >> n;
//	switch (n)
//	{
//	case 1:SubAttribute2 = "lifeStatic"; break;
//	case 2:SubAttribute2 = "lifePercentage"; break;
//	case 3:SubAttribute2 = "defendStatic"; break;
//	case 4:SubAttribute2 = "defendPercentage"; break;
//	case 5:SubAttribute2 = "attackStatic"; break;
//	case 6:SubAttribute2 = "attackPercentage"; break;
//	case 7:SubAttribute2 = "elementalMastery"; break;
//	case 8:SubAttribute2 = "recharge"; break;
//	case 9:SubAttribute2 = "critical"; break;
//	case 10:SubAttribute2 = "criticalDamage"; break;
//	}
//	cout << "请输入数值（百分比请转换为小数，例2.7%→0.027）" << endl;
//	cin >> SubAttributeValue2;
//}

//void Import::ImportSubAttribute3()
//{
//	int n;
//	cout << "请选择第三个副属性" << endl;
//	cout << "【1】生命值（小）" << endl;
//	cout << "【2】生命值（大）" << endl;
//	cout << "【3】防御力（小）" << endl;
//	cout << "【4】防御力（大）" << endl;
//	cout << "【5】攻击力（小）" << endl;
//	cout << "【6】攻击力（大）" << endl;
//	cout << "【7】元素精通" << endl;
//	cout << "【8】元素充能效率" << endl;
//	cout << "【9】暴击率" << endl;
//	cout << "【10】暴击伤害" << endl;
//	cin >> n;
//	switch (n)
//	{
//	case 1:SubAttribute3 = "lifeStatic"; break;
//	case 2:SubAttribute3 = "lifePercentage"; break;
//	case 3:SubAttribute3 = "defendStatic"; break;
//	case 4:SubAttribute3 = "defendPercentage"; break;
//	case 5:SubAttribute3 = "attackStatic"; break;
//	case 6:SubAttribute3 = "attackPercentage"; break;
//	case 7:SubAttribute3 = "elementalMastery"; break;
//	case 8:SubAttribute3 = "recharge"; break;
//	case 9:SubAttribute3 = "critical"; break;
//	case 10:SubAttribute3 = "criticalDamage"; break;
//	}
//	cout << "请输入数值（百分比请转换为小数，例2.7%→0.027）" << endl;
//	cin >> SubAttributeValue3;
//}

//void Import::ImportSubAttribute4()
//{
//	int n;
//	cout << "请选择第四个副属性" << endl;
//	cout << "【1】生命值（小）" << endl;
//	cout << "【2】生命值（大）" << endl;
//	cout << "【3】防御力（小）" << endl;
//	cout << "【4】防御力（大）" << endl;
//	cout << "【5】攻击力（小）" << endl;
//	cout << "【6】攻击力（大）" << endl;
//	cout << "【7】元素精通" << endl;
//	cout << "【8】元素充能效率" << endl;
//	cout << "【9】暴击率" << endl;
//	cout << "【10】暴击伤害" << endl;
//	cout << "【0】没有第四个副属性" << endl;
//	cin >> n;
//	if (n != 0)
//	{
//		switch (n)
//		{
//		case 1:SubAttribute4 = "lifeStatic"; break;
//		case 2:SubAttribute4 = "lifePercentage"; break;
//		case 3:SubAttribute4 = "defendStatic"; break;
//		case 4:SubAttribute4 = "defendPercentage"; break;
//		case 5:SubAttribute4 = "attackStatic"; break;
//		case 6:SubAttribute4 = "attackPercentage"; break;
//		case 7:SubAttribute4 = "elementalMastery"; break;
//		case 8:SubAttribute4 = "recharge"; break;
//		case 9:SubAttribute4 = "critical"; break;
//		case 10:SubAttribute4 = "criticalDamage"; break;
//		}
//		cout << "请输入数值（百分比请转换为小数，例2.7%→0.027）" << endl;
//		cin >> SubAttributeValue4;
//	}
//	else
//	{
//		SubAttribute4.clear();
//		SubAttributeValue4 = 0;
//	}
//}

void Import::get(Artifact** Art, int n)
{
	setName = Art[n]->Get_setName();
	position = Art[n]->Get_position();
	MainAttribute = Art[n]->Get_MainAttribute();
	MainAttributeValue = Art[n]->Get_MainAttributeValue();
	SubAttribute1= Art[n]->Get_SubAttribute1();
	SubAttributeValue1 = Art[n]->Get_SubAttributeValue1();
	SubAttribute2 = Art[n]->Get_SubAttribute2();
	SubAttributeValue2 = Art[n]->Get_SubAttributeValue3();
	SubAttribute3 = Art[n]->Get_SubAttribute3();
	SubAttributeValue3 = Art[n]->Get_SubAttributeValue3();
	SubAttribute4 = Art[n]->Get_SubAttribute1();
	SubAttributeValue4 = Art[n]->Get_SubAttributeValue4();
	level = Art[n]->Get_level();
	star = Art[n]->Get_star();
}

void Import::clear()
{
	setName.clear();
	position.clear();
	MainAttribute.clear();
	MainAttributeValue = 0;
	SubAttribute1.clear();
	SubAttributeValue1 = 0;
	SubAttribute2.clear();
	SubAttributeValue2 = 0;
	SubAttribute3.clear();
	SubAttributeValue3 = 0;
	SubAttribute4.clear();
	SubAttributeValue4 = 0;
	level = 0;
	star = 0;
}
