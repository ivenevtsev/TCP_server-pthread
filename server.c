#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

int sock, count, good, bad = 0;
int delay = 0;
pthread_mutex_t lock;
clock_t begin;
char *serverIP = "127.0.0.1";
int serverPort = 8088;
FILE *logFile;

void check(int ret) {
    if (ret < 0) {
        fprintf(stderr, "ERROR: failed to set proc mask: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}

char *currentTimestamp() {
    time_t timer;
    char *buffer = (char *) malloc(sizeof(char) * 26);
    struct tm *tm_info;
    time(&timer);
    tm_info = localtime(&timer);
    strftime(buffer, 26, "%d.%m.%Y %H:%M:%S", tm_info);
    return buffer;
}

void error(char *err) {
    if (logFile == NULL) {
        printf("%s\t%s\n", currentTimestamp(), err);
    } else {
        fprintf(logFile, "%s\t%s\n", currentTimestamp(), err);
        fflush(logFile);
        fclose(logFile);
    }
    perror(err);
    exit(1);
}


void quit() {
    printf("\n%s\tЗавершение работы сервера\n", currentTimestamp());
    fprintf(logFile, "%s\tЗавершение работы сервера\n", currentTimestamp());
    fflush(logFile);
    close(sock);
    fclose(logFile);
    exit(0);
}

void quitWithLog() {
    clock_t end = clock();
    double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    fprintf(logFile, "Завершение работы сервера.\n"
                     "Сервер работал: %f с\n"
                     "Обслуженные запросы: %d\n"
                     "Текущее время: %s\n"
                     "Количество обработанных запросов: %d\n"
                     "Количество ошибочных запросов запросов: %d\n", time_spent, count, currentTimestamp(), good, bad);
    printf("Завершение работы сервера.\n"
           "Сервер работал: %f с\n"
           "Обслуженные запросы: %d\n"
           "Текущее время: %s\n"
           "Количество обработанных запросов: %d\n"
           "Количество ошибочных запросов запросов: %d\n", time_spent, count, currentTimestamp(), good, bad);
    fflush(logFile);
}

void *func(void *arg) {
    int sockfd = *(int *) arg;
    char buff;
    char *buf;
    while (1) {
        int y = 1;
        char *istr = NULL;
        int c = -1;
        int k;
        int i = 0;
        int l = 0;
        int j = 1, o = 0;
        buf = NULL;
        if ((buf = (char *) realloc(buf, sizeof(char *))) == NULL) {
            pthread_mutex_lock(&lock);
            bad++;
            pthread_mutex_unlock(&lock);
            send(sockfd, "ERROR_98\n", 9, 0);
            error("\nERROR 98: Realloc failed\n");
        };
        if (recv(sockfd, &buff, sizeof(char), 0) == -1) {
            pthread_mutex_lock(&lock);
            bad++;
            pthread_mutex_unlock(&lock);
            send(sockfd, "ERROR_2\n", 8, 0);
            error("\nERROR 2: Receiv failed\n");
        };
        buf[0] = buff;
        while (buff != '\0') {
            if (recv(sockfd, &buff, sizeof(char), 0) == -1) {
                pthread_mutex_lock(&lock);
                bad++;
                pthread_mutex_unlock(&lock);
                send(sockfd, "ERROR_2\n", 8, 0);
                error("\nERROR 2: Receiv failed\n");
            };
            y++;
            if ((buf = (char *) realloc(buf, (y) * sizeof(char))) == NULL) {
                pthread_mutex_lock(&lock);
                bad++;
                pthread_mutex_unlock(&lock);
                send(sockfd, "ERROR_98\n", 9, 0);
                error("\nERROR 98: Realloc failed\n");
            };
            buf[y - 1] = buff;
        };
        sleep(delay);
        pthread_mutex_lock(&lock);
        fprintf(logFile, "%s\tПоступление запроса\n", currentTimestamp());
        pthread_mutex_unlock(&lock);
        if ((strncmp(buf, "exit", 4)) == 0) {
            pthread_mutex_lock(&lock);
            fprintf(logFile, "%s\tЗавершение работы клиента\n", currentTimestamp());
            fflush(logFile);
            pthread_mutex_unlock(&lock);
            close(sockfd);
            pthread_exit(NULL);
            exit(0);
        };
        printf("From client: %s", buf);

        istr = strtok(buf, "\n\x20\x0B\x0C\t\r");
        while (istr != NULL) {
            l = 0;
            for (i = 0; i < (int) strlen(istr); i++)
                if (!((istr[i] >= '0') && (istr[i] <= '9')))
                    l++;
            sscanf(istr, "%d", &c);
            if (c == 0) {
                sscanf(istr, "%x", &c);
                do {
                    k = (i * (i + 1) / 2 + 1);
                    i++;

                } while (k < c);
                if ((l == 1) && (istr[0] = '0') && (istr[1] = 'x')) {
                    l--;
                };
                if (k == c) {
                    o++;
                };
            } else {
                do {
                    k = (i * (i + 1)) / 2 + 1;
                    i++;
                } while (k < c);
                if ((k == c) && (l == 0)) {
                    o++;
                }
            };
            if ((l == 0) || ((l == 1) && (istr[0] == '0') && istr[1] == 'x'))
                j++;
            istr = strtok(NULL, "\n\x20\x0B\x0C\t\r");
        };
        buf = NULL;
        if (l > 0) {
            send(sockfd, "ERROR_90 Not SIMBOL\n", 20, 0);
            pthread_mutex_lock(&lock);
            bad++;
            pthread_mutex_unlock(&lock);
        } else {
            if ((j == (o + 1)) && (j != 1)) {
                i = 4;
                if (send(sockfd, "ALL\n", i, 0) == -1) {
                    pthread_mutex_lock(&lock);
                    bad++;
                    pthread_mutex_unlock(&lock);
                    error("\nERROR 14: Sending failed\n");
                };
                pthread_mutex_lock(&lock);
                good++;
                pthread_mutex_unlock(&lock);
            } else {
                if (o == 0) {
                    i = 5;
                    if (send(sockfd, "NONE\n", i, 0) == -1) {
                        pthread_mutex_lock(&lock);
                        bad++;
                        pthread_mutex_unlock(&lock);
                        error("\nERROR 14: Sending failed\n");
                    };
                    pthread_mutex_lock(&lock);
                    good++;
                    pthread_mutex_unlock(&lock);
                } else {
                    i = 5;
                    if (send(sockfd, "SOME\n", i, 0) == -1) {
                        pthread_mutex_lock(&lock);
                        bad++;
                        pthread_mutex_unlock(&lock);
                        error("\nERROR 14: Sending failed\n");
                    };
                    pthread_mutex_lock(&lock);
                    good++;
                    pthread_mutex_unlock(&lock);
                }
            }
        }
        fprintf(logFile, "%s\tЗавершение обслуживания запроса\n", currentTimestamp());
        count++;
        fflush(logFile);
        pthread_mutex_unlock(&lock);
    }

    close(sockfd);
    pthread_exit(NULL);
}

void serverHandler() {
    fprintf(logFile, "\n%s\tНачало работы сервера\n", currentTimestamp());
    fflush(logFile);
    if (pthread_mutex_init(&lock, NULL) != 0) {
        error("\nERROR 54: Mutex init failed\n");
    }

    int newSocket;
    struct sockaddr_in serverAddress;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    pthread_t tid[60];
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        error("ERROR 73: Socket failed");
    };
    fprintf(logFile, "%s\tSocket created\n", currentTimestamp());
    fflush(logFile);
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET; //IP4 internetwork: UDP, TCP, etc.
    serverAddress.sin_port = htons(serverPort); //Устанавливаем порт
    serverAddress.sin_addr.s_addr = inet_addr(serverIP); //00000
    if (bind(sock, (struct sockaddr *) &serverAddress,
             sizeof(serverAddress)) == -1) {
        error("ERROR 42: Binding failed");
    };
    fprintf(logFile, "%s\tBinding done\n", currentTimestamp());
    fflush(logFile);
    if ((listen(sock, 5)) != 0) {
        error("ERROR 105:Listenning failed");
    };
    fprintf(logFile, "%s\tListenning socket\n", currentTimestamp());
    fflush(logFile);
    int i = 0;
    while (1) {
        addr_size = sizeof serverStorage;
        newSocket = accept(sock, (struct sockaddr *) &serverStorage, &addr_size);
        if (pthread_create(&tid[i], NULL, func, (void *) &newSocket) != 0)
            error("ERROR 1:Failed to create thread\n");
        fprintf(logFile, "%s\tThread created\n", currentTimestamp());
        fflush(logFile);
        if (i >= 50) {
            i = 0;
            while (i < 50) {
                pthread_join(tid[i++], NULL);
            }
            i = 0;
        }

    }
}

int main(int argc, char *argv[]) {
    char *help = "\033[1mNAME\033[0m\n\tKaratist - TCP server, which checks if there are Central polygonal numbers in the string\n"
                 "\033[1mSYNOPSIS\033[0m\n\t Karatist [OPTIONS]\n"
                 "\033[1mDESCRIPTION\033[0m\n"
                 "\t-w=N\n\t\tset delay N for client \n"
                 "\t-d\n\t\tdaemon mode\n"
                 "\t-l=path/to/log\n\t\tPath to log-file\n"
                 "\t-a=IP\n\t\tset server listening IP\n"
                 "\t-p=PORT\n\t\tset server listening PORT\n"
                 "\t-v\n\t\tcheck program version\n"
                 "\t-h\n\t\tprint help\n";
    int rez;
    int daemonFlag = 0;
    char *logPath = "/tmp/lab2.log";
    begin = clock();
    struct sigaction sa = {0};
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGINT);
    sigaddset(&sa.sa_mask, SIGQUIT);
    sigaddset(&sa.sa_mask, SIGTERM);
    sa.sa_sigaction = quit;
    sa.sa_flags |= (SA_SIGINFO | SA_RESTART); // mind SA_RESTART here!
    check(sigaction(SIGINT, &sa, NULL));
    check(sigaction(SIGQUIT, &sa, NULL));
    check(sigaction(SIGTERM, &sa, NULL));
    struct sigaction sa1 = {0};
    sigemptyset(&sa1.sa_mask);
    sigaddset(&sa1.sa_mask, SIGUSR1);
    sa1.sa_sigaction = quitWithLog;
    sa1.sa_flags |= (SA_SIGINFO | SA_RESTART);
    check(sigaction(SIGUSR1, &sa1, NULL));
    if (getenv("L2ADDR") != NULL) {
        serverIP = getenv("L2ADDR");
    }
    if (getenv("L2PORT") != NULL) {
        serverPort = atoi(getenv("L2PORT"));
    }
    if (getenv("L2WAIT") != NULL) {
        delay = atoi(getenv("L2WAIT"));
    }
    while ((rez = getopt(argc, argv, "w:dl:a:p:vh")) != -1) {
        switch (rez) {
            case 'w':
                delay = atoi(optarg);
                break;
            case 'd':
                daemonFlag = 1;
                break;
            case 'l':
                if (strncmp(optarg, "", 1) == 0) {
                    printf("%s", help);
                    return 0;
                }
                logPath = strdup(optarg);
                break;
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
                printf("\033[1mKaratist version 2.14,5 \"Rasskazat\'?\"\033[0m\n");
                return 0;
            case 'h': //далее ключи для справки
            case '?':
            default:
                printf("%s", help);
                return 0;
        }
    }

    if (daemonFlag == 1) {
        pid_t pid, sid;
        pid = fork();
        if (pid < 0) {
            error("ERROR 99: Fork failed ");
        }
        if (pid > 0) {
            exit(0);
        }

        sid = setsid();
        if (sid < 0) {
            error("ERROR 98: SID failed ");
        }
        struct sigaction sa;
        sigemptyset(&sa.sa_mask);
        sa.sa_handler = SIG_IGN;
        sa.sa_flags = 0;
        sigaction(SIGCHLD, &sa, NULL);
        sigaction(SIGHUP, &sa, NULL);
        if ((pid = fork()) < 0) {
            error("ERROR 99: Fork failed ");
        }
        if (pid > 0) {
            exit(0);
        }
        umask(0);
        chdir("/");
        int fd;
        for (fd = sysconf(_SC_OPEN_MAX); fd > 0; --fd) {
            close(fd);
        }
        stdin = fopen("/dev/null", "r");
        stdout = fopen("/dev/null", "w+");
        stderr = fopen("/dev/null", "w+");
        if ((logFile = fopen(logPath, "rb+")) == NULL) {
            error("ERROR 24: Open file");
        }

        serverHandler();
        pthread_mutex_destroy(&lock);

    } else {
        if ((logFile = fopen(logPath, "a+b")) == NULL) {
            error("ERROR 24: Open file");
        }
        serverHandler();
        pthread_mutex_destroy(&lock);
    }
}
