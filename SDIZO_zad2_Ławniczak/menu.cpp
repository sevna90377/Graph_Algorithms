#include <iostream>
#include <conio.h>
#include "AdjacencyList.h"
#include "AdjacencyMatrix.h"
#include <fstream>

/*
* NAPRAWIÆ GENEROWANIE BY GRAF BY£ SPÓJNY <3 po raz kolejny to cholerne generowanie
* 
* Byæ mo¿e trzeba zmodyfikowaæ heap, aby prim by³ taki sam w obu przypadkach
* trzeba by zmieniæ warunek zamiany ¿e jeœli syn jest = ojcowi to te¿ siê zamienia
* 
* !!! mo¿e to spowodowaæ b³êdy w Kruskalu !!!
* 
* Algorytm Dijkstry i Forda Belmana
*/


using namespace std;

void menu_mst() {

	AdjacencyList listRep;
	AdjacencyMatrix matrixRep;
	char opt;
	string fileName;
	


	do {
		cout << endl;
		cout << "=== MST ===" << endl;
		cout << "1. Wczytaj z pliku" << endl;
		cout << "2. Wygeneruj losowo" << endl;
		cout << "3. Wyswietl" << endl;
		cout << "4. Algorytmem Prima" << endl;
		cout << "5. Algorytm Kruskala" << endl;
		cout << "Podaj opcje:";
		opt = _getche();
		cout << endl << endl;

		switch (opt) {

		case '1':	//tutaj wczytywanie grafu z pliku
			cout << "Podaj nazwe zbioru: ";
			cin >> fileName;
			listRep.loadFromFile(fileName, 0);
			matrixRep.loadFromFile(fileName, 0);
			matrixRep.display();
			listRep.display();
			break;
		case '2':	//tutaj losowe generowanie grafu
			int size, density;
			bool directed;
			do {
				cout << "Graf skierowany t/n?";
				opt = _getche();
				cout << endl;
				switch (opt) {
				case 't':
					directed = true;
					break;
				case 'n':
					directed = false;
					break;
				}
			} while (opt != 't' && opt != 'n');
			cout << "Podaj liczbe wierzcholkow: ";
			cin >> size;
			cout << "Podaj gestosc grafu: ";
			cin >> density;
			srand((unsigned int)time(0));
			matrixRep.generateRandom(size, density, directed);
			//listRep.generateRandom(size, density, directed);
			matrixRep.display();
			listRep.display();
			break;
		case '3':
			matrixRep.display();
			listRep.display();
			break;
		case '4':	//tutaj Prim
			if(listRep.graph_size != 0) {
				matrixRep.mst_prim();
				listRep.mst_prim();
			}
			else {
				cout << "Nie utworzono/wczytano grafu!" << endl;
			}
			break;
		case '5':	//tutaj Kruskal
			if (listRep.graph_size != 0) {
				matrixRep.mst_kruskal();
				listRep.mst_kruskal();
			}
			else {
				cout << "Nie utworzono/wczytano grafu!" << endl;
			}
			break;
		}
	} while (opt != '0');
}

int main(int argc, char* argv[])
{	
	char option;
	do {
		cout << endl;
		cout << "=== MENU ===" << endl;
		cout << "1. MST" << endl;
		//cout << "2. NAJKROTSZA SCIEZKA" << endl;
		cout << "Podaj opcje:";
		option = _getche();
		cout << endl;

		switch (option) {
		case '1':
			menu_mst();
			break;

		case '2':

			break;

		case 's':		//w³asny case do przeprowadzania testów

			break;
		}

	} while (option != '0');
}

