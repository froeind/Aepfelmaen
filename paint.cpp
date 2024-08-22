
#include "paint.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void makePause(sf::RenderWindow& window)
{
	// Pause einlegen
	//std::cout << "Pause. Drücken Sie eine beliebige Taste, um fortzufahren." << std::endl;
	//window.setFramerateLimit(0); // Deaktiviert Framerate-Limit für die Pause
	bool paused = true;
	while (paused)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed)
			{
				paused = false;
			}
		}
	}
	// Framerate-Limit wieder aktivieren (optional)
	//window.setFramerateLimit(60);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void LinieZiehen(sf::RenderWindow& window, myA::Config* config, const unsigned int& aktf, const unsigned int& anf, const unsigned int& end, const unsigned int& zeile)
{
	sf::RectangleShape pixelline(sf::Vector2f((float)(1 + end - anf), 1.));
	pixelline.setPosition((float)(anf + config->apfelxabstand), (float)(zeile + config->apfelyabstand));
	pixelline.setFillColor(sf::Color::Red);

	if (aktf == config->schwarzgrenze)
	{
		pixelline.setFillColor(sf::Color::Black);
	}
	else
	{
		if (config->farbe == 0)
		{
			pixelline.setFillColor(config->arcolor.at(aktf));
		}
		else if (config->farbe == 1)
		{
			pixelline.setFillColor(config->agcolor.at(aktf));
		}
		else if (config->farbe == 2)
		{
			pixelline.setFillColor(config->abcolor.at(aktf));
		}
		else
		{
			pixelline.setFillColor(config->acolor.at(aktf));
		}
	}
	window.draw(pixelline);

	// temp
	/*
	myA::Menu menu(window);
	menu.msgBoxBig(std::to_string(anf + config->apfelxabstand)
		+ "\n" + std::to_string(zeile + config->apfelyabstand)
		+ "\n" + std::to_string(end + config->apfelxabstand)
		+ "\n" + std::to_string(zeile + config->apfelyabstand));
	*/
	window.display();
}

void FarbeBestimmen(sf::RenderWindow& window, myA::Config* config, const unsigned int& i, const unsigned int& j, bool malen)
{
	// Imaginärteil von c erstellen
	double ic = config->cimgrenze + j * config->cistep;
	double rc = config->crmgrenze + i * config->crstep;
	unsigned int rausbei = 0;
	double rz = config->rzf;
	double iz = config->izf;
	double qrz = config->qrzf;
	double qiz = config->qizf;
	double rzh;
	double izh;
	do
	{
		// neuen Punkt erstellen
		// und 'rausbei' hochzählen
		++rausbei;
		// quadratrischer Exponent wird vorberechnet
		rzh = qrz - qiz;
		izh = 2 * rz * iz;
		// kubischer Exponent explizit
		//rz = rz*(qrz-3*qiz)+rc;
		//iz = iz*(3*qrz-qiz)+ic;
		for (unsigned int ii = 3; ii <= config->exponent; ++ii)
		{
			double rzhh = rzh * rz - izh * iz;
			izh = rzh * iz + izh * rz;
			rzh = rzhh;
		}
		rz = rzh + rc;
		iz = izh + ic;
		qrz = rz * rz;
		qiz = iz * iz;
	} while ((rausbei < config->schwarzgrenze) && (qrz + qiz < config->grenzqradius));

	if ((rausbei > config->schwarzgrenze - 5) && (rausbei < config->schwarzgrenze))
	{
		if ((1. * rand() / RAND_MAX > 0.9) && (config->lupe < 10))
		{
			config->ineu = i;
			config->jneu = j;
			++config->lupe;
		}
	}

	// im Punkt- und Randmodus werden die Pixel gesetzt
	// aber nicht beim Suchen im Randmodus
	if (malen) LinieZiehen(window, config, rausbei, i, i, j);

	// für den Randmodus zusätzlich der Arraywert
	config->punktfarbe[config->iend * j + i] = rausbei;
}

