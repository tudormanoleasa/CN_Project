#include<sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 2728
char* creeazaCont(char user[],char password[],char type[])
{
    char date[256];
    bzero(&date,sizeof(date));
    FILE *f=fopen("users.txt","a+");
    strcpy(date,user);
    strcat(date," ");
    strcat(date,password);
    strcat(date," ");
    strcat(date,type);
    fprintf(f,"%s\n",date);
    fclose(f);
    return " We have created your account";
}

char* validareDate(char user[],char password[],char type[])
{
    int ok=0;
    char sir[256],*p;
    FILE *f=fopen("users.txt","r");
    while(fgets(sir,256,f))
    {
        p=strtok(sir," ");
        if(strcmp(p,user)==0)
        {
            ok=1;
            p=strtok(0," ");
            if(strcmp(p,password)!=0)
                return "Invalid password!";
            p=strtok(0," ");
            p[1]='\0';
            if(strcmp(p,type)!=0)
                return "Invalid type!";
        }
    }
    fclose(f);
    if(ok==0)
        return "Invalid user!";
    return "Successful log in";
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
char* adaugaMelodie(char melodie[], char gen[], char votes[], char link[], char descriere[])
{
    FILE *f=fopen("songs.txt","a+");
    char date[256];
    bzero(&date,sizeof(date));
    strcpy(date,melodie);
    strcat(date,"|");
    strcat(date,gen);
    strcat(date,"|");
    strcat(date,votes);
    strcat(date,"|");
    strcat(date,link);
    strcat(date,"|");
    strcat(date,descriere);
    fprintf(f,"%s\n",date);
    fclose(f);
    return "The song has been added";
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
char* voteazaMelodie(char melodie[],char votes[])
{
    char *p,sir[256];
    FILE *f=fopen("songs.txt","a+");
    while(fgets(sir,256,f))
    {
        if(strstr(sir,melodie)!=0)
        {
            fprintf(f,"%s ",melodie);
            fprintf(f,"%s\n",votes);
        }
    }
    fclose(f);
    return "The song has been voted!\n";
}

char* isInTop(char melodie[])
{
    char sir[256];
    FILE *f=fopen("songs.txt","r");
    while(fgets(sir,256,f))
        if(strstr(sir,melodie)!=0)
            return "Da";
    return "The song is not in the charts... Please add it if you want to vote\n";
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
int n,d[256];
char a[256][256];
int isInMatrix(char cuv[])
{
    int i;
    for(i=1; i<=n; i++)
        if(strcmp(a[i],cuv)==0)
        {
            d[i]++;
            return 1;
        }
    return 0;
}

void clasamentGeneral()
{
    char sir[256],*p,aux[256];
    int i,j,aux2;
    FILE *f=fopen("songs.txt","rw");
    while(fgets(sir,256,f))
        if(strstr(sir,"|")!=0)
        {
            p=strtok(sir,"|");
            if(!isInMatrix(p))
            {
                n++;
                strcpy(a[n],p);
                d[n]=1;
            }
        }
    fclose(f);
    for(i=1; i<=n; i++)
    {
        f=fopen("songs.txt","rw");
        while(fgets(sir,256,f))
            if(strstr(sir,a[i])!=0 && strstr(sir,"|")==0)
                d[i]++;
        fclose(f);
    }

    for(i=1;i<n;i++)
        for(j=i+1;j<=n;j++)
            if(d[i]<d[j])
            {
                strcpy(aux,a[i]);
                strcpy(a[i],a[j]);
                strcpy(a[j],aux);
                aux2=d[i];
                d[i]=d[j];
                d[j]=aux2;
            }
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
int m,q[256];
char b[256][256];
int inMatrix(char cuv[])
{
    int i;
    for(i=1; i<=m; i++)
        if(strcmp(b[i],cuv)==0)
        {
            q[i]++;
            return 1;
        }
    return 0;
}

void clasamentGen(char genre[])
{
    int i,j,aux2;
    char sir[256],*p,aux[256];
    FILE *f=fopen("songs.txt","rw");
    while(fgets(sir,256,f))
        if(strstr(sir,genre)!=0)
        {
            p=strtok(sir,"|");
            if(!inMatrix(p))
            {
                m++;
                strcpy(b[m],p);
                q[m]=1;
            }
        }
    fclose(f);
    for(i=1; i<=m; i++)
    {
        f=fopen("songs.txt","rw");
        while(fgets(sir,256,f))
            if(strstr(sir,b[i])!=0 && strstr(sir,"|")==0)
                q[i]++;
        fclose(f);
    }
    for(i=1;i<m;i++)
        for(j=i=1;j<=m;j++)
            if(q[i]<q[j])
            {
                strcpy(aux,b[i]);
                strcpy(b[i],b[j]);
                strcpy(b[j],aux);
                aux2=q[i];
                q[i]=q[j];
                q[j]=aux2;
            }
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
char* adaugaComentariu(char user[],char melodie[],char comentariu[])
{
    FILE *f=fopen("comentarii.txt","a+");
    char sir[256],line[256];
    bzero(&sir,sizeof(sir));
    strcpy(sir,user);
    strcat(sir,": ");
    strcat(sir,melodie);
    strcat(sir,": ");
    strcat(sir,comentariu);

    FILE *f2=fopen("songs.txt","r");
    int ok=0;
    while(fgets(line,256,f2))
        if(strstr(line,melodie))
        {
            ok=1;
            break;
        }
    fclose(f2);

    if(ok==1)
    {
        fprintf(f,"%s\n",sir);
        fclose(f);
        return "Your comment has been added\n";
    }
    else
    {
        fclose(f);
        return "The song is not in our file\n";
    }
}

int dim;
char c[256][256];
void returneazaComentarii(char melodie[])
{
    char sir[256];
    FILE *f=fopen("comentarii.txt","r");
    while(fgets(sir,256,f))
        if(strstr(sir,melodie)!=0)
        {
            dim++;
            strcpy(c[dim],sir);
        }
    fclose(f);
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void deleteSong(char mel[])
{
    char new[256];
    bzero(&new,sizeof(new));
    strcat(new,"/");
    strcat(new,mel);
    strcat(new,"/d");
    if(fork()==0)
    execlp("sed","sed","-i",new,"./songs.txt",NULL);
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void restriction(char user[])
{
    FILE *f=fopen("restrictii.txt","a+");
    fprintf(f,"%s\n",user);
    fclose(f);
}
int areRestrictie(char user[])
{
    char sir[256];
    FILE *f=fopen("restrictii.txt","rw");
    while(fgets(sir,strlen(user)+1,f))
        if(strcmp(sir,user)==0)
        {
            fclose(f);
            return 1;
        }
    fclose(f);
    return 0;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
int nrLinksPiesa;
char linksPiesa[256][256];
void showLinksPiese()
{
    char sirrr[256],*pointer,sirrr2[256];
    FILE *f=fopen("songs.txt","r");
    while(fgets(sirrr,sizeof(sirrr),f))
        if(strstr(sirrr,"|"))
        {
            sirrr2[0]='\0';
            strcpy(sirrr2,sirrr);
            nrLinksPiesa++;
            pointer=strtok(sirrr2,"|");
            strcpy(linksPiesa[nrLinksPiesa],pointer);
            strcat(linksPiesa[nrLinksPiesa]," ");
            pointer=strtok(0,"|");
            pointer=strtok(0,"|");
            pointer=strtok(0,"|");
            strcat(linksPiesa[nrLinksPiesa],pointer);
        }
    fclose(f);
}
int main()
{

    struct sockaddr_in server;
    bzero(&server,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);

    int sd;
    sd = socket(AF_INET, SOCK_STREAM, 0);


    bind(sd, (struct sockaddr*)&server, sizeof(struct sockaddr));

    listen(sd,5);

    while(1)
    {
        struct sockaddr_in from;
        int client,length=sizeof(struct sockaddr);
        bzero(&from,sizeof(from));
        client = accept(sd, (struct sockaddr*)&from, &length);
        printf("A client has connected!\n");
        fflush(stdout);

        char msg[256];
        if(fork() == 0)
        {
            close(sd);
            int nr=0;
            char msg1[256],msg2[256],msg3[256],msg4[256],msg5[256]="1",msg6[256],msg7[256],msg8[256],msg9[256],msg10[256];
            bzero(&msg1,sizeof(msg1)); // Username
            bzero(&msg2,sizeof(msg2)); // Password
            bzero(&msg3,sizeof(msg3)); // Type
            bzero(&msg4,sizeof(msg4)); // Mesaj referitor la logare

            read(client,msg1,sizeof(msg1)); // Iau Username de la client
            read(client,msg2,sizeof(msg2)); // Iau Password de la client
            read(client,msg3,sizeof(msg3)); // Iau Type de la client

            strcpy(msg4,validareDate(msg1,msg2,msg3));
            if(strcmp(msg4,"Invalid user!")==0)
                strcat(msg4,creeazaCont(msg1,msg2,msg3));
            write(client,msg4,sizeof(msg4));

            if(strstr(msg4,"Successful log in")!=0)
                while(1)
                {
                    nr++;
                    bzero(&msg5,sizeof(msg5));
                    bzero(&msg6,sizeof(msg6));
                    bzero(&msg7,sizeof(msg7));
                    bzero(&msg8,sizeof(msg8));
                    bzero(&msg9,sizeof(msg9));
                    bzero(&msg10,sizeof(msg10));


                    if(strstr(msg4,"Successful")!=0)
                    {
                        read(client,msg5,sizeof(msg5));
                        if(strcmp(msg5,"1")==0)
                        {
                            read(client,msg6,sizeof(msg6)); // Melodie
                            read(client,msg7,sizeof(msg7)); // Gen
                            read(client,msg8,sizeof(msg8)); // Votes
                            read(client,msg9,sizeof(msg9)); // Link
                            read(client,msg10,sizeof(msg10)); // Descriere

                            write(client,adaugaMelodie(msg6,msg7,msg8,msg9,msg10),sizeof("The song has been added"));
                        }
                        else if(strcmp(msg5,"2")==0)
                        {
                            read(client,msg6,sizeof(msg6)); // Melodie
                            read(client,msg7,sizeof(msg7)); // Votes
                            if(areRestrictie(msg1)==0)
                            {
                            if(strcmp(isInTop(msg6),"Da")==0)
                                write(client,voteazaMelodie(msg6,msg7),sizeof("The song has been added"));
                            else
                                write(client,isInTop(msg6),sizeof("The song is not in the charts... Please add it if you want to vote\n"));
                            }
                            else
                                write(client,"You are restricted!",sizeof("You are restricted!"));
                        }
                        else if(strcmp(msg5,"3")==0)
                        {
                            bzero(&n,sizeof(n));
                            bzero(a,sizeof(a));
                            bzero(d,sizeof(d));
                            clasamentGeneral();
                            write(client,&n,sizeof(n));
                            write(client,a,sizeof(a));
                            write(client,d,sizeof(d));
                        }
                        else if(strcmp(msg5,"4")==0)
                        {
                            read(client,msg10,sizeof(msg10));
                            bzero(&m,sizeof(m));
                            bzero(b,sizeof(b));
                            bzero(q,sizeof(q));
                            clasamentGen(msg10);
                            write(client,&m,sizeof(m));
                            write(client,b,sizeof(b));
                            write(client,q,sizeof(q));
                        }
                        else if(strcmp(msg5,"5")==0)
                        {
                            read(client,msg9,sizeof(msg9));
                            read(client,msg10,sizeof(msg10));
                            write(client,adaugaComentariu(msg1,msg9,msg10),sizeof("Your comment has been added!\n"));
                        }
                        else if(strcmp(msg5,"6")==0)
                        {
                            read(client,msg10,sizeof(msg10));
                            bzero(&dim,sizeof(dim));
                            bzero(c,sizeof(c));
                            returneazaComentarii(msg10);
                            write(client,&dim,sizeof(dim));
                            write(client,c,sizeof(c));
                        }
                        else if(strcmp(msg5,"7")==0)
                        {
                            if(msg3[0]=='a')
                            {
                                read(client,msg6,sizeof(msg6));
                                deleteSong(msg6);
                                write(client,"Operation done!",sizeof("Operation done!"));
                            }
                            else
                                write(client,"You may not perform this operation!",sizeof("You may not perform this operation!"));
                        }
                        else if(strcmp(msg5,"8")==0)
                        {
                            if(msg3[0]=='a')
                            {
                                read(client,msg6,sizeof(msg6));
                                restriction(msg6);
                                write(client,"Operation done!",sizeof("Operation done!"));
                            }
                            else
                                write(client,"You may not perform this operation!",sizeof("You may not perform this operation!"));
                        }
                        else if(strcmp(msg5,"9")==0)
                        {
                            bzero(&nrLinksPiesa,sizeof(nrLinksPiesa));
                            bzero(linksPiesa,sizeof(linksPiesa));
                            showLinksPiese();
                            write(client,&nrLinksPiesa,sizeof(nrLinksPiesa));
                            write(client,linksPiesa,sizeof(linksPiesa));
                        }
                        else if(strcmp(msg5,"exit")==0)
                        {
                            write(client,"exit",sizeof("exit"));
                            break;
                        }
                    }
                }
        printf("A user has disconnected!\n");
        exit(0);
        close(client);
        }
    }

    return 0;
}
