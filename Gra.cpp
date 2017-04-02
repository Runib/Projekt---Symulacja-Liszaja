#include "Gra.h"
#include "przycisk.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>


Gra::Gra()
	:Okno(sf::VideoMode(800,600,32),"Problem Liszaja",sf::Style::Titlebar | sf::Style::Close)
{
	// pobiera czcionke, ustawia stan , przypisuje startowe wartosci
	czcionka.loadFromFile("czcionka.ttf");
	stan = MENU;
	this->czas_choroby = 6;
	this->czas_odpornosci = 4;
	this->SzansaZarazenia = 50;
	this->liczydlo = 0;
	sound.openFromFile("muzyka.ogg");
	sound.pause();
}


Gra::~Gra()
{
}


int Gra::getRozmiar()
{
	return wielkosc;
}

void Gra::setRozmiar(int l)
{
	this->wielkosc = l;
}

// uruchamia cala gre
void Gra::runGame()
{
	while (stan != KONIEC)
	{
		switch (stan)
		{
		case MENU:
			menu();
			break;
		case URUCHOMIONA:
			playing();
			break;
		case USTAWIENIA:
			ustawienia(k);
			break;
		}
	}
}

//uruchamia okno menu
void Gra::menu()
{
	// to sie tyczy tla
	texk.loadFromFile("glowne.jpg");
	tlo.setTexture(texk);
	tlo.setScale(1.4, 1.4);
	// wszystko co nam potrzeba do wyswietlenia
	sf::Text plansza("Wybierz wielkosc planszy", czcionka, 30);
	przycisk Exit("exit.png",100,550);
	przycisk play("play.png", 30, 30);
	przycisk stop("stop.png", 70, 30);
	przycisk ustawienia("ustawienia.png", 300, 550);
	przycisk plansza1("50x50.png", 500, 100);
	przycisk plansza2("40x40.png", 500, 175);
	przycisk plansza3("30x30.png", 500, 250);
	przycisk plansza4("20x20.png", 500, 325);
	sf::Text tytul("Problem\nLiszaja", czcionka, 70);
	plansza.setPosition(400, 30);
	tytul.setFillColor(sf::Color::Red);
	plansza.setFillColor(sf::Color::Yellow);
	tytul.setPosition(60, 130);
	while (stan == MENU)
	{
		while (Okno.pollEvent(Zdarzenie))
		{
			if (Zdarzenie.type == sf::Event::KeyPressed && Zdarzenie.key.code == sf::Keyboard::Escape || Zdarzenie.type==sf::Event::Closed)
			{
				stan = KONIEC;
			}
			if (plansza1.Click(Okno, plansza1.imanage, Zdarzenie))
			{
				setRozmiar(50);
				stan = URUCHOMIONA;
			}
			if (plansza2.Click(Okno, plansza2.imanage, Zdarzenie))
			{
				setRozmiar(40);
				stan = URUCHOMIONA;
			}
			if (plansza3.Click(Okno, plansza3.imanage, Zdarzenie))
			{
				setRozmiar(30);
				stan = URUCHOMIONA;
			}
			if (plansza4.Click(Okno, plansza4.imanage, Zdarzenie))
			{
				setRozmiar(20);
				stan = URUCHOMIONA;
			}
			if (Exit.Click(Okno, Exit.imanage, Zdarzenie))
			{
				stan = KONIEC;
			}
			if (ustawienia.Click(Okno, ustawienia.imanage,Zdarzenie))
			{
				k = 1;
				stan = USTAWIENIA;
			}
			if (stop.Click(Okno, stop.imanage, Zdarzenie))
			{
				sound.play();
				music = true;
			}
			if (play.Click(Okno, play.imanage, Zdarzenie))
			{
				sound.pause();
				music = false;
			}

			
		}
		sf::Vector2f mouse_position(sf::Mouse::getPosition());
		Okno.clear(sf::Color::Cyan);
		Okno.draw(tlo);
		Okno.draw(plansza);
		Okno.draw(plansza1.imanage);
		Okno.draw(plansza2.imanage);
		Okno.draw(plansza3.imanage);
		Okno.draw(plansza4.imanage);
		Okno.draw(Exit.imanage);
		Okno.draw(tytul);
		if (music == false)
			Okno.draw(stop.imanage);
		else
			Okno.draw(play.imanage);
		Okno.draw(ustawienia.imanage);
		Okno.display();
	}
}

