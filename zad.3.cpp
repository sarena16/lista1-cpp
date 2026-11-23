//
// Created by Sara Niedzielska on 12/11/2026.
// Kod został napisany samodzielnie z wykorzystaniem źródeł, ktore są podane niżej
//
// Źródła:
// - Podstawy składni C++ (typy, if, pętle, funkcje, vector) z kursu AGH:
//   https://www.galaxy.agh.edu.pl/~pamalino/programowanie/cpp/index.php
// - Co to są warunki początkowe (preconditions) z learncpp:
//   https://www.learncpp.com/cpp-tutorial/assert-and-static_assert/
// - Ile podzbiorów ma zbiór n-elementowy (2^n) – na tym oparłam testy:
//   https://zpe.gov.pl/a/podzbiory-zbioru-skonczonego-tresc-rozszerzona/DUzQbD05Q
// - Jak pisać testy z assert i jak testować wyjątki:
//   https://uwf-fang.github.io/teaching/cpp/testing/testing/
//   https://stackoverflow.com/questions/15668309/c-assertion-function-to-check-that-exception-is-thrown
// - Format komentarzy dokumentacyjnych z dokumentacji Doxygen:
//   https://www.doxygen.nl/manual/docblocks.html
// - Claude Opus 5.5 (claude.ai): wyjaśnienia składni i niejasności, komentarze
//   dokumentacyjne, pętla tworząca podzbiory, przykład w main;

#include <iostream>   // żeby móc coś wypisać na ekran (cout)
#include <stdexcept>  // żeby móc rzucać wyjątki (invalid_argument)
#include <cassert>    // żeby móc pisać testy (assert)
#include <vector>     //żeby móc używać vector (multizbiory)

using namespace std;

/**
 * @brief Zwraca liste wszystkich podzbiorow zbioru x.
 *
 * Zaczyna od listy zawierajacej tylko zbior pusty. Dla kazdego kolejnego
 * elementu x robi kopie wszystkich dotychczasowych podzbiorow, dopisuje
 * do nich ten element i dodaje je do listy. Dzieki temu liczba podzbiorow
 * podwaja sie z kazdym elementem i na koncu wynosi 2^n (n - liczba elementow x).
 * Podzbiory sa zwracane w dowolnej kolejnosci.
 *
 * @param x zbior elementow (bez powtorzen)
 * @return lista wszystkich podzbiorow x, lacznie ze zbiorem pustym i calym x
 * @throws invalid_argument gdy w x jakis element wystepuje wiecej niz raz
 */



vector<vector<char>> podzbiory(vector<char> x) {

    for (int i = 0; i < x.size(); i++) {             // biorę każdą literę po kolei
        for (int j = i + 1; j < x.size(); j++) {     // porównuję ją z każdą następną
            if (x[i] == x[j]) {                      // jeśli są takie same
                throw invalid_argument("zbior nie moze miec powtorzen");      // błąd: powtórzenie
            }
        }
    }

    vector<vector<char>> wynik = {{}};      // na start tylko zbiór pusty

    for (char element : x) {                // biorę po kolei każdą literę z x
        int ile = wynik.size();             // ile podzbiorów jest przed dokładaniem

        for (int k = 0; k < ile; k++) {     // idę tylko po starych podzbiorach
            vector<char> nowy = wynik[k];   // kopia starego podzbioru
            nowy.push_back(element);        // dopisuję do niej literę
            wynik.push_back(nowy);          // dodaję nowy podzbiór do wyniku
        }
    }

    return wynik;                           // oddaje wszystkie podzbiory
}

//testy

/**
 * @brief Testy funkcji podzbiory.
 *
 * Sprawdza liczbe zwracanych podzbiorow (musi wynosic 2^n) dla zbioru
 * 4-elementowego, 1-elementowego i pustego, oraz to, czy funkcja rzuca
 * wyjatek dla zbioru z powtorzeniem. Jesli wszystko przejdzie,
 * wypisuje "testy przeszly".
 */

void test_podzbiory() {

    // to test typowy
    assert(podzbiory({'a', 'b', 'c', 'd'}).size() == 16);    // 4 elementy → 16 podzbiorów (jak w treści)
    // ten brzegowy (chodzi o to ze to przypadki w ktoryc kod sie najłatwiej psuje)
    assert(podzbiory({'a'}).size() == 2);   // 1 element → {} i {a}
    assert(podzbiory({}).size() == 1);    // zbiór pusty → tylko {}

    // zbior z powtorzeniem → powinien byc wyjatek
    bool byl_wyjatek = false;
    try {
        podzbiory({'a', 'b', 'a'});
    } catch (const invalid_argument& e) {
        byl_wyjatek = true;
    }
    assert(byl_wyjatek);

    cout << "testy przeszły" << endl;
}



/**
 * @brief Funkcja glowna programu.
 *
 * Uruchamia testy, a potem wyznacza i wypisuje wszystkie podzbiory
 * przykladowego zbioru {a, b, c}. Jesli zbior jest niepoprawny,
 * wypisuje komunikat bledu.
 *
 * @return 0 gdy program zakonczyl sie poprawnie
 */

int main() {
    test_podzbiory();

    vector<char> x = {'a', 'b', 'c'};                  // przykładowy zbiór ustalony w kodzie

    try {                                              // podzbiory może rzucić wyjątek (powtórzenia)
        vector<vector<char>> wynik = podzbiory(x);     // liczę wszystkie podzbiory

        cout << "podzbiory:" << endl;
        for (vector<char> podzbior : wynik) {          // biorę po kolei każdy podzbiór
            cout << "{ ";
            for (char litera : podzbior) {             // wypisuję litery z tego podzbioru
                cout << litera << " ";
            }
            cout << "}" << endl;                       // zamykam nawias i nowa linia
        }

    } catch (const invalid_argument& e) {              // jak był wyjątek → wypisuję komunikat
        cout << "błąd: " << e.what() << endl;
    }

    return 0;
}