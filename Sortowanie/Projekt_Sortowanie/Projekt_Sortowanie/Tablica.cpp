#include "pch.h"
#include "Tablica.h"
using namespace std;

//tworzymy tablice wlasciwa
template<typename T>
void Tablica<T>::tworzTab(int rozmiar) {
	tab = new T[rozmiar];
	this->rozmiar = rozmiar;
}

//tworzymy tablice pomocnicza
template<typename T>
void Tablica<T>::tworzPom() {
	pom = new T[rozmiar];
}

//wypelniamy tablice liczbami pseudolosowymi
template <typename T>
void Tablica<T>::wypelnij(T *tab){
		for (int i = 0; i < rozmiar; i++) {
			tab[i] = rand()%rozmiar+1;
		} 
}

//wypisuje tablice oryginalna i pomocnicza na standardowe wyjscie
template <typename T>
void Tablica<T>::wypisz(){
		for (int i = 0;i<rozmiar; i++) {
			cout << tab[i] << " ";
		}
		cout << "\n"<<endl;
		for (int i = 0; i <rozmiar; i++) {
			cout << pom[i] << " ";
		}
}

//Kopiowanie wszystkich elementow z jednej tablicy do drugiej
template <typename T>
void Tablica<T>::kopiuj(T *tab,T *tab2){
	for (int i = 0; i < rozmiar; i++) {
		tab[i] = tab2[i];
	}
}

//dopisywanie danych do pliku
template <typename T>
void Tablica<T>::zapisz() {
	fstream plik;
	plik.open("Wynik_sortowania.txt", ios_base::app); //dopisywanie danych na koniec pliku
	plik <<"Tablica oryginalna:" << endl;
	for (int i =0; i < rozmiar; i++) {
		plik << tab[i]<< " ";
	}
	plik <<"Tablica posortowana:" << endl;
	for (int i = 0; i < rozmiar; i++) {
		plik << pom[i] << " ";
	}
	plik.close();
}

//funkcja czyszczaca plik, do ktorego zapisujemy dane
template<typename T>
void Tablica<T>::czyszczeniePliku() {
	fstream plik;
	plik.open("Wynik_sortowania.txt", ios::out | ios::trunc);
}

//usuwanie tablicy - zwalnianie pamieci
template<typename T>
void Tablica<T>::zwolnij_pamiec(T* tab) {
	delete[] tab;
}

//odwracanie tablicy
/*Funkcja odwracajaca tablice, uzywana w przypadku
gdy liczby sa w odwrotnej kolejnosci*/
template<typename T>
void Tablica<T>::odwroc(T *tab) {
	T *tymczasowa = new T[rozmiar];
	for (int i = 0; i < rozmiar; i++) {
		tymczasowa[i] = tab[i];
	}
	for(int i=0;i<rozmiar;i++){
		tab[i] = tymczasowa[rozmiar - 1 - i];
	}
}

//zwracanie tablicy oryginalnej
template<typename T>
T* Tablica<T>::getTab() {
	return tab;
}

//zwracanie tablicy pomocniczej
template<typename T>
T* Tablica<T>::getPom() {
	return pom;
}

//zwracanie rozmiaru tablic
template<typename T>
int Tablica<T>::getRozmiar() {
	return rozmiar;
}

//funkcja partycjujaca, ktora jest elementem quicksorta
template<typename T>
int Tablica<T>::partycjonowanie(int poczatek, int koniec) {
	int piwot = pom[koniec];
	int k = poczatek, pom1;

	for (int i = poczatek; i < koniec; i++) {
		if (pom[i] <= piwot) {
			pom1 = pom[i];
			pom[i] = pom[k];
			pom[k] = pom1;
			k++;
		}
	}
	pom[koniec] = pom[k];
	pom[k] = piwot;
	return k;
}

//algorytm sortowania szybkiego
template<typename T>
void Tablica<T>::quick_sort(int poczatek, int koniec) {
	int piwot;
	if (poczatek < koniec) {
		piwot = partycjonowanie(poczatek, koniec);
		quick_sort(poczatek, piwot-1);
		quick_sort(piwot + 1, koniec);
	}
}

//sortowanie przez kopcowanie (uzywane w sortowaniu introspektywnym)
template<typename T>
void Tablica<T>::heap_sort(T *lewy,T *prawy) {
	make_heap(lewy,prawy);
	sort_heap(lewy,prawy);
}

//sortowanie przez wstawianie - uzywane w introsorcie
template<typename T>
void Tablica<T>::sortowanie_wstawianie(int n){
	int pom2, k;
	for (int i = 1; i < n; i++) {
		pom2 = pom[i];
		k = i - 1;
		while (k >= 0 && pom[k] > pom2) {
			pom[k + 1] = pom[k];
			k--;
		}
		pom[k+1] = pom2;
	}
}

