#include <iostream>
#include <string.h>
using namespace std;

class Eveniment {
private:
	static string denumireEveniment;
	int nrZone;
	string* zone;
	int* nrRanduri; // nrRanduri[zona];
	int** nrMaxLocuri; // nrMaxLocuri[zona][rand];

public:
	Eveniment() {
		nrZone = 0;
		zone = nullptr;
		nrRanduri = nullptr;
		nrMaxLocuri = nullptr;
	}

	Eveniment(int nrZone, const string* zone, int* nrRanduri, int** nrMaxLocuri) {
		if (zone != nullptr && nrZone > 0) {
			this->zone = new string[nrZone];
			this->nrZone = nrZone;
			for (int i = 0; i < nrZone; i++) {
				this->zone[i] = zone[i];
			}
		}
		else {
			this->zone = nullptr;
			this->nrZone = 0;
		}
		if (nrRanduri != nullptr) {
			this->nrRanduri = new int[nrZone];
			for (int i = 0; i < nrZone; i++) {
				this->nrRanduri[i] = nrRanduri[i];
			}
		}
		else {
			this->nrRanduri = nullptr;
		}
		if (nrMaxLocuri != nullptr && nrRanduri != nullptr) {
			int nrRanduriMax = 0;
			for (int i = 0; i < nrZone; i++) {
				if (nrRanduriMax < nrRanduri[i]) {
					nrRanduriMax = nrRanduri[i];
				}
			}
			this->nrMaxLocuri = new int* [nrZone];
			for (int i = 0; i < nrZone; i++) {
				this->nrMaxLocuri[i] = new int[nrRanduriMax];
			}
			for (int i = 0; i < nrZone; i++)
				for (int j = 0; j < nrRanduriMax; j++) {
					if (nrMaxLocuri[i][j])
					{
						this->nrMaxLocuri[i][j] = nrMaxLocuri[i][j];
					}
				}
		}
		else {
			this->nrMaxLocuri = nullptr;
		}
	}

	Eveniment& operator=(const Eveniment& e) {
		if (this != &e) {
			if (e.zone != nullptr) {
				if (zone != nullptr) {
					delete[] zone;
				}
				this->zone = new string[e.nrZone];
				this->nrZone = e.nrZone;
				for (int i = 0; i < e.nrZone; i++) {
					this->zone[i] = e.zone[i];
				}
			}
			if (e.nrRanduri != nullptr) {
				if (nrRanduri != nullptr)
				{
					delete[] nrRanduri;
				}
				this->nrRanduri = new int[e.nrZone];
				for (int i = 0; i < e.nrZone; i++) {
					this->nrRanduri[i] = e.nrRanduri[i];
				}

			}
			if (e.nrMaxLocuri != nullptr && e.nrRanduri != nullptr) {
				if (nrMaxLocuri != nullptr)
				{
					for (int i = 0; i < nrZone; ++i)
						delete[] nrMaxLocuri[i];
					delete[] nrMaxLocuri;
				}
				int nrRanduriMax = 0;
				for (int i = 0; i < e.nrZone; i++) {
					if (nrRanduriMax < e.nrRanduri[i]) {
						nrRanduriMax = e.nrRanduri[i];
					}
				}
				this->nrMaxLocuri = new int* [e.nrZone];
				for (int i = 0; i < e.nrZone; i++) {
					this->nrMaxLocuri[i] = new int[nrRanduriMax];
				}
				for (int i = 0; i < e.nrZone; i++)
					for (int j = 0; j < nrRanduriMax; j++) {
						if (e.nrMaxLocuri[i][j])
						{
							this->nrMaxLocuri[i][j] = e.nrMaxLocuri[i][j];
						}
					}
			}
		}
		return *this;
	}

