#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include<arpa/inet.h>

int port;
int i;
int main (int argc, char *argv[])
{
    printf("\033[1;36m");
    int nr=0;
    int vec[256],dim,linkk;
    char matrice[256][256],matrixx[256][256];
    char msg1[256],msg2[256],msg3[256],msg4[256],msg5[256],msg6[256];
    char raspuns[256],melodie[256],gen[256],votes[256],link[256],descriere[256],comment[256];

    struct sockaddr_in server;
    port = atoi (argv[2]);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_port = htons (port);

    int sd;
    sd = socket (AF_INET, SOCK_STREAM, 0);

    connect (sd, (struct sockaddr *) &server,sizeof (struct sockaddr));

    bzero(&msg1,sizeof(msg1));
    bzero(&msg2,sizeof(msg2));
    bzero(&msg3,sizeof(msg3));

    printf("Username: ");
    fflush(stdout);
    read(0,msg1,sizeof(msg1));

    printf("Password: ");
    fflush(stdout);
    read(0,msg2,sizeof(msg2));

    printf("Type: ");
    fflush(stdout);
    read(0,msg3,sizeof(msg3));

    msg1[strlen(msg1)-1]='\0';
    msg2[strlen(msg2)-1]='\0';
    msg3[strlen(msg3)-1]='\0';
    write(sd,msg1,sizeof(msg1));
    write(sd,msg2,sizeof(msg2));
    write(sd,msg3,sizeof(msg3));

    read(sd,raspuns,sizeof(raspuns));
    if(strcmp(raspuns,"Successful log in")==0)
    {
        printf("\033[0m");
        printf("1: Add song\n");
        printf("2: Vote song\n");
        printf("3: See general top\n");
        printf("4: See a specific top\n");
        printf("5: Add comment to a song\n");
        printf("6: See comments of a song\n");
        printf("7: Delete a song(admin only)\n");
        printf("8: Restrict a user from voting(admin only)\n");
        printf("9: Songs and the links attached to them(sends you to the browser\n");
        while(1)
        {
            bzero(&msg4,sizeof(msg4));
            bzero(&msg5,sizeof(msg5));
            bzero(&msg6,sizeof(msg6));
            bzero(&gen,sizeof(gen));
            bzero(&melodie,sizeof(melodie));
            bzero(&votes,sizeof(votes));
            bzero(&link,sizeof(link));
            bzero(&descriere,sizeof(descriere));
            bzero(&dim,sizeof(dim));
            bzero(&matrice,sizeof(matrice));
            bzero(&vec,sizeof(vec));
            bzero(&comment,sizeof(comment));
            bzero(&raspuns,sizeof(raspuns));

            printf("\033[01;33m");

            printf("Option: ");
            fflush(stdout);
            read(0,msg4,sizeof(msg4));
            msg4[strlen(msg4)-1]='\0';

            if(strcmp(msg4,"1")==0)
            {
                printf("Song: ");
                fflush(stdout);
                read(0,melodie,sizeof(melodie));
                melodie[strlen(melodie)-1]='\0';
                printf("Genre: ");
                fflush(stdout);
                read(0,gen,sizeof(gen));
                gen[strlen(gen)-1]='\0';
                printf("Votes: ");
                fflush(stdout);
                read(0,votes,sizeof(votes));
                votes[strlen(votes)-1]='\0';
                printf("Link: ");
                fflush(stdout);
                read(0,link,sizeof(link));
                link[strlen(link)-1]='\0';
                printf("Description: ");
                fflush(stdout);
                read(0,descriere,sizeof(descriere));
                descriere[strlen(descriere)-1]='\0';

                write(sd,msg4,sizeof(msg4));
                write(sd,melodie,sizeof(melodie));
                write(sd,gen,sizeof(gen));
                write(sd,votes,sizeof(votes));
                write(sd,link,sizeof(link));
                write(sd,descriere,sizeof(descriere));


                read(sd,msg5,sizeof(msg5));
                printf("%s\n",msg5);
            }
            else if(strcmp(msg4,"2")==0)
            {
                printf("Melodie: ");
                fflush(stdout);
                read(0,melodie,sizeof(melodie));
                melodie[strlen(melodie)-1]='\0';
                printf("Votes: ");
                fflush(stdout);
                read(0,gen,sizeof(gen));
                gen[strlen(gen)-1]='\0';

                write(sd,msg4,sizeof(msg4));
                write(sd,melodie,sizeof(melodie));
                write(sd,gen,sizeof(gen));

                read(sd,msg5,sizeof(msg5));
                printf("%s\n",msg5);
            }
            else if(strcmp(msg4,"3")==0)
            {
                printf("------General Music Top------\n");
                write(sd,msg4,sizeof(msg4));
                read(sd,&dim,sizeof(dim));
                read(sd,matrice,sizeof(matrice));
                read(sd,vec,sizeof(vec));
                for(i=1; i<=dim; i++)
                    printf("Song: %s,  Votes: %d\n",matrice[i],vec[i]);
            }
            else if(strcmp(msg4,"4")==0)
            {
                printf("Genre: ");
                fflush(stdout);

                read(0,gen,sizeof(gen));
                gen[strlen(gen)-1]='\0';
                write(sd,msg4,sizeof(msg4));
                write(sd,gen,sizeof(gen));
                read(sd,&dim,sizeof(dim));
                read(sd,matrice,sizeof(matrice));
                read(sd,vec,sizeof(vec));

                printf("------%s Music Top------\n",gen);
                for(i=1; i<=dim; i++)
                    printf("Song: %s, Votes: %d\n",matrice[i],vec[i]);
            }
            else if(strcmp(msg4,"5")==0)
            {
                printf("Song: ");
                fflush(stdout);
                read(0,melodie,sizeof(melodie));
                melodie[strlen(melodie)-1]='\0';

                printf("Comment: ");
                fflush(stdout);
                read(0,comment,sizeof(comment));
                comment[strlen(comment)-1]='\0';

                write(sd,msg4,sizeof(msg4));
                write(sd,melodie,sizeof(melodie));
                write(sd,comment,sizeof(comment));

                read(sd,msg6,sizeof(msg6));
                printf("%s",msg6);
            }
            else if(strcmp(msg4,"6")==0)
            {
                printf("Song: ");
                fflush(stdout);

                read(0,melodie,sizeof(melodie));
                melodie[strlen(melodie)-1]='\0';
                write(sd,msg4,sizeof(msg4));
                write(sd,melodie,sizeof(melodie));
                read(sd,&dim,sizeof(dim));
                read(sd,matrice,sizeof(matrice));

                printf("------Comments @%s------\n",melodie);
                for(i=1; i<=dim; i++)
                    printf("%s\n",matrice[i]);
            }
            else if(strcmp(msg4,"7")==0)
            {
              printf("Song: ");
              fflush(stdout);

              read(0,melodie,sizeof(melodie));
              melodie[strlen(melodie)-1]='\0';
              write(sd,msg4,sizeof(msg4));
              write(sd,melodie,sizeof(melodie));
              read(sd,raspuns,sizeof(raspuns));
              printf("%s\n",raspuns);
            }
            else if(strcmp(msg4,"8")==0)
            {
              printf("Username: ");
              fflush(stdout);

              read(0,msg6,sizeof(msg6));
              msg6[strlen(msg6)-1]='\0';
              write(sd,msg4,sizeof(msg4));
              write(sd,msg6,sizeof(msg6));
              read(sd,raspuns,sizeof(raspuns));
              printf("%s\n",raspuns);
            }
            else if(strcmp(msg4,"9")==0)
            {
                write(sd,msg4,sizeof(msg4));
                read(sd,&linkk,sizeof(linkk));
                read(sd,matrixx,sizeof(matrixx));
                if(linkk!=0)
                {
                    for(i=1;i<=linkk;i++)
                        printf("%s\n",matrixx[i]);
                }
            }
            else if(strcmp(msg4,"exit")==0)
            {
              write(sd,msg4,sizeof(msg4));
              read(sd,msg5,sizeof(msg5));
              if(strcmp(msg5,"exit")==0)
                break;
            }
        }
    }
    else
        printf("%s\n",raspuns);

    close (sd);
    return 0;
}
