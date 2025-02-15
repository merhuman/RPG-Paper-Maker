/*
    RPG Paper Maker Copyright (C) 2017-2022 Wano

    RPG Paper Maker engine is under proprietary license.
    This source code is also copyrighted.

    Use Commercial edition for commercial use of your games.
    See RPG Paper Maker EULA here:
        http://rpg-paper-maker.com/index.php/eula.
*/

#include "dialogsystemcharacteristic.h"
#include "ui_dialogsystemcharacteristic.h"
#include "rpm.h"
#include "common.h"

// -------------------------------------------------------
//
//  CONSTRUCTOR / DESTRUCTOR / GET / SET
//
// -------------------------------------------------------

DialogSystemCharacteristic::DialogSystemCharacteristic(SystemCharacteristic
    &characteristic, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSystemCharacteristic),
    m_characteristic(characteristic)
{
    ui->setupUi(this);
    this->initialize();
    this->translate();
}

DialogSystemCharacteristic::~DialogSystemCharacteristic() {
    delete ui;
}

SystemCharacteristic & DialogSystemCharacteristic::characteristic() const {
    return m_characteristic;
}

// -------------------------------------------------------
//
//  INTERMEDIARY FUNCTIONS
//
// -------------------------------------------------------

void DialogSystemCharacteristic::initialize() {
    switch(m_characteristic.kind()) {
    case CharacteristicKind::IncreaseDecrease:
        ui->radioButtonBuff->setChecked(true);
        break;
    case CharacteristicKind::AllowForbidEquip:
        ui->tabWidget->setCurrentIndex(1);
        ui->radioButtonEquip->setChecked(true);
        break;
    case CharacteristicKind::AllowForbidChange:
        ui->tabWidget->setCurrentIndex(1);
        ui->radioButtonEquipmentChange->setChecked(true);
        break;
    case CharacteristicKind::BeginEquipment:
        ui->tabWidget->setCurrentIndex(1);
        ui->radioButtonBeginEquipment->setChecked(true);
        break;
    case CharacteristicKind::Element:
        ui->tabWidget->setCurrentIndex(1);
        ui->radioButtonElementID->setChecked(true);
        break;
    case CharacteristicKind::Script:
        ui->tabWidget->setCurrentIndex(2);
        ui->radioButtonScript->setChecked(true);
        break;
    }

    // Buff
    int index = m_characteristic.isIncreaseDecrease() ? 0 : 1;
    ui->comboBoxIncreaseDecrease->addItem(RPM::translate(Translations::INCREASE));
    ui->comboBoxIncreaseDecrease->addItem(RPM::translate(Translations::DECREASE));
    ui->comboBoxIncreaseDecrease->setCurrentIndex(index);
    index = m_characteristic.increaseDecreaseKind()->id();
    ui->comboBoxIncreaseDecreaseKind->addItems(RPM
        ::ENUM_TO_STRING_INCREASE_DECREASE_KIND);
    ui->comboBoxIncreaseDecreaseKind->setCurrentIndex(index);
    ui->panelPrimitiveValueStatValue->initializeDataBaseAndUpdate(
        m_characteristic.statValueID());
    ui->panelPrimitiveValueElementRes->initializeDataBaseAndUpdate(
        m_characteristic.elementResID());
    ui->panelPrimitiveValueStatusRes->initializeDataBaseAndUpdate(
        m_characteristic.statusResID());
    ui->panelPrimitiveValueCurrencyGain->initializeDataBaseAndUpdate(
        m_characteristic.currencyGainID());
    ui->panelPrimitiveValueSkillCost->initializeDataBaseAndUpdate(
        m_characteristic.skillCostID());
    index = m_characteristic.isAllSkillCost() ? 0 : 1;
    ui->comboBoxSkillCostAll->addItem(RPM::translate(Translations::ALL));
    ui->comboBoxSkillCostAll->addItem(RPM::translate(Translations::SPECIFIC));
    ui->comboBoxSkillCostAll->setCurrentIndex(index);
    ui->widgetVariable->initializeSuper(m_characteristic.variableID());
    ui->comboBoxOperation->setCurrentIndex(m_characteristic.operation() ? 0 : 1);
    ui->panelPrimitiveValue->initializeNumberVariableAndUpdate(m_characteristic.value());
    index = m_characteristic.unit() ? 0 : 1;
    ui->comboBoxUnit->addItem(RPM::translate(Translations::FIX));
    ui->comboBoxUnit->setCurrentIndex(index);

    // Character
    index = m_characteristic.isAllowEquip() ? 0 : 1;
    ui->comboBoxEquipAllowForbid->addItem(RPM::translate(Translations::ALLOW));
    ui->comboBoxEquipAllowForbid->addItem(RPM::translate(Translations::FORBID));
    ui->comboBoxEquipAllowForbid->setCurrentIndex(index);
    ui->panelPrimitiveValueArmorKindID->hide();
    index = m_characteristic.isAllowEquipWeapon() ? 0 : 1;
    ui->comboBoxEquipWeaponArmor->addItem(RPM::translate(Translations::WEAPON));
    ui->comboBoxEquipWeaponArmor->addItem(RPM::translate(Translations::ARMOR));
    ui->comboBoxEquipWeaponArmor->setCurrentIndex(index);
    ui->panelPrimitiveValueWeaponKindID->initializeDataBaseAndUpdate(
        m_characteristic.equipWeaponTypeID());
    ui->panelPrimitiveValueArmorKindID->initializeDataBaseAndUpdate(
        m_characteristic.equipArmorTypeID());
    index = m_characteristic.isAllowChangeEquipment() ? 0 : 1;
    ui->comboBoxEquipmentChange->addItem(RPM::translate(Translations::ALLOW));
    ui->comboBoxEquipmentChange->addItem(RPM::translate(Translations::FORBID));
    ui->comboBoxEquipmentChange->setCurrentIndex(index);
    ui->panelPrimitiveValueEquipmentChangeID->initializeDataBaseAndUpdate(
        m_characteristic.changeEquipmentID());
    ui->panelPrimitiveValueBeginEquipmentID->initializeDataBaseAndUpdate(
        m_characteristic.beginEquipmentID());
    index = m_characteristic.isBeginWeapon() ? 0 : 1;
    ui->comboBoxBeginWeaponArmor->addItem(RPM::translate(Translations::WEAPON));
    ui->comboBoxBeginWeaponArmor->addItem(RPM::translate(Translations::ARMOR));
    ui->comboBoxBeginWeaponArmor->setCurrentIndex(index);
    m_characteristic.updateModelBeginWeaponArmor();
    ui->panelPrimitiveValueBeginWeaponArmorID->initializeDataBaseAndUpdate(
        m_characteristic.beginWeaponArmorID());
    connect(ui->panelPrimitiveValueBeginEquipmentID, SIGNAL(numberUpdated(int)),
        this, SLOT(on_beginWeaponArmorNumberChanged(int)));
    ui->panelPrimitiveElementID->initializeDataBaseAndUpdate(m_characteristic.elementID());

    // Script
    ui->panelPrimitiveValueScript->initializeMessageAndUpdate(m_characteristic
        .script(), true);
}