	~Eveniment() {
		if (zone != nullptr) {
			delete[] zone;
		}
		if (nrRanduri != nullptr) {
			delete[] nrRanduri;
		}
		if (nrMaxLocuri != nullptr) {
			for (int i = 0; i < nrZone; ++i)
				delete[] nrMaxLocuri[i];
			delete[] nrMaxLocuri;
		}
	}

	int getNrMaxLocuriRand(int zona, int rand) {
		return nrMaxLocuri[zona][rand];
	}

	int getNrRanduriPerZona(int zona) {
		return nrRanduri[zona];
	}

	int getNrZone() {
		return nrZone;
	}

	string getNumeZona(int zona) {
		return zone[zona];
	}

	string* getZone() {
		return zone;
	}

	void setZone(const string* zone, int nrZone) {
		if (zone != nullptr && nrZone > 0) {
			if (this->zone != nullptr) {
				delete[] this->zone;
				this->zone = nullptr;
			}
			this->zone = new string[nrZone];
			for (int i = 0; i < nrZone; i++) {
				this->zone[i] = zone[i];
			}
			this->nrZone = nrZone;
		}
	}

	void setNrRanduri(int zona, int nrRanduriNou) {
		if (zona < this->nrZone) {
			this->nrRanduri[zona] = nrRanduriNou;
		}
	}

	void setNrMaxLocuriRand(int zona, int rand, int nrMaxNou) {
		if (zona < this->nrZone && rand < this->nrRanduri[zona]) {
			this->nrMaxLocuri[rand][zona] = nrMaxNou;
		}
	}

	static void setDenumireEveniment(string denumireEveniment) {
		Eveniment::denumireEveniment = denumireEveniment;
	}

	static string getDenumireEveniment() {
		return denumireEveniment;
	}

	int getNrTotalLocuri() {
		int nrTotalLocuri = 0;
		if (zone != nullptr && nrRanduri != nullptr && nrMaxLocuri != nullptr) {
			for (int i = 0; i < nrZone; i++) {
				for (int j = 0; j < nrRanduri[i]; j++) {
					nrTotalLocuri += nrMaxLocuri[i][j];
				}
			}
		}
		return nrTotalLocuri;
	}

	int getNrTotalLocuriZona(int zona) {
		int nrTotalLocuriZona = 0;
		if (zone != nullptr && nrRanduri != nullptr && nrMaxLocuri != nullptr) {
			for (int j = 0; j < nrRanduri[zona]; j++) {
				nrTotalLocuriZona += nrMaxLocuri[zona][j];
			}
		}
		return nrTotalLocuriZona;
	}

	//Operatorul + intre doua evenimente aduna numarul maxim de locuri al celor doua evenimente.
	Eveniment operator+(Eveniment e) {
		Eveniment copie = *this;
		for (int i = 0; i < nrZone; i++) {
			for (int j = 0; j < nrRanduri[i]; j++) {
				copie.nrMaxLocuri[i][j] += e.nrMaxLocuri[i][j];
			}
		}
		return copie;
	}

	//Operatorul + intre un eveniment si o valoare aduna valoarea la numarul maxim de locuri al evenimentului.
	Eveniment operator+(int valoare) {
		Eveniment copie = *this;
		for (int i = 0; i < nrZone; i++) {
			for (int j = 0; j < nrRanduri[i]; j++) {
				copie.nrMaxLocuri[i][j] += valoare;
			}
		}
		return copie;
	}

	//Operatorul [] afiseaza numarul maxim de locuri al zonei indexate.
	int operator[](int index) {
		int nrMaxLocuriZona = 0;
		if (zone != nullptr && index <= nrZone) {
			for (int i = 0; i < nrZone; i++) {
				for (int j = 0; j < nrRanduri[i]; j++) {
					nrMaxLocuriZona += nrMaxLocuri[i][j];
				}
			}
		}
		return nrMaxLocuriZona;
	}

	friend ostream& operator<<(ostream& out, Eveniment e);
	friend istream& operator>>(istream& in, Eveniment& e);
};