void Gra::playing()
{
	// wszystko co nam potrzeba do wyswietlenia
	przycisk play("play.png", 595, 30);
	przycisk stop("stop.png", 645, 30);
	przycisk Start("start.png", 555, 80);
	przycisk Pauza("pauza.png", 555, 155);
	przycisk ustawienia1("ustawienia1.png", 555, 230);
	przycisk restart("reset.png", 555, 305);
	przycisk powrot1("powrot.png", 555, 380);
	// rysujemy plansze
	int n = getRozmiar();
	float przerwa;
	if (n == 40)
		przerwa = 13;
	else if (n == 50)
		przerwa = 10.5;
	else if (n == 30)
		przerwa = 18;
	else
		przerwa = 24;
	komorka **t = new komorka*[n];
	for (int i = 0;i < n;i++)
	{
		t[i] = new komorka[n];		//alokacja pamiecy tablicy plytek
	}

	float x = 10, y = 10;
	for (int i = 0;i < n;i++)
	{
		y = y + przerwa;
		x = 13;
		for (int j = 0;j < n;j++)
		{
			t[i][j].isChanged = false;
			t[i][j].Position(x, y);
			t[i][j].ZmianaStanu(1);
			if (n == 50)
				t[i][j].Komorka.setScale(0.27, 0.27);
			if (n == 40)
				t[i][j].Komorka.setScale(0.365, 0.365);
			if (n == 20)
				t[i][j].Komorka.setScale(0.7, 0.7);
			x = x + przerwa;
		}

	}
	poczatkowe(t);
	while (stan == URUCHOMIONA)
	{

		while (Okno.pollEvent(Zdarzenie))
		{
			if (Zdarzenie.type == sf::Event::KeyPressed && Zdarzenie.key.code == sf::Keyboard::Escape || powrot1.Click(Okno, powrot1.imanage, Zdarzenie))
			{
				stan = MENU;
			}
			if (Zdarzenie.type == sf::Event::Closed)
			{
				stan = KONIEC;
			}
			if (stop.Click(Okno, stop.imanage, Zdarzenie))
			{
				sound.play();
				music = true;
			}
			if (play.Click(Okno, play.imanage, Zdarzenie))
			{
				sound.pause();
				music = false;
			}
			if (ustawienia1.Click(Okno, ustawienia1.imanage, Zdarzenie))
			{
				k = 2;
				stan = USTAWIENIA;
			}
			if (Zdarzenie.type == sf::Event::MouseButtonPressed && Zdarzenie.key.code == sf::Mouse::Left)
			{
				sf::Vector2f mouse(sf::Mouse::getPosition(Okno));
				for (int i = 0;i < n;i++)
				{
					for (int j = 0;j < n;j++)
					{
						if (t[i][j].Komorka.getGlobalBounds().contains(mouse))
						{
							if (t[i][j].klik())
								t[i][j].ZmianaStanu(2);
							else
								t[i][j].ZmianaStanu(1);
						}
					}
				}
			}
			if (restart.Click(Okno, restart.imanage, Zdarzenie))
			{
				reset(t);
			}
			if (Start.Click(Okno, Start.imanage, Zdarzenie))
			{
				sf::Clock zegar;
				sf::Time Lu = sf::Time::Zero;
				bool koniec = false;
				while (koniec != true)
				{
					while (Okno.pollEvent(Zdarzenie))
					{
						if (restart.Click(Okno, restart.imanage, Zdarzenie))
						{
							reset(t);
						}
						if (Pauza.Click(Okno, Pauza.imanage, Zdarzenie))
						{
							koniec = true;
						}
						if (powrot1.Click(Okno, powrot1.imanage, Zdarzenie))
						{
							koniec = true;
							stan = MENU;
						}
						if (stop.Click(Okno, stop.imanage, Zdarzenie))
						{
							sound.play();
							music = true;
						}
						if (play.Click(Okno, play.imanage, Zdarzenie))
						{
							sound.pause();
							music = false;
						}
						if (Zdarzenie.type == sf::Event::Closed)
						{
							Okno.close();
						}
						if (ustawienia1.Click(Okno, ustawienia1.imanage, Zdarzenie))
						{
							k = 2;
							koniec = true;
							stan = USTAWIENIA;
						}

					}
					Lu += zegar.restart();
					while (Lu > CzasCyklu)
					{
						Lu -= CzasCyklu;

						for (int i = 1; i < n - 1; i++)
						{
							for (int j = 1; j < n - 1; j++)
							{

								switch (t[i][j].zwroc(1))
								{
								case 1:
									break;
								case 2://czy komorka nie zostala zmieniona juz w danym cyklu
									if (t[i][j].zwroc(3) == false)
									{
										if (t[i][j].zwroc(2) >=czas_choroby)
										{
											t[i][j].ZmianaStanu(3);
											t[i][j].Zmiana(true);
											t[i][j].czasK = 1;
										}
										else
										{
											t[i][j].wGore();
											//zarazenie komorek innych
											//gorna
											if (t[i - 1][j].zwroc(1) ==1 && Random() <= SzansaZarazenia)
											{
												t[i - 1][j].Zmiana(true);
												t[i - 1][j].ZmianaStanu(2);
											}
											//prawa
											if (t[i][j + 1].zwroc(1) == 1 && Random() <= SzansaZarazenia)
											{
												t[i][j + 1].Zmiana(true);
												t[i][j + 1].ZmianaStanu(2);
											}
											//dolna
											if (t[i + 1][j].zwroc(1) == 1 && Random() <= SzansaZarazenia)
											{
												t[i + 1][j].Zmiana(true);
												t[i + 1][j].ZmianaStanu(2);
											}
											//lewa
											if (t[i][j - 1].zwroc(1) == 1 && Random() <= SzansaZarazenia)
											{
												t[i][j - 1].Zmiana(true);
												t[i][j - 1].ZmianaStanu(2);
											}
											//lewa gorna
											if (t[i - 1][j - 1].zwroc(1) == 1 && Random() <= SzansaZarazenia)
											{
												t[i - 1][j - 1].Zmiana(true);
												t[i - 1][j - 1].ZmianaStanu(2);
											}
											//prawa gorna
											if (t[i - 1][j + 1].zwroc(1) == 1 && Random() <= SzansaZarazenia)
											{
												t[i - 1][j + 1].Zmiana(true);
												t[i - 1][j + 1].ZmianaStanu(2);
											}
											//lewa dolna
											if (t[i + 1][j - 1].zwroc(1) == 1 && Random() <= SzansaZarazenia)
											{
												t[i + 1][j - 1].Zmiana(true);
												t[i + 1][j - 1].ZmianaStanu(2);
											}
											//prawa dolna
											if (t[i + 1][j + 1].zwroc(1) == 1 && Random() <= SzansaZarazenia)
											{
												t[i + 1][j + 1].Zmiana(true);
												t[i + 1][j + 1].ZmianaStanu(2);
											}
										}
									}

									break;
								case 3:
									if (t[i][j].zwroc(2) >= czas_odpornosci)
									{
										t[i][j].ZmianaStanu(1);
										t[i][j].czasK = 1;
									}
									else
									{
										t[i][j].wGore();			
										
									}
									break;
								}
							}
						}
						for (int i = 1; i < n - 1; i++)
							for (int j = 1; j < n - 1; j++)
								t[i][j].Zmiana(false);
						this->liczydlo = 0;
						for (int i=1;i<n-1;i++)
							for (int j = 1;j < n-1;j++)
							{
								if (t[i][j].currentState == 1)
									liczydlo++;
							}
						if (liczydlo == (n-1)*(n-1))
							koniec = true;

						Okno.clear(sf::Color(80, 60, 60, 0.9));
						wyswietl(Okno, t, n);
						Okno.draw(ustawienia1.imanage);
						if (music == false)
							Okno.draw(stop.imanage);
						else
							Okno.draw(play.imanage);
						Okno.draw(Start.imanage);
						Okno.draw(Pauza.imanage);
						Okno.draw(powrot1.imanage);
						Okno.draw(restart.imanage);
						Okno.display();
					}
				}


			}
			Okno.clear(sf::Color(80, 60, 60, 0.9));
			wyswietl(Okno, t, n);
			Okno.draw(ustawienia1.imanage);
			if (music == false)
				Okno.draw(stop.imanage);
			else
				Okno.draw(play.imanage);
			Okno.draw(restart.imanage);
			Okno.draw(Start.imanage);
			Okno.draw(Pauza.imanage);
			Okno.draw(powrot1.imanage);
			Okno.display();
		}

	}
}


