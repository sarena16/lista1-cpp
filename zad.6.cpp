//
// Created by Sara Niedzielska on 16/11/2026.
// Kod został napisany samodzielnie z wykorzystaniem źródeł, ktore są podane niżej
//
// Źródła:
// - Transkrypcja, nić matrycowa i kodująca, komplementarność zasad:
//   https://zpe.gov.pl/a/ekspresja-informacji-genetycznej/D9HKLZ58J
// - Podstawy składni C++ (typy danych, pętle, funkcje) z kursu AGH:
//   https://www.galaxy.agh.edu.pl/~pamalino/programowanie/cpp/index.php
// - Odwracanie sekwencji funkcją reverse:
//   https://www.fi.muni.cz/~xvaclav/cppreference/en/cpp/algorithm/reverse.html
// - Co to są warunki początkowe (preconditions) z learncpp:
//   https://www.learncpp.com/cpp-tutorial/assert-and-static_assert/
// - Jak pisać testy z assert i jak testować wyjątki:
//   https://uwf-fang.github.io/teaching/cpp/testing/testing/
//   https://stackoverflow.com/questions/15668309/c-assertion-function-to-check-that-exception-is-thrown
// - Format komentarzy dokumentacyjnych z dokumentacji Doxygen:
//   https://www.doxygen.nl/manual/docblocks.html
// - Claude Opus 5.5 (claude.ai): wyjaśnienia, komentarze dokumentacyjne,
//   pomoc przy funkcjach komplement i transkrybuj, testach

#include <iostream>   // żeby móc coś wypisać na ekran (cout)
#include <stdexcept>  // żeby móc rzucać wyjątki (invalid_argument)
#include <cassert>    // żeby móc pisać testy (assert)
#include <string>     // żeby móc używać string (sekwencje DNA i RNA)
#include <algorithm>  // żeby mieć reverse (odwracanie sekwencji)

using namespace std;

/**
 * @brief Zwraca nic matrycowa DNA dla zadanej nici kodujacej.
 *
 * Kazda zasade zamienia na komplementarna (A <-> T, C <-> G), a potem
 * odwraca kolejnosc, bo nici biegna w przeciwnych kierunkach.
 * Obie nici sa zapisywane w kierunku 5' -> 3'.
 * Przyklad: ATGGCC -> GGCCAT.
 *
 * @param kodujaca sekwencja nici kodujacej DNA (5' -> 3'), tylko wielkie litery A, C, G, T
 * @return sekwencja nici matrycowej DNA (5' -> 3')
 * @throws std::invalid_argument gdy sekwencja jest pusta
 * @throws std::invalid_argument gdy sekwencja zawiera znak inny niz A, C, G, T
 */
string komplement(string kodujaca) {

    // najpierw sprawdzam, czy sekwencja ma sens (warunki początkowe)
    if (kodujaca.empty()) {
        throw invalid_argument("sekwencja DNA nie moze byc pusta");
    }

    string wynik = "";                          // tu będę zbierać komplementarne zasady

    for (char zasada : kodujaca) {              // biorę po kolei każdą literę
        if (zasada == 'A') {
            wynik += 'T';                       // A łączy się z T
        } else if (zasada == 'T') {
            wynik += 'A';                       // T łączy się z A
        } else if (zasada == 'C') {
            wynik += 'G';                       // C łączy się z G
        } else if (zasada == 'G') {
            wynik += 'C';                       // G łączy się z C
        } else {
            // każda inna litera (np. U, X, małe litery) to nie jest poprawne DNA
            throw invalid_argument("niepoprawna zasada w DNA - dozwolone tylko A, C, G, T");
        }
    }

    reverse(wynik.begin(), wynik.end());        // odwracam kolejność (nici biegną w przeciwnych kierunkach)
    return wynik;                               // oddaję nić matrycową
}

/**
 * @brief Zwraca sekwencje RNA powstala w transkrypcji zadanej nici matrycowej DNA.
 *
 * Kazda zasade matrycy zamienia na komplementarna zasade RNA
 * (A -> U, T -> A, C -> G, G -> C), a potem odwraca kolejnosc.
 * Otrzymane RNA ma te sama kolejnosc zasad co nic kodujaca, tylko z U zamiast T.
 * Przyklad: GGCCAT -> AUGGCC.
 *
 * @param matrycowa sekwencja nici matrycowej DNA (5' -> 3'), tylko wielkie litery A, C, G, T
 * @return sekwencja RNA (5' -> 3'), zlozona z liter A, C, G, U
 * @throws std::invalid_argument gdy sekwencja jest pusta
 * @throws std::invalid_argument gdy sekwencja zawiera znak inny niz A, C, G, T
 */
