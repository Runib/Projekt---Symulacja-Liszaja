#include "przycisk.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Gra.h"


//zawiera antialiasing oraz wczytanie pliku z folderu jak i ustawienie pozycji tego pliku
przycisk::przycisk(sf::String x,float a,float b)
{
	set.antialiasingLevel = 8;
	Textur.loadFromFile(x);
	imanage.setTexture(Textur);
	imanage.setPosition(a, b);
}


przycisk::~przycisk()
{
}

//pobiera pozycje z obiektu x
//sprawdza czy obiekt typu zdarzenie bylo nacisnieciem myszy i czy odbyla sie kolizja
bool przycisk::Click(sf::RenderWindow &x, sf::Sprite &y, sf::Event &evnt)
{
	sf::Vector2f mouse(sf::Mouse::getPosition(x));
	if (evnt.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left) && y.getGlobalBounds().contains(mouse))
		return true;
	else
	return false;
}

