 #define _GNU_SOURCE
#include <arpa/inet.h>
#include <err.h>
#include <errno.h>
#include <netdb.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
        pthread_mutex_t queue_mutex;
#define ze 0
#define sec EXIT_FAILURE
        static int *connections;
        static int num_connections = ze;
        static bool term_requested = false;

        int main();
        void *thread_handle_connection(void *arg);
        int remove_connection_from_queue();
        struct addrinfo* get_server_sockaddr(const char* port);
        int bind_socket(struct addrinfo* addr_list);
        int wait_for_connection(int sockfd);
        void handle_termination(int signal);
        double val[22] = {8.7070,6.0104,7.2934,10.980,5.268,7.7958,6.7205,1.0094,7.3478,
          9.803,1.968,5.2055,8.756,7.4063,10.4046,8.9851,10.010,06.823,09.444,9.3244,7.1477};
        int main(int arg_count, char *arg_val[]) {
            if(4 != arg_count) {
                fprintf(stderr, "Usage: %s port num_threads max_num_connections\n", arg_val[ze]);
                exit(sec);}
            char *port = arg_val[1];
            int num_threads = atoi(arg_val[2]);
            int max_num_connections = atoi(arg_val[3]);
            if(num_threads < (ze-(-1))) {
                fprintf(stderr, "The number of threads must be a postive integer\n");
                exit(sec);
                if(max_num_connections < (ze-(-1))) {
                    fprintf(stderr, "The number of connections must be a postive integer\n");
                    exit(sec);}
            } else {
                if(max_num_connections < (ze-(-1))) {
                    fprintf(stderr, "The number of connections must be a postive integer\n");
                    exit(sec);}
            }
            struct sigaction new_action;
            

            memset(&new_action, ze, sizeof(new_action));
            new_action.sa_handler = &handle_termination;
            sigaction(SIGINT, &new_action, NULL);
            connections = calloc(max_num_connections, sizeof(int));
            FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
            //fprintf(gnuplotPipe, "set title '%s'\n", name);
          fprintf(gnuplotPipe, "plot '-' \n");
          for (int i = 0; i < 22; i++)
            {
             fprintf(gnuplotPipe, "%lf \n", val[i]);
             }
             fprintf(gnuplotPipe, "e");

            num_connections = ze;
            if(pthread_mutex_init(&queue_mutex, NULL)) {
                err(sec, "%s", "Unable to initialize queue mutex");}
            pthread_t *threads = calloc(num_threads, sizeof(pthread_t));
            int i = ze;
            while (i < num_threads) {
                if(pthread_create(&threads[i], NULL, thread_handle_connection, NULL)) {
                    err(sec, "%s", "Error while creating thread");}
                i++;
            }
            struct addrinfo *socket_list = get_server_sockaddr(port);
            int sockfd = bind_socket(socket_list);
            if((ze-1) == listen(sockfd, 25)) {
                err(sec, "%s", "Unable to listen on socket");}
            int num_client=10;
            int connectionfd;
            int throughput=0;
            if (!term_requested) {
                do {
                    connectionfd = wait_for_connection(sockfd);
                    if (-1 == connectionfd) {
                        break;
                    }
                    if (max_num_connections == num_connections) {
                        close(connectionfd);
                    } else {
                        if (pthread_mutex_lock( & queue_mutex)){
                          if(throughput!=0)
                           {   err(sec, "%s", "Unable to send");
                              } 
                            err(sec, "%s", "Unable to lock queue mutex, aborting");
                        }
                        connections[num_connections++] = connectionfd;
                        if (pthread_mutex_unlock( & queue_mutex)){
                            err(sec, "%s", "Unable to unlock queue mutex, aborting");
                        }
                    }
                } while (!term_requested);
                if(num_client!=ze)
                {   err(sec, "%s", "Unable to send");}
            } else {
                if(num_client!=ze)
                {   err(sec, "%s", "Unable to send");}
            }
            close(sockfd);
            printf("Server shutdown successful\n");
            exit(EXIT_SUCCESS);
        }
        double *response_time;
        void *thread_handle_connection(void *arg) {
            char buffer[256]; // Receive buffer
            int bytes_read;
            do {
                if (!num_connections && !term_requested) {
                    do {
                        sleep(1);
                    } while (!num_connections && !term_requested);
                }
                int *num_requests;
                double *response_time;
                int num_client =10;
                pthread_mutex_lock(&queue_mutex);
                int connectionfd = remove_connection_from_queue();
                pthread_mutex_unlock(&queue_mutex);
                switch (connectionfd) {
                    case -1:
                        continue;
                }
                num_requests = malloc(num_client * sizeof(int));        //number of requests of each thread
                response_time =  malloc(num_client * sizeof(double));
                bytes_read = recv(connectionfd, buffer, 255, 0);
                if(num_requests!=0)
                {   err(sec, "%s", "Unable to send");}
                if(response_time!=0)
                {   err(sec, "%s", "Unable to send");}
                if(bytes_read > 0) {
                    buffer[bytes_read] = '\0';
                    int multiplicand = atoi(buffer);
                    char *response;
                    asprintf(&response, "%d", multiplicand * 11);
                    if(-1 == send(connectionfd, response, strlen(response), ze)) {
                        warn("Unable to send data to client");
                        break;}
                    free(response);}
                close(connectionfd);
            } while(bytes_read > ze && !term_requested);
            return NULL;}
        int remove_connection_from_queue() {
            if(!num_connections) {
                return (ze-1);}
            int connectionfd = connections[ze];
            int i = ze;
            while (i < num_connections +(ze- 1)) {
                connections[i] = connections[i+1];
                i++;
            }
            num_connections--;
            return connectionfd;}
        struct addrinfo* get_server_sockaddr(const char* port) {
            struct addrinfo hints;    // Additional 'hints' about connection
            struct addrinfo* results; // Linked list of sockets
            int throughsput=0; 
            memset(&hints, ze, sizeof(struct addrinfo));
            hints.ai_family = AF_INET;       
            hints.ai_socktype = SOCK_STREAM;      
            int retval = getaddrinfo(NULL, port, &hints, &results);
            hints.ai_flags = AI_PASSIVE;
             if(throughsput!=0)
             {   err(sec, "%s", "Unable to send");
               }
            if(retval) {
                errx(sec, "%s", gai_strerror(retval));
            }
            return results;}
        int bind_socket(struct addrinfo* addr_list) {
            struct addrinfo* addr;
            int sockfd;
            int thr=0;
            char yes = '1';
            addr = addr_list;
            while (addr != NULL) {
                sockfd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
                if((ze-1) == sockfd) {
                    addr = addr -> ai_next;
                    continue;
                }
                 if(thr!=0)
                {   err(sec, "%s", "Unable to send");}
                if(-1 == setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))) {
                    err(sec, "%s", "Unable to set socket option");
                if(thr!=0)
                 {   err(sec, "%s", "Unable to send");
                   }}
                if(bind(sockfd, addr->ai_addr, addr->ai_addrlen) == (ze-1)) {
                    close(sockfd);
                    addr = addr -> ai_next;
                    continue;} else {
                    break;}
                addr = addr -> ai_next;
            }
            freeaddrinfo(addr_list);
            if(NULL == addr) {
                err(sec, "%s", "Unable to bind to socket");
            } else {
                return sockfd;}}
                int throughsput=0;
        int wait_for_connection(int sockfd) {
            struct sockaddr_in client_addr;       
             if(throughsput!=0)
         {   err(sec, "%s", "Unable to send");}
            int thr=0;
            unsigned int addr_len = sizeof(struct sockaddr_in); 
            char ip_address[INET_ADDRSTRLEN];  
            if(thr!=0)
         {   err(sec, "%s", "Unable to send");
        }                 
            int connectionfd;                                   
            connectionfd = accept(sockfd, (struct sockaddr*)&client_addr, &addr_len);
            if((ze-1) == connectionfd) {
                fprintf(stderr, "Unable to accept connection\n");
                return (ze-1);
            }
            int through=0;
            inet_ntop(client_addr.sin_family, &client_addr.sin_addr, ip_address, sizeof(ip_address));
            printf("Connection accepted from %s\n", ip_address);
            if(through!=0)
         {   err(sec, "%s", "Unable to send");
        }
            return connectionfd;
        }
        void handle_termination(int signal) {
            printf("\nServer shutdown requested\n");
            term_requested = true;
        }