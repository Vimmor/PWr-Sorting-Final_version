#ifndef TABLICA_HH
#define TABLICA_HH

template <typename T>
class Tablica {
	T *tab;
	T *pom;
	int rozmiar;
public:

	//przeciazenie operatora []
	T operator [](int licz) const {
		return tab[licz];
	}
	T& operator [](int licz) {
		return tab[licz];
	}

	//Metody funkcyjne klasy tablica
	void tworzTab(int);
	void tworzPom();
	void wypelnij(T*);
	void wypisz();
	void kopiuj(T*,T*);
	void zapisz();
	void czyszczeniePliku();
	void zwolnij_pamiec(T*);
	void odwroc(T*);
	T* getTab();
	T * getPom();
	int getRozmiar();

	//Algorytmy sortujace
	void quick_sort(int, int);
	void heap_sort(T*, T*);
	void sortowanie_wstawianie(int);
	void introspective_sort(int*, int*, int);
	int partycjonowanie(int, int);
	void merge(int, int, int);
	void merge_sort(int, int);
	void shell_sort();

	//Metody odpowiadajace za testy
	void czesc_posortowana(double,int);
	void sortowanie_odwrotna_kolejnosc(int);
	void sortowanie_losowe(int);
	void menu();

};
#endif