// -------------------------------------------------------

void DialogSystemCharacteristic::setRadioCharacters() {
    ui->radioButtonBuff->setChecked(false);
    ui->radioButtonScript->setChecked(false);
}

// -------------------------------------------------------

void DialogSystemCharacteristic::uncheckAllRadiosCharacters() {
    ui->radioButtonEquip->setAutoExclusive(false);
    ui->radioButtonEquipmentChange->setAutoExclusive(false);
    ui->radioButtonBeginEquipment->setAutoExclusive(false);
    ui->radioButtonElementID->setAutoExclusive(false);
    ui->radioButtonEquip->setChecked(false);
    ui->radioButtonEquipmentChange->setChecked(false);
    ui->radioButtonBeginEquipment->setChecked(false);
    ui->radioButtonElementID->setChecked(false);
    ui->radioButtonEquip->setAutoExclusive(true);
    ui->radioButtonEquipmentChange->setAutoExclusive(true);
    ui->radioButtonBeginEquipment->setAutoExclusive(true);
    ui->radioButtonElementID->setAutoExclusive(true);
}

//-------------------------------------------------

void DialogSystemCharacteristic::translate()
{
    this->setWindowTitle(RPM::translate(Translations::SET_CHARACTERISTIC) + RPM
        ::DOT_DOT_DOT);
    ui->labelWith->setText(RPM::translate(Translations::WITH));
    ui->tabWidget->setTabText(0, RPM::translate(Translations::BUFF));
    ui->tabWidget->setTabText(1, RPM::translate(Translations::CHARACTER_SPECIFIC));
    ui->tabWidget->setTabText(2, RPM::translate(Translations::OTHER));
    ui->radioButtonBuff->setText(RPM::translate(Translations::BUFF) + RPM::COLON);
    ui->radioButtonEquip->setText(RPM::translate(Translations::EQUIP) + RPM::COLON);
    ui->radioButtonEquipmentChange->setText(RPM::translate(Translations
        ::CHANGE_EQUIPMENT) + RPM::COLON);
    ui->radioButtonBeginEquipment->setText(RPM::translate(Translations::BEGIN_EQUIPMENT)
        + RPM::COLON);
    ui->radioButtonElementID->setText(RPM::translate(Translations::ELEMENT_ID) + RPM::COLON);
    ui->radioButtonScript->setText(RPM::translate(Translations::SCRIPT) + RPM::COLON);
    RPM::get()->translations()->translateButtonBox(ui->buttonBox);
}

