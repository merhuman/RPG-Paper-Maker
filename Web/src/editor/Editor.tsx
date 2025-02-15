/*
    RPG Paper Maker Copyright (C) 2017-2022 Wano

    RPG Paper Maker engine is under proprietary license.
    This source code is also copyrighted.

    Use Commercial edition for commercial use of your games.
    See RPG Paper Maker EULA here:
        http://rpg-paper-maker.com/index.php/eula.
*/

import React from 'react';
import MainMenuBar from './components/MainMenuBar';
import PanelProject from './components/PanelProject';
import ToolBar from './components/Toolbar';
import { LocalFile } from './core/LocalFile';
import { Manager } from './Editor';
import './styles/Editor.css';

// Create GL contexts
Manager.GL.mapEditorContext = new Manager.GL();
Manager.GL.extraContext = new Manager.GL();

function Editor() {
    const [currentProjectName, setCurrentProjectName] = React.useState<string>('');
    
    return (
        <div className='flex-column fill-space'>
            <MainMenuBar currentProjectName={currentProjectName} setCurrentProjectName={setCurrentProjectName} />
            <ToolBar />
            <PanelProject currentProjectName={currentProjectName} />
        </div>
    );
}

LocalFile.config();
(async() => {
    await Manager.GL.initializeShaders();
    
    /*
    let all = await LocalFile.allStorage();
    console.log(all);
    for (let path of all) {
        await LocalFile.brutRemove(path);
    }
    */
})();

export * as Manager from './managers/index';
export * as Scene from './scenes/index';
export * as Model from './models/index';
export * as MapElement from './mapElements/index';
export * as Data from './data/index';

export default Editor;