string transkrybuj(string matrycowa) {

    // najpierw sprawdzam, czy sekwencja ma sens (warunki początkowe)
    if (matrycowa.empty()) {
        throw invalid_argument("sekwencja DNA nie moze byc pusta");
    }

    string wynik = "";                          // tu będę zbierać zasady RNA

    for (char zasada : matrycowa) {             // biorę po kolei każdą literę matrycy
        if (zasada == 'A') {
            wynik += 'U';                       // w RNA naprzeciw A stoi U (a nie T)
        } else if (zasada == 'T') {
            wynik += 'A';
        } else if (zasada == 'C') {
            wynik += 'G';
        } else if (zasada == 'G') {
            wynik += 'C';
        } else {
            // matryca to DNA, więc dozwolone są tylko A, C, G, T (U też jest błędem)
            throw invalid_argument("niepoprawna zasada w DNA - dozwolone tylko A, C, G, T");
        }
    }

    reverse(wynik.begin(), wynik.end());        // odwracam kolejność, tak jak przy komplemencie
    return wynik;                               // oddaję RNA
}

// testy

/**
 * @brief Testy funkcji komplement i transkrybuj.
 *
 * Sprawdza przypadki typowe (znane sekwencje), przypadki brzegowe
 * (jedna litera, same takie same litery), wlasnosci obu funkcji
 * (podwojny komplement, polaczenie komplement + transkrybuj),
 * poprawnosc danych wyjsciowych (brak litery T w RNA)
 * oraz wyjatki dla pustej sekwencji i niepoprawnych liter (X, male litery, U w DNA).
 * Jesli wszystko przejdzie, wypisuje "testy przeszly".
 */
void test_dna() {

    // komplement: przypadki typowe (znany wynik)
    assert(komplement("ATGC") == "GCAT");               // zamiana: TACG, po odwróceniu: GCAT
    assert(komplement("ATGCCG") == "CGGCAT");           // zamiana: TACGGC, po odwróceniu: CGGCAT
    assert(komplement("ATGGCC") == "GGCCAT");           // mój dodatkowy przykład

    // komplement: przypadki brzegowe
    assert(komplement("A") == "T");                     // jedna litera
    assert(komplement("AAAA") == "TTTT");               // same takie same litery

    // komplement komplementu wraca do wyjściowej sekwencji
    assert(komplement(komplement("ATGCCG")) == "ATGCCG");

    // transkrybuj: przypadki typowe (znany wynik)
    assert(transkrybuj("GCAT") == "AUGC");
    assert(transkrybuj("CGGCAT") == "AUGCCG");
    assert(transkrybuj("CAT") == "AUG");                // mój dodatkowy przykład: kodon start AUG

    // transkrybuj: przypadek brzegowy
    assert(transkrybuj("T") == "A");                    // jedna litera

    // obie funkcje razem: kodująca → matryca → RNA daje kodującą z U zamiast T
    assert(transkrybuj(komplement("ATGCCG")) == "AUGCCG");

    // poprawność danych wyjściowych: w RNA nie może być litery T
    // find zwraca string::npos, gdy niczego nie znalazł
    assert(transkrybuj("CGGCAT").find('T') == string::npos);

    // wyjątki: pusta sekwencja → invalid_argument
    bool byl_wyjatek = false;           // flaga: na start zakładam, że wyjątku nie było
    try {
        komplement("");
    } catch (const invalid_argument& e) {
        byl_wyjatek = true;             // był błąd → zmieniam na true
    }
    assert(byl_wyjatek);                // sprawdzam, czy funkcja zgłosiła błąd

    byl_wyjatek = false;                // zeruję przed kolejnym testem
    try {
        transkrybuj("");
    } catch (const invalid_argument& e) {
        byl_wyjatek = true;
    }
    assert(byl_wyjatek);

    // wyjątki: niepoprawna litera w DNA
    byl_wyjatek = false;
    try {
        komplement("ATXG");             // X to nie jest zasada
    } catch (const invalid_argument& e) {
        byl_wyjatek = true;
    }
    assert(byl_wyjatek);

    byl_wyjatek = false;
    try {
        komplement("atgc");             // małe litery traktuję jako błąd
    } catch (const invalid_argument& e) {
        byl_wyjatek = true;
    }
    assert(byl_wyjatek);

    // wyjątki: U w DNA (U występuje tylko w RNA)
    byl_wyjatek = false;
    try {
        komplement("AUGC");
    } catch (const invalid_argument& e) {
        byl_wyjatek = true;
    }
    assert(byl_wyjatek);

    byl_wyjatek = false;
    try {
        transkrybuj("GCAU");
    } catch (const invalid_argument& e) {
        byl_wyjatek = true;
    }
    assert(byl_wyjatek);

    cout << "testy przeszly" << endl;   // jak doszło tutaj, wszystkie testy przeszły
}
/**
 * @brief Funkcja glowna programu.
 *
 * Uruchamia testy, a potem dla przykladowej nici kodujacej
 * wypisuje nic matrycowa i powstale z niej RNA.
 *
 * @return 0 gdy program zakonczyl sie poprawnie
 */
int main() {
    test_dna();                                         // najpierw odpalam testy

    string kodujaca = "ATGGCCTTA";                      // przykładowa nić kodująca ustalona w kodzie

    try {                                               // funkcje mogą rzucić wyjątek (złe litery)
        string matrycowa = komplement(kodujaca);
        string rna = transkrybuj(matrycowa);

        cout << "nic kodujaca:  " << kodujaca << endl;
        cout << "nic matrycowa: " << matrycowa << endl;
        cout << "RNA:           " << rna << endl;

    } catch (const invalid_argument& e) {
        cout << "blad: " << e.what() << endl;
    }

    return 0;
}