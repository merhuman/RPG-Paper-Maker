/*
    RPG Paper Maker Copyright (C) 2017-2022 Wano

    RPG Paper Maker engine is under proprietary license.
    This source code is also copyrighted.

    Use Commercial edition for commercial use of your games.
    See RPG Paper Maker EULA here:
        http://rpg-paper-maker.com/index.php/eula.
*/

#include <QMimeData>
#include "dialogcommandplaysong.h"
#include "ui_dialogcommandplaysong.h"
#include "rpm.h"

// -------------------------------------------------------
//
//  CONSTRUCTOR / DESTRUCTOR / GET / SET
//
// -------------------------------------------------------

DialogCommandPlaySong::DialogCommandPlaySong(QString title, SongKind kind,
    EventCommand *command, QStandardItemModel *properties, QStandardItemModel
    *parameters, EventCommandKind eventCommandKind, QWidget *parent) :
    DialogCommand(parent),
    m_kind(kind),
    m_eventCommandKind(eventCommandKind),
    m_song(nullptr),
    ui(new Ui::DialogCommandPlaySong)
{
    ui->setupUi(this);
    
    this->setWindowTitle(title);
    ui->widget->setSongKind(kind);
    ui->widget->initializePrimitives(parameters, properties);
    ui->panelPrimitiveValueSongID->initializeNumber(parameters, properties);
    ui->widget->showAvailableContent(RPM::get()->engineSettings()
        ->showAvailableContent());

    if (command != nullptr) {
        initialize(command);
    }
    this->setAcceptDrops(true);
    this->translate();
}

DialogCommandPlaySong::DialogCommandPlaySong(QString title, SystemPlaySong
    *song) :
    DialogCommandPlaySong(title, song->kind(), nullptr, song->properties(), song
        ->parameters())
{
    EventCommand command;
    m_song = song;
    song->toEventCommand(command, this->getCommandKind());
    initialize(&command);
}

DialogCommandPlaySong::~DialogCommandPlaySong() {
    delete ui;
}

EventCommandKind DialogCommandPlaySong::getCommandKind() const
{
    if (m_eventCommandKind == EventCommandKind::None)
    {
        switch(m_kind) {
        case SongKind::Music:
            return EventCommandKind::PlayMusic;
        case SongKind::BackgroundSound:
            return EventCommandKind::PlayBackgroundSound;
        case SongKind::Sound:
            return EventCommandKind::PlayASound;
        case SongKind::MusicEffect:
            return EventCommandKind::PlayMusicEffect;
        default:
            return EventCommandKind::None;
        }
    } else
    {
        return m_eventCommandKind;
    }
}

// -------------------------------------------------------
//
//  INTERMEDIARY FUNCTIONS
//
// -------------------------------------------------------

void DialogCommandPlaySong::translate()
{
    ui->checkBoxSongID->setText(RPM::translate(Translations::SELECT_SONG_ID) +
        RPM::COLON);
    RPM::get()->translations()->translateButtonBox(ui->buttonBox);
}

void DialogCommandPlaySong::initialize(EventCommand* command) {
    int i = 0;

    ui->checkBoxSongID->setChecked(command->valueCommandAt(i++) == "1");
    ui->panelPrimitiveValueSongID->initializeCommand(command, i);
    ui->widget->initialize(command, i);
}

// -------------------------------------------------------

void DialogCommandPlaySong::getCommandList(QVector<QString> &command) const
{
    command.append(ui->checkBoxSongID->isChecked() ? "1" : "0");
    ui->panelPrimitiveValueSongID->getCommand(command);
    ui->widget->getCommand(command);
}

// -------------------------------------------------------

EventCommand* DialogCommandPlaySong::getCommand() const {
    QVector<QString> command;
    this->getCommandList(command);
    return new EventCommand(getCommandKind(), command);
}

// -------------------------------------------------------
//
//  VIRTUAL FUNCTIONS
//
// -------------------------------------------------------

void DialogCommandPlaySong::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

// -------------------------------------------------------

void DialogCommandPlaySong::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    QStringList list;
    for (int i = 0, l = urls.size(); i < l; i++)
    {
        list << urls.at(i).toLocalFile();
    }
    ui->widget->dropFiles(list);
}

// -------------------------------------------------------
//
//  SLOTS
//
// -------------------------------------------------------

void DialogCommandPlaySong::accept() {
    RPM::get()->project()->writeSongsDatas();

    if (m_song != nullptr) {
        m_song->setIsSelectedByID(ui->checkBoxSongID->isChecked());
        m_song->valueID()->setCopy(*ui->panelPrimitiveValueSongID->model());
        ui->widget->updatePlaySong(m_song);
        m_song->updateName();
    }

    QDialog::accept();
}

// -------------------------------------------------------

void DialogCommandPlaySong::reject() {
    RPM::get()->project()->readSongsDatas();
    QDialog::reject();
}

// -------------------------------------------------------

void DialogCommandPlaySong::on_checkBoxSongID_toggled(bool checked) {
    ui->panelPrimitiveValueSongID->setEnabled(checked);
}
