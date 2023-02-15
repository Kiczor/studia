#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdlib.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>

u_int16_t compute_icmp_checksum (const void *buff, int length)
{
	u_int32_t sum;
	const u_int16_t* ptr = buff;
	assert (length % 2 == 0);
	for (sum = 0; length > 0; length -= 2)
		sum += *ptr++;
	sum = (sum >> 16) + (sum & 0xffff);
	return (u_int16_t)(~(sum + (sum >> 16)));
}

void printheader( struct icmp* h )
{
    printf("header:\ntype: %d\ncode: %d\nid: %d\nseq: %d\ncksum: %d\nend\n\n", h->icmp_type, h->icmp_code, h->icmp_hun.ih_idseq.icd_id, h->icmp_hun.ih_idseq.icd_seq, h->icmp_cksum);
}

int cnt = 0;
void constructheader(struct icmp* header)
{
    header -> icmp_type = ICMP_ECHO;
    header -> icmp_code = 0;
    header -> icmp_hun.ih_idseq.icd_id = (u_int16_t)getpid();
    header -> icmp_hun.ih_idseq.icd_seq = ++cnt;
    header -> icmp_cksum = 0;
    header -> icmp_cksum = compute_icmp_checksum(header, sizeof(*header));
}

int equalheaders( struct icmp* h1, struct icmp* h2 ) /*sprawdzanie czy dwa headery sa rowne*/
{
    if( h1 -> icmp_type != h2 -> icmp_type ) return 0;
    if( h1 -> icmp_hun.ih_idseq.icd_id != h2 -> icmp_hun.ih_idseq.icd_id ) return 0;
    if( h1 -> icmp_hun.ih_idseq.icd_seq != h2 -> icmp_hun.ih_idseq.icd_seq ) return 0;
    if( h1 -> icmp_cksum != h2 -> icmp_cksum ) return 0;
    return 1;
}

/*sprawdzanie czy dany ciag jest poprawnym adresem ip*/
int isipaddress(char* s)
{
    int lens = (int)strlen(s);
    for(int i = 0; i < lens; i++)
        if( s[i] != '.' && s[i] - '0' > 9 )
            return 0;

    char k[5][4];
    
    int it = 0;
    int itk = 0;
    while( itk < 4 && it < lens )
    {
        int itink = 0;
        while( ( it < lens && s[it] != '.' ) && itink <= 3 )
        {
            k[itk][itink] = s[it];
            itink++;
            it ++;
        }
        it ++;
        itk ++;
    }
    
    if(itk != 4)
        return 0;

    for(int i = 0; i < itk; i++)
        if( atoi( k[i] ) > 255 )
            return 0;
    return 1;
}

