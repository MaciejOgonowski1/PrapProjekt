#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include "listawiazana.h"

//8888
int main(int argc , char *argv[]) {
	puts("Serwer PRST");
	int gniazdo_serwer, gnizdo_kolejne, rozmiargniazda2, flaga, cyfryzKlienta,wynik;
	struct sockaddr_in serwer_addr, klient_addr;
	pid_t pid;
	char wiadomosc_serwer[200];
    char wiadomosc_klient[200];



	if (argc != 2) {
        puts("Podałeś zbyt mało argumentów");
        exit(1);
    }
	if((gniazdo_serwer = socket(AF_INET , SOCK_STREAM , 0))==-1)
	    {
	    	perror("Nie udało się utworzyć gniazda");
	    	exit (2);
	    }
	serwer_addr.sin_family = AF_INET;
	serwer_addr.sin_addr.s_addr = INADDR_ANY;
	serwer_addr.sin_port = htons(atoi(argv[1]));

    if((bind(gniazdo_serwer,(struct sockaddr *)&serwer_addr ,(socklen_t)sizeof(serwer_addr))) == -1)
    {
    	perror("Problem z bindowaniem");
    	exit (3);
    }
    listen(gniazdo_serwer , 80);
    puts("Czekam na polaczenie...");
    rozmiargniazda2 = sizeof(struct sockaddr_in);
    while(1)
       {
    		gnizdo_kolejne = accept(gniazdo_serwer, (struct sockaddr *)&klient_addr, (socklen_t*)&rozmiargniazda2);
			if (gnizdo_kolejne<0)
			{
				perror("Błąd w utworzeniu połączenia");
				exit (4);
			}
			pid = fork();
			if(pid == -1)
			{
				perror ("Błąd przy tworzeniu procesu\n");
				exit (5);
			}
			else if(pid == 0)
			{
				puts("Połączenie aktywne");
				sprintf(wiadomosc_serwer,"Połączyłeś się z serwerem. Czekam na dane...\n");
				write(gnizdo_kolejne , wiadomosc_serwer , strlen(wiadomosc_serwer));
	    		for(int i=0;i<199;i++)
	    		{
	    			wiadomosc_serwer[i]=0;
	    		}
			    while(1)
			    {
			    	while(flaga =recv(gnizdo_kolejne, wiadomosc_klient , 200 , 0)>0)
						{
							if(flaga == 0)
							{
								close(gnizdo_kolejne);
								exit (6);
							}
							puts("SERWER: odebrałem dane");
							if((cyfryzKlienta = atoi(wiadomosc_klient)) != 0)
							{
								sprintf(wiadomosc_serwer, "%d\n",cyfryzKlienta);
								nowyElement(cyfryzKlienta);
								zawartosclisty();
								write(gnizdo_kolejne , wiadomosc_serwer , strlen(wiadomosc_serwer));
								for(int i=0;i<199;i++)
								{
									wiadomosc_klient[i]=0;
								}
							}
							else if(!strcmp(wiadomosc_klient,"DODAWANIE"))
							{
								wynik=dodawanie();
								printf("Wynikiem sumy jest %d\n",wynik);
								sprintf(wiadomosc_serwer, "Wynikiem dodawania jest %d\n",wynik);
								write(gnizdo_kolejne , wiadomosc_serwer , strlen(wiadomosc_serwer));
								for(int i=0;i<199;i++)
								{
									wiadomosc_klient[i]=0;
								}
							}
							else if(!strcmp(wiadomosc_klient,"ODEJMOWANIE"))
							{
								wynik=odejmowanie();
								printf("Wynikiem odejmowania jest %d\n",wynik);
								sprintf(wiadomosc_serwer, "Wynikiem odejmowania jest %d\n",wynik);
								write(gnizdo_kolejne , wiadomosc_serwer , strlen(wiadomosc_serwer));
								for(int i=0;i<199;i++)
								{
									wiadomosc_klient[i]=0;
								}
							}
							else if(!strcmp(wiadomosc_klient,"LISTA"))
							{
								sprintf(wiadomosc_serwer, "Lista to ");
								puts(wiadomosc_serwer);
								zawartosclistydlaKlienta(wiadomosc_serwer);
								puts(wiadomosc_serwer);
								write(gnizdo_kolejne , wiadomosc_serwer , strlen(wiadomosc_serwer));
								for(int i=0;i<199;i++)
								{
									wiadomosc_klient[i]=0;
								}
							}
							else if(!strcmp(wiadomosc_klient,"SORTUP"))
							{
								//sprintf(wiadomosc_serwer, "Lista przed sortowaniem ");
								//zawartosclistydlaKlienta(wiadomosc_serwer);
								//write(gnizdo_kolejne , wiadomosc_serwer , strlen(wiadomosc_serwer));
								sprintf(wiadomosc_serwer, "Lista posortowana to ");
								sortujWGore(wiadomosc_serwer);
								puts(wiadomosc_serwer);
								wait(2);
								write(gnizdo_kolejne , wiadomosc_serwer , strlen(wiadomosc_serwer));
								for(int i=0;i<199;i++)
								{
									wiadomosc_klient[i]=0;
								}
							}
							else if(!strcmp(wiadomosc_klient,"SORTDOWN"))
							{
								//sprintf(wiadomosc_serwer, "Lista przed sortowaniem ");
								//zawartosclistydlaKlienta(wiadomosc_serwer);
								//write(gnizdo_kolejne , wiadomosc_serwer , strlen(wiadomosc_serwer));
								sprintf(wiadomosc_serwer, "Lista posortowana to ");
								sortujWDOL(wiadomosc_serwer);
								puts(wiadomosc_serwer);
								wait(2);
								write(gnizdo_kolejne , wiadomosc_serwer , strlen(wiadomosc_serwer));
								for(int i=0;i<199;i++)
								{
									wiadomosc_klient[i]=0;
								}
							}
							else
							{
								puts("Błędnie wpisane dane");
								strcpy(wiadomosc_serwer,"Błędnie wpisane dane\n");
								write(gnizdo_kolejne , wiadomosc_serwer , strlen(wiadomosc_serwer));
								for(int i=0;i<199;i++)
								{
									wiadomosc_klient[i]=0;
								}
							}
						}
					for(int i=0;i<199;i++)
					{
						wiadomosc_serwer[i]=0;
					}
			    }

			}
			else
			{
				continue;
			}
       }

	return EXIT_SUCCESS;
}
