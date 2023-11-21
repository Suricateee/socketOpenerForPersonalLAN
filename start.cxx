#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
 
#define NUM_PORT 10016
#define BACKLOG 128
#define NB_CLIENTS 10000
 
using namespace std;
 
void exitErreur(const char * msg) {
    perror(msg);
    exit( EXIT_FAILURE);
 
}

int main(int argc, char * argv[]) {
 
    int sock_serveur = socket(AF_INET, SOCK_STREAM, 0);
 
    struct sockaddr_in sockaddr_serveur;
 
    sockaddr_serveur.sin_family = AF_INET;
    sockaddr_serveur.sin_port = htons(NUM_PORT);
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
        
    for (int i = 1; i <= NB_CLIENTS; i++) {
    
        struct sockaddr_in sockaddr_client ;
        socklen_t taille = sizeof(struct sockaddr_in);

        int sock_client = accept(sock_serveur, (struct sockaddr *) & sockaddr_client, &taille);
        
        string cmd = "telnet ";
        string cmd2 = inet_ntoa(sockaddr_client.sin_addr);
        string cmd3 = " 10015";
        
        cmd.append(cmd2);
        cmd.append(cmd3);
        
        std::string str = cmd;
        char * ligne2 = new char[str.length() + 1];
        strcpy(ligne2, str.c_str());
        
        system(ligne2);
        
        cout << "Adresse IP client : " << inet_ntoa(sockaddr_client.sin_addr) ;
        cout << " / port client : " << ntohs(sockaddr_client.sin_port ) << endl ;
            
        close(sock_client);
 
    }
    close(sock_serveur);
    return EXIT_SUCCESS;
}