// -------------------------------------------------------
//
//  SLOTS
//
// -------------------------------------------------------

void DialogSystemCharacteristic::on_radioButtonBuff_toggled(bool checked) {
    if (checked) {
        m_characteristic.setKind(CharacteristicKind::IncreaseDecrease);
        uncheckAllRadiosCharacters();
        ui->radioButtonScript->setChecked(false);
    }

    // Enable
    ui->comboBoxIncreaseDecrease->setEnabled(checked);
    ui->comboBoxIncreaseDecreaseKind->setEnabled(checked);
    ui->panelPrimitiveValueStatValue->setEnabled(checked);
    ui->panelPrimitiveValueElementRes->setEnabled(checked);
    ui->panelPrimitiveValueStatusRes->setEnabled(checked);
    ui->panelPrimitiveValueCurrencyGain->setEnabled(checked);
    ui->panelPrimitiveValueSkillCost->setEnabled(checked);
    ui->comboBoxSkillCostAll->setEnabled(checked);
    ui->widgetVariable->setEnabled(checked);
    ui->comboBoxOperation->setEnabled(checked);
    ui->panelPrimitiveValue->setEnabled(checked);
    ui->comboBoxUnit->setEnabled(checked);
}

// -------------------------------------------------------

void DialogSystemCharacteristic::on_radioButtonEquip_toggled(bool checked) {
    m_characteristic.setKind(CharacteristicKind::AllowForbidEquip);

    if (checked) {
        setRadioCharacters();
    }

    // Enable
    ui->comboBoxEquipAllowForbid->setEnabled(checked);
    ui->comboBoxEquipWeaponArmor->setEnabled(checked);
    ui->panelPrimitiveValueWeaponKindID->setEnabled(checked);
    ui->panelPrimitiveValueArmorKindID->setEnabled(checked);
}

// -------------------------------------------------------

void DialogSystemCharacteristic::on_radioButtonEquipmentChange_toggled(bool
    checked)
{
    if (checked) {
        m_characteristic.setKind(CharacteristicKind::AllowForbidChange);
        setRadioCharacters();
    }

    // Enable
    ui->comboBoxEquipmentChange->setEnabled(checked);
    ui->panelPrimitiveValueEquipmentChangeID->setEnabled(checked);
}

// -------------------------------------------------------

void DialogSystemCharacteristic::on_radioButtonBeginEquipment_toggled(bool
    checked)
{
    if (checked) {
        m_characteristic.setKind(CharacteristicKind::BeginEquipment);
        setRadioCharacters();
    }

    // Enable
    ui->panelPrimitiveValueBeginEquipmentID->setEnabled(checked);
    ui->labelWith->setEnabled(checked);
    ui->comboBoxBeginWeaponArmor->setEnabled(checked);
    ui->panelPrimitiveValueBeginWeaponArmorID->setEnabled(checked);
}

// -------------------------------------------------------

void DialogSystemCharacteristic::on_radioButtonElementID_toggled(bool checked)
{
    if (checked) {
        m_characteristic.setKind(CharacteristicKind::Element);
        setRadioCharacters();
    }

    // Enable
    ui->panelPrimitiveElementID->setEnabled(checked);
}

// -------------------------------------------------------

