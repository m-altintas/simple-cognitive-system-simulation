#ifndef VECTOR_HPP
#define VECTOR_HPP

class Vector {
    private:
        //-------Instance Variables
        float i, j;

    public:
        //-------Constructors
        Vector();
        Vector(float ci, float cj);

        //-------Getters
        float getI();
        float getJ();

        //-------Setters
        void setI(float newI);
        void setJ(float newJ);

        //-------Methods
        void makeUnit();
};


#endif