int main(int argc, char *argv[])
{
    if(argc != 2 || isipaddress(argv[1]) != 1)
    {
        printf("zly argument (nie jest to ip)!\n");
        return 0;
    }

    char* targetip = argv[1];

    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0)
    {
		fprintf(stderr, "socket error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
	}

    for(int ttl = 1; ttl <= 30; ttl++)
    {
        printf("%d. ", ttl);

        /*ustawianie ttl dla pakietu*/
        setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int));

        /*czas w ktorym zostal wyslany poszczegolny pakiet*/
        struct timeval timesend[4];
        
        /*naglowki wyslanych pakietow*/
        struct icmp headerssent[4];

        /*wysylanie 3 razy pakietow*/
        for(int c = 0; c < 3; c++)
        {
            /*konstrukcja naglowka ICMP*/
            struct icmp header;
            constructheader(&header);
            headerssent[c] = header;

            /*ustawianie odbiorcy*/
            struct sockaddr_in recipient;
            bzero (&recipient, sizeof(recipient));
            recipient.sin_family = AF_INET;
            inet_pton(AF_INET, targetip, &recipient.sin_addr);

            sendto( sockfd, &header, sizeof(header), 0, (struct sockaddr*)&recipient, sizeof(recipient) );
            gettimeofday(&timesend[c], 0);
        }

        fd_set descriptors;
        FD_ZERO(&descriptors);
        FD_SET(sockfd, &descriptors);

        /*timeleft - pozostaly czas czekania, timestart - moment rozpoczecia oczekiwania na pakiety, avgtime - sredni czas oczekiwania na otrzymane pakiety*/
        struct timeval timeleft, timestart, avgtime;
        timeleft.tv_sec = 0; timeleft.tv_usec = 1000000;
        avgtime.tv_sec = 0; avgtime.tv_usec = 0;
        gettimeofday(&timestart, 0);

        int received = 0; /*ile pakietow wrocilo*/
        int finished = 0; /*jezeli juz docelowe IP osiagniete to finished=1*/
        char* toprint[4];
        while( received < 3 && timeleft.tv_usec > 0 )
        {
            int ready = select(sockfd + 1, &descriptors, NULL, NULL, &timeleft);

            /*otrzymywanie pakietow*/
            if( ready > 0 )
            {
                for(int i = 0; i < ready; i++)
                {
                    struct sockaddr_in   sender;
                    socklen_t            sender_len = sizeof(sender);
                    u_int8_t             buffer[IP_MAXPACKET];

                    ssize_t packet_len = recvfrom(sockfd, buffer, IP_MAXPACKET, 0, (struct sockaddr*)&sender, &sender_len);
                    if (packet_len < 0)
                    {
                        fprintf(stderr, "recvfrom error: %s\n", strerror(errno)); 
                        return EXIT_FAILURE;
                    }

                    struct timeval timerec, diff;
                    gettimeofday(&timerec, 0);
                    timersub(&timerec, &timestart, &diff); // difference = receive time - start time
                    timersub(&timeleft, &diff, &timeleft); // left time -= difference

                    char ip_str[20];
                    inet_ntop(AF_INET, &(sender.sin_addr), ip_str, sizeof(ip_str));

                    /*sprawdzanie czy to jest odpowiedz na moje requesty*/
                    struct ip* ip_header = (struct ip*) buffer;
                    u_int8_t* icmp_packet = buffer + ip_header -> ip_hl * 4;
                    struct icmp* icmp_header = (struct icmp*)icmp_packet;

                    u_int8_t* p = (void*)icmp_packet + 8;
                    struct ip* responseipheader = (struct ip*)p;
                    u_int8_t* icmpresponsepacket = p + responseipheader -> ip_hl * 4;
                    struct icmp* icmpresponseheader = (struct icmp*)icmpresponsepacket;

                    int actual = 0;

                    if( icmp_header -> icmp_type != ICMP_ECHOREPLY && icmp_header -> icmp_type != ICMP_TIME_EXCEEDED ) /*przyszedł pakiet który nie jest ani echo reply ani time exceeded*/
                        continue;
                    
                    /*sprawdzanie czy nadszedl jeden z pakietow wyslanych przy obecnym ttl*/
                    for(int c = 0; c < 3; c++)
                    {
                        if( equalheaders(icmpresponseheader, &headerssent[c]) )
                            actual = 1;
                        if( icmp_header -> icmp_type == ICMP_ECHOREPLY && icmp_header -> icmp_hun.ih_idseq.icd_id == headerssent[c].icmp_hun.ih_idseq.icd_id )
                        {
                            finished = 1;
                            actual = 1;
                        }
                    }
                        
                    if( actual ) /*jeden z pakietow wyslanych przy obecnym ttl*/
                    {
                        received ++;

                        struct timeval tmp;
                        timersub(&timerec, &timesend[(icmpresponseheader -> icmp_seq) % 3], &tmp);
                        timeradd(&avgtime, &tmp, &avgtime);

                        toprint[received - 1] = ip_str;
                    }
                }
            }
            else
            {
                break;
            }
        }

        /*wypisanie adresu/adresow ip*/
        for(int i = 0; i < received; i++)
            if(i + 1 >= received || strcmp(toprint[i], toprint[i + 1] ) != 0 )
                printf("%s ", toprint[i]);

        if( received == 3 )
        {
            printf("%ldms", avgtime.tv_usec / 3000);
        }
        if( received > 0 && received < 3 )
        {
            printf("???");
        }
        if( received == 0 )
        {
            timeleft.tv_usec = 0;
            printf("*");
        }
        printf("\n");
        if( finished )
            break;
    }
}
