//
// Created by Sara Niedzielska on 12/11/2026.
// Kod został napisany samodzielnie z wykorzystaniem źródeł, ktore są podane niżej
//
// Źródła:
// - Wzór Herona wzięłam z Wikipedii:
//   https://pl.wikipedia.org/wiki/Wzór_Herona
// - Podstawy składni C++ (typy, if, funkcje) z kursu AGH:
//   https://www.galaxy.agh.edu.pl/~pamalino/programowanie/cpp/index.php
// - Co to są warunki początkowe (preconditions) z learncpp:
//   https://www.learncpp.com/cpp-tutorial/assert-and-static_assert/
// - Jak pisać testy z assert i jak testować wyjątki:
//   https://uwf-fang.github.io/teaching/cpp/testing/testing/
//   https://stackoverflow.com/questions/15668309/c-assertion-function-to-check-that-exception-is-thrown
// - Format komentarzy dokumentacyjnych z dokumentacji Doxygen:
//   https://www.doxygen.nl/manual/docblocks.html
// - Claude Opus 5.5 (claude.ai): wyjaśnienia składni i niejasności, komentarze
//   dokumentacyjne, sprawdzanie w main, czy wpisano liczby (cin.fail)
//

#include <iostream>   // żeby móc coś wypisać na ekran (cout)
#include <cmath>      // żeby mieć pierwiastek (sqrt) i wartość bezwzgl. (fabs)
#include <stdexcept>  // żeby móc rzucać wyjątki (invalid_argument)
#include <cassert>    // żeby móc pisać testy (assert)

using namespace std;

// Wzór Herona:
// p = (a + b + c) / 2
// S = √( p · (p − a) · (p − b) · (p − c) )

/**
 * @brief Oblicza pole trojkata o bokach a, b, c ze wzoru Herona.
 *
 * Najpierw sprawdza, czy boki sa dodatnie i czy spelniaja nierownosc trojkata.
 * Jesli dane sa poprawne, liczy polowe obwodu p i pole S = sqrt(p(p-a)(p-b)(p-c)).
 *
 * @param a dlugosc pierwszego boku
 * @param b dlugosc drugiego boku
 * @param c dlugosc trzeciego boku
 * @return pole trojkata
 * @throws invalid_argument gdy ktorys bok jest <= 0
 * @throws invalid_argument gdy trojkat o takich bokach nie istnieje
 * @see https://pl.wikipedia.org/wiki/Wzór_Herona
 */
// claude wygenerował te komntarze dokumentacyjne

double heron(double a, double b, double c) {   // funkcja heron: dostaje 3 boki trójkąta i oddaje jego pole

    // najpierw sprawdzam, czy boki mają sens
    // jak choć jeden bok jest 0 albo ujemny -> błąd (|| to "lub")
    if (a <= 0 || b <= 0 || c <= 0) {
        throw invalid_argument("boki musza byc dodatnie");   //throw = wyskakuje błąd i funkcja sie konczy i nie liczy dalej
    }

    // nierówność trójkąta: suma dwóch boków musi być większa od trzeciego
    // jak dla którejś pary tak nie jest, to trójkąta nie da się zbudować
    if (a + b <= c || a + c <= b  || b + c <= a ) {
        throw invalid_argument("trojkat o takich bokach nie istnieje");
    }

    // jeśli funkcja doszła do tego miejsca, to dane są poprawne i można liczyć pole
    double p = (a + b + c) / 2;                          // połowa obwodu
    double S = sqrt(p * (p - a) * (p - b) * (p - c));    // wzór Herona
    return S;                                            // zwracamy pole
}



// testy

/**
 * @brief Testuje funkcję heron na przypadkach typowych i brzegowych.
 */

void test_heron() {

    // te mają dobre boki i trójkąt istnieje
    assert(fabs(heron(3, 4, 5) - 6) < 1e-9);    // trójkąt 3-4-5 ma pole 6
    assert(fabs(heron(5, 5, 8) - 12) < 1e-9);   // trójkąt 5-5-8 ma pole 12

    // test: 1 + 2 < 10 → nierownosc trojkata nie jest spelniona → wyjatek
    bool byl_wyjatek = false;     // flaga: na start zakładam, że wyjątku nie było
    try {
        heron(1, 2, 10);   // próbuje policzyć pole dla złych boków
    } catch (const invalid_argument& e) {
        byl_wyjatek = true;       // // był błąd → zmieniam na true
    }
    assert(byl_wyjatek);

    // test: bok ujemny (-1) → wyjatek (lapie to pierwszy if)
    byl_wyjatek = false;       // zeruję przed kolejnym testem, żeby nie zostało true z poprzedniego (bez bool juz musi byc bo nie mozna go powtorzyc)
    try {
        heron(-1, 4, 5);  // próbuję policzyć pole z ujemnym bokiem
    } catch (const invalid_argument& e) {
        byl_wyjatek = true;      // wyjątek był → zmieniam flagę na true
    }
    assert(byl_wyjatek);        // sprawdzam czy funkcja zgłosiła blad

    cout << "testy przeszły " << endl;
}




// int main() {
//     test_heron();
//
//     double a = 3, b = 4, c = 5;               // boki ustalone od razu w kodzie
//
//     try {                                     // try = "spróbuj" - robię coś, co może się nie udać (heron może rzucić błąd)
//         double S = heron(a, b, c);            // liczę pole dla moich boków
//         cout << "Pole = " << S << endl;       // wypisuję wynik (endl = nowa linia)
//
//     } catch (const invalid_argument& e) {     // catch = "złap" - jak heron zrobi throw, program przeskakuje tutaj
//         cout << "Blad: " << e.what() << endl; // e to złapany błąd, a e.what() to tekst, który wpisałam w throw
//     }
//     return 0;
// }

int main() {
    test_heron();

    double a, b, c;
    cout << "podaj boki a, b, c (oddzielone spacjami): ";
    cin >> a >> b >> c;                       // wczytuję boki ktore ustalamy w terminalu

    if (cin.fail()) {                         // cin.fail() = "wczytywanie się nie udało"
        cout << "błąd: trzeba podac trzy liczby oddzielone spacjami" << endl;
        return 1;                             // 1 = program skończył się z błędem
    }

    try {
        double S = heron(a, b, c);
        cout << "pole = " << S << endl;
    } catch (const invalid_argument& e) {
        cout << "błąd: " << e.what() << endl;
    }
    return 0;
}




