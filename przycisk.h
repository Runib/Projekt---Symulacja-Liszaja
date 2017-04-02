#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class przycisk
{
public:
	przycisk(sf::String x,float a, float b);		// ustawia przycisk w podanym miejscu
	~przycisk();
	bool Click(sf::RenderWindow &, sf::Sprite&, sf::Event&);		// sprawdza czy przycisk zostal klikniety
	sf::Sprite imanage;			
	sf::ContextSettings set;
private:
	sf::Texture Textur;
};

