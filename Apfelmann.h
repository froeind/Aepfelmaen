
#pragma once

#include <vector>

class Apfelmann {
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
	/*Color[] acolor, arcolor, agcolor, abcolor;*/
	int ineu = -1;
	int jneu = -1;
	// 'neuoderalt' regelt was gerade gemalt werden soll
	// 0=altes nochmal - 1=nochmal das gleiche - 2=neue werte nehmen
	// 3=original-apfelmann zeichnen
	int neuoderalt = 3;
	const unsigned int schwarzgrenze = 200;
	const unsigned int zoom = 6;
	char modus = 'R';
	const unsigned int apfelxabstand = 200;
	const unsigned int apfelyabstand = 60;
	// 'grenzqradius' ist der Radius des Kreises,
	// den die Punkte verlassen oder auch nicht,
	// zum Quadrat genommen
	double grenzqradius = 100;
	std::vector<std::vector<int>> punktfarbe;
	const unsigned int lupe;
	const unsigned int exponent = 2;
};
