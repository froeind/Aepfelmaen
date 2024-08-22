
#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "tools.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace myA {

    struct Config {

		// Initialisierung
		/*
		Graphics G;

		Choice chx;
		Label[] label;
		TextField[] textfield;
		Button[] button;
		KnopfAbfrage[] knopfabfrage;
		*/

		const unsigned int anzkomponenten = 18;
		int* vonkomponente;
		int* biskomponente;

		// Vorauswahl
		//int auswahl = 4;
		int auswahl = 5;
		//int auswahl = 6;
		//int auswahl = 7;
		//unsigned int second = 0;
		//unsigned int second = 1;
		unsigned int second = 2;
		// Rechentiefe wird bei 'second=1' halbiert
		// also Hilfsvariable benutzen
		// in C++ ist das jetzt sehr zeitintensiv mit second = 0 und schneetiefe = 8
		unsigned int realetiefe = 0;
		unsigned int* dim;

		// Kreisring
		const unsigned int KrAradius = 200;
		unsigned int KrIradius = 125;

		// Apfelmann
		const unsigned int apfelbreite = 575;
		const unsigned int apfelhoehe = 450;
		const int iend = 2 * apfelbreite;
		const int jend = 2 * apfelhoehe;
		int* punktfarbe = new int[(iend + 1) * (jend + 1)];
		std::vector<sf::Color> acolor;
		std::vector<sf::Color> arcolor;
		std::vector<sf::Color> agcolor;
		std::vector<sf::Color> abcolor;
		double rzf = 0;
		double izf = 0;
		double qrzf = 0;
		double qizf = 0;
		double crstep = 0;
		double cistep = 0;
		double crmgrenze = 0;
		double crpgrenze = 0;
		double cimgrenze = 0;
		double cipgrenze = 0;
		double crstepAlt = 0;
		double cistepAlt = 0;
		double crmgrenzeAlt = 0;
		double crpgrenzeAlt = 0;
		double cimgrenzeAlt = 0;
		double cipgrenzeAlt = 0;
		unsigned int farbe = 0;
		unsigned int rausbei = 0;
		const unsigned int maxfarbe = 4;
		int ineu = -1;
		int jneu = -1;
		// 'neuoderalt' regelt was gerade gemalt werden soll
		// 0=altes nochmal - 1=nochmal das gleiche - 2=neue werte nehmen
		// 3=original-apfelmann zeichnen
		int neuoderalt = 3;
		//const unsigned int exponent = 2;
		const unsigned int exponent = 3;
		unsigned int schwarzgrenze = 200;
		const unsigned int zoom = 6;
		//char modus = 'P';
		char modus = 'R';
		const unsigned int apfelxabstand = 250;
		const unsigned int apfelyabstand = 30;
		// 'grenzqradius' ist der Radius des Kreises,
		// den die Punkte verlassen oder auch nicht,
		// zum Quadrat genommen
		double grenzqradius = 100;
		unsigned int lupe = 0;

		// Dreieckchen
		const unsigned int dxmitte = 850;
		const unsigned int dymitte = 400;
		//double faktor;
		//const unsigned int dfarbe = 71;
		const unsigned int dreitiefe = 16;
		const unsigned int dreikante = 400;

		// Schneeflocke
		const unsigned int schneetiefe = 6;
		//const unsigned int schneetiefe = 8;
		const unsigned int schneekante = 300;

		Config();
		~Config();
    };

	void farbeSetzen(sf::RenderWindow&, const unsigned int);
	void init(sf::RenderWindow&, Config*);

}