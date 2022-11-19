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
#include "Character.h"

class ImportCharacter :
    public Character
{
public:
    void Import(Character***, int*);
    void clear();
};

