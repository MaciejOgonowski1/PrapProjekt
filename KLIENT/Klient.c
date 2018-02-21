#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>




//127.0.0.1 8888
int main(int argc , char *argv[]) {
	puts("Klient PRST");
    char wiadomosc_serwer[200];
    char wiadomosc_klient[200];
    memset (wiadomosc_klient, 0, sizeof (wiadomosc_klient));
	struct sockaddr_in serwer_addr;
	int gniazdo_serwer;



    if (argc < 3) {
        puts("Podałeś zbyt mało argumentów");
        exit(1);
    }
	if((gniazdo_serwer = socket(AF_INET , SOCK_STREAM , 0))==-1)
	    {
	    	perror("Nie udało się utworzyć gniazda");
	    }
	    else{
	    	printf("Utworzono gniazdo\n");
	    }
	serwer_addr.sin_family = AF_INET;
	serwer_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serwer_addr.sin_port = htons(atoi(argv[2]));

    if (connect(gniazdo_serwer , (struct sockaddr *)&serwer_addr , (socklen_t)sizeof(serwer_addr)) < 0)
    {
        puts("Blad polaczenia");
        return 2;
    }
    puts("Polaczono");
    puts("Dostępne opcje to:");
    puts("1. Wpisz liczbę aby dodać ją do listy wiązanej");
    puts("2. DODAWANIE - liczby z listy");
    puts("3. ODEJMOWANIE - liczby z listy");
    puts("4. SORTUP - Sortowanie listy w górę");
    puts("5. SORTDOWN - Sortowanie listy w dół");
    puts("6. LISTA - wyświetli liczby dodane do listy");
    puts("6. DOSC - zakończenie działania klienta");
	for(int i=0;i<199;i++)
	{
		wiadomosc_serwer[i]=0;
	}



    while (1)
    {
		if( recv(gniazdo_serwer, wiadomosc_serwer , 200,  0) < 0)
			{
				puts("Blad odbioru danych");
			}
		puts("Dane odebrano\n");
		puts(wiadomosc_serwer);
		memset (wiadomosc_serwer, 0, sizeof(wiadomosc_serwer));
		gets(wiadomosc_klient);
		puts(wiadomosc_klient);
		if(!strcmp(wiadomosc_klient,"DOSC"))
		{
			close(gniazdo_serwer);
			return 3;
		}
		if( send(gniazdo_serwer , wiadomosc_klient , strlen(wiadomosc_klient) , 0) < 0)
		{
			puts("Błąd przy wysyłaniu danych");
			return 4;
		}
		else
		{
			puts("Dane zostały wysłane\n");
		}
    }

	return EXIT_SUCCESS;
}
