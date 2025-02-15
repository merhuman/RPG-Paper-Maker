/*
    RPG Paper Maker Copyright (C) 2017-2022 Wano

    RPG Paper Maker engine is under proprietary license.
    This source code is also copyrighted.

    Use Commercial edition for commercial use of your games.
    See RPG Paper Maker EULA here:
        http://rpg-paper-maker.com/index.php/eula.
*/

import * as THREE from 'three';
import { Manager } from '../Editor';
import { Project } from './Project';

class Camera {

    public static MIN_ZOOM = 20;
    public static MAX_ZOOM = 10000;
    
    public perspectiveCamera: THREE.PerspectiveCamera;
    public targetPosition: THREE.Vector3;
    public distance: number;
    public horizontalAngle: number;
    public verticalAngle: number;
    public defaultCameraPosition: THREE.Vector3;

    constructor() {
        this.perspectiveCamera = new THREE.PerspectiveCamera(45, 1, 0.1, 100000);
        this.distance = 800 * Project.current!.systems.getCoefSquareSize();
        this.horizontalAngle = -90;
        this.verticalAngle = 55;
        this.targetPosition = new THREE.Vector3(Project.getSquareSize() / 2, 0, 
            Project.getSquareSize() / 2);
        this.update();
        this.defaultCameraPosition = this.getThreeCamera().position.clone();
    }

    zoomIn(coef: number) {
        this.distance = Math.max(Camera.MIN_ZOOM, this.distance - this.getZoom(coef));
    }

    zoomOut(coef: number) {
        this.distance = Math.min(Camera.MAX_ZOOM, this.distance + this.getZoom(coef));
    }

    getZoom(coef: number): number {
        return (50 + (this.distance / Project.getSquareSize())) * coef;
    }

    getDistance(): number {
        return this.distance * Math.sin(this.verticalAngle * Math.PI / 180.0);
    }

    getHeight(): number {
        return this.distance * Math.cos(this.verticalAngle * Math.PI / 180.0);
    }

    getThreeCamera(): THREE.Camera {
        return this.perspectiveCamera;
    }

    updateCameraPosition() {
        let distance = this.getDistance();
        let camera = this.getThreeCamera();
        camera.position.x = this.targetPosition.x - (distance * Math
            .cos(this.horizontalAngle * Math.PI / 180.0));
        camera.position.y = this.targetPosition.y + this.getHeight();
        camera.position.z = this.targetPosition.z - (distance * Math
            .sin(this.horizontalAngle * Math.PI / 180.0));
    }

    updateView() {
        this.getThreeCamera().lookAt(this.targetPosition);
    }

    update() {
        // Update position
        this.updateCameraPosition();

        // Update view
        this.updateView();
    }

    resizeGL(GL: Manager.GL, width?: number, height?: number) {
        if (GL.parent) {
            this.perspectiveCamera.aspect = (width ? width : GL.parent.clientWidth) / 
                (height ? height : GL.parent.clientHeight);
            this.perspectiveCamera.updateProjectionMatrix();
        }
    }
}

export { Camera }