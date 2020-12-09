#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

int sock;
char *serverIP = "127.0.0.1";
int serverPort = 8088;

void error(char *err) { // Вывод ошибок в терминал
    printf("%s\n", err);
    fflush(stdin);
    perror(err);
    exit(1);
}


int main(int argc, char *argv[]) {
    char *help = "\033[1mNAME\033[0m\n\tParadist - Client which is connected to TCP Server (Karatist) to send him string with numbers and receive if there are Central polygonal numbers in there\n"
                 "\033[1mSYNOPSIS\033[0m\n\t Paradist [OPTIONS]\n"
                 "\033[1mDESCRIPTION\033[0m\n"
                 "\t-a=IP\n\t\tset server listening IP\n"
                 "\t-p=PORT\n\t\tset server listening PORT\n"
                 "\t-v\n\t\tcheck program version\n"
                 "\t-h\n\t\tprint help\n";
    int rez;
    if (getenv("L2ADDR") != NULL) {
        serverIP = getenv("L2ADDR");
    }
    if (getenv("L2PORT") != NULL) {
        serverPort = atoi(getenv("L2PORT"));
    }

    while ((rez = getopt(argc, argv, "a:p:vh")) != -1) { // Обработка ключей терминала
        switch (rez) {
            case 'a':
                if (strncmp(optarg, "", 1) == 0) {
                    printf("%s", help);
                    return 0;
                }
                serverIP = optarg;
                break;
            case 'p':
                if (strncmp(optarg, "", 1) == 0) {
                    printf("%s", help);
                    return 0;
                }
                serverPort = atoi(optarg);
                break;
            case 'v':
                printf("Paradist version 10.0 \"Rasskazat??\"");
                return 0;
            case 'h': //далее ключи для справки
            case '?':
            default:
                printf("%s", help);
                return 0;
        }
    }

    struct sockaddr_in serverAddr;
    int sockfd;
    socklen_t addr_size;
    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    serverAddr.sin_addr.s_addr = inet_addr(serverIP);
    addr_size = sizeof(serverAddr);
    connect(sockfd, (struct sockaddr *) &serverAddr, addr_size);
    char *buff = NULL;
    char buf;
    int n;
    int y = 1;
    while (1) {
        y = 1;
        printf("Enter the string : ");
        buff = NULL;
        buff = (char *) realloc(buff, sizeof(char));
        n = 0;
        while ((buff[n++] = getchar()) != '\n') {
            buff = (char *) realloc(buff, (n + 1) * sizeof(char));
        };
        send(sockfd, buff, n + 1, 0);
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            pthread_exit(NULL);
            exit(0);
        };
        buff = NULL;
        buff = (char *) realloc(buff, sizeof(char));
        recv(sockfd, &buf, sizeof(char), 0);
        buff[0] = buf;
        while (buf != '\n') {
            recv(sockfd, &buf, sizeof(char), 0);
            y++;
            buff = (char *) realloc(buff, (y) * sizeof(char));
            buff[y - 1] = buf;
        };
        printf("From Server : %s", buff);
    }
    free(buff);
    close(sockfd);
    return 0;
}
