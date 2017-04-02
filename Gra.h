#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "komorka.h"
class Gra
{
	friend class przycisk;
public:
	Gra();
	~Gra();
	int getRozmiar();	
	void setRozmiar(int l);		//pobiera wielkosc planszy
	void runGame();	//uruchamia caly program
	void menu();	// widok menu
	void playing();	// uruchamia symulacja
	void ustawienia(int h);	//ustawienia
	void wyswietl(sf::RenderWindow &okno,komorka **Komorka, int n);		//wyswietla plansze
	int Random();				// potrzebne do zarazania
	void poczatkowe(komorka **tab);			//poczatkowa zarazona na srodku
	void reset(komorka **tab);
	

private:
	sf::Texture texk;	//potrzebne do tla
	sf::Sprite tlo;		//potrzebne do tla
	enum StanGry {MENU,URUCHOMIONA,USTAWIENIA,KONIEC};		//4 mozliwych stanow gry
	StanGry stan;
	sf::Time CzasCyklu = sf::milliseconds(300);	//czas cyklu
	int wielkosc;		// wielkosc planszy
	sf::RenderWindow Okno;	
	sf::Event Zdarzenie;
	sf::Font czcionka;
	int czas_odpornosci;
	int czas_choroby;
	int k;		//potrzebne do wodiku ustawien , a doklaniej powrotu
	sf::Music sound;
	bool music = false;
	int SzansaZarazenia;
	int liczydlo;
};

