/*
    RPG Paper Maker Copyright (C) 2017-2022 Wano

    RPG Paper Maker engine is under proprietary license.
    This source code is also copyrighted.

    Use Commercial edition for commercial use of your games.
    See RPG Paper Maker EULA here:
        http://rpg-paper-maker.com/index.php/eula.
*/

#ifndef SYSTEMCLASS_H
#define SYSTEMCLASS_H

#include <QStandardItemModel>
#include <QMetaType>
#include "systemtranslatable.h"

// -------------------------------------------------------
//
//  CLASS SystemClass
//
//  A particulary class (datas).
//
// -------------------------------------------------------

class SystemClass : public SystemTranslatable
{
public:
    static const QString jsonInitialLevel;
    static const QString jsonMaxLevel;
    static const QString jsonExpBase;
    static const QString jsonExpInflation;
    static const QString jsonExpTable;
    static const QString JSON_CHARACTERISTICS;
    static const QString jsonStats;
    static const QString jsonSkills;

    SystemClass();
    SystemClass(int i, QString name, int initialLevel, int maxLevel, int expBase,
        int expInflation, QStandardItemModel *characteristics = new
        QStandardItemModel, QStandardItemModel *stats = new QStandardItemModel,
        QStandardItemModel *skills = new QStandardItemModel);
    virtual ~SystemClass();
    int initialLevel() const;
    void setInitialLevel(int i, SystemClass *originalClass = nullptr);
    int maxLevel() const;
    void setMaxLevel(int i, SystemClass *originalClass = nullptr);
    int expBase() const;
    void setExpBase(int i, SystemClass *originalClass = nullptr);
    int expInflation() const;
    void setExpInflation(int i, SystemClass *originalClass = nullptr);
    QHash<int, int> * expTable();
    QStandardItemModel * characteristics() const;
    QStandardItemModel* statisticsProgression() const;
    QStandardItemModel* skills() const;

    static SystemClass * createInheritanceClass();

    void initializeHeaders();
    void reset();
    void setClassValues();

    virtual SuperListItem * createCopy() const;
    virtual void setCopy(const SuperListItem &super);
    virtual void read(const QJsonObject &json);
    virtual void write(QJsonObject &json) const;

protected:
    int m_initialLevel;
    int m_maxLevel;
    int m_expBase;
    int m_expInflation;
    QHash<int, int> m_expTable;
    QStandardItemModel *m_characteristics;
    QStandardItemModel *m_statisticsProgression;
    QStandardItemModel *m_skills;
};

Q_DECLARE_METATYPE(SystemClass)

#endif // SYSTEMCLASS_H
