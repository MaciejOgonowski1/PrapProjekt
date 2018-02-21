#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lista
{
       struct lista *kolejny;
       int liczba;
}elementListy;

struct lista *ele1 = NULL;
struct lista *eleOst  = NULL;

void zawartosclisty()
{
     struct lista *lista=ele1;
     int flaga=rozmiar();
     printf("Zawartosc listy: ");
     for(int i=0;i<flaga;i++)
     {
    	 printf("%d ",lista->liczba);
    	 lista=lista->kolejny;
     }
     printf("\n");
     return;
}

void zawartosclistydlaKlienta(char *string)
{
    struct lista *lista=ele1;
    char flaga[9];
    int powtorzenie=rozmiar();
    for(int i=0;i<powtorzenie;i++)
    {
		sprintf(flaga, "%d ",lista->liczba);
		strcat(string,flaga);
		lista = lista -> kolejny;
	}
}


void nowyElement(int nowyelement)
{
	if(ele1==NULL)
	{
		ele1= malloc (sizeof(elementListy));
		eleOst=ele1;
		ele1->liczba=nowyelement;
		ele1->kolejny=NULL;
	}
	else
	{
        struct lista *nowy;
        nowy=malloc(sizeof(elementListy));
        nowy->liczba=nowyelement;
        nowy->kolejny=NULL;
        eleOst->kolejny=nowy;
        eleOst=nowy;
	}
}

int dodawanie()
{
	int wynik;
    struct lista *lista=ele1;
    int i;
    int wielkosc=rozmiar();
    for(i=0;i<wielkosc;i++)
    {
    	wynik=wynik+lista->liczba;
    	lista=lista->kolejny;
    }
	return wynik;
}

int odejmowanie()
{
	int wynik;
    struct lista *lista=ele1;

    int flaga=1;
    wynik=lista->liczba;
    lista=lista->kolejny;
	if(lista==NULL)
	{
    	flaga=0;
	}
    while(flaga)
    {
		wynik=wynik-lista->liczba;
		lista=lista->kolejny;
		if(lista==NULL)
		{
        	flaga=0;
    	}
    }

	return wynik;
}


int rozmiar()
{
	int rozmiar=0;
    struct lista *lista   = ele1;
	while(lista!=NULL)
	{
		rozmiar++;
		lista = lista->kolejny;
	}
	return rozmiar;
}


void sortujWGore(char *string)
{
    struct lista *lista1=ele1;
    struct lista *lista2=ele1;
    int i,j, flaga;
    int wielkosc=rozmiar();
    int tab[wielkosc];
    for(i=0;i<wielkosc;i++)
    {
    	tab[i]=lista1->liczba;
    	//printf("tab i=%d = %d\n",i,tab[i]);
    	lista1=lista1->kolejny;
    }
    /*
    for(i=0;i<wielkosc;i++)
    {
    	printf("%d ",tab[i]);
    }
    printf("\n");*/
    int h=0;

    for(j=0;j<wielkosc-1;j++)
    {
    	for(i=h;i<wielkosc-1;i++)
    	{
    		//printf("Porownuje %d>%d i=%d j=%d\n",tab[j], tab[i+1],i,j);
    		if(tab[j]<tab[i+1])
    		{
    			flaga=tab[j];
    			tab[j]=tab[i+1];
    			tab[i+1]=flaga;
    		}
    	}
    	h++;
    }
    /*
    for(i=0;i<wielkosc;i++)
    {
    	printf("%d ",tab[i]);
    }
    printf("\n");
    */
    char flagaznaku[9];

    for(i=0;i<wielkosc;i++)
    {
    //printf("Iteracja %d\n", i);
    sprintf(flagaznaku, "%d ",tab[i]);
    strcat(string,flagaznaku);
    }
    //printf("\n");

}


void sortujWDOL(char *string)
{
    struct lista *lista1=ele1;
    struct lista *lista2=ele1;
    int i,j, flaga;
    int wielkosc=rozmiar();
    int tab[wielkosc];
    for(i=0;i<wielkosc;i++)
    {
    	tab[i]=lista1->liczba;
    	lista1=lista1->kolejny;
    }

    int h=0;

    for(j=0;j<wielkosc-1;j++)
    {
    	for(i=h;i<wielkosc-1;i++)
    	{
    		if(tab[j]>tab[i+1])
    		{
    			flaga=tab[j];
    			tab[j]=tab[i+1];
    			tab[i+1]=flaga;
    		}
    	}
    	h++;
    }
    /*
    for(i=0;i<wielkosc;i++)
    {
    	printf("%d ",tab[i]);
    }
    printf("\n");
    */
    char flagaznaku[9];

    for(i=0;i<wielkosc;i++)
    {
    sprintf(flagaznaku, "%d ",tab[i]);
    strcat(string,flagaznaku);
    }

}



