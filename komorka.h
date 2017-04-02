#pragma once
#include <SFML\Graphics.hpp>
enum stanyKomorki { ZDROWA = 1, ZARAZONA = 2, OCHRONA = 3 };			//mozliwe stany komorki
class komorka{
public:
	komorka();
	~komorka();
	sf::Sprite Komorka;						// potrzebne do rysowania komorki
	void Position(float x, float y);		//ustala pozycje komorki
	bool czyKlik = false;					// do lklikania
	int klik();								// do klikania
	bool isChanged;							//czy komorka zostala zmieniona , potrzebne do petli i poprawnego wyswietlania
	stanyKomorki stan;						//zmienna stanowkomorki

	int currentState;						//aktualny stan
	void ZmianaStanu(int noweStaty);			//zmiana stanu komorki
	void Zmiana(bool nowazmiana);			//funkcja ktora zmienia isChanged 
	int czasK;						//czas dla konkretnej komorki, potrzebne do sprawdzania z czasem odp i choroby
	void wGore();							//zwieksza czas
	int zwroc(int cos);						//funkcja ktora zwraca cos w zaleznosci od podanego argumentu
private:
	sf::Texture zdrowa;						// tekstura dla komorki
	
};

