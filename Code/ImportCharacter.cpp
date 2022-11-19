#include "ImportCharacter.h"

void ImportCharacter::Import(Character*** Char, int* CharAmount)
{
    int i;
    QJsonParseError err_rpt;
    QFile fileChar(":/Data/Character.json");
    fileChar.open(QIODevice::ReadOnly);
    QJsonDocument  root_Char = QJsonDocument::fromJson(fileChar.readAll(), &err_rpt);
    QJsonObject root_CharObj = root_Char.object();

    QJsonValue pryo_Value = root_CharObj.value("Pryo");
    QJsonArray pryo_array=pryo_Value.toArray();//转化为QJsonArray
    CharAmount[1] = pryo_array.size();//获取火属性角色数量

    QJsonValue hydro_Value = root_CharObj.value("Hydro");
    QJsonArray hydro_array=hydro_Value.toArray();//转化为QJsonArray
    CharAmount[2] = hydro_array.size();

    QJsonValue electro_Value = root_CharObj.value("Electro");
    QJsonArray electro_array=electro_Value.toArray();//转化为QJsonArray
    CharAmount[3] = electro_array.size();

    QJsonValue anemo_Value = root_CharObj.value("Anemo");
    QJsonArray anemo_array=anemo_Value.toArray();//转化为QJsonArray
    CharAmount[4] = anemo_array.size();

    QJsonValue cryo_Value = root_CharObj.value("Cryo");
    QJsonArray cryo_array=cryo_Value.toArray();//转化为QJsonArray
    CharAmount[5] = cryo_array.size();

    QJsonValue geo_Value = root_CharObj.value("Geo");
    QJsonArray geo_array=geo_Value.toArray();//转化为QJsonArray
    CharAmount[6] = geo_array.size();

    QJsonValue dendro_Value = root_CharObj.value("Dendro");
    QJsonArray dendro_array=dendro_Value.toArray();//转化为QJsonArray
    CharAmount[7] = dendro_array.size();

    CharAmount[0] = CharAmount[1] + CharAmount[2] + CharAmount[3] + CharAmount[4] + CharAmount[5] + CharAmount[6] + CharAmount[7] + CharAmount[8];

    //遍历文件，获取所有角色的数据
    for (i = 0; i < CharAmount[0]; i++)
    {
        Char[i] = new Character * [3];//分别储存80级、80突、90级数据
    }

    i = 0;

    //遍历①：火
    for (int j = 0; j < CharAmount[1]; j++)
    {
        QJsonObject pryo_Obj = pryo_array.at(j).toObject();
        Name = pryo_Obj.value("Name").toString();
        NameChinese = pryo_Obj.value("NameChinese").toString();
        Element = pryo_Obj.value("Element").toString();
        Star = pryo_Obj.value("Star").toInt();
        WeaponType = pryo_Obj.value("WeaponType").toString();
        BaseAttribute = pryo_Obj.value("BaseAttribute").toString();
        Description=pryo_Obj.value("Description").toString();

        //获取角色不同等级的数据
        QJsonValue Value = pryo_Obj.value("Value");
        QJsonArray Value_array=Value.toArray();//转化为QJsonArray

        //遍历三种等级
        for (int k = 0; k < 3; k++)
        {
            QJsonObject Value_Obj = Value_array.at(k).toObject();
            BaseLife = Value_Obj.value("BaseLife").toDouble();
            BaseDefend = Value_Obj.value("BaseDefend").toDouble();
            BaseAttack = Value_Obj.value("BaseAttack").toDouble();
            BaseAttributeValue = Value_Obj.value("BaseAttributeValue").toDouble();

            Char[i][k] = new Character(Name, NameChinese, Element, Star, WeaponType, BaseAttribute, BaseLife, BaseDefend, BaseAttack, BaseAttributeValue,Description);
        }
        i++;
        clear();
    }

    //遍历②：水
    for (int j = 0; j < CharAmount[2]; j++)
    {
        QJsonObject hydro_Obj = hydro_array.at(j).toObject();
        Name = hydro_Obj.value("Name").toString();
        NameChinese = hydro_Obj.value("NameChinese").toString();
        Element = hydro_Obj.value("Element").toString();
        Star = hydro_Obj.value("Star").toInt();
        WeaponType = hydro_Obj.value("WeaponType").toString();
        BaseAttribute = hydro_Obj.value("BaseAttribute").toString();
        Description=hydro_Obj.value("Description").toString();

        //获取角色不同等级的数据
        QJsonValue Value = hydro_Obj.value("Value");
        QJsonArray Value_array=Value.toArray();//转化为QJsonArray

        //遍历三种等级
        for (int k = 0; k < 3; k++)
        {
            QJsonObject Value_Obj = Value_array.at(k).toObject();
            BaseLife = Value_Obj.value("BaseLife").toDouble();
            BaseDefend = Value_Obj.value("BaseDefend").toDouble();
            BaseAttack = Value_Obj.value("BaseAttack").toDouble();
            BaseAttributeValue = Value_Obj.value("BaseAttributeValue").toDouble();

            Char[i][k] = new Character(Name, NameChinese, Element, Star, WeaponType, BaseAttribute, BaseLife, BaseDefend, BaseAttack, BaseAttributeValue,Description);
        }
        i++;
        clear();
    }

    //遍历③：雷
    for (int j = 0; j < CharAmount[3]; j++)
    {
        QJsonObject electro_Obj = electro_array.at(j).toObject();
        Name = electro_Obj.value("Name").toString();
        NameChinese = electro_Obj.value("NameChinese").toString();
        Element = electro_Obj.value("Element").toString();
        Star = electro_Obj.value("Star").toInt();
        WeaponType = electro_Obj.value("WeaponType").toString();
        BaseAttribute = electro_Obj.value("BaseAttribute").toString();
        Description=electro_Obj.value("Description").toString();

        //获取角色不同等级的数据
        QJsonValue Value = electro_Obj.value("Value");
        QJsonArray Value_array=Value.toArray();//转化为QJsonArray

        //遍历三种等级
        for (int k = 0; k < 3; k++)
        {
            QJsonObject Value_Obj = Value_array.at(k).toObject();
            BaseLife = Value_Obj.value("BaseLife").toDouble();
            BaseDefend = Value_Obj.value("BaseDefend").toDouble();
            BaseAttack = Value_Obj.value("BaseAttack").toDouble();
            BaseAttributeValue = Value_Obj.value("BaseAttributeValue").toDouble();

            Char[i][k] = new Character(Name, NameChinese, Element, Star, WeaponType, BaseAttribute, BaseLife, BaseDefend, BaseAttack, BaseAttributeValue,Description);
        }
        i++;
        clear();
    }

    //遍历④：风
    for (int j = 0; j < CharAmount[4]; j++)
    {
        QJsonObject anemo_Obj = anemo_array.at(j).toObject();
        Name = anemo_Obj.value("Name").toString();
        NameChinese = anemo_Obj.value("NameChinese").toString();
        Element = anemo_Obj.value("Element").toString();
        Star = anemo_Obj.value("Star").toInt();
        WeaponType = anemo_Obj.value("WeaponType").toString();
        BaseAttribute = anemo_Obj.value("BaseAttribute").toString();
        Description=anemo_Obj.value("Description").toString();

        //获取角色不同等级的数据
        QJsonValue Value = anemo_Obj.value("Value");
        QJsonArray Value_array=Value.toArray();//转化为QJsonArray

        //遍历三种等级
        for (int k = 0; k < 3; k++)
        {
            QJsonObject Value_Obj = Value_array.at(k).toObject();
            BaseLife = Value_Obj.value("BaseLife").toDouble();
            BaseDefend = Value_Obj.value("BaseDefend").toDouble();
            BaseAttack = Value_Obj.value("BaseAttack").toDouble();
            BaseAttributeValue = Value_Obj.value("BaseAttributeValue").toDouble();

            Char[i][k] = new Character(Name, NameChinese, Element, Star, WeaponType, BaseAttribute, BaseLife, BaseDefend, BaseAttack, BaseAttributeValue,Description);
        }
        i++;
        clear();
    }

    //遍历⑤：冰
    for (int j = 0; j < CharAmount[5]; j++)
    {
        QJsonObject cryo_Obj = cryo_array.at(j).toObject();
        Name = cryo_Obj.value("Name").toString();
        NameChinese = cryo_Obj.value("NameChinese").toString();
        Element = cryo_Obj.value("Element").toString();
        Star = cryo_Obj.value("Star").toInt();
        WeaponType = cryo_Obj.value("WeaponType").toString();
        BaseAttribute = cryo_Obj.value("BaseAttribute").toString();
        Description=cryo_Obj.value("Description").toString();

        //获取角色不同等级的数据
        QJsonValue Value = cryo_Obj.value("Value");
        QJsonArray Value_array=Value.toArray();//转化为QJsonArray

        //遍历三种等级
        for (int k = 0; k < 3; k++)
        {
            QJsonObject Value_Obj = Value_array.at(k).toObject();
            BaseLife = Value_Obj.value("BaseLife").toDouble();
            BaseDefend = Value_Obj.value("BaseDefend").toDouble();
            BaseAttack = Value_Obj.value("BaseAttack").toDouble();
            BaseAttributeValue = Value_Obj.value("BaseAttributeValue").toDouble();

            Char[i][k] = new Character(Name, NameChinese, Element, Star, WeaponType, BaseAttribute, BaseLife, BaseDefend, BaseAttack, BaseAttributeValue,Description);
        }
        i++;
        clear();
    }

    //遍历⑥：岩
    for (int j = 0; j < CharAmount[6]; j++)
    {
        QJsonObject geo_Obj = geo_array.at(j).toObject();
        Name = geo_Obj.value("Name").toString();
        NameChinese = geo_Obj.value("NameChinese").toString();
        Element = geo_Obj.value("Element").toString();
        Star = geo_Obj.value("Star").toInt();
        WeaponType = geo_Obj.value("WeaponType").toString();
        BaseAttribute = geo_Obj.value("BaseAttribute").toString();
        Description=geo_Obj.value("Description").toString();

        //获取角色不同等级的数据
        QJsonValue Value = geo_Obj.value("Value");
        QJsonArray Value_array=Value.toArray();//转化为QJsonArray

        //遍历三种等级
        for (int k = 0; k < 3; k++)
        {
            QJsonObject Value_Obj = Value_array.at(k).toObject();
            BaseLife = Value_Obj.value("BaseLife").toDouble();
            BaseDefend = Value_Obj.value("BaseDefend").toDouble();
            BaseAttack = Value_Obj.value("BaseAttack").toDouble();
            BaseAttributeValue = Value_Obj.value("BaseAttributeValue").toDouble();

            Char[i][k] = new Character(Name, NameChinese, Element, Star, WeaponType, BaseAttribute, BaseLife, BaseDefend, BaseAttack, BaseAttributeValue,Description);
        }
        i++;
        clear();
    }

    //遍历⑦：草
    for (int j = 0; j < CharAmount[7]; j++)
    {
        QJsonObject dendro_Obj = dendro_array.at(j).toObject();
        Name = dendro_Obj.value("Name").toString();
        NameChinese = dendro_Obj.value("NameChinese").toString();
        Element = dendro_Obj.value("Element").toString();
        Star = dendro_Obj.value("Star").toInt();
        WeaponType = dendro_Obj.value("WeaponType").toString();
        BaseAttribute = dendro_Obj.value("BaseAttribute").toString();
        Description=dendro_Obj.value("Description").toString();

        //获取角色不同等级的数据
        QJsonValue Value = dendro_Obj.value("Value");
        QJsonArray Value_array=Value.toArray();//转化为QJsonArray

        //遍历三种等级
        for (int k = 0; k < 3; k++)
        {
            QJsonObject Value_Obj = Value_array.at(k).toObject();
            BaseLife = Value_Obj.value("BaseLife").toDouble();
            BaseDefend = Value_Obj.value("BaseDefend").toDouble();
            BaseAttack = Value_Obj.value("BaseAttack").toDouble();
            BaseAttributeValue = Value_Obj.value("BaseAttributeValue").toDouble();

            Char[i][k] = new Character(Name, NameChinese, Element, Star, WeaponType, BaseAttribute, BaseLife, BaseDefend, BaseAttack, BaseAttributeValue,Description);
        }
        i++;
        clear();
    }

    //遍历⑧：玩家
    QJsonObject all_Obj = root_CharObj.value("All").toArray().at(0).toObject();
    Name = all_Obj.value("Name").toString();
    NameChinese = all_Obj.value("NameChinese").toString();
    Element = all_Obj.value("Element").toString();
    Star = all_Obj.value("Star").toInt();
    WeaponType = all_Obj.value("WeaponType").toString();
    BaseAttribute = all_Obj.value("BaseAttribute").toString();
    Description=all_Obj.value("Description").toString();

    //获取角色不同等级的数据
    QJsonValue Value = all_Obj.value("Value");
    QJsonArray Value_array=Value.toArray();//转化为QJsonArray

    //遍历三种等级
    for (int k = 0; k < 3; k++)
    {
        QJsonObject Value_Obj = Value_array.at(k).toObject();
        BaseLife = Value_Obj.value("BaseLife").toDouble();
        BaseDefend = Value_Obj.value("BaseDefend").toDouble();
        BaseAttack = Value_Obj.value("BaseAttack").toDouble();
        BaseAttributeValue = Value_Obj.value("BaseAttributeValue").toDouble();

        Char[i][k] = new Character(Name, NameChinese, Element, Star, WeaponType, BaseAttribute, BaseLife, BaseDefend, BaseAttack, BaseAttributeValue,Description);
    }
    i++;
    clear();
}

void ImportCharacter::clear()
{
	Name.clear();
	NameChinese.clear();
	Star = 0;
	Element.clear();
	WeaponType.clear();
	BaseAttribute.clear();
	BaseLife = 0;
	BaseDefend = 0;
	BaseAttack = 0;
	BaseAttributeValue = 0;
    Description.clear();
}
