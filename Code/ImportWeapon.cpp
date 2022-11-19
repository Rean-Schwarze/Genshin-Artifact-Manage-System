#include "ImportWeapon.h"

void ImportWeapon::Import(Weapon*** Weap, int* WeapAmount)
{
	int i;

    QJsonParseError err_rpt;
    QFile fileWeap(":/Data/Weapon.json");
    fileWeap.open(QIODevice::ReadOnly);
    QJsonDocument  root_Weap = QJsonDocument::fromJson(fileWeap.readAll(), &err_rpt);
    QJsonObject root_WeapObj = root_Weap.object();

    QJsonValue sword_Value = root_WeapObj.value("Sword");
    QJsonArray sword_array=sword_Value.toArray();//转化为QJsonArray
    WeapAmount[1] = sword_array.size();//获取单手剑数量

    QJsonValue clay_Value = root_WeapObj.value("Claymore");
    QJsonArray clay_array=clay_Value.toArray();//转化为QJsonArray
    WeapAmount[2] = clay_array.size();//获取双手剑数量

    QJsonValue bow_Value = root_WeapObj.value("Bow");
    QJsonArray bow_array=bow_Value.toArray();//转化为QJsonArray
    WeapAmount[3] = bow_array.size();//获取弓数量

    QJsonValue cata_Value = root_WeapObj.value("Catalyst");
    QJsonArray cata_array=cata_Value.toArray();//转化为QJsonArray
    WeapAmount[4] = cata_array.size();//获取法器数量

    QJsonValue pole_Value = root_WeapObj.value("Polearm");
    QJsonArray pole_array=pole_Value.toArray();//转化为QJsonArray
    WeapAmount[5] = pole_array.size();//获取弓数量

    WeapAmount[0] = WeapAmount[1] + WeapAmount[2] + WeapAmount[3] + WeapAmount[4] + WeapAmount[5];

    //遍历文件，获取所有武器的数据
    for (i = 0; i < WeapAmount[0]; i++)
    {
        Weap[i] = new Weapon * [3];//分别储存80级、80突、90级数据
    }

    i = 0;

    //遍历①：单手剑
    for (int j = 0; j < WeapAmount[1]; j++)
    {
        QJsonObject sword_Obj = sword_array.at(j).toObject();
        WeaponType = "Sword";
        Name = sword_Obj.value("Name").toString();
        NameChinese = sword_Obj.value("NameChinese").toString();
        Star = sword_Obj.value("Star").toInt();
        BaseAttribute = sword_Obj.value("BaseAttribute").toString();
        SpecialAbilityName=sword_Obj.value("SpecialAbilityName").toString();
        SpecialAbility=sword_Obj.value("SpecialAbility").toString();
        Description=sword_Obj.value("Description").toString();

        QJsonValue val_Value = sword_Obj.value("Value");//获取武器不同等级的数据
        QJsonArray val_array=val_Value.toArray();

        //遍历三种等级
        for (int k = 0; k < 3; k++)
        {
            QJsonObject val_Obj=val_array.at(k).toObject();
            BaseAttack = val_Obj.value("BaseAttack").toDouble();
            BaseAttributeValue = val_Obj.value("BaseAttributeValue").toDouble();

            Weap[i][k] = new Weapon(WeaponType, Name, NameChinese, Star, BaseAttribute, BaseAttack, BaseAttributeValue, SpecialAbilityName, SpecialAbility, Description);
        }
        i++;
        clear();
    }

    //遍历②：双手剑
    for (int j = 0; j < WeapAmount[2]; j++)
    {
        QJsonObject clay_Obj = clay_array.at(j).toObject();
        WeaponType = "Claymore";
        Name = clay_Obj.value("Name").toString();
        NameChinese = clay_Obj.value("NameChinese").toString();
        Star = clay_Obj.value("Star").toInt();
        BaseAttribute = clay_Obj.value("BaseAttribute").toString();
        SpecialAbilityName=clay_Obj.value("SpecialAbilityName").toString();
        SpecialAbility=clay_Obj.value("SpecialAbility").toString();
        Description=clay_Obj.value("Description").toString();

        QJsonValue val_Value = clay_Obj.value("Value");//获取武器不同等级的数据
        QJsonArray val_array=val_Value.toArray();

        //遍历三种等级
        for (int k = 0; k < 3; k++)
        {
            QJsonObject val_Obj=val_array.at(k).toObject();
            BaseAttack = val_Obj.value("BaseAttack").toDouble();
            BaseAttributeValue = val_Obj.value("BaseAttributeValue").toDouble();

            Weap[i][k] = new Weapon(WeaponType, Name, NameChinese, Star, BaseAttribute, BaseAttack, BaseAttributeValue, SpecialAbilityName, SpecialAbility, Description);
        }
        i++;
        clear();
    }

    //遍历③：弓
    for (int j = 0; j < WeapAmount[3]; j++)
    {
        QJsonObject bow_Obj = bow_array.at(j).toObject();
        WeaponType = "Bow";
        Name = bow_Obj.value("Name").toString();
        NameChinese = bow_Obj.value("NameChinese").toString();
        Star = bow_Obj.value("Star").toInt();
        BaseAttribute = bow_Obj.value("BaseAttribute").toString();
        SpecialAbilityName=bow_Obj.value("SpecialAbilityName").toString();
        SpecialAbility=bow_Obj.value("SpecialAbility").toString();
        Description=bow_Obj.value("Description").toString();

        QJsonValue val_Value = bow_Obj.value("Value");//获取武器不同等级的数据
        QJsonArray val_array=val_Value.toArray();

        //遍历三种等级
        for (int k = 0; k < 3; k++)
        {
            QJsonObject val_Obj=val_array.at(k).toObject();
            BaseAttack = val_Obj.value("BaseAttack").toDouble();
            BaseAttributeValue = val_Obj.value("BaseAttributeValue").toDouble();

            Weap[i][k] = new Weapon(WeaponType, Name, NameChinese, Star, BaseAttribute, BaseAttack, BaseAttributeValue, SpecialAbilityName, SpecialAbility, Description);
        }
        i++;
        clear();
    }

    //遍历④：法器
    for (int j = 0; j < WeapAmount[4]; j++)
    {
        QJsonObject cata_Obj = cata_array.at(j).toObject();
        WeaponType = "Catalyst";
        Name = cata_Obj.value("Name").toString();
        NameChinese = cata_Obj.value("NameChinese").toString();
        Star = cata_Obj.value("Star").toInt();
        BaseAttribute = cata_Obj.value("BaseAttribute").toString();
        SpecialAbilityName=cata_Obj.value("SpecialAbilityName").toString();
        SpecialAbility=cata_Obj.value("SpecialAbility").toString();
        Description=cata_Obj.value("Description").toString();

        QJsonValue val_Value = cata_Obj.value("Value");//获取武器不同等级的数据
        QJsonArray val_array=val_Value.toArray();

        //遍历三种等级
        for (int k = 0; k < 3; k++)
        {
            QJsonObject val_Obj=val_array.at(k).toObject();
            BaseAttack = val_Obj.value("BaseAttack").toDouble();
            BaseAttributeValue = val_Obj.value("BaseAttributeValue").toDouble();

            Weap[i][k] = new Weapon(WeaponType, Name, NameChinese, Star, BaseAttribute, BaseAttack, BaseAttributeValue, SpecialAbilityName, SpecialAbility, Description);
        }
        i++;
        clear();
    }

    //遍历⑤：长柄武器
    for (int j = 0; j < WeapAmount[5]; j++)
    {
        QJsonObject pole_Obj = pole_array.at(j).toObject();
        WeaponType = "Polearm";
        Name = pole_Obj.value("Name").toString();
        NameChinese = pole_Obj.value("NameChinese").toString();
        Star = pole_Obj.value("Star").toInt();
        BaseAttribute = pole_Obj.value("BaseAttribute").toString();
        SpecialAbilityName=pole_Obj.value("SpecialAbilityName").toString();
        SpecialAbility=pole_Obj.value("SpecialAbility").toString();
        Description=pole_Obj.value("Description").toString();

        QJsonValue val_Value = pole_Obj.value("Value");//获取武器不同等级的数据
        QJsonArray val_array=val_Value.toArray();

        //遍历三种等级
        for (int k = 0; k < 3; k++)
        {
            QJsonObject val_Obj=val_array.at(k).toObject();
            BaseAttack = val_Obj.value("BaseAttack").toDouble();
            BaseAttributeValue = val_Obj.value("BaseAttributeValue").toDouble();

            Weap[i][k] = new Weapon(WeaponType, Name, NameChinese, Star, BaseAttribute, BaseAttack, BaseAttributeValue, SpecialAbilityName, SpecialAbility, Description);
        }
        i++;
        clear();
    }
}

void ImportWeapon::clear()
{
	WeaponType.clear();
	Name.clear();
	NameChinese.clear();
	Star = 0;
	BaseAttribute.clear();
	BaseAttack = 0;
	BaseAttributeValue = 0;
    SpecialAbilityName.clear();
    SpecialAbility.clear();
    Description.clear();
}
