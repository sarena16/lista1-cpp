//
// Created by Sara Niedzielska on 16/11/2026.
// Kod został napisany samodzielnie z wykorzystaniem źródeł, ktore są podane niżej
//
//
// Źródła:
// - Definicja ciągu Fibonacciego (start od F0 = 0) i uwagi o wydajności rekurencji:
//   https://www.algorytm.edu.pl/algorytmy-maturalne/ciag-fibonacciego.html
// - Podstawy składni C++ (typy danych i ich zakresy, pętle, funkcje, rekurencja) z kursu AGH:
//   https://www.galaxy.agh.edu.pl/~pamalino/programowanie/cpp/index.php
// - Co to są warunki początkowe (preconditions) z learncpp:
//   https://www.learncpp.com/cpp-tutorial/assert-and-static_assert/
// - Jak pisać testy z assert i jak testować wyjątki:
//   https://uwf-fang.github.io/teaching/cpp/testing/testing/
//   https://stackoverflow.com/questions/15668309/c-assertion-function-to-check-that-exception-is-thrown
// - Format komentarzy dokumentacyjnych z dokumentacji Doxygen:
//   https://www.doxygen.nl/manual/docblocks.html
// - Claude Opus 5.5 (claude.ai): wyjaśnienia składni i niejasności, komentarze
//   dokumentacyjne, pomoc przy pętli, wersji rekurencyjnej, testach i przykładzie w main;



#include <iostream>   // żeby móc coś wypisać na ekran (cout)
#include <stdexcept>  // żeby móc rzucać wyjątki
#include <cassert>    // żeby móc pisać testy (assert)
#include <vector>     //żeby móc używać vector (lista wyrazów ciągu)

using namespace std;

/**
 * @brief Zwraca liste n pierwszych wyrazow ciagu Fibonacciego (wersja z petla).
 *
 * Ciag zaczyna sie od F0 = 0 i F1 = 1, a kazdy kolejny wyraz jest suma
 * dwoch poprzednich: 0, 1, 1, 2, 3, 5, 8, ...
 * Dla n = 0 zwracana jest pusta lista.
 *
 * @param n liczba wyrazow do obliczenia (od 0 do 93)
 * @return lista n pierwszych wyrazow ciagu
 * @throws std::invalid_argument gdy n jest ujemne
 * @throws std::out_of_range gdy n > 93 (94. wyraz przekracza zakres long long)
 */


vector<long long> fib_iteracja(int n) {

    // najpierw sprawdzam, czy n ma sens (warunki początkowe)
    // n < 0 → nie da się chcieć ujemnej liczby wyrazów
    if (n < 0) {
        throw invalid_argument("n nie moze byc ujemne");
    }

    // n > 93 → bo 94 wyraz ciągu przekracza zakres dla long long
    if (n > 93) {
        throw out_of_range("n za duze - liczby nie mieszcza sie w long long");
    }

    vector<long long> wynik;                    // pusta lista na wyrazy

    if (n >= 1) {
        wynik.push_back(0);                     // pierwszy wyraz, jeśli chcę co najmniej 1
    }
    if (n >= 2) {
        wynik.push_back(1);                     // drugi wyraz, jeśli chcę co najmniej 2
    }

    for (int i = 2; i < n; i++) {               // dalsze wyrazy: od pozycji 2 do n-1
        wynik.push_back(wynik[i - 1] + wynik[i - 2]);   // suma dwóch poprzednich
    }

    return wynik;
}


/**
 * @brief Zwraca liste n pierwszych wyrazow ciagu Fibonacciego (wersja rekurencyjna).
 *
 * Przypadki bazowe: n = 0, 1, 2 (wynik znany od razu).
 * Dla wiekszego n funkcja wywoluje sama siebie dla n - 1, a do otrzymanej
 * listy dopisuje sume dwoch ostatnich wyrazow. Kazde wywolanie wola siebie
 * tylko raz, wiec kazdy wyraz liczony jest jeden raz.
 *
 * @param n liczba wyrazow do obliczenia (od 0 do 93)
 * @return lista n pierwszych wyrazow ciagu
 * @throws std::invalid_argument gdy n jest ujemne
 * @throws std::out_of_range gdy n > 93 (94. wyraz przekracza zakres long long)
 */

vector<long long> fib_rekurencja(int n) {

    if (n < 0) {
        throw invalid_argument("n nie moze byc ujemne");
    }
    if (n > 93) {
        throw out_of_range("n za duze - liczby nie mieszcza sie w long long");
    }

    // przypadki bazowe (warunek stopu) – znam wynik od razu, bez wołania siebie
    if (n == 0) return {};             // 0 wyrazów → pusta lista
    if (n == 1) return {0};            // 1 wyraz → {0}
    if (n == 2) return {0, 1};         // 2 wyrazy → {0, 1}

    // krok rekurencyjny: biorę listę o jeden krótszą i dopisuję jeden wyraz
    vector<long long> wynik = fib_rekurencja(n - 1);   // funkcja woła samą siebie dla n-1
    int k = wynik.size();                              // ile elementów ma teraz lista
    wynik.push_back(wynik[k - 1] + wynik[k - 2]);      // ostatni + przedostatni

    return wynik;
}