ostream& operator<<(ostream& out, Eveniment e) {
	if (e.zone != nullptr && e.nrRanduri != nullptr && e.nrMaxLocuri != nullptr) {
		for (int i = 0; i < e.nrZone; i++) {
			out << "Zona " << e.zone[i] << " are " << e.nrRanduri[i] << " randuri." << endl;
			for (int j = 0; j < e.nrRanduri[i]; j++) {
				out << "Randul " << j + 1 << " are " << e.nrMaxLocuri[i][j] << " locuri." << endl;
			}
		}
	}
	else {
		out << "Evenimentul nu a fost definit!";
	}
	return out;
}

istream& operator>>(istream& in, Eveniment& e) {
	cout << "Nr. de zone: "; in >> e.nrZone;
	if (e.zone != nullptr) {
		delete[] e.zone;
		e.zone = nullptr;
	}
	e.zone = new string[e.nrZone];
	cout << "Zone" << endl;
	for (int i = 0; i < e.nrZone; i++) {
		cout << "Numele zonei " << i + 1 << " este: "; in >> e.zone[i];
	}
	if (e.nrRanduri != nullptr) {
		delete[] e.nrRanduri;
		e.nrRanduri = nullptr;
	}
	e.nrRanduri = new int[e.nrZone];
	int nrRanduriMax = 0;
	for (int i = 0; i < e.nrZone; i++) {
		cout << "Nr. de randuri al zonei " << i + 1 << " este: "; in >> e.nrRanduri[i];
		if (e.nrRanduri[i] > nrRanduriMax) {
			nrRanduriMax = e.nrRanduri[i];
		}
	}
	if (e.nrMaxLocuri != nullptr) {
		delete[] e.nrMaxLocuri;
		e.nrMaxLocuri = nullptr;
	}
	e.nrMaxLocuri = new int* [e.nrZone];
	for (int i = 0; i < e.nrZone; i++) {
		e.nrMaxLocuri[i] = new int[nrRanduriMax];
	}
	for (int i = 0; i < e.nrZone; i++)
		for (int j = 0; j < e.nrRanduri[i]; j++) {
			cout << "Numarul maxim de locuri pentru randul " << j + 1 << " al zonei " << e.zone[i] << " este: "; in >> e.nrMaxLocuri[i][j];
		}
	return in;
}

class Bilet {
private:
	const int id;
	char* zona;
	int rand;
	int loc;

public:
	float pret;
	Bilet() :id(0) {
		zona = nullptr;
		rand = 0;
		loc = 0;
		pret = 0.0;
	}

	Bilet(int id, char* zona, int rand, int loc, float pret) : id(id) {
		this->zona = zona;
		this->rand = rand;
		this->loc = loc;
		this->pret = pret;
	}

	~Bilet() {
		delete[] zona;
	}

	Bilet& operator=(const Bilet& b) {
		if (this != &b) {
			if (this->zona != nullptr) {
				delete[] this->zona;
				this->zona = nullptr;
			}
			this->zona = new char[strlen(b.zona) + 1];
			strcpy(this->zona, b.zona);
			this->rand = b.rand;
			this->loc = b.loc;
			this->pret = b.pret;
		}
	}

	void setZona(const char* zona) {
		if (zona != nullptr) {
			if (this->zona != nullptr) {
				delete[] this->zona;
			}
			this->zona = new char[strlen(zona) + 1];
			strcpy(this->zona, zona);
		}
	}

	char* getZona() {
		return zona;
	}

	void setLoc(int loc) {
		if (loc > 0) {
			this->loc = loc;
		}
	}

	int getLoc() {
		return loc;
	}

	void setRand(int rand) {
		if (rand > 0) {
			this->rand = rand;
		}
	}

	int getRand() {
		return rand;
	}

	void setPret(float pret) {
		if (pret > 0) {
			this->pret = pret;
		}
	}