void SuchePunkte(sf::RenderWindow& window, myA::Config* config, const int& akti, const int& aktj, const unsigned int& aktf, const int& jrand)
{
	int pfn;

	int spi = akti;
	int spj = aktj;
	int spr = 0;
	bool abbruch = false;

	while ((!abbruch) || (akti != spi) || (aktj != spj))
	{
		// kein Abbruch am Anfang, da ja der Startpunkt der Ausgangspunkt ist
		// und ein Abbruch erst beim Eintreffen in Startpunkt stattfindet
		abbruch = true;

		// nächste Richtung, ausgehend von gültigem Punkt,
		// in der neuer Punkt gesucht wird
		int sprn = (spr + 1) % 4;

		// nächster Punkt in dieser Richtung
		int spin = spi - ((sprn - 1) % 2);
		int spjn = spj - ((sprn - 2) % 2);

		// neue Richtung für Weitersuche in gültigem Punkt
		// aber ausgehend von einem ungültigen Punkt
		// aus dieser wird dann die neue Richtung gegen Uhrzeigersinn
		int spru = (sprn + 2) % 4;

		if ((spin < 0) || (spin > config->iend) || (spjn < jrand) || (spjn > config->jend))
		{
			// neuer Punkt ist außerhalb des Suchbereichs
			// also zum Vorgänger zurück
			// und dort in Richtung gegen Uhrzeigersinn weitersuchen
			spr = spru;
		}
		else
		{
			// Punkt ist innerhalb des Suchbereichs

			if ((akti != spin) || (aktj != spjn))
			{
				// Ausgangspunkt wurde noch nicht erreicht
				// also weitersuchen
				pfn = std::abs(config->punktfarbe[config->iend * spjn + spin]);
				if (pfn == 0)
				{
					// Punkt ist unbekannt
					FarbeBestimmen(window, config, spin, spjn, true);
					pfn = config->punktfarbe[config->iend * spjn + spin];
					if (pfn == aktf)
					{
						// neuer Punkt hat gewünschte Farbe
						if ((spin < akti) && (spjn == aktj))
						{
							// aber liegt vor aktuellem Startpunkt
							// man ist auf einen schon durchlaufenen Punktsuchpfad gestoßen
							// also Abbruch
							spi = akti;
							spj = aktj;
						}
						else
						{
							// sonst weiter
							spi = spin;
							spj = spjn;
							spr = sprn;
						}
					}
					else
					{
						// neuer Punkt mit anderer Farbe, also ungültiger Punkt
						// diese Farbe negieren, da durch Punkt noch kein Suchpfad lief
						config->punktfarbe[config->iend * spjn + spin] = -pfn;

						// also zum Vorgänger zurück und dort in nächster Richtung weitersuchen
						spr = spru;
					}
				}
				else if (pfn == aktf)
				{
					// Punkt ist bekannt und hat gleiche Farbe
					// man ist irgendwie auf dem Rückweg
					// bzw. vorhergehende Suche hatte diesen Punkt schon negativ markiert
					// auf jeden Fall Farbwert positiv setzen
					config->punktfarbe[config->iend * spjn + spin] = pfn;

					if ((spin < akti) && (spjn == aktj))
					{
						// aber liegt vor aktuellem Startpunkt
						// man ist auf einen schon durchlaufenen Punktsuchpfad gestoßen
						// also Abbruch
						spi = akti;
						spj = aktj;
					}
					else
					{
						// sonst weiter
						spi = spin;
						spj = spjn;
						spr = sprn;
					}

					// also von hier weiter
					//spi = spin;
					//spj = spjn;
					//spr = sprn;
				}
				else
				{
					// Punkt bekannt mit anderer Farbe, also ungültiger Punkt
					// also zum Vorgänger zurück und dort in nächster Richtung weitersuchen
					spr = spru;
				}
			}
			else
			{
				// Abbruch
				spi = akti;
				spj = aktj;
			}
		}
	}
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

sf::Color farbeSetzen(unsigned int& i)
{
	if (i == 71) return sf::Color((int)(myT::random(0, 150) + 105), (int)(myT::random(0, 150) + 105), 0);
	else if (i == 72) return sf::Color((int)(myT::random(0, 150) + 105), 0, (int)(myT::random(0, 150) + 105));
	//else if (i == 73) return sf::Color(0, (int)(myT::random(0, 150) + 105), (int)(myT::random(0, 150) + 105));
	else return sf::Color(0, (int)(myT::random(0, 150) + 105), (int)(myT::random(0, 150) + 105));
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void SeiteBauen(sf::RenderWindow& window, myA::Config* config, int sx, int sy, int sr, int sl, int stz, unsigned int& teilung)
{
	int sxa = 0;
	int sya = 0;
	int sxag = 0;
	int syag = 0;
	int sxe = 0;
	int sye = 0;
	int sl3 = 0;
	int sl3m = 0;

	if (stz == config->realetiefe)
	{
		// Maximaltiefe erreicht, also Kante setzen
		sxe = sx - ((sr - 1) % 2) * sl;
		sye = sy - ((sr - 2) % 2) * sl;
		sf::Vertex line1[2];
		line1[0].position = sf::Vector2f((float)sx, (float)sy);
		line1[1].position = sf::Vector2f((float)sxe, (float)sye);
		line1[0].color = sf::Color::White;
		window.draw(line1, 2, sf::Lines);
		window.display();
	}
	else
	{
		// Maximaltiefe noch nicht erreicht, also rekursiv weiter

		// Seitenkanten sind hier Drittelstrecken oder beliebige Strecken
		// die zwei Außenstücke sind gleichlang
		// das Mittelstück immer das längere
		sl3 = (int)(sl / teilung);
		sl3m = sl - 2 * sl3;
		if (sl3m > sl3)
		{
			sl3 = ++sl3;
			sl3m -= 2;
		}

		if (config->second == 0)
		{
			// die zwei Kantenstücke, die gezeichnet werden
			sxe = sx - ((sr - 1) % 2) * sl3;
			sye = sy - ((sr - 2) % 2) * sl3;
			sf::Vertex line2[2];
			line2[0].position = sf::Vector2f((float)sx, (float)sy);
			line2[1].position = sf::Vector2f((float)sxe, (float)sye);
			line2[0].color = sf::Color::White;
			window.draw(line2, 2, sf::Lines);
			window.display();
			sxa = sx - ((sr - 1) % 2) * (sl3 + sl3m);
			sya = sy - ((sr - 2) % 2) * (sl3 + sl3m);
			sxe = sxa - ((sr - 1) % 2) * sl3;
			sye = sya - ((sr - 2) % 2) * sl3;
			sf::Vertex line3[2];
			line3[0].position = sf::Vector2f((float)sxa, (float)sya);
			line3[1].position = sf::Vector2f((float)sxe, (float)sye);
			line3[0].color = sf::Color::White;
			window.draw(line3, 2, sf::Lines);
			window.display();
		}
		else
		{
			// die zwei Kantenstücke werden auch gedrittelt
			SeiteBauen(window, config, sx, sy, sr, sl3, stz + 1, teilung);
			// Gegenrichtung
			sxag = sx - ((sr - 1) % 2) * sl3;
			syag = sy - ((sr - 2) % 2) * sl3;
			SeiteBauen(window, config, sxag, syag, (sr + 2) % 4, sl3, stz + 1, teilung);

			sxa = sx - ((sr - 1) % 2) * (sl3 + sl3m);
			sya = sy - ((sr - 2) % 2) * (sl3 + sl3m);
			SeiteBauen(window, config, sxa, sya, sr, sl3, stz + 1, teilung);
			// Gegenrichtung
			sxag = sxa - ((sr - 1) % 2) * sl3;
			syag = sya - ((sr - 2) % 2) * sl3;
			SeiteBauen(window, config, sxag, syag, (sr + 2) % 4, sl3, stz + 1, teilung);
		}
		// die Mittelkante, die zu drei neuen Kanten wird
		sxa = sx - ((sr - 1) % 2) * sl3;
		sya = sy - ((sr - 2) % 2) * sl3;
		SeiteBauen(window, config, sxa, sya, (sr + 3) % 4, sl3m, stz + 1, teilung);
		// Gegenrichtung
		sxag = sxa - ((((sr + 3) % 4) - 1) % 2) * sl3m;
		syag = sya - ((((sr + 3) % 4) - 2) % 2) * sl3m;
		SeiteBauen(window, config, sxag, syag, (sr + 1) % 4, sl3m, stz + 1, teilung);

		sxa = sxa - ((((sr + 3) % 4) - 1) % 2) * sl3m;
		sya = sya - ((((sr + 3) % 4) - 2) % 2) * sl3m;
		SeiteBauen(window, config, sxa, sya, sr, sl3m, stz + 1, teilung);
		// Gegenrichtung
		sxag = sxa - ((sr - 1) % 2) * sl3m;
		syag = sya - ((sr - 2) % 2) * sl3m;
		SeiteBauen(window, config, sxag, syag, (sr + 2) % 4, sl3m, stz + 1, teilung);

		sxa = sxa - ((sr - 1) % 2) * sl3m;
		sya = sya - ((sr - 2) % 2) * sl3m;
		SeiteBauen(window, config, sxa, sya, (sr + 1) % 4, sl3m, stz + 1, teilung);
		// Gegenrichtung
		sxag = sxa - ((((sr + 1) % 4) - 1) % 2) * sl3m;
		syag = sya - ((((sr + 1) % 4) - 2) % 2) * sl3m;
		SeiteBauen(window, config, sxag, syag, (sr + 3) % 4, sl3m, stz + 1, teilung);
	}
}

void DreiSeiteBauen(sf::RenderWindow& window, myA::Config* config, double sx, double sy, double alpha, double sl, int stz, unsigned int& teilung, double& faktor, unsigned int& dfarbe)
{
	double sxa = 0;
	double sya = 0;
	double sxe = 0;
	double sye = 0;
	double sl3 = 0;
	double sl3m = 0;

	if (stz == config->realetiefe)
	{
		// Maximaltiefe erreicht, also Kante setzen
		sxe = sx + std::cos(alpha) * sl;
		sye = sy + std::sin(alpha) * sl;
		sf::Vertex line1[2];
		line1[0].position = sf::Vector2f((float)(config->dxmitte + sx), (float)(config->dymitte - sy));
		line1[1].position = sf::Vector2f((float)(config->dxmitte + sxe), (float)(config->dymitte - sye));
		line1[0].color = farbeSetzen(dfarbe);
		window.draw(line1, 2, sf::Lines);
	}
	else
	{
		// Maximaltiefe noch nicht erreicht, also rekursiv weiter

		// Seitenkanten sind hier Drittelstrecken oder beliebige Strecken
		// die zwei Außenstücke sind gleichlang
		// das Mittelstück immer das längere
		sl3 = sl / teilung;
		sl3m = sl - 2 * sl3;
		if (sl3m > sl3)
		{
			sl3 = ++sl3;
			sl3m -= 2;
		}

		if ((config->second % 2) == 0)
		{
			// zwei Kantenstücke, die gezeichnet werden
			sxe = sx + std::cos(alpha) * sl3;
			sye = sy + std::sin(alpha) * sl3;
			sf::Vertex line2[2];
			line2[0].position = sf::Vector2f((float)(config->dxmitte + sx), (float)(config->dymitte - sy));
			line2[1].position = sf::Vector2f((float)(config->dxmitte + sxe), (float)(config->dymitte - sye));
			line2[0].color = farbeSetzen(dfarbe);
			window.draw(line2, 2, sf::Lines);
			sxa = sx + std::cos(alpha) * (sl3 + sl3m);
			sya = sy + std::sin(alpha) * (sl3 + sl3m);
			sxe = sx + std::cos(alpha) * sl;
			sye = sy + std::sin(alpha) * sl;
			sf::Vertex line3[2];
			line3[0].position = sf::Vector2f((float)(config->dxmitte + sxa), (float)(config->dymitte - sya));
			line3[1].position = sf::Vector2f((float)(config->dxmitte + sxe), (float)(config->dymitte - sye));
			line3[0].color = farbeSetzen(dfarbe);
			window.draw(line3, 2, sf::Lines);
		}
		else
		{
			// auch mit Dreieck besetzen
			DreiSeiteBauen(window, config, sx, sy, alpha, sl3, stz + 1, teilung, faktor, dfarbe);
			sxa = sx + std::cos(alpha) * (sl3 + sl3m);
			sya = sy + std::sin(alpha) * (sl3 + sl3m);
			DreiSeiteBauen(window, config, sxa, sya, alpha, sl3, stz + 1, teilung, faktor, dfarbe);
		}
		// zwei neue Dreieckseiten
		sxa = sx + std::cos(alpha) * sl3;
		sya = sy + std::sin(alpha) * sl3;

		// 'acos'-Argument muß im Definitionsbereich bleiben
		double argument = sl3m / (sl * 2 * faktor);
		argument = argument < -1 ? -1 : argument;
		argument = argument > 1 ? 1 : argument;
		double alphax = std::acos(argument);		
		//double alphaneu = (alpha + alphax) % (2 * PI);
		double alphaneu = fmod(alpha + alphax, 2 * PI);
		DreiSeiteBauen(window, config, sxa, sya, alphaneu, faktor * sl, stz + 1, teilung, faktor, dfarbe);
		sxa += std::cos(alphaneu) * faktor * sl;
		sya += std::sin(alphaneu) * faktor * sl;
		//alphaneu = (alpha + 2 * PI - alphax) % (2 * PI);
		alphaneu = fmod(alpha + 2 * PI - alphax, 2 * PI);
		DreiSeiteBauen(window, config, sxa, sya, alphaneu, faktor * sl, stz + 1, teilung, faktor, dfarbe);
	}
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void myA::paint(sf::RenderWindow& window, Config* config)
{
	// temp
	myA::Menu menu(window);

	if (config->auswahl <= 4)
	{
		// Polygonzug, der Rechteck ausfüllt

		const unsigned int seite = 200;
		const unsigned int xabstand = 250;
		const unsigned int yabstand = 50;

		// VertexArray erstellen
		sf::VertexArray polygonR(sf::LinesStrip, config->dim[1]);
		// Zufällige Positionen für die Eckpunkte generieren
		for (unsigned int i = 0; i < config->dim[1]; ++i)
		{
			polygonR[i].position = sf::Vector2f((float) (myT::random(0, 2 * seite - 1) + xabstand), (float)(myT::random(0, 2 * seite - 1) + yabstand));
			polygonR[i].color = sf::Color::Red;
		}

		window.draw(polygonR);
		menu.msgBoxBig("test");
	}
	if (config->auswahl <= 4)
	{
		// Polygonzug, der Kreis ausfüllt

		const unsigned int radius = 225;
		const unsigned int xabstand = 750;
		const unsigned int yabstand = 40;

		// VertexArray erstellen
		sf::VertexArray polygonC(sf::LinesStrip, config->dim[2]);
		// Zufällige Positionen für die Eckpunkte generieren
		for (unsigned int i = 0; i < config->dim[2]; ++i)
		{
			int x = myT::random(0, 2 * radius - 1) + xabstand;
			int h = x - xabstand - radius;
			int y = myT::random(0, (int)(std::sqrt(radius * radius - h * h)));
			y = myT::random(0, 2) == 0 ? yabstand + radius + y : yabstand + radius - y;
			polygonC[i].position = sf::Vector2f((float) x, (float) y);
			polygonC[i].color = sf::Color::Blue;
		}

		window.draw(polygonC);
	}
	if (config->auswahl <= 4)
	{
		// ausgefüllter Polygonzug, der Dreieck ausfüllt

		const unsigned int seite = 500;
		const unsigned int hoehe = 350;
		const unsigned int xabstand = 725;
		const unsigned int yabstand = 500;
		unsigned int h1 = (int)(seite / 2);
		//bool paused = false;

		// VertexArray erstellen
		sf::VertexArray polygonT(sf::LinesStrip, config->dim[3]);
		// Zufällige Positionen für die Eckpunkte generieren
		for (unsigned int i = 0; i < config->dim[3]; ++i)
		{
			int x = myT::random(0, seite - 1) + xabstand;
			int h2 = std::abs(static_cast<int>(x - xabstand - h1));
			int y = yabstand;
			unsigned int h3 = 0;
			if (h2 != 0)
			{
				y += hoehe;
				if (h2 < 0)
				{
					h2 = -h2;
				}
				h3 = (unsigned int)(std::max(hoehe - hoehe * h2 / h1 , 1u) - 1);
				y -= myT::random(0, (unsigned int)h3);
			}
			/*
			if (y < 0)
			{
				paused = true;
				menu.msgBoxBig("x=" + std::to_string(x)
					+ " , y=" + std::to_string(y)
					+ " , h1=" + std::to_string(h1)
					+ " , h2=" + std::to_string(h2)
					+ " , h3=" + std::to_string(h3)
					+ " , d=" + std::to_string(h2 / h1)
					+ " , d=" + std::to_string(hoehe * h2 / h1)
					+ " , d=" + std::to_string((hoehe - hoehe * h2 / h1))
					+ " , d=" + std::to_string(((hoehe - hoehe * h2 / h1) - 1))
				);
			}
			*/
			polygonT[i].position = sf::Vector2f((float)x, (float)y);
			polygonT[i].color = sf::Color::Green;
		}

		window.draw(polygonT);
		/*window.display();
		if (paused) {
			makePause(window);
		}			
		*/
	}
	if (config->auswahl <= 4)
	{
		// gezogener Polygonzug, der Kreisring ausfüllt
		// er ist nicht mehr geschlossen (wenn er das in Java überhaupt sauber war),
		// ansonsten müsste ich gegen Ende immer überprüfen, ob ich den Startpunkt erreichen kann ...

		unsigned int* x = new unsigned int[config->dim[4]];
		unsigned int* y = new unsigned int[config->dim[4]];
		const unsigned int xabstand = 250;
		const unsigned int yabstand = 475;

		/*
		sf::CircleShape circleA((float)config->KrAradius);
		circleA.setFillColor(sf::Color::Transparent);
		circleA.setOutlineColor(sf::Color::Blue);
		circleA.setOutlineThickness(1.f);
		//circleA.setFillColor(sf::Color::Blue);
		circleA.setOrigin(circleA.getRadius(), circleA.getRadius());
		circleA.setPosition((float)(xabstand + config->KrAradius), (float)(yabstand + config->KrAradius));

		sf::CircleShape circleI((float)config->KrIradius);
		circleI.setFillColor(sf::Color::Transparent);
		circleI.setOutlineColor(sf::Color::Blue);
		circleI.setOutlineThickness(1.f);
		//circleI.setFillColor(sf::Color::Blue);
		circleI.setOrigin(circleI.getRadius(), circleI.getRadius());
		circleI.setPosition((float)(xabstand + config->KrAradius), (float)(yabstand + config->KrAradius));

		std::string msg = "";
		*/

		// VertexArray erstellen
		sf::VertexArray polygonCc(sf::LinesStrip, config->dim[4]);
		x[0] = xabstand;
		y[0] = config->KrAradius + yabstand;
		polygonCc[0].position = sf::Vector2f((float)x[0], (float)y[0]);
		polygonCc[0].color = sf::Color(153, 50, 204);
		// Zufällige Positionen für die Eckpunkte generieren
		//for (unsigned int i = 1; i < config->dim[4] - 1; ++i)
		for (unsigned int i = 1; i < config->dim[4]; ++i)
		{
			bool nochnichtfertig = true;
			// Endlosschleifenabbruch
			unsigned int sofortraus = 0;
			do
			{
				x[i] = myT::random(0, 2 * config->KrAradius - 1) + xabstand;
				int x0 = x[i] - xabstand - config->KrAradius;
				double py = std::max(std::sqrt(config->KrAradius * config->KrAradius - x0 * x0), 1.) - 1;
				int y0 = myT::random(0, (unsigned int)(py));
				y0 = myT::random(0, 2) == 0 ? y0 : -y0;
				y[i] = y0 + yabstand + config->KrAradius;

				// erster Test, ob y-Wert außerhalb Innenkreis liegt
				if (std::sqrt(x0 * x0 + y0 * y0) > config->KrIradius)
				{
					//msg += "py > rI : " + std::to_string(std::sqrt(x0 * x0 + y0 * y0)) + "\n";

					// der Richtungsvektor
					int vx = x[i] - x[i - 1];
					int vy = y[i] - y[i - 1];
					// Vergleich mit 0 ist ja in C++ bei Fließkomma gefährlich
					// deswegen habe ich auf int umgestellt
					if ((vx != 0) || (vy != 0))
					{
						// aufeinanderfolgende Punkte sind nicht gleich
						// also Normalenvektor zur Verbindungsgeraden aufstellen
						double nx = (double)vy;
						double ny = (double)-vx;
						// Normalenvektor auf Länge 1 bringen
						double nl = std::sqrt(nx * nx + ny * ny);
						nx /= nl;
						ny /= nl;
						// Abstand von Nullpunkt, d.h. Kreisringmitte, zu Gerade berechnen
						// und mit Innenradius vergleichen
						if (std::abs(nx * x0 + ny * y0) > config->KrIradius)
						{
							nochnichtfertig = false;
							//msg += "p1p2 > rI = " + std::to_string(std::abs(nx * x0 + ny * y0)) + "\n";
						}
						++sofortraus;
					}
				}
			} while (nochnichtfertig);
			// ich gehe jetzt davon aus, dass irgendwann ein Punkt gefunden wird
			//} while ((nochnichtfertig) && (sofortraus <= 2000));

			//window.draw(polygonCc);
			//window.display();
			//makePause(window);

			/*
			if (sofortraus > 20000)
			{
				// nächster Punkt wird 'einfach' als vorhergehender gesetzt
				// wenn dieser Punkt schon vorhanden ist
				if (i > 2)
				{
					x[i] = x[i - 2];
					y[i] = y[i - 2];
				}
				else
				{
					x[i] = x[i - 1];
					y[i] = y[i - 1];
				}
			}
			*/

			polygonCc[i].position = sf::Vector2f((float)x[i], (float)y[i]);
			polygonCc[i].color = sf::Color(153, 50, 204);
		}

		/*
		// der letzte Punkt muß eine Brücke zum ersten schlagen
		// wenn aber der letzte Weg sozusagen um den Innenkreis herum verlief
		// wird dieser eventuell umgefärbt (nicht bei gezogenem Polygon)
		x[config->dim[4] - 1] = config->KrAradius + xabstand;
		y[config->dim[4] - 1] = y[config->dim[4] - 2] < config->KrAradius + yabstand ? yabstand : 2 * config->KrAradius + yabstand;
		//x[config->dim[4] - 1] = x[config->dim[4] - 2];
		//y[config->dim[4] - 1] = y[config->dim[4] - 2];
		polygonCc[config->dim[4] - 1].position = sf::Vector2f((float)x[config->dim[4] - 1], (float)y[config->dim[4] - 1]);
		polygonCc[config->dim[4] - 1].color = sf::Color(153, 50, 204);
		*/

		window.draw(polygonCc);
		//window.draw(circleA);
		//window.draw(circleI);
		
		//menu.msgBoxBig(msg);
		//window.display();
		//makePause(window);

		delete[] x;
		delete[] y;
	}
	else if (config->auswahl == 5)
	{
		// Apfelmännchen

		//window.clear(sf::Color::White);

		// die Funktion lautet 'z^2+c'
		// wo c den Bereich durchläuft
		// und z iteriert wird
		config->qrzf = config->rzf * config->rzf;
		config->qizf = config->izf * config->izf;

		// eigentlich nur im Randmodus nötig, das was ich gerade weggelöscht habe
		// Java-Compiler meckert aber sonst
		// mal sehen wie es C++ handhabt, wenn ich das wieder verstehe und genauer anschauen kann/muss
		// und ja fast komplett umschreiben darf

		if (config->neuoderalt == 3)
		{
			// das Original-Apfelmännchen
			config->crmgrenzeAlt = config->crmgrenze;
			config->crpgrenzeAlt = config->crpgrenze;
			config->cimgrenzeAlt = config->cimgrenze;
			config->cipgrenzeAlt = config->cipgrenze;
			config->crstepAlt = config->crstep;
			config->cistepAlt = config->cistep;

			if (config->exponent == 2)
			{
				config->crmgrenze = -2.1;
				config->crpgrenze = 0.7;
				config->cimgrenze = -1.2375;
				config->cipgrenze = 1.2375;
			}
			else if (config->exponent == 3)
			{
				config->crmgrenze = -1.35;
				config->crpgrenze = 1.25;
				config->cimgrenze = -1.4;
				config->cipgrenze = 1.4;
			}
			else
			{
				config->crmgrenze = -1.45;
				config->crpgrenze = 1.15;
				config->cimgrenze = -1.1;
				config->cipgrenze = 1.1;
			}
			if ((config->exponent == 4) || (config->exponent == 6) || (config->exponent == 7))
			{
				config->cimgrenze = -1.2;
				config->cipgrenze = 1.2;
			}
			config->crstep = (config->crpgrenze - config->crmgrenze) / config->iend;
			config->cistep = (config->cipgrenze - config->cimgrenze) / (config->jend + 1);
			config->schwarzgrenze = 200;

			// Vorgabefarbe im 'Mittelpunkt'
			config->punktfarbe[config->iend * 50 + 250] = config->schwarzgrenze;
		}
		else if (config->neuoderalt == 2)
		{
			// ganz neuen Bereich festlegen
			config->crmgrenzeAlt = config->crmgrenze;
			config->crpgrenzeAlt = config->crpgrenze;
			config->cimgrenzeAlt = config->cimgrenze;
			config->cipgrenzeAlt = config->cipgrenze;
			config->crstepAlt = config->crstep;
			config->cistepAlt = config->cistep;

			double innercr = config->crmgrenze + config->ineu * config->crstep;
			double innerci = config->cimgrenze + config->jneu * config->cistep;
			double intervall = (config->crpgrenze - config->crmgrenze) / config->zoom;
			config->crmgrenze = innercr - intervall;
			config->crpgrenze = innercr + intervall;
			intervall = (config->cipgrenze - config->cimgrenze) / config->zoom;
			config->cimgrenze = innerci - intervall;
			config->cipgrenze = innerci + intervall;
			config->crstep = (config->crpgrenze - config->crmgrenze) / config->iend;
			config->cistep = (config->cipgrenze - config->cimgrenze) / config->jend;

			config->schwarzgrenze += 2 * config->zoom;
		}
		else if (config->neuoderalt == 0)
		{
			// alten Bereich wieder festlegen
			config->crmgrenze = config->crmgrenzeAlt;
			config->crpgrenze = config->crpgrenzeAlt;
			config->cimgrenze = config->cimgrenzeAlt;
			config->cipgrenze = config->cipgrenzeAlt;
			config->crstep = config->crstepAlt;
			config->cistep = config->cistepAlt;

			config->schwarzgrenze -= 2 * config->zoom;
		}
		// in allen anderen Fällen
		// letzten Bereich nochmals zeichnen

		//->textfield[config->vonkomponente[5]].setText("" + config->schwarzgrenze);

		// ääh farbe taucht nirgends mehr auf?? zumindest hier nicht mehr
		//farbe = ((int)(rand.nextDouble() * 12345)) % maxfarbe;
		//config->farbe = myT::random(0, 12345 - 1) % config->maxfarbe;
		// und ich schiebe das auch ins config (auch hier, weil es übersichtlicher wird und keine Extraparameter bei Funktionsaufrufen braucht
		//std::vector<sf::Color> acolor;
		//std::vector<sf::Color> arcolor;
		//std::vector<sf::Color> agcolor;
		//std::vector<sf::Color> abcolor;
		for (unsigned int c = 0; c < config->schwarzgrenze; ++c) config->acolor.push_back(sf::Color(myT::random(0, 255), myT::random(0, 255), myT::random(0, 255)));
		for (unsigned int c = 0; c < config->schwarzgrenze; ++c) config->arcolor.push_back(sf::Color(myT::random(0, 205) + 50, myT::random(0, 205) + 50, 0));
		for (unsigned int c = 0; c < config->schwarzgrenze; ++c) config->agcolor.push_back(sf::Color(myT::random(0, 255), 0, myT::random(0, 255)));
		for (unsigned int c = 0; c < config->schwarzgrenze; ++c) config->abcolor.push_back(sf::Color(0, myT::random(0, 205) + 50, myT::random(0, 205) + 50));

		// irgendwann mit der Maussteuerung
		//->window.setColor(Color.black);
		//->Font ffont = new Font("Tahoma", Font.PLAIN, 11);
		//->window.setFont(ffont);
		// die Koordinaten setzen
		//->window.drawString("i-Wert", 201, 40);
		for (int i = 0; i <= (int)(config->iend / 50); ++i)
		{
			//->std::string s = "   " + (i * 50);
			//->s = s.substring(s.length() - 4);
			//->window.drawString(s, 194 + i * 49, 55);
			//->window.drawString(s, 194 + i * 49, 925);
		}
		//->window.drawString("j-Wert", 149, 69);
		for (int i = 0; i <= (int)(config->jend / 50); ++i)
		{
			//->std::string s = "  " + (i * 50);
			//->s = s.substring(s.length() - 3);
			//->window.drawString(s, 178, 69 + i * 49);
			//->window.drawString(s, 1356, 69 + i * 49);
		}

		if (config->modus = 'P')
		{
			// Pixelmalerei
			config->lupe = 0;
			for (int j = 0; j <= config->jend; ++j)
			{
				for (int i = 0; i <= config->iend; ++i)
				{
					FarbeBestimmen(window, config, i, j, true);
				}
			}
		}
		else
		{
			// Randabsuchen
			config->lupe = 0;
			unsigned int janf = 0;
			unsigned int ianf = 0;
			int i = ianf;
			int j = janf;
			int aktuellefarbe;

			if (config->neuoderalt == 3)
			{
				// den inneren schwarzen Bereich vorbestimmen
				// Voraussetzung ist hierfür,
				// daß der Punkt (575,425) für jeden Exponenten im Schwarzbereich liegt
				int ii = 575;
				int jj = 425;
				FarbeBestimmen(window, config, ii, jj, false);
				while (config->punktfarbe[config->iend * jj + ii] == config->schwarzgrenze)
				{
					// Punkte weder anzeigen noch Farbe wirklich setzen
					config->punktfarbe[config->iend * jj + ii] = 0;
					--ii;
					FarbeBestimmen(window, config, ii, jj, false);
				}
				// linker Randpunkt gefunden
				// jetzt Rand 'abklappern'
				SuchePunkte(window, config, ii + 1, jj, config->schwarzgrenze, 0);
			}

			// zur Verdeutlichung der möglichen Konstellationen
			// Grafiken mit folgenden Symbolen
			// + = gewünschte Farbe
			// - = unerwünschte Farbe
			// · = keine Farbe

			while (j <= config->jend)
			{
				while (i <= config->iend)
				{
					aktuellefarbe = config->punktfarbe[config->iend * j + i];
					if (aktuellefarbe == 0)
					{
						// hier wird nichts gemalt

						// in diesem Punkt war man noch nicht
						// ·
						// also zuerst Farbe des Punktes bestimmen
						FarbeBestimmen(window, config, i, j, true);
						aktuellefarbe = config->punktfarbe[config->iend * j + i];

						// dann das zugehörige Gebiet umkreisen

						// Startrichtung ist Ost,
						// d.h. von Osten wird jeder Startpunkt anfänglich erreicht
						// Richtungsabfolge innerhalb Suche ist Ost=0 Süd=1 West=2 Nord=3 Süd...,

						// kommt man von Westen (Richtung Ost)
						// in einen gültigen Punkt (Punkt gleicher Farbe) wird versucht
						// in südlicher Richtung von ihm aus weiterzusuchen
						// kommt man von Norden (Richtung Süd) wird versucht
						// in westlicher Richtung weiterzusuchen
						// d.h. die Richtungssuche in gültigen Punkten läuft im Uhrzeigersinn

						// aber kommt man von irgendeiner Richtung X
						// in einen ungültigen Punkt (Punkt anderer Farbe oder außerhalb Bereichs)
						// wird vom gültigen Vorgängerpunkt aus in der Richtung weitergesucht,
						// die gegen den Uhrzeigersinn nach X kommt

						SuchePunkte(window, config, i, j, aktuellefarbe, j);
					}
					else if (aktuellefarbe < 0)
					{
						// hier wird nichts gemalt

						// in diesem Punkt war man
						// +
						// aber man hat noch nicht von hier aus gesucht
						// Farbe richtigstellen
						config->punktfarbe[config->iend * j + i] = -aktuellefarbe;

						// nun Suche wie oben
						SuchePunkte(window, config, i, j, -aktuellefarbe, j);
					}
					else
					{
						// hier wird eventuell gemalt

						// dieser Punkt hat schon eine Farbe
						// also nachfolgende Punkte testen
						if (i == config->iend)
						{
							// Rand erreicht
							// Wechsel in neue Zeile vorbereiten
							++i;
						}
						else if (config->punktfarbe[config->iend * j + i + 1] == 0)
						{
							// nächster Punkt hat keine Farbe
							// +·
							// also rechten Randpunkt in dieser Farbe suchen
							int ii = i;
							do ++ii;
							while ((ii < config->iend) && (config->punktfarbe[config->iend * j + ii] == 0));
							if (config->punktfarbe[config->iend * j + ii] == aktuellefarbe)
							{
								// Farbrandpunkt gefunden
								// +··········+
								// nun testen,
								// ob Punkt rechts vom linken Randpunkt aber auch diese Farbe hat
								FarbeBestimmen(window, config, i + 1, j, true);
								if (config->punktfarbe[config->iend * j + i + 1] == aktuellefarbe)
								{
									// ++·········+
									// diese Linie kann also auf jeden Fall gezogen werden

									// nun noch testen, ob rechts vom rechten Randpunkt
									// auch ein gleichfarbiger Punkt sitzt
									// das wäre dann die Sonderkonstellation
									// ++·········++······
									// in dem Fall wird der rechte Randpunkt wieder Startpunkt
									// im nächsten Durchlauf

									// Test auf Sonderkonstellation
									if (ii < config->iend)
									{
										// der rechte Randpunkt ist nicht genereller Randpunkt

										bool neuefarbe = false;
										if (config->punktfarbe[config->iend * j + ii + 1] == 0)
										{
											FarbeBestimmen(window, config, ii + 1, j, true);
											neuefarbe = true;
										}
										// Sonderkonstellation
										// ++·········++······
										// eingetreten oder
										if (config->punktfarbe[config->iend * j + ii + 1] != aktuellefarbe)
										{
											// rechter Randpunkt ist echter Farbrandpunkt
											// ++·········+-······
											// Farbe rechts negieren, falls sie noch nicht vorlag
											if (neuefarbe)
											{
												config->punktfarbe[config->iend * j + ii + 1] = -config->punktfarbe[config->iend * j + ii + 1];
											}
										}
									}

									LinieZiehen(window, config, aktuellefarbe, i, ii, j);
									i = ii + 1;
								}
								else
								{
									// aber nächster Punkt hat eine andere Farbe
									// +-········+
									// Farbe rechts negieren
									config->punktfarbe[config->iend * j + i + 1] = -config->punktfarbe[config->iend * j + i + 1];
									++i;
								}
							}
							else
							{
								// Gebiet rechts davon noch nicht erforscht
								// +·········-
								// oder
								// +··········Rand
								++i;
							}
						}
						else if (config->punktfarbe[config->iend * j + i + 1] != aktuellefarbe)
						{
							// nächster Punkt hat eine andere Farbe
							// +-
							++i;
						}
						else
						{
							// nächster Punkt hat gleiche Farbe
							// ++
							// also weitermachen
							// bis zum letzten nächsten Punkt mit gleicher Farbe
							++i;
						}
					}
				}
				i = ianf;
				++j;
			}
		}

		//->textfield[config->vonkomponente[5] + 3].setText("" + config->ineu);
		//->textfield[config->vonkomponente[5] + 4].setText("" + config->jneu);

		config->modus = 'R';
		//->textfield[config->vonkomponente[5] + 6].setText(modus);

	}
	else if (config->auswahl == 6)
	{
		// Schneeflocke
		int xmitte = 850;
		int ymitte = 450;
		int tiefenzaehler = 0;

		if (config->second == 0)
		{
			config->realetiefe = config->schneetiefe;
		}
		else
		{
			config->realetiefe = config->schneetiefe / 2;
		}

		// Zufallsauswahl: Teilung zwischen 3 und 5
		unsigned int teilung = myT::random(0, 2) + 3;
		int halbkante = config->schneekante / 2;
		halbkante = (int)(3 * halbkante / teilung);

		// das lasse ich erst mal
		//std::vector<sf::Vertex> lines;

		// Parameter sind
		// das Window
		// die Konfiguration
		//// der Vektor der Vertexe
		// Startpunkt x und y
		// die Richtung (0, 1, 2 oder 3 für ost, süd, west oder nord)
		// die Länge der Seite
		// die Rechentiefe
		// die Teilung
		
		// in Richtung
		SeiteBauen(window, config, xmitte - halbkante, ymitte - halbkante, 0, 2 * halbkante, tiefenzaehler, teilung);
		SeiteBauen(window, config, xmitte + halbkante, ymitte - halbkante, 1, 2 * halbkante, tiefenzaehler, teilung);
		SeiteBauen(window, config, xmitte + halbkante, ymitte + halbkante, 2, 2 * halbkante, tiefenzaehler, teilung);
		SeiteBauen(window, config, xmitte - halbkante, ymitte + halbkante, 3, 2 * halbkante, tiefenzaehler, teilung);
		// in Gegenrichtung
		SeiteBauen(window, config, xmitte + halbkante, ymitte - halbkante, 2, 2 * halbkante, tiefenzaehler, teilung);
		SeiteBauen(window, config, xmitte + halbkante, ymitte + halbkante, 3, 2 * halbkante, tiefenzaehler, teilung);
		SeiteBauen(window, config, xmitte - halbkante, ymitte + halbkante, 0, 2 * halbkante, tiefenzaehler, teilung);
		SeiteBauen(window, config, xmitte - halbkante, ymitte - halbkante, 1, 2 * halbkante, tiefenzaehler, teilung);
	}
	else if (config->auswahl == 7)
	{
		if (config->second == 0) config->realetiefe = config->dreitiefe;
		else config->realetiefe = config->dreitiefe / 2;

		// Schneeflocke mit Dreiecken
		unsigned int tiefenzaehler = 0;

		// Zufallsauswahl: Teilung zwischen 3 und 8
		unsigned int teilung = myT::random(0, 5) + 3;		

		// und die Malgrundfarbe
		unsigned int dfarbe;
		unsigned int rr = myT::random(0, 3);
		dfarbe = rr == 1 ? 72 : 71;
		dfarbe = rr == 2 ? 73 : dfarbe;

		// die Seitenlänge der aufgesetzten Dreiecke
		double faktor;
		//do faktor = 1. * rand() / RAND_MAX; while ((faktor < 0.4) || (faktor > 0.8));
		do faktor = 1. * rand() / RAND_MAX; while ((faktor < 0.4) || (faktor > 0.6));

		// Parameter sind
		// Startpunkt x und y
		// die Richtung als trigonometrischer Winkel
		// die Länge der Kante
		// die Rechentiefe
		// die Teilung
		// die Färbung
		double idkante = config->dreikante / std::sqrt(3);
		DreiSeiteBauen(window, config, std::cos(7 * PI / 6.0) * idkante, std::sin(7 * PI / 6.0) * idkante, PI / 3.0, config->dreikante, tiefenzaehler, teilung, faktor, dfarbe);
		DreiSeiteBauen(window, config, std::cos(PI / 2.0) * idkante, std::sin(PI / 2.0) * idkante, 5 * PI / 3.0, config->dreikante, tiefenzaehler, teilung, faktor, dfarbe);
		DreiSeiteBauen(window, config, std::cos(11 * PI / 6.0) * idkante, std::sin(11 * PI / 6.0) * idkante, PI, config->dreikante, tiefenzaehler, teilung, faktor, dfarbe);
		if (config->second >= 2)
		{
			// Gegenrichtung
			DreiSeiteBauen(window, config, std::cos(7 * PI / 6.0) * idkante, std::sin(7 * PI / 6.0) * idkante, 0, config->dreikante, tiefenzaehler, teilung, faktor, dfarbe);
			DreiSeiteBauen(window, config, std::cos(PI / 2.0) * idkante, std::sin(PI / 2.0) * idkante, 4 * PI / 3.0, config->dreikante, tiefenzaehler, teilung, faktor, dfarbe);
			DreiSeiteBauen(window, config, std::cos(11 * PI / 6.0) * idkante, std::sin(11 * PI / 6.0) * idkante, 2 * PI / 3.0, config->dreikante, tiefenzaehler, teilung, faktor, dfarbe);
		}
	}

}

/*
 	public void farbeSetzen(Graphics G,int i)
	{
		// Hintergrund-, Vordergrund- und Farbe an sich setzen
		int rAnteil = (int)(rand.nextDouble()*200+55);
		int gAnteil = (int)(rand.nextDouble()*200+55);
		int bAnteil = (int)(rand.nextDouble()*200+55);
		if(i == 0) setBackground(new Color(rAnteil,gAnteil,bAnteil));
		else if(i == 1) setForeground(new Color((int)(rAnteil/10),(int)(gAnteil/10),(int)(bAnteil/10)));
		else if(i == 2) G.setColor(new Color(rAnteil,gAnteil,bAnteil));
		else if(i == 11) G.setColor(new Color((int)(rand.nextDouble()*150+105),(int)(rand.nextDouble()*150+105),0));
		else if(i == 12) G.setColor(new Color((int)(rand.nextDouble()*150+105),0,(int)(rand.nextDouble()*150+105)));
		else if(i == 13) G.setColor(new Color(0,(int)(rand.nextDouble()*150+105),(int)(rand.nextDouble()*150+105)));
	}
*/