// implementacja sortowania introspektywnego
template<typename T>
void Tablica<T>::introspective_sort(int *poczatek,int *koniec,int glebokosc) {
	if ((koniec - poczatek) < 16)
		sortowanie_wstawianie(rozmiar);
	else if (glebokosc == 0)
		heap_sort(poczatek, koniec + 1);
	else{
		int piwot = partycjonowanie(0,rozmiar-1);
		introspective_sort(poczatek,pom + piwot, glebokosc - 1);
		introspective_sort(pom + piwot + 1, koniec, glebokosc - 1);
	}
}

// scalanie tablic
template<typename T>
void Tablica<T>::merge(int poczatek, int srodkowy, int koniec) {
	int i, j;
	for (i = srodkowy + 1; i > poczatek; i--)
		pom[i - 1] = tab[i - 1];
	for (j = srodkowy; j < koniec; j++)
		pom[koniec + srodkowy - j] = tab[j + 1];
	for (int k = poczatek; k <= koniec; k++)
		if (pom[j] < pom[i])
			tab[k] = pom[j--];
		else
			tab[k] = pom[i++];
}

// algorytm sortowania przez scalanie wykorzystujace metode merge
template<typename T>
void Tablica<T>::merge_sort(int poczatek, int koniec){
	if (koniec <= poczatek)
		return;
	int srodkowy = (poczatek + koniec) / 2;
	merge_sort(poczatek, srodkowy);
	merge_sort(srodkowy + 1, koniec);
	merge(poczatek, srodkowy, koniec);
}

// implementacja sortowania Shella - nie uzywana do testow 
template<typename T>
void Tablica<T>::shell_sort(){
	int odstep = rozmiar / 2;
	while (odstep >= 1) {
		for (int i = odstep; i < rozmiar; i++) {
			int tymczasowy = pom[i];
			int j;
			for (j = i; j >= odstep && pom[j - odstep] > tymczasowy; j -= odstep)
				pom[j] = pom[j - odstep];
			pom[j] = tymczasowy;
		}
		odstep /= 2;
	}
}

// sortowanie tablicy, ktora wczesniej zostala czesciowo posortowana
template<typename T>
void Tablica<T>::czesc_posortowana(double ilosc,int rozmiar) {
	srand(time(NULL));
	int x = (int)((rozmiar*ilosc)/100);
	clock_t start;
	double czas;
	start = clock();
	for (int i = 0; i < 100; i++) {
		tworzTab(rozmiar);
		tworzPom();
		wypelnij(tab);
		kopiuj(pom, tab);
		quick_sort(0,x-1);
		kopiuj(tab, pom);
		quick_sort(0, rozmiar - 1);
		//zapisz();
		zwolnij_pamiec(tab);
		zwolnij_pamiec(pom);
	}
	czas = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Czasy sortowania poszczegolnych algorytmow to:\nSortowanie szybkie:" << czas << endl;
	start = clock();
	for (int i = 0; i < 100; i++) {
		tworzTab(rozmiar);
		tworzPom();
		wypelnij(tab);
		kopiuj(pom, tab);
		merge_sort(0, x - 1);
		kopiuj(tab, pom);
		merge_sort(0, rozmiar - 1);
		//zapisz();
		zwolnij_pamiec(tab);
		zwolnij_pamiec(pom);
	}
	czas = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Sortowanie przez Scalanie:" << czas << endl;
	int glebokosc = log(rozmiar) * 2;
	start = clock();
	for (int i = 0; i < 100; i++) {
		tworzTab(rozmiar);
		tworzPom();
		wypelnij(tab);
		kopiuj(pom, tab);
		quick_sort(0, x - 1);
		kopiuj(tab, pom);
		introspective_sort(pom,pom+rozmiar,glebokosc);
		//zapisz();
		zwolnij_pamiec(tab);
		zwolnij_pamiec(pom);
	}
	czas = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Sortowanie Introspektywne (Introsort):" << czas << endl;
}

