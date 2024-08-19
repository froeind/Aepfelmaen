
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
		int auswahl = 4;
		//int auswahl = 5;
		unsigned int second = 0;
		// Rechentiefe wird bei 'second=1' halbiert
		// also Hilfsvariable benutzen
		unsigned int realetiefe = 0;
		unsigned int* dim;

		// Kreisring
		const unsigned int KrAradius = 200;
		unsigned int KrIradius = 125;

		// Apfelmann
		const unsigned int apfelbreite = 575;
		const unsigned int apfelhoehe = 425;
		const unsigned int iend = 2 * apfelbreite;
		const unsigned int jend = 2 * apfelhoehe;
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
		// das muss ich noch übersetzen
		//->Color[] acolor, arcolor, agcolor, abcolor;
		int ineu = -1;
		int jneu = -1;
		// 'neuoderalt' regelt was gerade gemalt werden soll
		// 0=altes nochmal - 1=nochmal das gleiche - 2=neue werte nehmen
		// 3=original-apfelmann zeichnen
		int neuoderalt = 3;
		unsigned int schwarzgrenze = 200;
		const unsigned int zoom = 6;
		char modus = 'R';
		const unsigned int apfelxabstand = 200;
		const unsigned int apfelyabstand = 60;
		// 'grenzqradius' ist der Radius des Kreises,
		// den die Punkte verlassen oder auch nicht,
		// zum Quadrat genommen
		double grenzqradius = 100;
		std::vector<std::vector<int>> punktfarbe;
		unsigned int lupe = 0;
		const unsigned int exponent = 2;

		// Dreieckchen
		const unsigned int dxmitte = 425;
		const unsigned int dymitte = 250;
		double faktor;
		const unsigned int dfarbe = 11;
		const unsigned int dreitiefe = 8;
		const unsigned int dreikante = 140;

		// Schneeflocke
		const unsigned int schneetiefe = 6;
		const unsigned int schneekante = 150;

		Config();
		~Config();
    };

	void farbeSetzen(sf::RenderWindow&, const unsigned int);
	void init(sf::RenderWindow&, Config*);

}