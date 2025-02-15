/*
    RPG Paper Maker Copyright (C) 2017-2022 Wano

    RPG Paper Maker engine is under proprietary license.
    This source code is also copyrighted.

    Use Commercial edition for commercial use of your games.
    See RPG Paper Maker EULA here:
        http://rpg-paper-maker.com/index.php/eula.
*/

#ifndef WIDGETTREESTRUCTURE_H
#define WIDGETTREESTRUCTURE_H

#include "widgetsupertree.h"
#include "primitivevalue.h"
#include "systemcustomstructureelement.h"

// -------------------------------------------------------
//
//  CLASS WidgetTreeStructure
//
//  A widget representing the custom structure or list.
//
// -------------------------------------------------------

class WidgetTreeStructure : public WidgetSuperTree
{
    Q_OBJECT
public:
    WidgetTreeStructure();
    explicit WidgetTreeStructure(QWidget *parent = nullptr);
    ~WidgetTreeStructure();

    static bool itemLessThan(const QStandardItem *item1, const QStandardItem
        *item2);

    QStandardItem * first() const;
    QStandardItem * last() const;
    QStandardItemModel * getParentModel(QStandardItem *selected,
        SystemCustomStructureElement *element = nullptr) const;
    SystemCustomStructure * getCustomStructureList(QStandardItem *selected,
        SystemCustomStructureElement *element = nullptr) const;
    QList<QStandardItem *> getAllSelected() const;
    QStandardItem * getRootOfStructure(QStandardItem *selected) const;
    void initializeNodes(PrimitiveValue *v);
    void removeStructureModel();
    void initializeNodesCustom(QStandardItem *parent, SystemCustomStructure
        *custom);
    void initializeNodesElement(QStandardItem *parent,
        SystemCustomStructureElement *element = nullptr);
    void selectChildren(QStandardItem *item, QItemSelectionModel::SelectionFlag
        flag = QItemSelectionModel::Select);
    void selectChildrenOnly(QStandardItem *item, QItemSelectionModel
        ::SelectionFlag flag = QItemSelectionModel::Select);
    void removeElementParentModel(QStandardItem *item,
        SystemCustomStructureElement *element);
    void removeItem(QStandardItem *item, PrimitiveValueKind kind,
        SystemCustomStructureElement *element);
    void addItem(QStandardItem *item, SystemCustomStructureElement *element);
    void addItemTree(QStandardItem *item, SystemCustomStructureElement *element);

    virtual QStandardItem * getSelected() const;
    virtual void updateKeyboardUpDown(int offset);

protected:
    PrimitiveValue *m_prim;
    SystemCustomStructureElement *m_element;
    QStandardItemModel *m_completeList;

    virtual void newItem(QStandardItem *selected);
    virtual void editItem(QStandardItem *selected);
    virtual void copyItem(QStandardItem *selected);
    virtual void pasteItem(QStandardItem *selected);
    virtual void deleteItem(QStandardItem *selected);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void updateContextMenu();

public slots:
    void onSelectionChanged(QModelIndex index, QModelIndex indexBefore);
};

#endif // WIDGETTREESTRUCTURE_H
