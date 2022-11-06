/*
    Run:
    g++ main.cpp Vector.cpp World2D.cpp Agent2D.cpp -o app && ./app
    Debug:
    g++ -g main.cpp Vector.cpp World2D.cpp Agent2D.cpp && gdb ./a.out
*/

#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <iomanip>
#include "World2D.hpp"
#include "Agent2D.hpp"
#include "Vector.hpp"

//test variables
#define alpha 0.80
#define trial 100

int main()  {
    srand(time(0));

    World2D world;

    //File output
    std::ofstream file("trials_alpha_" + std::to_string(alpha) + ".txt");
    file << std::fixed << std::setprecision(2);

    int trialCount = 0;
    while(trialCount < trial) {
        //File output: trial title
        file << "Trial: " << trialCount+1 << std::endl;

        Agent2D agent1(187.5, 25+(rand()%(world.getHeightMod()/2)));
        Agent2D agent2(7.5, 25+(rand()%(world.getHeightMod()/2)));

        //Initialization of vectors and first view angle
        Vector v1;
        float y = (0+(double)(rand())/(double)(RAND_MAX)/1)-1.0/2.0;
        float x = sqrt(1-(y*y));
        Vector v2(-x,y);
        agent1.setIndicX((agent1.getX()+2)+2*(v2.getI()));
        agent1.setIndicY((agent1.getY()+2)+2*(v2.getJ()));

        while (true) {
            
            file << "Agent1 coords: (" << agent1.getX() << "," << agent1.getY() << ")  \t";
            file << "Agent2 coords: (" << agent2.getX() << "," << agent2.getY() << ")  \t";
            file << "distance: " << agent1.percieve(agent2) << std::endl;
            
            if(agent1.decide(agent2, v1, v2, alpha))
                agent1.move(world, v2);
            else {
                file << "Hedefe ulasildi!" << std::endl << std::endl;
                break;
            }
        }

        trialCount++;
    }
    file.close();

    return 0;
}