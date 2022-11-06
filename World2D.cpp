#include "World2D.hpp"
#include "Agent2D.hpp"

//-------Constructors
    World2D::World2D() {
        widthMod = 200;
        heightMod = 100;
    }

//-------Getters
    int World2D::getWidthMod() {return widthMod;}
    int World2D::getHeightMod() {return heightMod;}

//-------Setters
    void World2D::setWidthMod(int newWidhtMod) {widthMod = newWidhtMod;}
    void World2D::setHeightMod(int newHeightMod) {heightMod = newHeightMod;}