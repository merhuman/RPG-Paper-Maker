/*
    RPG Paper Maker Copyright (C) 2017-2022 Wano

    RPG Paper Maker engine is under proprietary license.
    This source code is also copyrighted.

    Use Commercial edition for commercial use of your games.
    See RPG Paper Maker EULA here:
        http://rpg-paper-maker.com/index.php/eula.
*/

import { Model } from '../Editor';
import { Constants } from './Constants';

class Utils {

    constructor() {
        throw new Error("This is a static class!");
    }

    public static defaultValue<T>(value: T | undefined, defaultValue: T): T {
        return value === undefined ? defaultValue : value;
    }

    public static writeDefaultValue<T>(json: any, jsonName: string, value: T, 
        defaultValue: T) {
        if (value !== defaultValue) {
            json[jsonName] = value;
        }
    }

    public static writeDefaultValueArray(prop: any, propName: string, value: any[]) {
        if (value.length > 0) {
            prop[propName] = value;
        }
    }

    static isNumber(value: any): boolean {
        return typeof value === Constants.NUMBER;
    }

    static isString(value: any): boolean {
        return typeof value === Constants.STRING;
    }
    
    static readList(list: any[], json: Record<string, any>[], constructor: any) {
        let model: Model.Base;
        for (let jsonModel of json) {
            model = new constructor();
            model.read(jsonModel);
            list.push(model);
        }
    }

    static writeList(list: any[], json: Record<string, any>, jsonName: string) {
        let jsonList: Record<string, any> = [];
        for (let model of list) {
            let jsonModel = {};
            model.write(jsonModel);
            jsonList.push(jsonModel);
        }
        json[jsonName] = jsonList;
    }

    static formatNumber(num: number, size: number): string {
        return ('000000000' + num).substr(-size);
    }

    static numToBool(n: number): boolean {
        return n === Constants.NUM_BOOL_TRUE;
    }

    static boolToNum(b: boolean): number {
        return b ? Constants.NUM_BOOL_TRUE : Constants.NUM_BOOL_FALSE;
    }
}

export { Utils }