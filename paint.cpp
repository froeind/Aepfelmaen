
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
		//->G.setColor(Color.white);
		sxe = sx - ((sr - 1) % 2) * sl;
		sye = sy - ((sr - 2) % 2) * sl;
		//->G.drawLine(sx, sy, sxe, sye);
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
			//->G.setColor(Color.white);
			sxe = sx - ((sr - 1) % 2) * sl3;
			sye = sy - ((sr - 2) % 2) * sl3;
			//->G.drawLine(sx, sy, sxe, sye);
			//->G.setColor(Color.white);
			sxa = sx - ((sr - 1) % 2) * (sl3 + sl3m);
			sya = sy - ((sr - 2) % 2) * (sl3 + sl3m);
			sxe = sxa - ((sr - 1) % 2) * sl3;
			sye = sya - ((sr - 2) % 2) * sl3;
			//->G.drawLine(sxa, sya, sxe, sye);
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

/*
public void DreiSeiteBauen(sf::RenderWindow& window, Config* config, double sx, double sy, double alpha, double sl, int stz, unsigned int& teilung, double& faktor)
{
	double sxa = 0;
	double sya = 0;
	double sxe = 0;
	double sye = 0;
	double sl3 = 0;
	double sl3m = 0;

	if (stz == realetiefe)
	{
		// Maximaltiefe erreicht, also Kante setzen
		////////farbeSetzen(G, dfarbe);
		sxe = sx + Math.cos(alpha) * sl;
		sye = sy + Math.sin(alpha) * sl;
		G.drawLine(dxmitte + (int)sx, dymitte - (int)sy, dxmitte + (int)sxe, dymitte - (int)sye);
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

		if ((second % 2) == 0)
		{
			// zwei Kantenstücke, die gezeichnet werden
			farbeSetzen(G, dfarbe);
			sxe = sx + Math.cos(alpha) * sl3;
			sye = sy + Math.sin(alpha) * sl3;
			G.drawLine(dxmitte + (int)sx, dymitte - (int)sy, dxmitte + (int)sxe, dymitte - (int)sye);
			farbeSetzen(G, dfarbe);
			sxa = sx + Math.cos(alpha) * (sl3 + sl3m);
			sya = sy + Math.sin(alpha) * (sl3 + sl3m);
			sxe = sx + Math.cos(alpha) * sl;
			sye = sy + Math.sin(alpha) * sl;
			G.drawLine(dxmitte + (int)sxa, dymitte - (int)sya, dxmitte + (int)sxe, dymitte - (int)sye);
		}
		else
		{
			// auch mit Dreieck besetzen
			DreiSeiteBauen(window, config, sx, sy, alpha, sl3, stz + 1, teilung, faktor);
			sxa = sx + Math.cos(alpha) * (sl3 + sl3m);
			sya = sy + Math.sin(alpha) * (sl3 + sl3m);
			DreiSeiteBauen(window, config, sxa, sya, alpha, sl3, stz + 1, teilung, faktor);
		}
		// zwei neue Dreieckseiten
		sxa = sx + Math.cos(alpha) * sl3;
		sya = sy + Math.sin(alpha) * sl3;

		// 'acos'-Argument muß im Definitionsbereich bleiben
		double argument = sl3m / (sl * 2 * faktor);
		argument = argument < -1 ? -1 : argument;
		argument = argument > 1 ? 1 : argument;
		double alphax = Math.acos(argument);
		double alphaneu = (alpha + alphax) % (2 * Math.PI);
		DreiSeiteBauen(window, config, sxa, sya, alphaneu, faktor * sl, stz + 1, teilung, faktor);
		sxa += Math.cos(alphaneu) * faktor * sl;
		sya += Math.sin(alphaneu) * faktor * sl;
		alphaneu = (alpha + 2 * Math.PI - alphax) % (2 * Math.PI);
		DreiSeiteBauen(window, config, sxa, sya, alphaneu, faktor * sl, stz + 1, teilung, faktor);
	}
}
*/

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
	/*
	if (config->auswahl == 5)
	{
		// Apfelmännchen

		// die Funktion lautet 'z^2+c'
		// wo c den Bereich durchläuft
		// und z iteriert wird
		config->qrzf = config->rzf * config->rzf;
		config->qizf = config->izf * config->izf;

		// eigentlich nur im Randmodus nötig
		// Java-Compiler meckert aber sonst
		// mal sehen wie es C++ handhabt, wenn ich das wieder verstehe und genauer anschauen kann/muss
		//punktfarbe = new int[iend + 1][jend + 1];	
		config->punktfarbe.resize(config->iend + 1);
		for (auto& row : config->punktfarbe)
		{
			row.resize(config->jend + 1);
		}

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
			config->crstep = (config->crpgrenze - config->crmgrenze) / (config->iend + 1);
			config->cistep = (config->cipgrenze - config->cimgrenze) / (config->jend + 1);
			config->schwarzgrenze = 200;

			// Vorgabefarbe im 'Mittelpunkt'
			//punktfarbe[250][50] = schwarzgrenze;
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
			config->crstep = (config->crpgrenze - config->crmgrenze) / (config->iend + 1);
			config->cistep = (config->cipgrenze - config->cimgrenze) / (config->jend + 1);

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
		config->farbe = myT::random(0, 12345 - 1) % config->maxfarbe;
		// das muss ich noch übersetzen
		//acolor = new Color[config->schwarzgrenze];
		//arcolor = new Color[config->schwarzgrenze];
		//agcolor = new Color[config->schwarzgrenze];
		//abcolor = new Color[config->schwarzgrenze];
		//for (int c = 0; c < config->schwarzgrenze; ++c) acolor[c] = new Color((int)(rand.nextDouble() * 256), (int)(rand.nextDouble() * 256), (int)(rand.nextDouble() * 256));
		//for (int c = 0; c < config->schwarzgrenze; ++c) arcolor[c] = new Color((int)(rand.nextDouble() * 206 + 50), (int)(rand.nextDouble() * 206 + 50), 0);
		//for (int c = 0; c < config->schwarzgrenze; ++c) agcolor[c] = new Color((int)(rand.nextDouble() * 256), 0, (int)(rand.nextDouble() * 256));
		//for (int c = 0; c < config->schwarzgrenze; ++c) abcolor[c] = new Color(0, (int)(rand.nextDouble() * 206 + 50), (int)(rand.nextDouble() * 206 + 50));

		//->window.setColor(Color.black);
		//->Font ffont = new Font("Tahoma", Font.PLAIN, 11);
		//->window.setFont(ffont);
		// die Koordinaten setzen
		//->window.drawString("i-Wert", 201, 40);
	for (unsigned int i = 0; i <= (config->iend + 1) / 50; ++i)
	{
		//->std::string s = "   " + (i * 50);
		//->s = s.substring(s.length() - 4);
		//->window.drawString(s, 194 + i * 49, 55);
		//->window.drawString(s, 194 + i * 49, 925);
	}
	//->window.drawString("j-Wert", 149, 69);
	for (unsigned int i = 0; i <= (config->jend + 1) / 50; ++i)
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
		for (unsigned int j = 0; j <= config->jend; ++j)
		{
			for (unsigned int i = 0; i <= config->iend; ++i)
			{
				//-<FarbeBestimmen(i, j, g, true);
			}
		}
	}
	else
	{
		// Randabsuchen
		config->lupe = 0;
		unsigned int janf = 0;
		unsigned int ianf = 0;
		unsigned int i = ianf;
		unsigned int j = janf;
		int aktuellefarbe;

		if (config->neuoderalt == 3)
		{
			// den inneren schwarzen Bereich vorbestimmen
			// Voraussetzung ist hierfür,
			// daß der Punkt (575,425) für jeden Exponenten im Schwarzbereich liegt
			unsigned int ii = 575;
			unsigned int jj = 425;
			//->FarbeBestimmen(ii, jj, g, false);
			while (config->punktfarbe[ii][jj] == config->schwarzgrenze)
			{
				// Punkte weder anzeigen noch Farbe wirklich setzen
				config->punktfarbe[ii][jj] = 0;
				--ii;
				//->FarbeBestimmen(ii, jj, g, false);
			}
			// linker Randpunkt gefunden
			// jetzt Rand 'abklappern'
			//->SuchePunkte(ii + 1, jj, config->schwarzgrenze, g, 0);
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
				aktuellefarbe = config->punktfarbe[i][j];
				if (aktuellefarbe == 0)
				{
					// hier wird nichts gemalt

					// in diesem Punkt war man noch nicht
					// ·
					// also zuerst Farbe des Punktes bestimmen
					//->FarbeBestimmen(i, j, g, true);
					aktuellefarbe = config->punktfarbe[i][j];

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

					//->SuchePunkte(i, j, aktuellefarbe, g, j);
				}
				else if (aktuellefarbe < 0)
				{
					// hier wird nichts gemalt

					// in diesem Punkt war man
					// +
					// aber man hat noch nicht von hier aus gesucht
					// Farbe richtigstellen
					config->punktfarbe[i][j] = -aktuellefarbe;

					// nun Suche wie oben
					//->SuchePunkte(i, j, -aktuellefarbe, g, j);
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
					else if (config->punktfarbe[i + 1][j] == 0)
					{
						// nächster Punkt hat keine Farbe
						// +·
						// also rechten Randpunkt in dieser Farbe suchen
						unsigned int ii = i;
						do ++ii;
						while ((ii < config->iend) && (config->punktfarbe[ii][j] == 0));
						if (config->punktfarbe[ii][j] == aktuellefarbe)
						{
							// Farbrandpunkt gefunden
							// +··········+
							// nun testen,
							// ob Punkt rechts vom linken Randpunkt aber auch diese Farbe hat
							//->FarbeBestimmen(i + 1, j, g, true);
							if (config->punktfarbe[i + 1][j] == aktuellefarbe)
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
									if (config->punktfarbe[ii + 1][j] == 0)
									{
										//->FarbeBestimmen(ii + 1, j, g, true);
										neuefarbe = true;
									}
									// Sonderkonstellation
									// ++·········++······
									// eingetreten oder
									if (config->punktfarbe[ii + 1][j] != aktuellefarbe)
									{
										// rechter Randpunkt ist echter Farbrandpunkt
										// ++·········+-······
										// Farbe rechts negieren, falls sie noch nicht vorlag
										if (neuefarbe)
										{
											config->punktfarbe[ii + 1][j] = -config->punktfarbe[ii + 1][j];
										}
									}
								}

								//->LinieZiehen(aktuellefarbe, i, ii, j, g);
								i = ii + 1;
							}
							else
							{
								// aber nächster Punkt hat eine andere Farbe
								// +-········+
								// Farbe rechts negieren
								config->punktfarbe[i + 1][j] = -config->punktfarbe[i + 1][j];
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
					else if (config->punktfarbe[i + 1][j] != aktuellefarbe)
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
	*/
	else if (config->auswahl == 6)
	{
		// Schneeflocke
		int xmitte = 400;
		int ymitte = 270;
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

		// Parameter sind
		// Startpunkt x und y
		// die Richtung (0, 1, 2 oder 3 für ost, süd, west oder nord)
		// die Länge der Seite
		// die Rechentiefe
		// das Grafikobjekt
		// die Teilung
		// Richtung
		SeiteBauen(window, config, xmitte - halbkante, ymitte - halbkante, 0, 2 * halbkante, tiefenzaehler, teilung);
		SeiteBauen(window, config, xmitte + halbkante, ymitte - halbkante, 1, 2 * halbkante, tiefenzaehler, teilung);
		SeiteBauen(window, config, xmitte + halbkante, ymitte + halbkante, 2, 2 * halbkante, tiefenzaehler, teilung);
		SeiteBauen(window, config, xmitte - halbkante, ymitte + halbkante, 3, 2 * halbkante, tiefenzaehler, teilung);
		// Gegenrichtung
		SeiteBauen(window, config, xmitte + halbkante, ymitte - halbkante, 2, 2 * halbkante, tiefenzaehler, teilung);
		SeiteBauen(window, config, xmitte + halbkante, ymitte + halbkante, 3, 2 * halbkante, tiefenzaehler, teilung);
		SeiteBauen(window, config, xmitte - halbkante, ymitte + halbkante, 0, 2 * halbkante, tiefenzaehler, teilung);
		SeiteBauen(window, config, xmitte - halbkante, ymitte - halbkante, 1, 2 * halbkante, tiefenzaehler, teilung);
	}
	/*
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
		unsigned int rr = myT::random(0, 2);
		dfarbe = rr == 1 ? 12 : 11;
		dfarbe = rr == 2 ? 13 : dfarbe;

		// die Seitenlänge der aufgesetzten Dreiecke
		double faktor;
		do faktor = rand(); while ((faktor < 0.4) || (faktor > 0.8));

		// Parameter sind
		// Startpunkt x und y
		// die Richtung als trigonometrischer Winkel
		// die Länge der Kante
		// die Rechentiefe
		// die Teilung
		// die Färbung
		double idkante = config->dreikante / std::sqrt(3);
		DreiSeiteBauen(Math.cos(7 * Math.PI / 6.0) * idkante, Math.sin(7 * Math.PI / 6.0) * idkante, Math.PI / 3.0, config->dreikante, tiefenzaehler, teilung, faktor);
		DreiSeiteBauen(Math.cos(Math.PI / 2.0) * idkante, Math.sin(Math.PI / 2.0) * idkante, 5 * Math.PI / 3.0, config->dreikante, tiefenzaehler, teilung, faktor);
		DreiSeiteBauen(Math.cos(11 * Math.PI / 6.0) * idkante, Math.sin(11 * Math.PI / 6.0) * idkante, Math.PI, config->dreikante, tiefenzaehler, teilung, faktor);
		if (config->second >= 2)
		{
			// Gegenrichtung
			DreiSeiteBauen(Math.cos(7 * Math.PI / 6.0) * idkante, Math.sin(7 * Math.PI / 6.0) * idkante, 0, config->dreikante, tiefenzaehler, teilung, faktor);
			DreiSeiteBauen(Math.cos(Math.PI / 2.0) * idkante, Math.sin(Math.PI / 2.0) * idkante, 4 * Math.PI / 3.0, config->dreikante, tiefenzaehler, teilung, faktor);
			DreiSeiteBauen(Math.cos(11 * Math.PI / 6.0) * idkante, Math.sin(11 * Math.PI / 6.0) * idkante, 2 * Math.PI / 3.0, config->dreikante, tiefenzaehler, teilung, faktor);
		}
	}
	*/

}