// testy

/**
 * @brief Testy funkcji fib_iteracja i fib_rekurencja.
 *
 * Sprawdza przypadki typowe (n = 5, n = 10), przypadki brzegowe (n = 0, 1, 2
 * oraz najwieksze dozwolone n = 93), zgodnosc obu wersji dla kazdego n od 0
 * do 93 oraz to, czy obie funkcje rzucaja wyjatki dla n = -1 i n = 94.
 * Jesli wszystko przejdzie, wypisuje "testy przeszly".
 */

void test_fibonacci() {

    // przypadki typowe (znam wynik)
    assert(fib_iteracja(5) == vector<long long>({0, 1, 1, 2, 3}));                    // 5 pierwszych wyrazów
    assert(fib_iteracja(10) == vector<long long>({0, 1, 1, 2, 3, 5, 8, 13, 21, 34})); // 10 pierwszych wyrazów

    // przypadki brzegowe: małe n
    assert(fib_iteracja(0).empty());                        // 0 wyrazów → pusta lista
    assert(fib_iteracja(1) == vector<long long>({0}));      // 1 wyraz → {0}
    assert(fib_iteracja(2) == vector<long long>({0, 1}));   // 2 wyrazy → {0, 1}

    // przypadek brzegowy: największe dozwolone n
    assert(fib_iteracja(93).size() == 93);                       // lista ma 93 wyrazy
    assert(fib_iteracja(93).back() == 7540113804746346429LL);    // ostatni wyraz jest poprawny (nie przepełnił się)
                                                                 // back() = ostatni element, LL = liczba typu long long

    // obie wersje muszą dawać to samo dla każdego n od 0 do 93
    // skoro iteracja jest sprawdzona wyżej, to rekurencja też jest dobra
    for (int n = 0; n <= 93; n++) {
        assert(fib_iteracja(n) == fib_rekurencja(n));
    }

    // wyjątki: n ujemne → invalid_argument (obie funkcje)
    bool byl_wyjatek = false;           // flaga: na start zakładam, że wyjątku nie było
    try {
        fib_iteracja(-1);
    } catch (const invalid_argument& e) {
        byl_wyjatek = true;             // był błąd → zmieniam na true
    }
    assert(byl_wyjatek);                // sprawdzam, czy funkcja zgłosiła błąd

    byl_wyjatek = false;                // zeruję przed kolejnym testem
    try {
        fib_rekurencja(-1);
    } catch (const invalid_argument& e) {
        byl_wyjatek = true;
    }
    assert(byl_wyjatek);

    // wyjątki: n za duże → out_of_range (obie funkcje), inny typ wyjątku niż wyżej
    byl_wyjatek = false;
    try {
        fib_iteracja(94);
    } catch (const out_of_range& e) {
        byl_wyjatek = true;
    }
    assert(byl_wyjatek);

    byl_wyjatek = false;
    try {
        fib_rekurencja(94);
    } catch (const out_of_range& e) {
        byl_wyjatek = true;
    }
    assert(byl_wyjatek);

    cout << "testy przeszły" << endl;         // jak doszło tutaj, wszystkie testy przeszły
}


/**
 * @brief Funkcja glowna programu.
 *
 * Uruchamia testy, a potem wypisuje 10 pierwszych wyrazow ciagu
 * obliczonych obiema wersjami funkcji.
 *
 * @return 0 gdy program zakonczyl sie poprawnie
 */

int main() {
    test_fibonacci();                                   // najpierw odpalam testy

    int n = 10;                                         // ile wyrazów chcę (ustalone w kodzie)

    try {                                               // funkcje mogą rzucić wyjątek (złe n)
        vector<long long> wynik_iter = fib_iteracja(n);     // wersja z pętlą
        vector<long long> wynik_rek = fib_rekurencja(n);    // wersja z rekurencją

        cout << "iteracja:  ";
        for (long long wyraz : wynik_iter) {            // wypisuję wyrazy po kolei
            cout << wyraz << " ";
        }
        cout << endl;

        cout << "rekurencja: ";
        for (long long wyraz : wynik_rek) {
            cout << wyraz << " ";
        }
        cout << endl;

    } catch (const invalid_argument& e) {               // n ujemne
        cout << "błąd: " << e.what() << endl;
    } catch (const out_of_range& e) {                   // n za duże
        cout << "błąd: " << e.what() << endl;
    }

    return 0;
}