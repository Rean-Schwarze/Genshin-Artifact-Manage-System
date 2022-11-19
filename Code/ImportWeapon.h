#pragma once
#include<iostream>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QString>
#include <QFile>
#include <QDir>
#include "Weapon.h"

class ImportWeapon :
    public Weapon
{
public:
    void Import(Weapon***, int*);
    void clear();
};

