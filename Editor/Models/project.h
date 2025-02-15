/*
    RPG Paper Maker Copyright (C) 2017-2022 Wano

    RPG Paper Maker engine is under proprietary license.
    This source code is also copyrighted.

    Use Commercial edition for commercial use of your games.
    See RPG Paper Maker EULA here:
        http://rpg-paper-maker.com/index.php/eula.
*/

#ifndef PROJECT_H
#define PROJECT_H

#include "map.h"
#include "gamedatas.h"
#include "treemapdatas.h"
#include "langsdatas.h"
#include "scriptsdatas.h"
#include "picturesdatas.h"
#include "videosdatas.h"
#include "songsdatas.h"
#include "shapesdatas.h"
#include "fontsdatas.h"
#include "keyboarddatas.h"
#include "specialelementsdatas.h"
#include "oskind.h"

// -------------------------------------------------------
//
//  CLASS Project
//
//  All the datas of a project.
//
// -------------------------------------------------------

class Project
{

public:
    Project();
    virtual ~Project();
    static const QString ENGINE_VERSION;
    static const QString LAST_BUILD_DATE;
    static const int MAX_PROJECTS_NUMBER;
    void setDefault();
    void setDefaultTranslations();
    QString pathCurrentProject() const;
    QString pathCurrentProjectApp() const;
    void setPathCurrentProject(QString s);
    void setPathCurrentProjectApp(QString s);
    Map* currentMap(bool force = false) const;
    void setCurrentMap(Map* m);
    MapProperties * currentMapProperties() const;
    void setCurrentMapProperties(MapProperties *currentMapProperties);
    SystemCommonObject * currentObject() const;
    void setCurrentObject(SystemCommonObject *object);
    QStandardItemModel * currentParameters() const;
    void setCurrentParameters(QStandardItemModel *parameters);
    GameDatas* gameDatas() const;
    TreeMapDatas* treeMapDatas() const;
    LangsDatas* langsDatas() const;
    ScriptsDatas* scriptsDatas() const;
    PicturesDatas* picturesDatas() const;
    VideosDatas * videosDatas() const;
    SongsDatas* songsDatas() const;
    ShapesDatas * shapesDatas() const;
    FontsDatas * fontsDatas() const;
    KeyBoardDatas* keyBoardDatas() const;
    SpecialElementsDatas* specialElementsDatas() const;
    QString version() const;

    QStandardItemModel * currentObjectProperties() const;

    bool read(QString path);
    void readAll();
    bool readVersion();
    bool readOS();
    OSKind getProjectOS();
    QString getPathMapsToSave() const;
    void readMapsToSave(QSet<int> &mapsToSave) const;
    void writeMapsToSave(QSet<int> &mapsToSave) const;
    static OSKind getComputerOS();
    bool copyOSFiles();
    void removeOSFiles();
    void readGameDatas();
    void readLangsDatas();
    void readTreeMapDatas();
    void readScriptsDatas();
    void readKeyBoardDatas();
    void readPicturesDatas();
    void readVideosDatas();
    void readSongsDatas();
    void readShapesDatas();
    void readFontsDatas();
    void readSpecialsDatas();
    void readSystemDatas();
    void readBattleSystemDatas();
    void readTilesetsDatas();
    void readCommonEvents();
    void readTitleScreenGameOver();
    void readDlcs();
    void write(QString path);
    void writeAll();
    void writeGameDatas();
    void writeLangsDatas();
    void writeTreeMapDatas();
    void writeScriptsDatas();
    void writeKeyBoardDatas();
    void writePicturesDatas();
    void writeVideosDatas();
    void writeSongsDatas();
    void writeShapesDatas();
    void writeFontsDatas();
    void writeSpecialsDatas();
    void writeSystemDatas();
    void writeBattleSystemDatas();
    void writeTilesetsDatas();
    void writeCommonEvents();
    void writeTitleScreenGameOver();
    void writeDlcs();
    void saveCurrentMap();

    QString createRPMFile();
    bool isHeroDefined() const;

private:
    QString p_pathCurrentProject;
    QString p_pathCurrentProjectApp;
    Map* p_currentMap;
    Map* p_currentMapConfig;
    MapProperties *m_currentMapProperties;
    SystemCommonObject *m_currentObject;
    QStandardItemModel *m_currentParameters;
    GameDatas* p_gameDatas;
    TreeMapDatas* m_treeMapDatas;
    LangsDatas* m_langsDatas;
    ScriptsDatas* m_scriptsDatas;
    PicturesDatas* m_picturesDatas;
    VideosDatas *m_videosDatas;
    SongsDatas* m_songsDatas;
    ShapesDatas * m_shapesDatas;
    FontsDatas *m_fontsDatas;
    KeyBoardDatas* m_keyBoardDatas;
    SpecialElementsDatas* m_specialElementsDatas;
    QString m_version;
};

#endif // PROJECT_H
