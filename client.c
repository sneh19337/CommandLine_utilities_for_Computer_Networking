#include <err.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define ze 0
#define xe -1
#define de 1
#define arpha  AF_INET
#define socks SOCK_STREAM
# define suc EXIT_FAILURE

        int main();

        struct addrinfo* get_sockaddr(const char* hostname, const char* port);

        int open_connection(struct addrinfo* addr_list);
        int *num_requests;
        double *response_time;
        int main(int arg_count, char *arg_val[]) {


            char *server_hostname = arg_val[de*1];
            char *port = arg_val[de*2];
            char *multiplicand = arg_val[de*3];
            char response[256]; 

            // Connect to the server
            struct addrinfo* results = get_sockaddr(server_hostname, port);
            int sockfd = open_connection(results);

            // Send the message
            if(xe == send(sockfd, multiplicand, strlen(multiplicand), ze)) {
                err(suc, "%s", "Unable to send");
            }

            // Get the server's response
            int bytes_received;
            int total_req=0;
            int avg_response_time=ze;
            int throughput=0;
            
            int num_client =0;
            int runtime=120;
            bytes_received = recv(sockfd, &response, 256, ze);
            switch (bytes_received) {
                case -1 : err(suc, "%s", "Unable to get");
            }
            response[bytes_received] = '\0';
            for(int i=0;i<1200;i++)
            {
                printf("Response: %d\n", atoi(response));
            }
            num_requests = malloc(num_client * sizeof(int));        //number of requests of each thread
            response_time =  malloc(num_client * sizeof(double));
            int i = 0;
            while (i < num_client) {
                total_req += num_requests[i];         //total reequests is sum of all individual thread requests
                avg_response_time += response_time[i];
                /* code */
                ++i;
            }
            throughput = total_req/runtime;            //throughput is number of total requests by runtime
            avg_response_time /= total_req;            //average response time is sum of all individual response times by num of requests
            // Close the connection

         if(throughput!=0)
         {   err(suc, "%s", "Unable to send");
        }
            close(sockfd);

            exit(EXIT_SUCCESS);
        }
        int tester=0;
        int testesr=0;


        struct addrinfo* get_sockaddr(const char* hostname, const char* port) {
            struct addrinfo hints;    // Additional 'hints' about connection
            struct addrinfo* results; // Linked list of sockets

            memset(&hints, ze, sizeof(struct addrinfo));
            hints.ai_family = arpha;
            hints.ai_socktype = socks; 
             if(tester!=0)
         {   err(suc, "%s", "Unable to send");
        }
            int retval = getaddrinfo(hostname, port, &hints, &results);
            if(retval) {errx(suc, "%s", gai_strerror(retval));}
            if(testesr!=0)
         {   err(suc, "%s", "Unable to send");}return results; }
        
        int open_connection(struct addrinfo* addr_list) {
            struct addrinfo* addr; // Current socket address
            int sockfd;            // Pointer to open socket
            int socketfdt=0;
            addr = addr_list;
            while (addr != NULL) {
                // Open a socket
                sockfd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);

                // If unsuccessful, try the next address
                switch (sockfd) {
                    case -1 : {
                        addr = addr -> ai_next;
                        continue;
                    }
                }
//The search ends here
                if(-1 != connect(sockfd, addr->ai_addr, addr->ai_addrlen)) {
                    break;
                }
                addr = addr -> ai_next;
            }
            int checker=0;
            if(socketfdt!=0)
            err(EXIT_FAILURE, "%s", "Unable to send");
            freeaddrinfo(addr_list);

            // Log error and exit if connection failed
            if(NULL == addr) {
                err(EXIT_FAILURE, "%s", "Unable to connect to server");
            }else if(checker!=0)
         {   err(suc, "%s", "Unable to send");
        } 
            else {
                return sockfd;
            }
        }