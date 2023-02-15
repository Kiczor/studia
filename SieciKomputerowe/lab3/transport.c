#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>
#include <errno.h>

#define min(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b;       \
})

const int SWS = 500;
const int dgramsize = 1000;
const long int INF = 4000000000;
struct timeval timeout;

int main(int argc, char *argv[])
{
    if( argc != 5 )
    {
        printf("zle uzycie programu\n");
        return 0;
    }

    /*ustawianie timeout*/
    timeout.tv_sec = 0; timeout.tv_usec = 100000;
    
    char* targetip = argv[1];
    int targetport = atoi( argv[2] );
    const char* outname = argv[3];
    int datasize = atoi( argv[4] );

    int state[SWS + 1]; //stan 0/1/2 niewyslane/wyslane niepotwierdzone/wyslane potwierdzone
    struct timeval sendtime[SWS + 1];
    char* recbuf[SWS + 1];

    for(int i = 0; i < SWS; i++)
    {
        state[i] = 0;
        sendtime[i].tv_sec = INF; sendtime[i].tv_usec = INF;
        recbuf[i] = NULL;
    }

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
    {
		fprintf(stderr, "socket error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
	}

    int filefd = open( outname, O_RDWR | O_CREAT );
    if( filefd < 0 )
    {
        fprintf(stderr, "file opening error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    fd_set descriptors;
    FD_ZERO(&descriptors);
    FD_SET(sockfd, &descriptors);

    struct sockaddr_in server_address;
	bzero (&server_address, sizeof(server_address));
	server_address.sin_family      = AF_INET;
	server_address.sin_port        = htons(targetport);
	inet_pton(AF_INET, targetip, &server_address.sin_addr);

    int winlastdgram = datasize / dgramsize;
    if( datasize % dgramsize ) winlastdgram += 1;

    int winbegin = 0, winend = 0; /*winbegin - poczatek okna, winend - kolejny po ostatnim w oknie*/
    while( winbegin * dgramsize < datasize )
    {
        /*poszerzanie okna i wysylanie pakietow*/
        while( winend - winbegin < SWS - 1 && winend < winlastdgram ) // && winend * dgramsize < datasize )
        {
            state[winend - winbegin] = 0;

            char message[25];
            sprintf(message, "GET %d %d\n", winend * dgramsize, min( dgramsize, datasize - winend * dgramsize ) );
            ssize_t message_len = strlen(message);

            gettimeofday( &sendtime[winend - winbegin], 0 );

            if (sendto(sockfd, message, message_len, 0, (struct sockaddr*) &server_address, sizeof(server_address)) != message_len)
            {
                fprintf(stderr, "sendto error: %s\n", strerror(errno)); 
                return EXIT_FAILURE;		
            }

            state[winend - winbegin] = 1;
            winend++;
        }

        /*odbieranie wszystkich ack*/
        struct sockaddr_in sender;	
		socklen_t sender_len = sizeof(sender);
        u_int8_t buffer[IP_MAXPACKET];

        struct timeval selecttimeout;
        selecttimeout.tv_sec = timeout.tv_sec; selecttimeout.tv_usec = timeout.tv_usec;
        int readyselect = select(sockfd + 1, &descriptors, NULL, NULL, &selecttimeout);
        if( readyselect < 0 )
        {
            fprintf(stderr, "select error: %s\n", strerror(errno));
            return EXIT_FAILURE;
        }

        while( recvfrom(sockfd, buffer, IP_MAXPACKET, MSG_DONTWAIT, (struct sockaddr*)&sender, &sender_len ) >= 0 ) //nie ma errora typu EWOULDBLOCK !!! MSG_DONTWAIT zamaist 0 moze
        {
            /*czy zgadza sie adres z ktorego przyszedl pakiet*/
            if( sender.sin_addr.s_addr != server_address.sin_addr.s_addr )
                continue;

            int it = 0;
            while( buffer[it] != '\n' ) /*\n = 10*/
                it ++;
            it ++; //\n tez sie nie liczy

            u_int8_t* udp_header = buffer;
            u_int8_t* udpdata = udp_header + it;

            char* startnum = malloc(10);
            int its = 5;
            while( buffer[its] != 32 ) /*32 - spacja*/
            {
                startnum[its - 5] = buffer[its];
                its ++;
            }
            //its ++; /*tu poczatek drugiego numeru*/
            startnum[its - 5] = 0;

            char* sizenum = malloc(10);
            int itsize = its;
            while( buffer[its] != 10 ) /*\n*/
            {
                sizenum[its - itsize] = buffer[its];
                its++;
            }
            sizenum[its - itsize] = 0;

            int dstart = atoi(startnum), dsize = atoi(sizenum);

            free(startnum);
            free(sizenum);

            /*czy jest to pakiet ktory mnie interesuje*/
            int x = dstart / dgramsize; //numer datagramowy
            if( winbegin > x || x > winend )
                continue;

            state[x - winbegin] = 2;

            /*wpisanie danych z pakietu*/
            size_t dlen = (size_t)dsize;
            recbuf[x - winbegin] = malloc( dlen );
            memcpy( recbuf[x - winbegin], udpdata, dlen );
        }

        /*sprawdzenie timeoutow i ewentualne wysylanie jeszcze raz*/
        for(int i = 0; i <= winend - winbegin; i++)
        {
            if( state[i] == 2 ) continue;

            struct timeval now; gettimeofday( &now, 0 );
            struct timeval diff; timersub( &now, &sendtime[i], &diff );
            if( timercmp( &diff, &timeout, > ) != 0 ) /*diff > timeout -> wyslanie jeszcze raz*/
            {
                char message[25];
                sprintf(message, "GET %d %d\n", (i + winbegin) * dgramsize, min( dgramsize, datasize - (i + winbegin) * dgramsize ));
                ssize_t message_len = strlen(message);

                gettimeofday( &sendtime[i], 0 );

                if (sendto(sockfd, message, message_len, 0, (struct sockaddr*) &server_address, sizeof(server_address)) != message_len)
                {
                    fprintf(stderr, "sendto error: %s\n", strerror(errno)); 
                    return EXIT_FAILURE;		
                }

                state[i] = 1;
            }
        }

        /*przesuniecie poczatku okna i zapisywanie do pliku otrzymanych danych*/
        int change = 0;
        while( state[change] == 2 )
        {
            int reswrite = write( filefd, recbuf[change], (winbegin + change == winlastdgram - 1 && datasize % dgramsize != 0) ? datasize % dgramsize : dgramsize ); /*zapisywanie do pliku*/
            if( reswrite < 0 )
            {
                printf("write error:%s\n", strerror(errno));
                return EXIT_FAILURE;
            }
            free(recbuf[change]);

            change ++;
        }

        /*poprawienie tablic*/
        for(int i = 0; i < SWS; i++)
        {
            if( i + change < SWS )
            {
                state[i] = state[i + change];
                sendtime[i] = sendtime[i + change];
                recbuf[i] = recbuf[i + change];
            }
            else
            {
                state[i] = 0;
                sendtime[i].tv_sec = INF; sendtime[i].tv_usec = INF;
                recbuf[i] = NULL;
            }
        }

        winbegin += change;
    
        printf("%.2lf procent\n", 100.0 * (double)(winbegin * dgramsize) / (double)datasize);
    }

    close(sockfd);
    close(filefd);
}