
#pragma once

#include <SFML/Graphics.hpp>

#include "Button.h"

namespace myA {

    class Menu {
    public:
        sf::RenderWindow* window_ = nullptr;
        sf::Font font_;
        Button apfelmann_;
        Button dreieckchen_;
        Button dreieckchenp_;
        Button dreieckcheni_;
        Button dreieckchenpi_;
        Button schneeflocke_;
        Button schneedeckchen_;
        Button kreisring_;
        Button kreisring2_;
        Button dreieck_;
        Button kreis_;
        Button rechteck_;
        Menu(sf::RenderWindow&);
        ~Menu();
        void draw();
        void msgBox(std::string);
        void msgBoxBig(std::string);
    private:
    };


}