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

#include "dialogsystemloot.h"
#include "ui_dialogsystemloot.h"
#include "rpm.h"

// -------------------------------------------------------
//
//  CONSTRUCTOR / DESTRUCTOR / GET / SET
//
// -------------------------------------------------------

DialogSystemLoot::DialogSystemLoot(SystemLoot &loot, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSystemLoot),
    m_loot(loot)
{
    ui->setupUi(this);
    
    // Initilize comboBoxes
    SuperListItem::fillComboBox(ui->comboBoxItem, RPM::get()->project()
        ->gameDatas()->itemsDatas()->model());
    SuperListItem::fillComboBox(ui->comboBoxWeapon, RPM::get()->project()
        ->gameDatas()->weaponsDatas()->model());
    SuperListItem::fillComboBox(ui->comboBoxArmor, RPM::get()->project()
        ->gameDatas()->armorsDatas()->model());

    // Connect
    connect(ui->radioButtonItem, SIGNAL(toggled(bool)), this, SLOT(
        on_radioButtonItemToggled(bool)));
    connect(ui->radioButtonWeapon, SIGNAL(toggled(bool)), this, SLOT(
        on_radioButtonWeaponToggled(bool)));
    connect(ui->radioButtonArmor, SIGNAL(toggled(bool)), this, SLOT(
        on_radioButtonArmorToggled(bool)));
    connect(ui->comboBoxItem, SIGNAL(currentIndexChanged(int)), this, SLOT(
        on_comboBoxItemCurrentIndexChanged(int)));
    connect(ui->comboBoxWeapon, SIGNAL(currentIndexChanged(int)), this, SLOT(
        on_comboBoxWeaponCurrentIndexChanged(int)));
    connect(ui->comboBoxArmor, SIGNAL(currentIndexChanged(int)), this, SLOT(
        on_comboBoxArmorCurrentIndexChanged(int)));

    initialize();
}

DialogSystemLoot::~DialogSystemLoot()
{
    delete ui;
}

// -------------------------------------------------------
//
//  INTERMEDIARY FUNCTIONS
//
// -------------------------------------------------------

void DialogSystemLoot::initialize() {

    // Numbers
    ui->widgetVariableConstantNumber->initializeNumberVariable();
    ui->widgetVariableConstantNumber->initializeModel(m_loot.number());
    ui->widgetVariableConstantNumber->updateModel();
    ui->widgetVariableConstantProbability->initializeNumberVariable();
    ui->widgetVariableConstantProbability->initializeModel(m_loot.probability());
    ui->widgetVariableConstantProbability->updateModel();
    ui->panelPrimitiveValueInit->initializeNumberVariable();
    ui->panelPrimitiveValueInit->initializeModel(m_loot.initialLevel());
    ui->panelPrimitiveValueInit->updateModel();
    ui->panelPrimitiveValueFinal->initializeNumberVariable();
    ui->panelPrimitiveValueFinal->initializeModel(m_loot.finalLevel());
    ui->panelPrimitiveValueFinal->updateModel();

    // Loots
    QStandardItem* item;
    switch(m_loot.kind()){
    case LootKind::Item:
        item = RPM::get()->project()->gameDatas()->itemsDatas()->model()
                ->invisibleRootItem();
        ui->comboBoxItem->setCurrentIndex(
                    SuperListItem::getIndexById(item, m_loot.id()));
        ui->radioButtonItem->setChecked(true);
        break;
    case LootKind::Weapon:
        item = RPM::get()->project()->gameDatas()->weaponsDatas()->model()
                ->invisibleRootItem();
        ui->comboBoxWeapon->setCurrentIndex(
                    SuperListItem::getIndexById(item, m_loot.id()));
        ui->radioButtonWeapon->setChecked(true);
        break;
    case LootKind::Armor:
        item = RPM::get()->project()->gameDatas()->armorsDatas()->model()
                ->invisibleRootItem();
        ui->comboBoxArmor->setCurrentIndex(
                    SuperListItem::getIndexById(item, m_loot.id()));
        ui->radioButtonArmor->setChecked(true);
        break;
    }
}

// -------------------------------------------------------

void DialogSystemLoot::radioChanged(bool checked, LootKind kind){

    // Getting all the informations according to loot kind
    QStandardItemModel* model = nullptr;
    QComboBox* combo = nullptr;
    switch (kind){
    case LootKind::Item:
        combo = ui->comboBoxItem;
        model = RPM::get()->project()->gameDatas()->itemsDatas()->model();
        break;
    case LootKind::Weapon:
        combo = ui->comboBoxWeapon;
        model = RPM::get()->project()->gameDatas()->weaponsDatas()->model();
        break;
    case LootKind::Armor:
        combo = ui->comboBoxArmor;
        model = RPM::get()->project()->gameDatas()->armorsDatas()->model();
        break;
    }

    // Modifying loot properties
    combo->setEnabled(checked);
    if (checked){
        m_loot.setKind(kind);
        SuperListItem* super = (SuperListItem*)model
                ->item(combo->currentIndex())->data().value<quintptr>();
        m_loot.setId(super->id());
        m_loot.setName(super->name());
    }
}

// -------------------------------------------------------
//
//  SLOTS
//
// -------------------------------------------------------

void DialogSystemLoot::on_radioButtonItemToggled(bool checked){
    radioChanged(checked, LootKind::Item);
}

// -------------------------------------------------------

void DialogSystemLoot::on_radioButtonWeaponToggled(bool checked){
    radioChanged(checked, LootKind::Weapon);
}

// -------------------------------------------------------

void DialogSystemLoot::on_radioButtonArmorToggled(bool checked){
    radioChanged(checked, LootKind::Armor);
}

// -------------------------------------------------------

void DialogSystemLoot::on_comboBoxItemCurrentIndexChanged(int){
    radioChanged(true, LootKind::Item);
}

// -------------------------------------------------------

void DialogSystemLoot::on_comboBoxWeaponCurrentIndexChanged(int){
    radioChanged(true, LootKind::Weapon);
}

// -------------------------------------------------------

void DialogSystemLoot::on_comboBoxArmorCurrentIndexChanged(int){
    radioChanged(true, LootKind::Armor);
}
