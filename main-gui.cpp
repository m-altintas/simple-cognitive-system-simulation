/*
    Run:
    g++ main-gui.cpp Vector.cpp World2D.cpp Agent2D.cpp -o app -lsfml-graphics -lsfml-window -lsfml-system && ./app
    Debug:
    g++ -g main-gui.cpp Vector.cpp World2D.cpp Agent2D.cpp -lsfml-graphics -lsfml-window -lsfml-system && gdb ./a.out
*/

#include <SFML/Graphics.hpp>

#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <thread>

#include "World2D.hpp"
#include "Agent2D.hpp"
#include "Vector.hpp"

//test variables
#define alpha 0.85
#define trial 100
//pixel size to determine gui details
#define pxSize 8

using namespace sf;
using std::ofstream;


int main()  {
    srand(time(0));

    World2D world;

    //GUI foundation {
    RenderWindow window(VideoMode(world.getWidthMod()*pxSize, world.getHeightMod()*pxSize), "PSI 103");
    window.setFramerateLimit(60);

    Texture txtrBackground, txtrAgent1, txtrAgent2, txtrAgent1indic;
    txtrBackground.loadFromFile("images/tile.png");
    txtrAgent1.loadFromFile("images/agent1-round.png");
    txtrAgent1.setSmooth(true);
    txtrAgent2.loadFromFile("images/agent2-round.png");
    txtrAgent2.setSmooth(true);
    txtrAgent1indic.loadFromFile("images/eye.png");
    txtrAgent1indic.setSmooth(true);

    Sprite sprtBackground(txtrBackground);
    Sprite sprtAgent1(txtrAgent1);
    Sprite sprtAgent2(txtrAgent2);
    Sprite sprtAgent1indic(txtrAgent1indic);
    // }

    //File output
    ofstream file("trials_alpha_" + std::to_string(alpha) + ".txt");
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
            Event e;
            while (window.pollEvent(e)) {
                if (e.type == Event::Closed) window.close();
            }
            
            file << "Agent1 coords: (" << agent1.getX() << "," << agent1.getY() << ")  \t";
            file << "Agent2 coords: (" << agent2.getX() << "," << agent2.getY() << ")  \t";
            file << "distance: " << agent1.percieve(agent2) << std::endl;
            
            if(agent1.decide(agent2, v1, v2, alpha))
                agent1.move(world, v2);
            else {
                file << "Hedefe ulasildi!" << std::endl << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                break;
            }

            ///////draw
            window.clear();

            //background
            for (int i = 0; i < world.getWidthMod(); i++)
                for (int j = 0; j < world.getHeightMod(); j++) {
                    sprtBackground.setPosition(i*pxSize, j*pxSize);
                    window.draw(sprtBackground);
                }
                
            //agent1
            sprtAgent1.setPosition(agent1.getX()*pxSize, agent1.getY()*pxSize);
            window.draw(sprtAgent1);
            
            //agent2
            sprtAgent2.setPosition(agent2.getX()*pxSize, agent2.getY()*pxSize);
            window.draw(sprtAgent2);

            //TODO: direction indicator
            sprtAgent1indic.setPosition(agent1.getIndicX()*pxSize, agent1.getIndicY()*pxSize);
            window.draw(sprtAgent1indic);

            window.display();
            std::this_thread::sleep_for(std::chrono::milliseconds(7));
        }

        trialCount++;
    }
    file.close();
    window.close();

    return 0;
}