	float getPret() {
		return pret;
	}

	static float pretMediu(Bilet* bilete, int nrBilete) {
		float suma = 0;
		if (bilete != nullptr && nrBilete > 0) {
			for (int i = 0; i < nrBilete; i++) {
				suma += bilete[i].pret;
			}
		}
		return suma / nrBilete;
	}

	//Operatorul ++ creste pretul unui bilet cu 1 leu (post-incrementare).
	Bilet operator++(int i) {
		Bilet copie = *this;
		copie.pret++;
		return copie;
	}

	//pre-incrementare
	Bilet& operator++() {
		pret++;
		return *this;
	}

	//Operatorul -- scade pretul unui bilet cu 1 leu (post-decrementare).
	Bilet operator--(int i) {
		Bilet copie = *this;
		copie.pret--;
		return copie;
	}

	//pre-decrementare
	Bilet& operator--() {
		pret--;
		return *this;
	}

	friend ostream& operator<<(ostream& out, Bilet b);
	friend istream& operator>>(istream& in, Bilet& b);
};

ostream& operator<<(ostream& out, Bilet b) {
	out << "Id bilet: " << b.id << endl;
	out << "Zona: " << b.zona << endl;
	out << "Rand: " << b.rand << endl;
	out << "Loc: " << b.loc << endl;
	out << "Pret: " << b.pret << endl;
	return out;
}
istream& operator>>(istream& in, Bilet& b) {
	cout << "Zona: ";
	string buffer;
	in >> buffer;
	if (buffer.length() > 0) {
		b.setZona(buffer.c_str());
	}
	else {
		b.zona = nullptr;
	}
	cout << "Rand: ";
	int rand; in >> rand;
	if (rand > 0) {
		b.setRand(rand);
	}
	else {
		b.rand = 0;
	}
	cout << "Loc: ";
	int loc; in >> loc;
	if (loc > 0) {
		b.setLoc(loc);
	}
	else {
		b.loc = 0;
	}
	cout << "Pret: ";
	float pret; in >> pret;
	if (pret > 0) {
		b.setPret(pret);
	}
	else {
		b.pret = 0.0;
	}
	return in;
}


// Biletul special este un bilet cu preturi diferite pentru cei care sufera de handicap, ori provin din orfelinate.
class BiletSpecial : public Bilet {
private:
	string motiv;

public:
	BiletSpecial() :Bilet() {
		motiv = "N/A";
	}

	BiletSpecial(int id, char* zona, int rand, int loc, float pret, string motiv) : Bilet(id, zona, rand, loc, pret) {
		this->motiv = motiv;
	}

	BiletSpecial& operator=(const BiletSpecial& bs) {
		Bilet::operator=(bs);
		this->motiv = bs.motiv;
		return *this;
	}

	~BiletSpecial() {
	}

	void setMotiv(string motiv) {
		if (motiv == "Handicap" || motiv == "Orfelinat") {
			this->motiv = motiv;
		}
		else {
			this->motiv = "N/A";
		}
	}

	string getMotiv() {
		return motiv;
	}

	void setPretSpecial() {
		if (motiv == "Handicap") {
			this->pret = pret / 2;
		}
		else if (motiv == "Orfelinat") {
			this->pret = 0;
		}
	}

	explicit operator string() {
		return motiv;
	}

	void operator-=(float valoare) {
		this->pret -= valoare;
	}

	friend ostream& operator<<(ostream& out, BiletSpecial bs);
	friend istream& operator>>(istream& in, BiletSpecial& bs);
};

ostream& operator<<(ostream& out, BiletSpecial bs) {
	out << (Bilet)bs;
	out << "Motiv: " << bs.motiv << endl;
	return out;
}
istream& operator>>(istream& in, BiletSpecial& bs) {
	in >> (Bilet&)bs;
	cout << "Motiv: "; in >> bs.motiv;
	return in;
}