void DialogSystemCharacteristic::on_radioButtonScript_toggled(bool checked) {
    if (checked) {
        m_characteristic.setKind(CharacteristicKind::Script);
        ui->radioButtonBuff->setChecked(false);
        uncheckAllRadiosCharacters();
    }

    // Enable
    ui->panelPrimitiveValueScript->setEnabled(checked);
}

// -------------------------------------------------------

void DialogSystemCharacteristic::on_comboBoxIncreaseDecrease_currentIndexChanged(
    int index)
{
    m_characteristic.setIsIncreaseDecrease(index == 0);
}

// -------------------------------------------------------

void DialogSystemCharacteristic::
    on_comboBoxIncreaseDecreaseKind_currentIndexChanged(int index)
{
    m_characteristic.increaseDecreaseKind()->setId(index);

    ui->panelPrimitiveValueStatValue->hide();
    ui->panelPrimitiveValueElementRes->hide();
    ui->panelPrimitiveValueStatusRes->hide();
    ui->panelPrimitiveValueCurrencyGain->hide();
    ui->panelPrimitiveValueSkillCost->hide();
    ui->comboBoxSkillCostAll->hide();
    ui->widgetVariable->hide();

    switch(static_cast<IncreaseDecreaseKind>(index)) {
    case IncreaseDecreaseKind::StatValue:
        ui->panelPrimitiveValueStatValue->show();
        break;
    case IncreaseDecreaseKind::ElementRes:
        ui->panelPrimitiveValueElementRes->show();
        break;
    case IncreaseDecreaseKind::StatusRes:
        ui->panelPrimitiveValueStatusRes->show();
        break;
    case IncreaseDecreaseKind::CurrencyGain:
        ui->panelPrimitiveValueCurrencyGain->show();
        break;
    case IncreaseDecreaseKind::SkillCost:
        ui->comboBoxSkillCostAll->show();
        if (!m_characteristic.isAllSkillCost()) {
            ui->panelPrimitiveValueSkillCost->show();
        }
        break;
    case IncreaseDecreaseKind::Variable:
        ui->widgetVariable->show();
        break;
    default:
        break;
    }
}

// -------------------------------------------------------

void DialogSystemCharacteristic::on_comboBoxSkillCostAll_currentIndexChanged(int
    index)
{
    m_characteristic.setIsAllSkillCost(index == 0);

    if (index == 0) {
        ui->panelPrimitiveValueSkillCost->hide();
    } else {
        ui->panelPrimitiveValueSkillCost->show();
    }
}

// -------------------------------------------------------

void DialogSystemCharacteristic::on_comboBoxOperation_currentIndexChanged(int
    index)
{
    m_characteristic.setOperation(index == 0);
}

// -------------------------------------------------------

void DialogSystemCharacteristic::on_comboBoxUnit_currentIndexChanged(int index) {
    m_characteristic.setUnit(index == 0);
}

// -------------------------------------------------------

void DialogSystemCharacteristic::on_comboBoxEquipAllowForbid_currentIndexChanged(
    int index)
{
    m_characteristic.setIsAllowEquip(index == 0);
}

// -------------------------------------------------------

void DialogSystemCharacteristic::on_comboBoxEquipWeaponArmor_currentIndexChanged(
    int index)
{
    m_characteristic.setIsAllowEquipWeapon(index == 0);

    ui->panelPrimitiveValueWeaponKindID->hide();
    ui->panelPrimitiveValueArmorKindID->hide();
    if (index == 0) {
        ui->panelPrimitiveValueWeaponKindID->show();
    } else {
        ui->panelPrimitiveValueArmorKindID->show();
    }
}

// -------------------------------------------------------

void DialogSystemCharacteristic::on_comboBoxEquipmentChange_currentIndexChanged(
    int index)
{
    m_characteristic.setIsAllowChangeEquipment(index == 0);
}

// -------------------------------------------------------

void DialogSystemCharacteristic::on_comboBoxBeginWeaponArmor_currentIndexChanged(
    int index)
{
    m_characteristic.setIsBeginWeapon(index == 0);
    m_characteristic.updateModelBeginWeaponArmor();
    ui->panelPrimitiveValueBeginWeaponArmorID->clearDataBase();
}

// -------------------------------------------------------

void DialogSystemCharacteristic::on_beginWeaponArmorNumberChanged(int) {
    m_characteristic.updateModelBeginWeaponArmor();
    ui->panelPrimitiveValueBeginWeaponArmorID->clearDataBase();
}
