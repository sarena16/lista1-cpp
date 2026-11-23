//
// Created by Sara Niedzielska on 16/11/2026.
// Kod został napisany samodzielnie z wykorzystaniem źródeł, ktore są podane niżej
//
// Źródła:
// - Definicja ciągu i problemu Collatza (źródło podane w treści zadania):
//   https://pl.wikipedia.org/wiki/Problem_Collatza
// - Podstawy składni C++ (typy danych i ich zakresy, numeric_limits, pętle, funkcje) z kursu AGH:
//   https://www.galaxy.agh.edu.pl/~pamalino/programowanie/cpp/index.php
// - Co to są warunki początkowe (preconditions) z learncpp:
//   https://www.learncpp.com/cpp-tutorial/assert-and-static_assert/
// - Jak pisać testy z assert i jak testować wyjątki:
//   https://uwf-fang.github.io/teaching/cpp/testing/testing/
//   https://stackoverflow.com/questions/15668309/c-assertion-function-to-check-that-exception-is-thrown
// - Format komentarzy dokumentacyjnych z dokumentacji Doxygen:
//   https://www.doxygen.nl/manual/docblocks.html
// - Claude Opus 5.5 (claude.ai): wyjaśnienia składni i niejasności, komentarze
//   dokumentacyjne, pomoc przy funkcji collatz (w tym sprawdzanie przepełnienia),
//   testach

#include <iostream>   // żeby móc coś wypisać na ekran (cout)
#include <stdexcept>  // żeby móc rzucać wyjątki (invalid_argument, overflow_error)
#include <cassert>    // żeby móc pisać testy (assert)
#include <vector>     // żeby móc używać vector (lista elementów ciągu)
#include <limits>     // żeby znać największą liczbę long long (numeric_limits)

using namespace std;

/**
 * @brief Zwraca elementy ciagu Collatza dla c0 przed wpadnieciem w cykl (4, 2, 1).
 *
 * Kolejny element: c/2 gdy c jest parzyste, 3c + 1 gdy c jest nieparzyste.
 * Funkcja zbiera elementy, dopoki ciag nie trafi na 4, 2 lub 1 (czyli na cykl).
 * Elementy cyklu nie sa dolaczane, wiec dla c0 = 1, 2 lub 4 zwracana jest
 * pusta lista (ciag od razu jest w cyklu).
 *
 * @param c0 pierwszy element ciagu (liczba naturalna, c0 >= 1)
 * @return lista elementow ciagu przed wpadnieciem w cykl
 * @throws std::invalid_argument gdy c0 <= 0
 * @throws std::overflow_error gdy kolejny element przekroczylby zakres long long
 */
vector<long long> collatz(long long c0) {

    // najpierw sprawdzam, czy c0 ma sens (warunki początkowe)
    // c0 <= 0 → to nie jest liczba naturalna, a dla 0 ciąg byłby 0, 0, 0... w nieskończoność
    if (c0 <= 0) {
        throw invalid_argument("c0 musi byc liczba naturalna (wieksza od 0)");
    }

    vector<long long> wynik;                    // pusta lista na elementy ciągu
    long long c = c0;                           // aktualny element, zaczynam od c0

    // dopóki nie trafiłam na cykl (4, 2, 1), dopisuję element i liczę następny
    while (c != 4 && c != 2 && c != 1) {
        wynik.push_back(c);                     // dopisuję aktualny element

        if (c % 2 == 0) {                       // % 2 == 0 → liczba parzysta
            c = c / 2;
        } else {                                // nieparzysta → 3c + 1
            // sprawdzam, czy 3c + 1 zmieści się w long long (inaczej nastąpiłoby przepełnienie)
            if (c > (numeric_limits<long long>::max() - 1) / 3) {
                throw overflow_error("kolejny element ciagu przekracza zakres long long");
            }
            c = 3 * c + 1;
        }
    }

    return wynik;
}

// testy

/**
 * @brief Testy funkcji collatz.
 *
 * Sprawdza przypadki typowe (c0 = 6, 3, 27), przypadki brzegowe
 * (c0 = 1, 2, 4 – od razu w cyklu, c0 = 8 – jeden element przed cyklem)
 * oraz wyjatki dla c0 = 0, c0 ujemnego i przepelnienia.
 * Jesli wszystko przejdzie, wypisuje "testy przeszly".
 */
