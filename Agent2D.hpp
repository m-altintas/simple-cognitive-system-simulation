#ifndef AGENT2D_HPP
#define AGENT2D_HPP

class Vector;
class World2D;

class Agent2D {
    private:
        //-------Instance Variables
        float x, y, indicX, indicY;
        int size, speed;

    public:
        //-------Constructors
        Agent2D(float cx, float cy);

        //-------Getters
        float getX();
        float getY();
        float getIndicX();
        float getIndicY();
        int getSize();
        int getSpeed();

        //-------Setters
        void setX(float newX);
        void setY(float newY);
        void setIndicX(float newIndicX);
        void setIndicY(float newIndicY);
        void setSpeed(int newSpeed);
        void setSize(int newSize);

        //-------Methods
        //percieve
        float percieve(Agent2D &target);

        //deciede
        bool decide(Agent2D &target, Vector &v1, Vector &v2, float alpha);

        //move
        void move(World2D &world, Vector &v);
};

#endif