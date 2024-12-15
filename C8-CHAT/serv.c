#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>      // Pour getaddrinfo
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT "12345"    // Le port d'écoute du serveur

void handle_client(int client_socket) {
    char buffer[1024];
    int bytes_received;

    // Boucle pour recevoir des messages du client
    while ((bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';  // Ajouter un terminateur de chaîne
        printf("Message reçu: %s\n", buffer);

        // Répondre au client
        send(client_socket, buffer, bytes_received, 0);
    }

    if (bytes_received == 0) {
        printf("Le client s'est déconnecté\n");
    } else {
        perror("recv");
    }

    // Fermer la connexion avec le client
    close(client_socket);
}

int main() {
    struct addrinfo hints, *res;
    int server_socket, client_socket;
    struct sockaddr_storage client_addr;
    socklen_t addr_size;
    int status;

    // Initialiser la structure hints
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;        // Utiliser IPv4
    hints.ai_socktype = SOCK_STREAM;  // Utiliser le type de socket TCP
    hints.ai_flags = AI_PASSIVE;      // Indique que l'on veut une adresse IP locale

    // Résoudre l'adresse et le port
    if ((status = getaddrinfo(NULL, PORT, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo failed: %s\n", gai_strerror(status));
        return 1;
    }

    // Créer la socket
    server_socket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (server_socket == -1) {
        perror("socket");
        freeaddrinfo(res);
        return 1;
    }

    // Lier la socket à l'adresse et au port
    if (bind(server_socket, res->ai_addr, res->ai_addrlen) == -1) {
        perror("bind");
        close(server_socket);
        freeaddrinfo(res);
        return 1;
    }

    // Écouter les connexions entrantes
    if (listen(server_socket, 5) == -1) {
        perror("listen");
        close(server_socket);
        freeaddrinfo(res);
        return 1;
    }

    // Libérer la mémoire allouée par getaddrinfo
    freeaddrinfo(res);

    printf("Serveur en écoute sur le port %s...\n", PORT);

    // Accepter les connexions des clients
    while (1) {
        addr_size = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_size);
        if (client_socket == -1) {
            perror("accept");
            continue;
        }

        printf("Client connecté\n");

        // Gérer le client dans un thread ou un processus séparé
        handle_client(client_socket);
    }

    // Fermer la socket du serveur
    close(server_socket);
    return 0;
}

