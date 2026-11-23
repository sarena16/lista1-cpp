//
// Created by Sara Niedzielska on 12/11/2026.
// Kod został napisany samodzielnie z wykorzystaniem źródeł, ktore są podane niżej
//
// Źródła:
// - Podstawy składni C++ (typy, if, pętle, funkcje, vector) z kursu AGH:
//   https://www.galaxy.agh.edu.pl/~pamalino/programowanie/cpp/index.php
// - Co to są warunki początkowe (preconditions) z learncpp:
//   https://www.learncpp.com/cpp-tutorial/assert-and-static_assert/
// - Jak pisać testy z assert i jak testować wyjątki:
//   https://uwf-fang.github.io/teaching/cpp/testing/testing/
//   https://stackoverflow.com/questions/15668309/c-assertion-function-to-check-that-exception-is-thrown
// - Format komentarzy dokumentacyjnych z dokumentacji Doxygen:
//   https://www.doxygen.nl/manual/docblocks.html
// - Claude Opus 5.5 (claude.ai): wyjaśnienia składni i niejasności, komentarze
//   dokumentacyjne, pomysł na szukanie i usuwanie elementów (find/erase)


#include <iostream>   // żeby móc coś wypisać na ekran (cout)
#include <stdexcept>  // żeby móc rzucać wyjątki (invalid_argument)
#include <cassert>    // żeby móc pisać testy (assert)
#include <vector>     //żeby móc używać vector (multizbiory)
#include <algorithm>  // żeby mieć find (szukanie elementu w wektorze)


using namespace std;

/**
 * @brief Zwraca czesc wspolna dwoch multizbiorow x i y.
 *
 * Kazdy element trafia do wyniku tyle razy, ile razy wystepuje w obu
 * multizbiorach naraz (czyli mniejsza z liczb wystapien).
 * Elementy w wyniku sa w kolejnosci, w jakiej wystepuja w x.
 *
 * @param x pierwszy multizbior
 * @param y drugi multizbior (funkcja dostaje kopie, oryginal sie nie zmienia)
 * @return czesc wspolna x i y
 * @throws invalid_argument gdy x lub y jest pusty
 */
// claude wygenerował te komntarze dokumentacyjne

vector<int> wspolne(vector<int> x, vector<int> y) {

    if (x.empty() || y.empty()) {                // najpierw sprawdzam dane: oba multizbiory muszą mieć jakieś elementy
        throw invalid_argument("multizbiory nie moga byc puste");
    }

    vector<int> wynik;            // tu będę zbierać część wspólną

    // przechodzę po każdym elemencie z x
    for (int element : x) {                                                   // biorę po kolei każdy element z x
        auto it = find(y.begin(), y.end(), element);   // szukam tego elementu w y
        if (it != y.end()) {                                                  // jeśli znalazło (nie jest "za końcem")
            wynik.push_back(element);                                         // dodaję go do wyniku
            y.erase(it);                                                   // usuwam go z y, żeby nie użyć drugi raz
        }
    }

    return wynik;                                      // oddaję część wspólną
}


// testy

/**
 * @brief Testy funkcji wspolne.
 *
 * Sprawdza przypadki typowe (z powtorzeniami i bez), przypadki nietypowe
 * (brak wspolnych elementow, identyczne multizbiory) oraz to, czy funkcja
 * rzuca wyjatek, gdy x lub y jest pusty. Jesli wszystko przejdzie,
 * wypisuje "testy przeszly".
 */
// te też claude wygenerował komentarze

void test_wspolne() {

    //przypadki typowe
    assert(wspolne({1, 1, 1, 2}, {1, 1, 3}) == vector<int>({1, 1}));   // powtórzenia: 1 jest 2 razy w obu
    assert(wspolne({1, 2, 3}, {2, 3, 4}) == vector<int>({2, 3}));      // zwykła część wspólna

    //przypadki nietypowe
    assert(wspolne({1, 2}, {3, 4}).empty());                           // nic wspólnego → pusty wynik
    assert(wspolne({5, 5}, {5, 5}) == vector<int>({5, 5}));

    // pusty x → powinien być wyjątek
    bool byl_wyjatek = false;
    try {
        wspolne({}, {1, 2});
    } catch (const invalid_argument& e) {
        byl_wyjatek = true;
    }
    assert(byl_wyjatek);

    // pusty y → też wyjątek
    byl_wyjatek = false;
    try {
        wspolne({1, 2}, {});
    } catch (const invalid_argument& e) {
        byl_wyjatek = true;
    }
    assert(byl_wyjatek);

    cout << "testy przeszły" << endl;
}

int main() {
    test_wspolne();

    // ten fragment wygenerował mi claude
    vector<int> x = {1, 1, 2, 3};          // przykładowe multizbiory ustalone w kodzie
    vector<int> y = {1, 1, 1, 2, 4};

    try {                                  // wspolne może rzucić wyjątek (pusty multizbiór)
        vector<int> wynik = wspolne(x, y); // liczę część wspólną

        cout << "czesc wspólna: ";
        for (int element : wynik) {        // przechodzę po każdym elemencie wyniku
            cout << element << " ";        // wypisuję go ze spacją
        }
        cout << endl;                      // nowa linia na końcu

    } catch (const invalid_argument& e) {  // jak był wyjątek → wypisuję komunikat
        cout << "bład: " << e.what() << endl;
    }

    return 0;
}