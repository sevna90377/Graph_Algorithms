#include "List.h"
#include <iostream>
#include <fstream>
#include "heap.h"

using namespace std;

List::List() {

	List::headPointer = nullptr;
	List::tailPointer = nullptr;
	List::list_length = 0;

}

List::~List() {
	ListElement* holder = nullptr;

	for (int i = 0; i < list_length; i++) {
		holder = headPointer->next;
		delete headPointer;
		headPointer = holder;
	}
}

void List::addValue(Edge e) {

	if (headPointer == nullptr) {	//gdy lista jest pusta
		tailPointer = new ListElement;
		tailPointer->next = nullptr;
		tailPointer->previous = nullptr;
		tailPointer->edge = e;
		headPointer = tailPointer;
	}
	else {
		//Utworzenie wska�nika, kt�ry przechowa pozycj� poprzedniego elementu
		// po przypisaniu nowego elementu do wska�nika na ogon listy
		ListElement* lastElement = tailPointer;

		//Przypisanie do wska�nika na ogon nowego elementu i uzupe�nienie jego p�l
		tailPointer = new ListElement;
		tailPointer->edge = e;
		tailPointer->next = nullptr;
		tailPointer->previous = lastElement;

		//Przypisanie ostatniemu elementowi wska�nika na nowy element
		lastElement->next = tailPointer;
	}
	list_length++;
}

void List::display(int option) {

	if (headPointer != nullptr) {

		//Utworzenie wska�nika na aktualnie wy�wietlany element potrzebnego do iteracji
		// i przypisanie mu pocz�tku listy
		ListElement* holder = headPointer;

		cout << "Drzewo rozpinajace ";
		if (option == 1) {
			cout << "bedace wynikiem algorytmu o reprezentacji macierzowej: " << endl;
		}
		else {
			cout << "bedace wynikiem algorytmu o reprezentacji listowej: " << endl;
		}

		for (int i = 0; i < list_length; i++) {
			cout << " [" << holder->edge.v1 << ";" << holder->edge.v2 << "] " << holder->edge.weight << " ,";
			holder = holder->next;
		}
		cout << endl;
		
		int mst_weight = 0;
		holder = headPointer;
		for (int i = 0; i < list_length; i++) {
			mst_weight += holder->edge.weight;
			holder = holder->next;
		}

		cout << "Calkowita waga MST: " << mst_weight << endl;
	}
}