// sortowanie tablicy ktora jest w calosci posortowana ale ustawiona w odwrotnej kolejnosc 4
// quicksort sortuje dla piwota = srodek
template<typename T>
void Tablica<T>::sortowanie_odwrotna_kolejnosc(int rozmiar) {
	srand(time(NULL));
	clock_t start;
	double czas;
	start = clock();
	for (int i = 0; i < 100; i++) {
		tworzTab(rozmiar);
		tworzPom();
		wypelnij(tab);
		kopiuj(pom, tab);
		quick_sort(0, rozmiar - 1);
		odwroc(pom);
		kopiuj(tab, pom);
		quick_sort(0, rozmiar - 1);
		//zapisz();
		zwolnij_pamiec(tab);
		zwolnij_pamiec(pom);
	}
	czas = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Czasy sortowania poszczegolnych algorytmow to:\nSortowanie szybkie:" << czas << endl;
	start = clock();
	for (int i = 0; i < 100; i++) {
		tworzTab(rozmiar);
		tworzPom();
		wypelnij(tab);
		kopiuj(pom, tab);
		merge_sort(0, rozmiar - 1);
		odwroc(pom);
		merge_sort(0, rozmiar - 1);
		//zapisz();
		zwolnij_pamiec(tab);
		zwolnij_pamiec(pom);
	}
	czas = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Sortowanie przez Scalanie:" << czas << endl;
	int glebokosc = log(rozmiar) * 2;
	start = clock();
	for (int i = 0; i < 100; i++) {
		tworzTab(rozmiar);
		tworzPom();
		wypelnij(tab);
		kopiuj(pom, tab);
		quick_sort(0, rozmiar - 1);
		odwroc(pom);
		introspective_sort(pom,pom+rozmiar,glebokosc);
		//zapisz();
		zwolnij_pamiec(tab);
		zwolnij_pamiec(pom);
	}
	czas = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Sortowanie Introspektywne (Introsort):" << czas << endl;*/
}

// sortowanie tablicy calkowicie nieposortowanej
template<typename T>
void Tablica<T>::sortowanie_losowe(int rozmiar) {
	srand(time(NULL));
	clock_t start,t;
	double czas;
	start = clock();
	for (int i = 0; i < 100; i++){
	tworzTab(rozmiar);
	tworzPom();
	wypelnij(tab);
	kopiuj(pom, tab);
	quick_sort(0, rozmiar - 1);
	//zapisz();s
	zwolnij_pamiec(tab);
	zwolnij_pamiec(pom);
	}
	czas = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Czasy sortowania poszczegolnych algorytmow to:\nSortowanie szybkie:" << czas << endl;
	start = clock();
	for (int i = 0; i < 100; i++) {
		tworzTab(rozmiar);
		tworzPom();
		wypelnij(tab);
		kopiuj(pom, tab);
		merge_sort(0, rozmiar - 1); 
		//zapisz();
		zwolnij_pamiec(tab);
		zwolnij_pamiec(pom);
	}
	czas = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Sortowanie przez scalanie:"<< czas << endl;
	start = clock();
	int glebokosc = 2 * log(rozmiar);
	for (int i = 0; i < 100; i++) {
		tworzTab(rozmiar);
		tworzPom();
		wypelnij(tab);
		kopiuj(pom, tab);
		introspective_sort(pom, pom + rozmiar, glebokosc);
		//zapisz();
		zwolnij_pamiec(tab);
		zwolnij_pamiec(pom);
	}
	czas = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Sortowanie Introspektywne (Introsort)"<< czas << endl;
}

// menu uzytkownika - wykorzystywane do przeprowadzenia testow
template<typename T>
void Tablica<T>::menu() {
	int wybor, ilosc;
	cout << "Witaj w programie do sortowania elementow calkowitoliczbowych\n";
	do {
		cout << "1. 25% poczatkowych elementow posortowanych\n2. 50% poczatkowych elementow posortowanych\n3. 75% poczatkowych elementow posortowanych\n4. 95% poczatkowych elementow posortowanych\n5. 99% poczatkowych elementow posortowanych\n6. 99,7% poczatkowych elementow posortowanych\n7. Wszystkie elementy juz posortowane, ale w odwrotnej kolejnosci\n8. Wszystkie elementy losowe.\n0. Zakoncz dzialanie programu\n";
		cin >> wybor;
		switch (wybor) {
		case 1: {
			cout << "Podaj rozmiar tablic:";
			cin >> ilosc;
			czesc_posortowana(25,ilosc);
			break;
		}
		case 2: {
			cout << "Podaj rozmiar tablic:";
			cin >> ilosc;
			czesc_posortowana(50,ilosc);
			break;
		}
		case 3: {
			cout << "Podaj rozmiar tablic:";
			cin >> ilosc;
			czesc_posortowana(75,ilosc);
			break;
		}
		case 4: {
			cout << "Podaj rozmiar tablic:";
			cin >> ilosc;
			czesc_posortowana(95,ilosc);
			break;
		}
		case 5: {
			cout << "Podaj rozmiar tablic:";
			cin >> ilosc;
			czesc_posortowana(99,ilosc);
			break;
		}
		case 6: {
			cout << "Podaj rozmiar tablic:";
			cin >> ilosc;
			czesc_posortowana(99.7, ilosc);
			break;
		}
		case 7: {
			cout << "Podaj rozmiar tablic:";
			cin >> ilosc;
			sortowanie_odwrotna_kolejnosc(ilosc);
			break;
		}
		case 8: {
			cout << "Podaj rozmiar tablic:";
			cin >> ilosc;
			sortowanie_losowe(ilosc);
			break;
		}
		case 0: break;
		}
	} while (wybor != 0);
}
template class Tablica<int>;