void test_collatz() {

    // przypadki typowe
    assert(collatz(6) == vector<long long>({6, 3, 10, 5, 16, 8}));   // 6 → 3 → 10 → 5 → 16 → 8 → (4, 2, 1)
    assert(collatz(3) == vector<long long>({3, 10, 5, 16, 8}));      // 3 → 10 → 5 → 16 → 8 → (4, 2, 1)
    assert(collatz(27).size() == 109);                                  // 27 ma 109 elementów przed cyklem

    // przypadki brzegowe: c0 już jest w cyklu → pusta lista
    assert(collatz(1).empty());
    assert(collatz(2).empty());
    assert(collatz(4).empty());

    // przypadek brzegowy: tylko jeden element przed cyklem
    assert(collatz(8) == vector<long long>({8}));                    // 8 → (4, 2, 1)

    // wyjątki: c0 = 0 → invalid_argument
    bool byl_wyjatek = false;           // flaga: na start zakładam, że wyjątku nie było
    try {
        collatz(0);
    } catch (const invalid_argument& e) {
        byl_wyjatek = true;             // był błąd → zmieniam na true
    }
    assert(byl_wyjatek);                // sprawdzam, czy funkcja zgłosiła błąd

    // wyjątki: c0 ujemne → invalid_argument
    byl_wyjatek = false;                // zeruję przed kolejnym testem
    try {
        collatz(-5);
    } catch (const invalid_argument& e) {
        byl_wyjatek = true;
    }
    assert(byl_wyjatek);

    // wyjątki: ogromne c0 → 3c + 1 nie mieści się w long long → overflow_error
    byl_wyjatek = false;
    try {
        collatz(numeric_limits<long long>::max());   // największy long long (nieparzysty)
    } catch (const overflow_error& e) {
        byl_wyjatek = true;
    }
    assert(byl_wyjatek);

    cout << "testy przeszły" << endl;         // jak doszło tutaj, wszystkie testy przeszły
}

/**
 * @brief Bada ciagi Collatza dla c0 od 1 do max_c0.
 *
 * Wyszukuje najdluzszy ciag przed wpadnieciem w cykl oraz najwiekszy element,
 * jaki pojawil sie w ktorymkolwiek ciagu, i wypisuje odpowiadajace im c0.
 * Przy remisie zapamietywane jest najmniejsze c0.
 *
 *
 *Wyniki dla c0 od 1 do 10000 (bez cyklu 4, 2, 1):
 * - max wartosc elementu: 27114424 dla c0 = 9663
 * - max dlugosc ciagu: 259 dla c0 = 6171
 *
 *
 * @param max_c0 najwieksze badane c0
 */
void badanie(long long max_c0) {
    long long najdluzsza_dlugosc = 0;
    long long c0_najdluzszy = 1;
    long long najwiekszy_element = 0;
    long long c0_najwiekszy = 1;

    for (long long c0 = 1; c0 <= max_c0; c0++) {
        vector<long long> ciag = collatz(c0);

        long long dlugosc = ciag.size();
        if (dlugosc > najdluzsza_dlugosc) {
            najdluzsza_dlugosc = dlugosc;
            c0_najdluzszy = c0;
        }

        for (long long element : ciag) {
            if (element > najwiekszy_element) {
                najwiekszy_element = element;
                c0_najwiekszy = c0;
            }
        }
    }

    cout << "badanie dla c0 od 1 do " << max_c0 << ":" << endl;
    cout << "  najdłuzszy ciag: " << najdluzsza_dlugosc << " elementow, dla c0 = " << c0_najdluzszy << endl;
    cout << "  najwiekszy element: " << najwiekszy_element << ", dla c0 = " << c0_najwiekszy << endl;
}

/**
 * @brief Funkcja glowna programu.
 *
 * Uruchamia testy, wypisuje przykladowy ciag dla c0 = 6,
 * a potem przeprowadza badanie dla c0 od 1 do 10000.
 *
 * @return 0 gdy program zakonczyl sie poprawnie
 */

int main() {
    test_collatz();

    long long c0 = 6;

    try {
        vector<long long> ciag = collatz(c0);

        cout << "ciąg dla c0 = " << c0 << ": ";
        for (long long element : ciag) {
            cout << element << " ";
        }
        cout << endl;

    } catch (const invalid_argument& e) {
        cout << "błąd: " << e.what() << endl;
    } catch (const overflow_error& e) {
        cout << "błąd: " << e.what() << endl;
    }

    badanie(10000);

    return 0;
}

