/*
    RPG Paper Maker Copyright (C) 2017-2022 Wano

    RPG Paper Maker engine is under proprietary license.
    This source code is also copyrighted.

    Use Commercial edition for commercial use of your games.
    See RPG Paper Maker EULA here:
        http://rpg-paper-maker.com/index.php/eula.
*/

#include "paneltroopreaction.h"
#include "ui_paneltroopreaction.h"
#include "rpm.h"

// -------------------------------------------------------
//
//  CONSTRUCTOR / DESTRUCTOR / GET / SET
//
// -------------------------------------------------------

PanelTroopReaction::PanelTroopReaction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PanelTroopReaction),
    m_reaction(nullptr)
{
    ui->setupUi(this);
    ui->comboBoxFrequency->addItems(RPM::ENUM_TO_STRING_TROOP_REACTION_FREQUENCY_KIND);
    this->translate();
}

PanelTroopReaction::~PanelTroopReaction()
{
    delete ui;
}

// -------------------------------------------------------
//
//  INTERMEDIARY FUNCTIONS
//
// -------------------------------------------------------

void PanelTroopReaction::initialize(SystemTroopReaction *reaction, QStandardItemModel
    *troopMonstersList)
{
    m_reaction = reaction;
    if (m_reaction == nullptr)
    {
        ui->lineEditName->setText("");
        ui->comboBoxFrequency->setCurrentIndex(0);
        ui->widgetTreeCommands->initializeModel(nullptr);
    } else
    {
        ui->lineEditName->setText(m_reaction->name());
        ui->comboBoxFrequency->setCurrentIndex(static_cast<int>(m_reaction
            ->frequency()));
        ui->widgetTreeCommands->initializeModel(m_reaction->modelCommands());
        ui->widgetTreeCommands->initializeTroopMonstersList(troopMonstersList);
    }
}

// -------------------------------------------------------

void PanelTroopReaction::translate()
{
    ui->labelName->setText(RPM::translate(Translations::NAME) + RPM::COLON);
    ui->labelConditions->setText(RPM::translate(Translations::CONDITIONS) + RPM::COLON);
    ui->labelFrequency->setText(RPM::translate(Translations::FREQUENCY) + RPM::COLON);
}

// -------------------------------------------------------
//
//  SLOTS
//
// -------------------------------------------------------

void PanelTroopReaction::on_lineEditName_textEdited(const QString &text)
{
    if (m_reaction != nullptr)
    {
        m_reaction->setName(text);
        emit nameChanged();
    }
}

// -------------------------------------------------------

void PanelTroopReaction::on_pushButtonCondition_clicked()
{
    m_reaction->conditions()->openDialog();
}

// -------------------------------------------------------

void PanelTroopReaction::on_comboBoxFrequency_currentIndexChanged(int index)
{
    if (m_reaction != nullptr)
    {
        m_reaction->setFrequency(static_cast<TroopReactionFrequencyKind>(index));
    }
}
