
#include "Menu.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

myA::Menu::Menu(sf::RenderWindow& window) : window_(&window) {

    // Lade eine Schriftart
    if ( ! font_.loadFromFile("C:\\Windows\\Fonts\\tahoma.ttf")) {
        // Fehlerbehandlung, falls die Schriftart nicht geladen werden kann
        font_.loadFromFile("C:\\Windows\\Fonts\\calibril.ttf");
        // Calibri Standard "muss" es geben
    }

    float x = 10.f;
    float y = 10.f;
    float yIncr = 40.f;
    float w = 128.f;
    float h = 32.f;
	unsigned char r = 192;
    unsigned char g = 192;
    unsigned char b = 192;
    apfelmann_ = Button(*window_, "apfelmann", font_, x, y, w, h, r, g, b);
    y += yIncr;
    dreieckchen_ = Button(*window_, "dreieckchen", font_, x, y, w, h, r, g, b);
    y += yIncr;
    dreieckchenp_ = Button(*window_, "dreieckchen +", font_, x, y, w, h, r, g, b);
    y += yIncr;
    dreieckcheni_ = Button(*window_, "dreieckchen i", font_, x, y, w, h, r, g, b);
    y += yIncr;
    dreieckchenpi_ = Button(*window_, "dreieckchen +i", font_, x, y, w, h, r, g, b);
    y += yIncr;
    schneeflocke_ = Button(*window_, "schneeflocke", font_, x, y, w, h, r, g, b);
    y += yIncr;
    schneedeckchen_ = Button(*window_, "schneedeckchen", font_, x, y, w, h, r, g, b);
    y += yIncr;
    kreisring_ = Button(*window_, "kreisring", font_, x, y, w, h, r, g, b);
    y += yIncr;
    kreisring2_ = Button(*window_, "kreisring 2", font_, x, y, w, h, r, g, b);
    y += yIncr;
    dreieck_ = Button(*window_, "dreieck", font_, x, y, w, h, r, g, b);
    y += yIncr;
    kreis_ = Button(*window_, "kreis", font_, x, y, w, h, r, g, b);
    y += yIncr;
    rechteck_ = Button(*window_, "rechteck", font_, x, y, w, h, r, g, b);
}

myA::Menu::~Menu() {}

void myA::Menu::draw() {
    (*window_).draw(apfelmann_.button_);
    (*window_).draw(apfelmann_.text_);
    (*window_).draw(dreieckchen_.button_);
    (*window_).draw(dreieckchen_.text_);
    (*window_).draw(dreieckchenp_.button_);
    (*window_).draw(dreieckchenp_.text_);
    (*window_).draw(dreieckcheni_.button_);
    (*window_).draw(dreieckcheni_.text_);
    (*window_).draw(dreieckchenpi_.button_);
    (*window_).draw(dreieckchenpi_.text_);
    (*window_).draw(schneeflocke_.button_);
    (*window_).draw(schneeflocke_.text_);
    (*window_).draw(schneedeckchen_.button_);
    (*window_).draw(schneedeckchen_.text_);
    (*window_).draw(kreisring_.button_);
    (*window_).draw(kreisring_.text_);
    (*window_).draw(kreisring2_.button_);
    (*window_).draw(kreisring2_.text_);
    (*window_).draw(dreieck_.button_);
    (*window_).draw(dreieck_.text_);
    (*window_).draw(kreis_.button_);
    (*window_).draw(kreis_.text_);
    (*window_).draw(rechteck_.button_);
    (*window_).draw(rechteck_.text_);
}

void myA::Menu::msgBox(std::string msg)
{
    myA::Button msgBox = myA::Button(*window_, msg, font_, 600.f, 10.f, 200.f, 200.f, 255, 255, 255);
    (*window_).draw(msgBox.button_);
    (*window_).draw(msgBox.text_);
}

void myA::Menu::msgBoxBig(std::string msg)
{
    myA::Button msgBox = myA::Button(*window_, msg, font_, 1300.f, 50.f, 250.f, 800.f, 255, 255, 255);
    (*window_).draw(msgBox.button_);
    (*window_).draw(msgBox.text_);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

