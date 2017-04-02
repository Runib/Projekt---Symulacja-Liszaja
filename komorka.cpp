#include "komorka.h"



komorka::komorka()
{
	zdrowa.loadFromFile("plytka.png");			//pobiera teksture komorki z pliku
	Komorka.setTexture(zdrowa);					//ustawia teksture
	Komorka.setScale(0.5, 0.5);					//ustawia skale domyslna
	isChanged = false;							// ustawienie na false powoduje sprawdzenie czy komorka zostala zmieniona
	czasK = 1;							//czas rowny 1 
	stan = ZDROWA;								// poczatkowy stan

}


komorka::~komorka()
{
}

//ustawia pozycje komorki
void komorka::Position(float x, float y)
{
	Komorka.setPosition(x, y);	
}

int komorka::klik()
{
	if (!czyKlik)
	{
		Komorka.setColor(sf::Color::Yellow);		//jesli wcisnieto komorke to jest zarazona i zmienia kolor
		czyKlik = true;
		return 1;
	}
	else
	{
		Komorka.setColor(sf::Color::Green);			//jesli wcisnieto komorke to jest chora i zmienia kolor
		czyKlik = false;
		return 0;
	}

}
// funkcja powoduje zmiane stanu komorki i koloru w zaleznosci od podanego argumentu

void komorka::ZmianaStanu(int noweStaty)
{
	this->currentState = noweStaty;
	if (noweStaty == 1)
	{
		stan = ZDROWA;
		Komorka.setColor(sf::Color::Green);
		czasK = 1;
	}
	if (noweStaty == 2)
	{
		stan = ZARAZONA;
		Komorka.setColor(sf::Color::Yellow);
		czasK = 1;
	}
	if (noweStaty == 3)
	{
		stan = OCHRONA;
		Komorka.setColor(sf::Color::Blue);
		czasK = 1;
	}
}

//zmiana po zmianie stanu komorki
void komorka::Zmiana(bool nowazmiana)
{
	isChanged = nowazmiana;
}

//zwiekszenie czasu
void komorka::wGore()
{
	czasK = czasK + 1;
}

// zwraca stan lub czas lub zmiane 
int komorka::zwroc(int cos)
{
	switch (cos)
	{
	case 1: return this->stan;
	case 2: return czasK;
	case 3: return isChanged;
	}
	return 0;
}