void Gra::ustawienia(int h)
{
	
texk.loadFromFile("tlo.jpg");
tlo.setTexture(texk);
tlo.setScale(1.4, 1.4);
sf::Text predkosc, czas_odp, czas_zar, sza_zar;
sf::String predkosc_s, czas_zars, czas_odps,sza_zars;
przycisk powrot("powrot.png", 350, 510);
przycisk Plus("plus.png", 560, 75);
przycisk Minus("minus.png", 630, 75);
przycisk Plus1("plus1.png", 560, 160);
przycisk Minus1("minus1.png", 630, 160);
przycisk Plus2("plus2.png", 560, 245);
przycisk Minus2("minus2.png", 630, 245);
przycisk Plus3("plus.png", 560, 330);
przycisk Minus3("minus.png", 630, 330);
predkosc.setFont(czcionka);
predkosc.setScale(1, 1);
predkosc.setPosition(220, 75);
predkosc.setFillColor(sf::Color::Yellow);
czas_zar.setFont(czcionka);
czas_zar.setPosition(220, 160);
czas_zar.setScale(1, 1);
czas_zar.setFillColor(sf::Color::Yellow);
czas_odp.setFont(czcionka);
czas_odp.setScale(1, 1);
czas_odp.setPosition(220, 245);
czas_odp.setFillColor(sf::Color::Yellow);
sza_zar.setFont(czcionka);
sza_zar.setScale(1, 1);
sza_zar.setPosition(220, 330);
sza_zar.setFillColor(sf::Color::Yellow);

while (stan == USTAWIENIA)
	{
		while (Okno.pollEvent(Zdarzenie))
		{
			if (Plus1.Click(Okno, Plus1.imanage, Zdarzenie))
				czas_choroby++;
			if (czas_choroby > 1)
			{
				if (Minus1.Click(Okno, Minus1.imanage, Zdarzenie))
					czas_choroby--;
			}
			if (Plus2.Click(Okno, Plus2.imanage, Zdarzenie))
				czas_odpornosci++;
			if (czas_odpornosci > 1)
			{
				if (Minus2.Click(Okno, Minus2.imanage, Zdarzenie))
					czas_odpornosci--;
			}
			if (Minus.Click(Okno, Minus.imanage, Zdarzenie))
			{
				if (CzasCyklu.asMilliseconds() > 10)
					CzasCyklu -= sf::seconds(1.f / 50.f);
			}
			if (Plus.Click(Okno, Plus.imanage, Zdarzenie))
			{
				if (CzasCyklu.asMilliseconds() < 1000)
					CzasCyklu += sf::seconds(1.f / 50.f);
			}
			if (Plus3.Click(Okno, Plus3.imanage, Zdarzenie) && SzansaZarazenia<100)
				this->SzansaZarazenia++;
			if (Minus3.Click(Okno, Minus3.imanage, Zdarzenie) && SzansaZarazenia > 1)
				this->SzansaZarazenia--;
			if (powrot.Click(Okno, powrot.imanage, Zdarzenie))
			{
				if (h==1)
					stan = MENU;
				if (h == 2)
					stan = URUCHOMIONA;
			}
			if (Zdarzenie.type == sf::Event::Closed)
				Okno.close();
			Okno.clear(sf::Color::Blue);
			Okno.draw(tlo);
			predkosc_s = std::to_string(CzasCyklu.asMilliseconds());
			predkosc_s = "Predkosc: " + predkosc_s + "ms";
			predkosc.setString(predkosc_s);
			czas_zars = std::to_string(this->czas_choroby);
			czas_zars = "Czas zarazenia: " + czas_zars;
			czas_zar.setString(czas_zars);
			czas_odps = std::to_string(this->czas_odpornosci);
			czas_odps = "Czas odpornosci: " + czas_odps;
			czas_odp.setString(czas_odps);
			sza_zars = std::to_string(this->SzansaZarazenia);
			sza_zars = "Szansa Zarazenia: " + sza_zars;
			sza_zar.setString(sza_zars);
			Okno.draw(powrot.imanage);
			Okno.draw(Plus.imanage);
			Okno.draw(Minus.imanage);
			Okno.draw(Plus1.imanage);
			Okno.draw(Minus1.imanage);
			Okno.draw(Plus2.imanage);
			Okno.draw(Minus2.imanage);
			Okno.draw(Plus3.imanage);
			Okno.draw(Minus3.imanage);
			Okno.draw(sza_zar);
			Okno.draw(predkosc);
			Okno.draw(czas_zar);
			Okno.draw(czas_odp);
			Okno.display();
		}
	}

}

void Gra::wyswietl(sf::RenderWindow &okno,komorka **Komorka, int n)
{
	for (int i = 1;i < n-1;i++)
	{
		for (int j = 1;j < n-1;j++)
		{
				okno.draw(Komorka[i][j].Komorka);
		}
	}
}

int Gra::Random()
{
	return (rand() % (100) +1);
}



void Gra::poczatkowe(komorka ** tab)
{
	int n = getRozmiar();
	tab[(n /2) ][(n / 2) ].ZmianaStanu(2);
}

void Gra::reset(komorka ** tab)
{
	int n = getRozmiar();
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j < n;j++)
		{
			tab[i][j].ZmianaStanu(1);
		}
	}
	poczatkowe(tab);
}






