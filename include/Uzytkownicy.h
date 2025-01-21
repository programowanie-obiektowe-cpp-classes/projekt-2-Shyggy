#pragma once
class Uzytkownik
{
private:
	std::string imie;
	unsigned int wzrost;
	unsigned int wiek;
	int orientacja;
	std::vector<std::string> zainteresowania_;
	unsigned int id;
	bool isKobieta;
public:
	//settery
	void setImie(std::string a) { imie = a; }
	void setWzrost(unsigned int a) { wzrost = a; }
	void setWiek(unsigned int a) { wiek = a; }
	void setOrientacja(int a)
	{
		if (a < -1 || a>1) { throw std::invalid_argument("Bledna wartosc"); }
		else orientacja = a;
	}
	void setZainteresowania(std::vector<std::string> likes)
	{
		for (std::string like : likes)
		{
			zainteresowania_=likes;
		}
	}
	void setId(int i)
	{
		id = i;
	}
	void setPlec(bool a)
	{
		isKobieta = a;
	}
	//gettery
	std::string getImie() { return imie; }
	int getWzrost() { return wzrost; }
	int getWiek() { return wiek; }
	int getOrientacja(){ return orientacja; }
	std::vector<std::string> getZainteresowania() { return zainteresowania_; }
	int getId()
	{
		return id;
	}
	bool getPlec()
	{
		return isKobieta;
	}
	//funkcje wirtualne
	virtual ~Uzytkownik() = default; //destruktor
	virtual void ident() {}; //funkcja identyfikuj¹ca
};
class Mezczyzna :public Uzytkownik
{
public:
	Mezczyzna() { setPlec(false); }
	void ident() override
	{
		std::cout << "Numer uzytkownika: " << getId() << std::endl;
		std::cout << "Plec: Mezczyzna" << std::endl;
		std::cout << "Imie: " << getImie() << std::endl;
		std::cout << "Wzrost: " << getWzrost() << std::endl;
		std::cout << "Wiek" << getWiek() << std::endl;
		if (getOrientacja() == -1) { std::cout << "Orientacja: heteroseksualna" << std::endl; }
		else if (getOrientacja() == 0) { std::cout << "Orientacja: biseksulana" << std::endl; }
		else if (getOrientacja() == 1) { std::cout << "Orientacja: homoseksulana" << std::endl; }
		else std::cout << "B³¹d"<<std::endl;
		std::cout << "Zainteresowania uzytkownika:" << std::endl;
		for (std::string like : getZainteresowania())
		{
			std::cout << like<<std::string(3,' ');
		}
		std::cout << std::endl;
	}
};
class Kobieta :public Uzytkownik
{
public:
	Kobieta() { setPlec(true); }
	void ident() override
	{
		std::cout << "Numer uzytkownika: " << getId() << std::endl;
		std::cout << "Plec: Kobieta" << std::endl;
		std::cout << "Imie: " << getImie() << std::endl;
		std::cout << "Wzrost: " << getWzrost() << std::endl;
		std::cout << "Wiek" << getWiek() << std::endl;
		if (getOrientacja() == -1) { std::cout << "Orientacja: heteroseksualna" << std::endl; }
		else if (getOrientacja() == 0) { std::cout << "Orientacja: biseksulana"<<std::endl; }
		else if (getOrientacja() == 1) { std::cout << "Orientacja: homoseksualana"<<std::endl; }
		else std::cout << "B³¹d" << std::endl;
		std::cout << "Zainteresowania uzytkownika:" << std::endl;
		for (std::string like : getZainteresowania())
		{
			std::cout << like << std::string(3, ' ');
		}
		std::cout << std::endl;
	}
};