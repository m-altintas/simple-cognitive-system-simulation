#include "Agent2D.hpp"
#include <math.h>
#include "Vector.hpp"
#include "World2D.hpp"

//-------Constructors
    Agent2D::Agent2D(float cx, float cy) {
        x = cx;
        y = cy;
        indicX = cx;
        indicY = cy;
        size = 5;
        speed = 2;
    }

//-------Getters
    float Agent2D::getX() {return x;}
    float Agent2D::getY() {return y;}
    float Agent2D::getIndicX() {return indicX;}
    float Agent2D::getIndicY() {return indicY;}
    int Agent2D::getSize() {return size;}
    int Agent2D::getSpeed() {return speed;}

//-------Setters
    void Agent2D::setX(float newX) {x = newX;}
    void Agent2D::setY(float newY) {y = newY;}
    void Agent2D::setIndicX(float newIndicX) {indicX = newIndicX;}
    void Agent2D::setIndicY(float newIndicY) {indicY = newIndicY;}
    void Agent2D::setSpeed(int newSpeed) {speed = newSpeed;}
    void Agent2D::setSize(int newSize) {size = newSize;}

//-------Methods
    //percieve
    float Agent2D::percieve(Agent2D &target) {
        //distance between this agent and the target
        float x, y, distance;
        x = pow((target.getX() - this->getX()), 2);
        y = pow((target.getY()- this->getY()), 2);
        distance = sqrt(x+y)-5;
        if(distance < 0)
            distance = 0;
        return distance;
    }

    //deciede
    bool Agent2D::decide(Agent2D &target, Vector &v1, Vector &v2, float alpha) {
        //v1 - distance vector
        v1.setI(target.getX()-this->getX());
        v1.setJ(target.getY()-this->getY());
        v1.makeUnit();

        //v2 - direction vector
        Vector v((1-alpha)*v2.getI() + (alpha)*v1.getI(),(1-alpha)*v2.getJ() + (alpha)*v1.getJ());
        v2.setI(v.getI());
        v2.setJ(v.getJ());
        v2.makeUnit();

        //catch control
        float xD, yD, distanceD;
        xD = pow((target.getX() - this->getX()), 2);
        yD = pow((target.getY() - this->getY()), 2);
        distanceD = sqrt(xD+yD);
        if(distanceD < 6)
            return 0;
        else
            return 1;
    }

    //move
    void Agent2D::move(World2D &world, Vector &v) {
        //move this agent
        this->setX(this->getX()+2*(v.getI()));
        this->setY(this->getY()+2*(v.getJ()));

        //move this agent's indicator/eye
        this->setIndicX((this->getX()+2)+2*(v.getI()));
        this->setIndicY((this->getY()+2)+2*(v.getJ()));

        //control world boundaries and stay inside
        if (this->getX()+this->getSize() > world.getWidthMod()) 
            this->setX(world.getWidthMod()-this->getSize());
        if (this->getX() < 0)
            this->setX(0);
        if (this->getY()+this->getSize() > world.getHeightMod())
            this->setY(world.getHeightMod()-this->getSize());
        if (this->getY() < 0)
            this->setY(0);
    }