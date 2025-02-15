/*
    RPG Paper Maker Copyright (C) 2017-2022 Wano

    RPG Paper Maker engine is under proprietary license.
    This source code is also copyrighted.

    Use Commercial edition for commercial use of your games.
    See RPG Paper Maker EULA here:
        http://rpg-paper-maker.com/index.php/eula.
*/

#ifndef ENGINESETTINGS_H
#define ENGINESETTINGS_H

#include "keyboarddatas.h"
#include "themekind.h"
#include "axiskind.h"
#include "drawkind.h"

// -------------------------------------------------------
//
//  CLASS EngineSettings
//
//  The different engine settings.
//
// -------------------------------------------------------

class EngineSettings : public Serializable
{
public:
    static const QString JSON_KEYBOARD;
    static const QString JSON_ZOOM_PICTURES;
    static const QString JSON_THEME;
    static const QString JSON_PROJECT_NAMES;
    static const QString JSON_PROJECT_LINKS;
    static const QString JSON_FIRST_TIME;
    static const QString JSON_TRANSLATION_LEFT_RIGHT_CLICK;
    static const QString JSON_TRANSLATION_BY_SQUARE;
    static const QString JSON_TRANSLATION_VALUES;
    static const QString JSON_ROTATION_OPERATIONS;
    static const QString JSON_ROTATION_LEFT_RIGHT_CLICK;
    static const QString JSON_ROTATION_ANGLES;
    static const QString JSON_SCALING_LEFT_RIGHT_CLICK;
    static const QString JSON_SCALING_BY_SQUARE;
    static const QString JSON_SCALING_VALUES;
    static const QString JSON_UPDATER;
    static const QString JSON_SHOW_AVAILABLE_CONTENT;
    static const QString JSON_FIRST_TIME_LANGUAGES;
    static const QString JSON_CURRENT_LANGUAGE;
    static const QString JSON_BATTLE_TROOP_TEST_BATTLE_MAP_ID;
    static const QString JSON_BATTLE_TROOP_TEST_HEROES;
    static const QString JSON_TAB_INDEX_DATAS;
    static const QString JSON_TAB_INDEX_SYSTEMS;
    static const QString JSON_PATREON_MESSAGE;
    static const QString JSON_GUIDE_STEP_PICTURES;
    static const QString JSON_SPLASH_SCREEN_ON_START;
    static const QString THEME_DEFAULT;
    static const QString THEME_WHITE;
    static const QString THEME_WHITE_MAC;
    static const QString THEME_DARK;
    static const QString PATH_THEMES;
    static const bool DEFAULT_FIRST_TIME_LANGUAGES;
    static const QString DEFAULT_CURRENT_LANGUAGE;
    static const int DEFAULT_BATTLE_TROOP_TEST_BATTLE_MAP_ID;
    static const int DEFAULT_TAB_INDEX_DATAS;
    static const int DEFAULT_TAB_INDEX_SYSTEMS;
    static const bool DEFAULT_PATREON_MESSAGE;
    static const int DEFAULT_GUIDE_STEP_PICTURES;
    static const bool DEFAULT_SPLASH_SCREEN_ON_START;

    EngineSettings();
    virtual ~EngineSettings();

    KeyBoardDatas * keyBoardDatas() const;
    int zoomPictures() const;
    void setZoomPictures(int z);
    ThemeKind theme() const;
    void setTheme(ThemeKind t);
    int projectNumber() const;
    QString projectAtName(int i) const;
    QString projectAtLink(int i) const;
    bool firstTime() const;
    void setFirstTime(bool b);
    bool translationLeftRightClick() const;
    void setTranslationLeftRightClick(bool b);
    bool translationBySquare() const;
    void setTranslationBySquare(bool b);
    double translationValue(AxisKind axisKind) const;
    void setTranslationValue(AxisKind axisKind, double a);
    bool rotationOperation(AxisKind ak) const;
    void setRotationOperation(AxisKind ak, bool b);
    bool rotationLeftRightClick() const;
    void setRotationLeftRightClick(bool b);
    double rotationAngle(AxisKind ak) const;
    void setRotationAngle(AxisKind ak, double a);
    bool scalingLeftRightClick() const;
    void setScalingLeftRightClick(bool b);
    bool scalingBySquare() const;
    void setScalingBySquare(bool b);
    double scalingValue(AxisKind axisKind) const;
    void setScalingValue(AxisKind axisKind, double value);
    bool applyLeftRightClick(DrawKind drawKind) const;
    void setApplyLeftRightClick(DrawKind drawKind, bool applyLeftRightClick);
    bool bySquare(DrawKind drawKind) const;
    void setBySquare(DrawKind drawKind, bool bySquare);
    bool operation(DrawKind drawKind, AxisKind axisKind);
    void setOperation(DrawKind drawKind, AxisKind axisKind, bool b);
    double value(DrawKind drawKind, AxisKind axisKind) const;
    void setValue(DrawKind drawKind, AxisKind axisKind, double value);
    bool updater() const;
    void setUpdater(bool u);
    bool showAvailableContent() const;
    void setShowAvailableContent(bool sac);
    bool firstTimeLanguages() const;
    void setFirstTimeLanguages(bool ftl);
    QString currentLanguage() const;
    void setCurrentLanguage(QString cl);
    int battleTroopTestBattleMapID() const;
    void setBattleTroopTestBattleMapID(int battleTroopTestBattleMapID);
    QJsonArray battleTroopTestHeroes() const;
    void setBattleTroopTestHeroes(QJsonArray &battleTroopTestHeroes);
    int tabIndexDatas() const;
    void setTabIndexDatas(int tabIndexDatas);
    int tabIndexSystems() const;
    void setTabIndexSystems(int tabIndexSystems);
    bool patreonMessage() const;
    void setPatreonMessage(bool patreonMessage);
    int guideStepPictures() const;
    void setGuideStepPictures(int guideStepPictures);
    bool splashScreenOnStart() const;
    void setSplashScreenOnStart(bool b);

    void setDefault();
    QString getThemeContent() const;
    void read();
    void write();
    void updateTheme();
    void updateProject(QString name, QString link);
    void clearProjects();
    void clearTroopBattleTestHeroes();

    virtual void read(const QJsonObject &json);
    virtual void write(QJsonObject &json) const;

protected:
    KeyBoardDatas *m_keyBoardDatas;
    int m_zoomPictures;
    ThemeKind m_theme;
    QStringList m_projectNames;
    QStringList m_projectLinks;
    bool m_firstTime;
    bool m_translationLeftRightClick;
    bool m_translationBySquare;
    QList<double> m_translationValues;
    QList<bool> m_rotationOperations;
    bool m_rotationLeftRightClick;
    QList<double> m_rotationAngles;
    bool m_scalingLeftRightClick;
    bool m_scalingBySquare;
    QList<double> m_scalingValues;
    bool m_updater;
    bool m_showAvailableContent;
    bool m_firstTimeLanguages;
    QString m_currentLanguage;
    int m_battleTroopTestBattleMapID;
    QJsonArray m_battleTroopTestHeroes;
    int m_tabIndexDatas;
    int m_tabIndexSystems;
    bool m_patreonMessage;
    int m_guideStepPictures;
    bool m_splashScreenOnStart;

    QString readContent(QString name) const;
};

#endif // ENGINESETTINGS_H
