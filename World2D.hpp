#ifndef WORLD2D_HPP
#define WORLD2D_HPP

class Agent2D;

class World2D {
    private:
        int widthMod, heightMod;

    public:
        //-------Constructors
        World2D();

        //-------Getters
        int getWidthMod();
        int getHeightMod();

        //-------Setters
        void setWidthMod(int newWidthMod);
        void setHeightMod(int newHeightMod);
};

#endif