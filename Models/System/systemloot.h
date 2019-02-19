/*
    RPG Paper Maker Copyright (C) 2017-2019 Marie Laporte

    This file is part of RPG Paper Maker.

    RPG Paper Maker is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    RPG Paper Maker is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SYSTEMLOOT_H
#define SYSTEMLOOT_H

#include <QMetaType>
#include "superlistitem.h"
#include "lootkind.h"
#include "primitivevalue.h"

// -------------------------------------------------------
//
//  CLASS SystemLoot
//
//  A particulary loot (datas).
//
// -------------------------------------------------------

class SystemLoot : public SuperListItem
{
public:
    static const QString JSON_KIND;
    static const QString JSON_NUMBER;
    static const QString JSON_PROBABILITY;
    static const QString JSON_INITIAL;
    static const QString JSON_FINAL;

    SystemLoot();
    SystemLoot(int i, QString n, LootKind kind, PrimitiveValue *number,
        PrimitiveValue *probability, PrimitiveValue *initialLevel,
        PrimitiveValue *finalLevel);
    virtual ~SystemLoot();
    LootKind kind() const;
    void setKind(LootKind k);
    PrimitiveValue * number() const;
    PrimitiveValue * probability() const;
    PrimitiveValue * initialLevel() const;
    PrimitiveValue * finalLevel() const;

    void updateName();

    virtual bool openDialog();
    virtual SuperListItem* createCopy() const;
    virtual void setCopy(const SystemLoot &loot);
    virtual QList<QStandardItem *> getModelRow() const;
    virtual void read(const QJsonObject &json);
    virtual void write(QJsonObject &json) const;

protected:
    LootKind m_kind;
    PrimitiveValue *m_number;
    PrimitiveValue *m_probability;
    PrimitiveValue *m_initialLevel;
    PrimitiveValue *m_finalLevel;
};

Q_DECLARE_METATYPE(SystemLoot)

#endif // SYSTEMLOOT_H
