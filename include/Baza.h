#pragma once

class Baza
{
public:
	std::vector<Uzytkownik*> v;
	unsigned int id = 0;
	//destruktor gwarantuj¹cy zwolnienie pamiêci
	~Baza() {
		for (Uzytkownik* a : v)
		{
			delete a;
		}
	}
	//dodanie uzytkownika
	void addUzytkownik()
	{
		char p; //zmienna plci
		std::string i; //zmienna imienia
		unsigned int wz; //zmienna wzrostu
		unsigned int wi; //zmienna wieku 
		std::string o; //zmienna orientacji
		std::string z_str; //tymczasowa zmienna zainteresowañ
		std::vector<std::string> z_; //wektor zainteresowañ
		Uzytkownik* u;

		std::cout << "Podaj plec uzytkownika (k,m)" << std::endl;
		std::cin >> p;
		std::cout << "Podaj imie uzytkownika" << std::endl;
		std::cin >> i;
		std::cout << "Podaj wzrost uzytkownika"<<std::endl;
		std::cin >> wz;
		std::cout << "Podaj wiek uzytkownika"<<std::endl;
		std::cin >> wi;
		std::cout << "Podaj orientacje uzytkownika (ht-heteroseksualna,ho-homoseksualna,bi-biseksualna)"<<std::endl;
		std::cin >> o;
		std::cout << "Podaj zainteresowania uzytkownika, wpisz przynajmniej jedno (wpisz k aby zakonczyc)" << std::endl;
		while (true)
		{
			std::getline(std::cin, z_str);
			if (z_str == "k") { break; }
			if (!z_str.empty()) { z_.push_back(z_str); }
		}
		//Tworzenie u¿ytkownika
		if (p == 'k') { u = new Kobieta(); }
		else if (p == 'm') { u = new Mezczyzna(); }
		else throw std::invalid_argument("Bledna wartosc");
		//Ustalanie wartoœci u¿ytkownika
		u->setImie(i); u->setWiek(wi); u->setWzrost(wz); u->setZainteresowania(z_); u->setId(id); id++;
		if (o == "ht") { u->setOrientacja(-1); }
		else if (o == "bi") { u->setOrientacja(0); }
		else if (o == "ho") { u->setOrientacja(1); }
		else throw std::invalid_argument("Bledna wartosc");
		v.push_back(u);
	}
	//drukowanie informacji do konsoli
	void printID()
	{
		for (Uzytkownik* user :v)
		{
			user->ident();
		}
	}
	//Porównywanie zainteresowañ
	std::map<std::pair<int, int>, int> CntWsplZaint()
	{
		std::map<std::pair<int, int>, int> WsplZaint;
		bool warunek=false;
		for (int i = 0; i != v.size(); i++)
		{
			for (int j = i + 1; j != v.size(); j++)
			{
				std::vector<std::string> z1 = v[i]->getZainteresowania();
				std::vector<std::string> z2 = v[j]->getZainteresowania();
				int o1 = v[i]->getOrientacja();
				int o2 = v[j]->getOrientacja();
				bool p1 = v[i]->getPlec();
				bool p2 = v[j]->getPlec();

				if (o1 == 1 && o2 == 1)
				{
					warunek = (p1 == p2);
				}
				else if (o1 == 0 || o2 == 0)
				{
					warunek = true;
				}
				else if (o1 == -1 && o2 == -1)
				{
					warunek = (p1 != p2);
				}

				if (warunek)
				{
					std::set<std::string> s1(z1.begin(), z1.end());
					std::set<std::string> s2(z2.begin(), z2.end());

					int common = 0;
					for (std::string zainteresowanie : s1)
					{
						if (s2.count(zainteresowanie) > 0)
						{
							common++;
						}
					}
					WsplZaint[{i, j}] = common;
				}
			}
		}
		return WsplZaint;
	}
	void printWsplZaint(std::map<std::pair<int, int>, int> a)
	{
		for (const auto& elem : a)
		{
			const std::pair<int, int>& para = elem.first;
			int liczba = elem.second;
			std::cout << "Para uzytkownikow (" << para.first << ", " << para.second
				<< "): " << liczba << " wspolnych zainteresowan" << std::endl;
		}
	}
	//zapis wektora do pliku csv
	void saveVCSV(const std::string& filename)
	{
		std::ofstream p(filename);
		if (!p.is_open()) { throw std::ios_base::failure("Plik nie mogl zostac otwarty"); }
		p << "ID,Plec,Imie,Wzrost,Wiek,Orientacja,Zainteresowania\n";
		for (Uzytkownik* user : v)
		{
			p << user->getId() << ',' << (user->getPlec() ? "Kobieta" : "Mezczyzna") << ',' << user->getImie() << ',' << user->getWzrost() << ',' << user->getWiek() << ',' << user->getOrientacja() << ',';
			std::ostringstream zainteresowania;
			std::vector < std::string > temp_zainteresowania = user->getZainteresowania();
			for (int i = 0; i < temp_zainteresowania.size(); i++)
			{
				zainteresowania << temp_zainteresowania[i];
				if (i < temp_zainteresowania.size() - 1)
				{
					zainteresowania << ';';
				}
			}
			p << zainteresowania.str() << '\n';
		}
		p.close();
	}
	void readVCSV(const std::string& filename)
	{
		for (int i = 0; i < v.size(); i++)
		{
			delete v[i];
		}

		std::ifstream p(filename);
		if (!p.is_open()) { throw std::ios_base::failure("Plik nie mogl zostac otwarty"); }
		std::string linia;
		std::getline(p, linia);
		while (std::getline(p, linia))
		{
			std::istringstream ss(linia);
			std::string pole;
			std::vector<std::string> pola;
			while (std::getline(ss, pole, ',')) { pola.push_back(pole); }
			if (pola.size() < 7) { throw std::runtime_error("Niepoprawny format pliku"); }
			bool isKobieta=(pola[1] == "Kobieta");
			Uzytkownik* user = isKobieta ? static_cast<Uzytkownik*>(new Kobieta()) : static_cast<Uzytkownik*>(new Mezczyzna());
			user->setId(std::stoi(pola[0]));
			user->setImie(pola[2]);
			user->setWzrost(std::stoi(pola[3]));
			user->setWiek(std::stoi(pola[4]));
			user->setOrientacja(std::stoi(pola[5]));
			std::vector<std::string> zainteresowania;
			std::istringstream s_zainteresowania(pola[6]);
			std::string zainteresowanie;
			while (std::getline(s_zainteresowania, zainteresowanie, ';')) { zainteresowania.push_back(zainteresowanie); }
			user->setZainteresowania(zainteresowania);
			v.push_back(user);

		}
		p.close();
	}
	void operacja() 
	{
		std::cout << "Obsluga bazy danych biura matrymonialnego" << std::endl;
		std::cout << "Funkcje bazy danych:" << std::endl;
		std::cout << "addu - dodanie u¿ytkownika do bazy danych" << std::endl;
		std::cout<<"uid - wyœwietlenie bazy danych do konsoli" << std::endl;
		std::cout << "comp - porownanie uzytkownikow bazy danych pod katem orientacji i zainteresowan" << std::endl;
		std::cout << "save - zapisanie obecnej bazy danych do pliku csv" << std::endl;
		std::cout << "read - otwarcie obecnej bazy danych z pliku csv" << std::endl;
		std::cout << "end - zamkniecie bazy danych" << std::endl;
		std::string input;
		while (true)
		{
			std::cout << "Podaj operacje:" << std::endl;
			std::cin >> input;
			if (input == "addu") { addUzytkownik(); }
			if (input == "uid") { printID(); }
			if (input == "comp"){ printWsplZaint(CntWsplZaint()); }
			if (input == "save") { saveVCSV("baza_danych.csv"); }
			if (input == "read") { readVCSV("baza_danych.csv"); }
			if (input == "end") { break; }

		}
	}
		
};