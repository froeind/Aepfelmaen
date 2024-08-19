
#include "init.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

myA::Config::Config() {
	vonkomponente = new int[anzkomponenten];
	biskomponente = new int[anzkomponenten];
	dim = new unsigned int[5];
}
myA::Config::~Config() {
	delete[] vonkomponente;
	delete[] biskomponente;
	delete[] dim;
	//delete punktfarbe;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void myA::farbeSetzen(sf::RenderWindow& window, const unsigned int i)
{
	// Hintergrund-, Vordergrund- und Farbe an sich setzen
	const unsigned int rAnteil = myT::random(0, 199) + 55;
	const unsigned int gAnteil = myT::random(0, 199) + 55;
	const unsigned int bAnteil = myT::random(0, 199) + 55;
	/*
	if (i == 0) { setBackground(new Color(rAnteil, gAnteil, bAnteil)) };
	else if (i == 1) { setForeground(new Color((const unsigned int)(rAnteil / 10), (const unsigned int)(gAnteil / 10), (const unsigned int)(bAnteil / 10))) };
	else if (i == 2) { G.setColor(new Color(rAnteil, gAnteil, bAnteil)) };
	else if (i == 11) { G.setColor(new Color(myT::random(0, 149) + 105, myT::random(0, 149) + 105, 0)) };
	else if (i == 12) { G.setColor(new Color(myT::random(0, 149) + 105, 0, myT::random(0, 149) + 105)) };
	else if (i == 13) { G.setColor(new Color(0, myT::random(0, 149) + 105, myT::random(0, 149) + 105)) };
	*/
}

void myA::init(sf::RenderWindow& window, Config* config)
{
	farbeSetzen(window, 1);
	if (config->auswahl == 7)
	{ 
		//setBackground(Color.white); 
	}
	else
	{
		farbeSetzen(window, 0);
	}
	/*
	setLayout(null);
	label = new Label[anzkomponenten];
	textfield = new TextField[anzkomponenten];
	button = new Button[anzkomponenten];
	knopfabfrage = new KnopfAbfrage[anzkomponenten];
	vonkomponente = new int[anzkomponenten];
	biskomponente = new int[anzkomponenten];
	*/
	/*
	label[0] = new Label("Auswahl");
	label[0].setBounds(10, 10, 100, 20);
	add(label[0]);

	chx = new Choice();
	chx.add("apfelmann");
	chx.add("dreieckchen");
	chx.add("dreieckchen +");
	chx.add("dreieckchen i");
	chx.add("dreieckchen +i");
	chx.add("schneeflocke");
	chx.add("schneedeckchen");
	chx.add("kreisring");
	chx.add("kreisring 2");
	chx.add("dreieck");
	chx.add("kreis");
	chx.add("rechteck");
	ItemAbfrager ihy = new ItemAbfrager();
	chx.addItemListener(ihy);
	chx.setBounds(10, 35, 120, 20);
	add(chx);
	*/

	// Rechteck + Kreis + Dreieck
	for (unsigned int i = 1; i <= 3; ++i)
	{
		config->vonkomponente[i] = i;
		config->biskomponente[i] = i;
		config->dim[i] = 1000;
		/*
		label[i] = new Label("Kantenanzahl");
		label[i].setBounds(10, 70, 100, 20);
		add(label[i]);
		label[i].setVisible(false);
		textfield[i] = new TextField();
		textfield[i].setText("" + config->dim[i]);
		textfield[i].setBounds(10, 95, 120, 20);
		add(textfield[i]);
		textfield[i].setVisible(false);
		button[i] = new Button("Datenübergabe");
		knopfabfrage[i] = new KnopfAbfrage();
		button[i].addActionListener(knopfabfrage[i]);
		button[i].setBounds(10, 120, 120, 20);
		add(button[i]);
		button[i].setVisible(false);
		*/
	}

	// Kreisring hat Extraparameter Innenkreisradius
	config->vonkomponente[4] = 4;
	config->biskomponente[4] = 5;
	config->dim[4] = 1000;
	unsigned int loc = 4;

	/*
	label[vonkomponente[loc]] = new Label("Kantenanzahl");
	label[vonkomponente[loc]].setBounds(10, 70, 100, 20);
	add(label[vonkomponente[loc]]);
	label[vonkomponente[loc]].setVisible(false);
	textfield[vonkomponente[loc]] = new TextField();
	textfield[vonkomponente[loc]].setText("" + config->dim[vonkomponente[loc]]);
	textfield[vonkomponente[loc]].setBounds(10, 95, 120, 20);
	add(textfield[vonkomponente[loc]]);
	textfield[vonkomponente[loc]].setVisible(false);

	label[vonkomponente[loc] + 1] = new Label("Innenradius");
	label[vonkomponente[loc] + 1].setBounds(10, 120, 100, 20);
	add(label[vonkomponente[loc] + 1]);
	label[vonkomponente[loc] + 1].setVisible(false);
	textfield[vonkomponente[loc] + 1] = new TextField();
	textfield[vonkomponente[loc] + 1].setText("" + KrIradius);
	textfield[vonkomponente[loc] + 1].setBounds(10, 145, 120, 20);
	add(textfield[vonkomponente[loc] + 1]);
	textfield[vonkomponente[loc] + 1].setVisible(false);

	button[vonkomponente[loc]] = new Button("Datenübergabe");
	knopfabfrage[vonkomponente[loc]] = new KnopfAbfrage();
	button[vonkomponente[loc]].addActionListener(knopfabfrage[vonkomponente[loc]]);
	button[vonkomponente[loc]].setBounds(10, 170, 120, 20);
	add(button[vonkomponente[loc]]);
	button[vonkomponente[loc]].setVisible(false);
	*/

	// Apfelmännchen
	config->vonkomponente[5] = 6;
	config->biskomponente[5] = 13;
	loc = 5;

	/*
	label[vonkomponente[loc]] = new Label("Schwarzgrenze");
	label[vonkomponente[loc]].setBounds(10, 190, 100, 20);
	add(label[vonkomponente[loc]]);
	label[vonkomponente[loc]].setVisible(false);
	textfield[vonkomponente[loc]] = new TextField();
	textfield[vonkomponente[loc]].setText("" + schwarzgrenze);
	textfield[vonkomponente[loc]].setBounds(10, 215, 120, 20);
	add(textfield[vonkomponente[loc]]);
	textfield[vonkomponente[loc]].setVisible(false);

	label[vonkomponente[loc] + 1] = new Label("x-Wert");
	label[vonkomponente[loc] + 1].setBounds(10, 80, 100, 20);
	add(label[vonkomponente[loc] + 1]);
	label[vonkomponente[loc] + 1].setVisible(false);
	textfield[vonkomponente[loc] + 1] = new TextField();
	textfield[vonkomponente[loc] + 1].setText("" + rzf);
	textfield[vonkomponente[loc] + 1].setBounds(10, 105, 120, 20);
	add(textfield[vonkomponente[loc] + 1]);
	textfield[vonkomponente[loc] + 1].setVisible(false);

	label[vonkomponente[loc] + 2] = new Label("y-Wert");
	label[vonkomponente[loc] + 2].setBounds(10, 130, 100, 20);
	add(label[vonkomponente[loc] + 2]);
	label[vonkomponente[loc] + 2].setVisible(false);
	textfield[vonkomponente[loc] + 2] = new TextField();
	textfield[vonkomponente[loc] + 2].setText("" + izf);
	textfield[vonkomponente[loc] + 2].setBounds(10, 155, 120, 20);
	add(textfield[vonkomponente[loc] + 2]);
	textfield[vonkomponente[loc] + 2].setVisible(false);

	label[vonkomponente[loc] + 3] = new Label("i-Wert");
	label[vonkomponente[loc] + 3].setBounds(10, 310, 100, 20);
	add(label[vonkomponente[loc] + 3]);
	label[vonkomponente[loc] + 3].setVisible(false);
	textfield[vonkomponente[loc] + 3] = new TextField();
	textfield[vonkomponente[loc] + 3].setText("original");
	textfield[vonkomponente[loc] + 3].setBounds(10, 335, 120, 20);
	add(textfield[vonkomponente[loc] + 3]);
	textfield[vonkomponente[loc] + 3].setVisible(false);

	label[vonkomponente[loc] + 4] = new Label("j-Wert");
	label[vonkomponente[loc] + 4].setBounds(10, 360, 100, 20);
	add(label[vonkomponente[loc] + 4]);
	label[vonkomponente[loc] + 4].setVisible(false);
	textfield[vonkomponente[loc] + 4] = new TextField();
	textfield[vonkomponente[loc] + 4].setText("original");
	textfield[vonkomponente[loc] + 4].setBounds(10, 385, 120, 20);
	add(textfield[vonkomponente[loc] + 4]);
	textfield[vonkomponente[loc] + 4].setVisible(false);

	label[vonkomponente[loc] + 5] = new Label("Zoom");
	label[vonkomponente[loc] + 5].setBounds(10, 250, 100, 20);
	add(label[vonkomponente[loc] + 5]);
	label[vonkomponente[loc] + 5].setVisible(false);
	textfield[vonkomponente[loc] + 5] = new TextField();
	textfield[vonkomponente[loc] + 5].setText("" + zoom);
	textfield[vonkomponente[loc] + 5].setBounds(10, 275, 120, 20);
	add(textfield[vonkomponente[loc] + 5]);
	textfield[vonkomponente[loc] + 5].setVisible(false);

	button[vonkomponente[loc]] = new Button("Datenübergabe");
	knopfabfrage[vonkomponente[loc]] = new KnopfAbfrage();
	button[vonkomponente[loc]].addActionListener(knopfabfrage[vonkomponente[loc]]);
	button[vonkomponente[loc]].setBounds(10, 420, 120, 20);
	add(button[vonkomponente[loc]]);
	button[vonkomponente[loc]].setVisible(false);

	label[vonkomponente[loc] + 6] = new Label("Rand oder Pixel");
	label[vonkomponente[loc] + 6].setBounds(10, 455, 96, 20);
	add(label[vonkomponente[loc] + 6]);
	label[vonkomponente[loc] + 6].setVisible(false);
	textfield[vonkomponente[loc] + 6] = new TextField();
	textfield[vonkomponente[loc] + 6].setText(modus);
	textfield[vonkomponente[loc] + 6].setBounds(110, 455, 18, 20);
	add(textfield[vonkomponente[loc] + 6]);
	textfield[vonkomponente[loc] + 6].setVisible(false);

	label[vonkomponente[loc] + 7] = new Label("Exponent");
	label[vonkomponente[loc] + 7].setBounds(10, 490, 91, 20);
	add(label[vonkomponente[loc] + 7]);
	label[vonkomponente[loc] + 7].setVisible(false);
	textfield[vonkomponente[loc] + 7] = new TextField();
	textfield[vonkomponente[loc] + 7].setText("" + exponent);
	textfield[vonkomponente[loc] + 7].setBounds(105, 490, 23, 20);
	add(textfield[vonkomponente[loc] + 7]);
	textfield[vonkomponente[loc] + 7].setVisible(false);
	*/

	// Schneeflocke
	config->vonkomponente[6] = 14;
	config->biskomponente[6] = 15;
	loc = 6;

	/*
	label[vonkomponente[loc]] = new Label("Rechentiefe");
	label[vonkomponente[loc]].setBounds(10, 70, 100, 20);
	add(label[vonkomponente[loc]]);
	label[vonkomponente[loc]].setVisible(false);
	textfield[vonkomponente[loc]] = new TextField();
	textfield[vonkomponente[loc]].setText("" + schneetiefe);
	textfield[vonkomponente[loc]].setBounds(10, 95, 120, 20);
	add(textfield[vonkomponente[loc]]);
	textfield[vonkomponente[loc]].setVisible(false);

	label[vonkomponente[loc] + 1] = new Label("Kantenlänge");
	label[vonkomponente[loc] + 1].setBounds(10, 120, 100, 20);
	add(label[vonkomponente[loc] + 1]);
	label[vonkomponente[loc] + 1].setVisible(false);
	textfield[vonkomponente[loc] + 1] = new TextField();
	textfield[vonkomponente[loc] + 1].setText("" + schneekante);
	textfield[vonkomponente[loc] + 1].setBounds(10, 145, 120, 20);
	add(textfield[vonkomponente[loc] + 1]);
	textfield[vonkomponente[loc] + 1].setVisible(false);

	button[vonkomponente[loc]] = new Button("Datenübergabe");
	knopfabfrage[vonkomponente[loc]] = new KnopfAbfrage();
	button[vonkomponente[loc]].addActionListener(knopfabfrage[vonkomponente[loc]]);
	button[vonkomponente[loc]].setBounds(10, 170, 120, 20);
	add(button[vonkomponente[loc]]);
	button[vonkomponente[loc]].setVisible(false);
	*/

	// Dreieckchen
	config->vonkomponente[7] = 16;
	config->biskomponente[7] = 17;
	loc = 7;

	/*
	label[vonkomponente[loc]] = new Label("Rechentiefe");
	label[vonkomponente[loc]].setBounds(10, 70, 100, 20);
	add(label[vonkomponente[loc]]);
	label[vonkomponente[loc]].setVisible(false);
	textfield[vonkomponente[loc]] = new TextField();
	textfield[vonkomponente[loc]].setText("" + dreitiefe);
	textfield[vonkomponente[loc]].setBounds(10, 95, 120, 20);
	add(textfield[vonkomponente[loc]]);
	textfield[vonkomponente[loc]].setVisible(false);

	label[vonkomponente[loc] + 1] = new Label("Kantenlänge");
	label[vonkomponente[loc] + 1].setBounds(10, 120, 100, 20);
	add(label[vonkomponente[loc] + 1]);
	label[vonkomponente[loc] + 1].setVisible(false);
	textfield[vonkomponente[loc] + 1] = new TextField();
	textfield[vonkomponente[loc] + 1].setText("" + dreikante);
	textfield[vonkomponente[loc] + 1].setBounds(10, 145, 120, 20);
	add(textfield[vonkomponente[loc] + 1]);
	textfield[vonkomponente[loc] + 1].setVisible(false);

	button[vonkomponente[loc]] = new Button("Datenübergabe");
	knopfabfrage[vonkomponente[loc]] = new KnopfAbfrage();
	button[vonkomponente[loc]].addActionListener(knopfabfrage[vonkomponente[loc]]);
	button[vonkomponente[loc]].setBounds(10, 170, 120, 20);
	add(button[vonkomponente[loc]]);
	button[vonkomponente[loc]].setVisible(false);
	*/

	// vorausgewählte Komponenten einblenden
	for (int i = config->vonkomponente[config->auswahl]; i <= config->biskomponente[config->auswahl]; ++i)
	{
		//label[i].setVisible(true);
		//textfield[i].setVisible(true);
	}
	// es existiert immer nur ein Button
	//button[config->vonkomponente[config->auswahl]].setVisible(true);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
