#ifndef LISTAWIAZANA_H_
#define LISTAWIAZANA_H_

struct lista
{
    struct lista *kolejny, *wczesniejszy;
    int liczba;
}elementListy;

void zawartosclisty();
void nowyElement(int liczba);
int dodawanie();
int odejmowanie();
int rozmiar();
void zawartosclistydlaKlienta(char *string);
void sortujWGore(char *string);
void sortujWDOL(char *string);

#endif
