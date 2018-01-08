#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
//#include <iostream>
#include "./serialPort/serialport.hpp"

using namespace std;

#define BUFLEN 1024

//#define DEBUG_MAIN_LOOP

#define FIRST_PAIR   //AZYMUT
//#define SECOND_PAIR  //ELEWACJA KAMERY
//#define THIRD_PAIR   //AZYMUT
//#define FOURTH_PAIR  //AZYMUT KAMERY
//#define FIFTH_PAIR   //SKO
//#define SIXTH_PAIR

#define CLIENT_IP "192.168.103.97"
//#define CLIENT_IP "127.0.0.1"

#ifdef FIRST_PAIR
#define FIRST_SERIAL_FILE "/dev/ttyCTI3"
#define FIRST_SERIAL_BAUDRATE B115200
#define FIRST_SERIAL_PARITY NO_PARITY
#define FIRST_SERIAL_STOP_BITS ONE_STOP_BIT
#define FIRST_LISTEN_PORT 6234
#define FIRST_SEND_PORT 6235
#endif

#ifdef SECOND_PAIR
#define SECOND_SERIAL_FILE "/dev/tnt3"
#define SECOND_SERIAL_BAUDRATE B115200
#define SECOND_SERIAL_PARITY NO_PARITY
#define SECOND_SERIAL_STOP_BITS ONE_STOP_BIT
#define SECOND_LISTEN_PORT 1236
#define SECOND_SEND_PORT 1237
#endif

#ifdef THIRD_PAIR
#define THIRD_SERIAL_FILE "/dev/tnt5"
#define THIRD_SERIAL_BAUDRATE B115200
#define THIRD_SERIAL_PARITY NO_PARITY
#define THIRD_SERIAL_STOP_BITS ONE_STOP_BIT
#define THIRD_LISTEN_PORT 1238
#define THIRD_SEND_PORT 1239
#endif

#ifdef FOURTH_PAIR
#define FOURTH_SERIAL_FILE "/dev/tnt7"
#define FOURTH_SERIAL_BAUDRATE B115200
#define FOURTH_SERIAL_PARITY NO_PARITY
#define FOURTH_SERIAL_STOP_BITS ONE_STOP_BIT
#define FOURTH_LISTEN_PORT 1240
#define FOURTH_SEND_PORT 1241
#endif

#ifdef FIFTH_PAIR
#define FIFTH_SERIAL_FILE "/dev/tnt9"
#define FIFTH_SERIAL_BAUDRATE B115200
#define FIFTH_SERIAL_PARITY NO_PARITY
#define FIFTH_SERIAL_STOP_BITS ONE_STOP_BIT
#define FIFTH_LISTEN_PORT 1242
#define FIFTH_SEND_PORT 1243
#endif

#ifdef SIXTH_PAIR
#define SIXTH_SERIAL_FILE "/dev/tnt11"
#define SIXTH_SERIAL_BAUDRATE B115200
#define SIXTH_SERIAL_PARITY NO_PARITY
#define SIXTH_SERIAL_STOP_BITS ONE_STOP_BIT
#define SIXTH_LISTEN_PORT 1244
#define SIXTH_SEND_PORT 1245
#endif

void die(const char *s);
static int make_socket_non_blocking (int sfd);

int main(void)
{
    cout << "***** SERIAL PORT SERVER *****" << endl << endl;


    const int lenght_ofAdressStruct = sizeof(sockaddr_in);

#ifdef FIRST_PAIR
    //FIRST SERIAL PORT ******************************************
    int first_serial_fd;
    ssize_t first_rozmiarOdebranychDanych = 0;
    unsigned char first_serial_rx_buffer[BUFLEN];
    initConnection(first_serial_fd, FIRST_SERIAL_FILE, FIRST_SERIAL_BAUDRATE,FIRST_SERIAL_PARITY,FIRST_SERIAL_STOP_BITS);

    //FIRST SOCKET ************************************************
    struct sockaddr_in first_listenAddress, first_sendAddress;

    int first_socket_fd, first_recv_len;

    char first_socket_rx_buffer[BUFLEN];

    if ((first_socket_fd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
        die("socket");
    }else{
        cout << "Sucessfull created socket First" << endl;
    }

    memset((char *) &first_sendAddress, 0, sizeof(first_sendAddress));
    first_sendAddress.sin_family = AF_INET;
    first_sendAddress.sin_port = htons(FIRST_SEND_PORT);
    if (inet_aton(CLIENT_IP , &first_sendAddress.sin_addr) == 0) {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    memset((char *) &first_listenAddress, 0, sizeof(first_listenAddress));
    first_listenAddress.sin_family = AF_INET;
    first_listenAddress.sin_port = htons(FIRST_LISTEN_PORT);
    first_listenAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    if(make_socket_non_blocking (first_socket_fd) == -1){
        abort ();
    }

    if( bind(first_socket_fd , (struct sockaddr*)&first_listenAddress, sizeof(first_listenAddress) ) == -1){
        die("bind");
    }

#endif

#ifdef SECOND_PAIR
    //SECOND SERIAL PORT ******************************************
    int second_serial_fd;
    ssize_t second_rozmiarOdebranychDanych = 0;
    unsigned char second_serial_rx_buffer[BUFLEN];
    initConnection(second_serial_fd, SECOND_SERIAL_FILE, SECOND_SERIAL_BAUDRATE,SECOND_SERIAL_PARITY,SECOND_SERIAL_STOP_BITS);

    //SECOND SOCKET ************************************************
    struct sockaddr_in second_listenAddress, second_sendAddress;

    int second_socket_fd, second_recv_len;

    char second_socket_rx_buffer[BUFLEN];

    if ((second_socket_fd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
        die("socket");
    }else{
        cout << "Sucessfull created socket Second" << endl;
    }

    memset((char *) &second_sendAddress, 0, sizeof(second_sendAddress));
    second_sendAddress.sin_family = AF_INET;
    second_sendAddress.sin_port = htons(SECOND_SEND_PORT);
    if (inet_aton(CLIENT_IP , &second_sendAddress.sin_addr) == 0) {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    memset((char *) &second_listenAddress, 0, sizeof(second_listenAddress));
    second_listenAddress.sin_family = AF_INET;
    second_listenAddress.sin_port = htons(SECOND_LISTEN_PORT);
    second_listenAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    if(make_socket_non_blocking (second_socket_fd) == -1){
        abort ();
    }

    if( bind(second_socket_fd , (struct sockaddr*)&second_listenAddress, sizeof(second_listenAddress) ) == -1){
        die("bind");
    }
#endif

#ifdef THIRD_PAIR
    //THIRD SERIAL PORT ******************************************
    int third_serial_fd;
    ssize_t third_rozmiarOdebranychDanych = 0;
    unsigned char third_serial_rx_buffer[BUFLEN];
    initConnection(third_serial_fd, THIRD_SERIAL_FILE, THIRD_SERIAL_BAUDRATE,THIRD_SERIAL_PARITY,THIRD_SERIAL_STOP_BITS);

    //THIRD SOCKET ************************************************
    struct sockaddr_in third__listenAddress, third_sendAddress;

    int third_socket_fd, third_recv_len;

    char third_socket_rx_buffer[BUFLEN];

    if ((third_socket_fd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
        die("socket");
    }else{
        cout << "Sucessfull created socket Third" << endl;
    }

    memset((char *) &third_sendAddress, 0, sizeof(third_sendAddress));
    third_sendAddress.sin_family = AF_INET;
    third_sendAddress.sin_port = htons(THIRD_SEND_PORT);
    if (inet_aton(CLIENT_IP , &third_sendAddress.sin_addr) == 0) {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    memset((char *) &third__listenAddress, 0, sizeof(third__listenAddress));
    third__listenAddress.sin_family = AF_INET;
    third__listenAddress.sin_port = htons(THIRD_LISTEN_PORT);
    third__listenAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    if(make_socket_non_blocking (third_socket_fd) == -1){
        abort ();
    }

    if( bind(third_socket_fd , (struct sockaddr*)&third__listenAddress, sizeof(third__listenAddress) ) == -1){
        die("bind");
    }
#endif

#ifdef FOURTH_PAIR
    //FOURTH SERIAL PORT ******************************************
    int fourth_serial_fd;
    ssize_t fourth_rozmiarOdebranychDanych = 0;
    unsigned char fourth_serial_rx_buffer[BUFLEN];
    initConnection(fourth_serial_fd, FOURTH_SERIAL_FILE, FOURTH_SERIAL_BAUDRATE,FOURTH_SERIAL_PARITY,FOURTH_SERIAL_STOP_BITS);

    //FOURTH SOCKET ************************************************
    struct sockaddr_in fourth_listenAddress, fourth_sendAddress;

    int fourth_socket_fd, fourth_recv_len;

    char fourth_socket_rx_buffer[BUFLEN];

    if ((fourth_socket_fd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
        die("socket");
    }else{
        cout << "Sucessfull created socket Fourth" << endl;
    }

    memset((char *) &fourth_sendAddress, 0, sizeof(fourth_sendAddress));
    fourth_sendAddress.sin_family = AF_INET;
    fourth_sendAddress.sin_port = htons(FOURTH_SEND_PORT);
    if (inet_aton(CLIENT_IP , &fourth_sendAddress.sin_addr) == 0) {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    memset((char *) &fourth_listenAddress, 0, sizeof(fourth_listenAddress));
    fourth_listenAddress.sin_family = AF_INET;
    fourth_listenAddress.sin_port = htons(FOURTH_LISTEN_PORT);
    fourth_listenAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    if(make_socket_non_blocking (fourth_socket_fd) == -1){
        abort ();
    }

    if( bind(fourth_socket_fd , (struct sockaddr*)&fourth_listenAddress, sizeof(fourth_listenAddress) ) == -1){
        die("bind");
    }
#endif

#ifdef FIFTH_PAIR
    //FIFTH SERIAL PORT ******************************************
    int fifth_serial_fd;
    ssize_t fifth_rozmiarOdebranychDanych = 0;
    unsigned char fifth_serial_rx_buffer[BUFLEN];
    initConnection(fifth_serial_fd, FIFTH_SERIAL_FILE, FIFTH_SERIAL_BAUDRATE,FIFTH_SERIAL_PARITY,FIFTH_SERIAL_STOP_BITS);

    //FIFTH SOCKET ************************************************
    struct sockaddr_in fifth__listenAddress, fifth_sendAddress;

    int fifth_socket_fd, fifth_recv_len;

    char fifth_socket_rx_buffer[BUFLEN];

    if ((fifth_socket_fd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
        die("socket");
    }else{
        cout << "Sucessfull created socket Fifth" << endl;
    }

    memset((char *) &fifth_sendAddress, 0, sizeof(fifth_sendAddress));
    fifth_sendAddress.sin_family = AF_INET;
    fifth_sendAddress.sin_port = htons(FIFTH_SEND_PORT);
    if (inet_aton(CLIENT_IP , &fifth_sendAddress.sin_addr) == 0) {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    memset((char *) &fifth__listenAddress, 0, sizeof(fifth__listenAddress));
    fifth__listenAddress.sin_family = AF_INET;
    fifth__listenAddress.sin_port = htons(FIFTH_LISTEN_PORT);
    fifth__listenAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    if(make_socket_non_blocking (fifth_socket_fd) == -1){
        abort ();
    }

    if( bind(fifth_socket_fd , (struct sockaddr*)&fifth__listenAddress, sizeof(fifth__listenAddress) ) == -1){
        die("bind");
    }
#endif

#ifdef SIXTH_PAIR
    //SIXTH SERIAL PORT ******************************************
    int sixth_serial_fd;
    ssize_t sixth_rozmiarOdebranychDanych = 0;
    unsigned char sixth_serial_rx_buffer[BUFLEN];
    initConnection(sixth_serial_fd, SIXTH_SERIAL_FILE, SIXTH_SERIAL_BAUDRATE,SIXTH_SERIAL_PARITY,SIXTH_SERIAL_STOP_BITS);

    //SIXTH SOCKET ************************************************
    struct sockaddr_in sixth_listenAddress, sixth_sendAddress;

    int sixth_socket_fd, sixth_recv_len;

    char sixth_socket_rx_buffer[BUFLEN];

    if ((sixth_socket_fd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
        die("socket");
    }else{
        cout << "Sucessfull created socket sixth" << endl;
    }

    memset((char *) &sixth_sendAddress, 0, sizeof(sixth_sendAddress));
    sixth_sendAddress.sin_family = AF_INET;
    sixth_sendAddress.sin_port = htons(SIXTH_SEND_PORT);
    if (inet_aton(CLIENT_IP , &sixth_sendAddress.sin_addr) == 0) {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    memset((char *) &sixth_listenAddress, 0, sizeof(sixth_listenAddress));
    sixth_listenAddress.sin_family = AF_INET;
    sixth_listenAddress.sin_port = htons(SIXTH_LISTEN_PORT);
    sixth_listenAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    if(make_socket_non_blocking (sixth_socket_fd) == -1){
        abort ();
    }

    if( bind(sixth_socket_fd , (struct sockaddr*)&sixth_listenAddress, sizeof(sixth_listenAddress) ) == -1){
        die("bind");
    }
#endif

    //EPOLL ************************************************
    int epollfd, number_of_file_descriptors;

#define MAX_EVENTS 10
    struct epoll_event events[MAX_EVENTS];

    epollfd = epoll_create1(0);
    if (epollfd == -1) {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

#ifdef FIRST_PAIR
    struct epoll_event first_serial_ev;
    first_serial_ev.events = EPOLLIN;
    first_serial_ev.data.fd = first_serial_fd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, first_serial_fd, &first_serial_ev) == -1) {
        perror("Error adding first serial to epoll");
        exit(EXIT_FAILURE);
    }else{
        cout << "Sucessfull adding first serial to epoll" << endl;
    }

    struct epoll_event first_socket_ev;
    first_socket_ev.events = EPOLLIN;
    first_socket_ev.data.fd = first_socket_fd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, first_socket_fd, &first_socket_ev) == -1) {
        perror("Error adding first socket to epoll");
        exit(EXIT_FAILURE);
    }else{
        cout << "Sucessfull adding first socket to epoll" << endl;
    }
#endif

#ifdef SECOND_PAIR
    struct epoll_event second_serial_ev;
    second_serial_ev.events = EPOLLIN;
    second_serial_ev.data.fd = second_serial_fd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, second_serial_fd, &second_serial_ev) == -1) {
        perror("Error adding second serial to epoll");
        exit(EXIT_FAILURE);
    }else{
        cout << "Sucessfull adding second serial to epoll" << endl;
    }

    struct epoll_event second_socket_ev;
    second_socket_ev.events = EPOLLIN;
    second_socket_ev.data.fd = second_socket_fd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, second_socket_fd, &second_socket_ev) == -1) {
        perror("Error adding second socket to epoll");
        exit(EXIT_FAILURE);
    }else{
        cout << "Sucessfull adding second socket to epoll" << endl;
    }
#endif

#ifdef THIRD_PAIR
    struct epoll_event third_serial_ev;
    third_serial_ev.events = EPOLLIN;
    third_serial_ev.data.fd = third_serial_fd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, third_serial_fd, &third_serial_ev) == -1) {
        perror("Error adding third serial to epoll");
        exit(EXIT_FAILURE);
    }else{
        cout << "Sucessfull adding third serial to epoll" << endl;
    }

    struct epoll_event third_socket_ev;
    third_socket_ev.events = EPOLLIN;
    third_socket_ev.data.fd = third_socket_fd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, third_socket_fd, &third_socket_ev) == -1) {
        perror("Error adding third socket to epoll");
        exit(EXIT_FAILURE);
    }else{
        cout << "Sucessfull adding third socket to epoll" << endl;
    }
#endif

#ifdef FOURTH_PAIR
    struct epoll_event fourth_serial_ev;
    fourth_serial_ev.events = EPOLLIN;
    fourth_serial_ev.data.fd = fourth_serial_fd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, fourth_serial_fd, &fourth_serial_ev) == -1) {
        perror("Error adding fourth serial to epoll");
        exit(EXIT_FAILURE);
    }else{
        cout << "Sucessfull adding fourth serial to epoll" << endl;
    }

    struct epoll_event fourth_socket_ev;
    fourth_socket_ev.events = EPOLLIN;
    fourth_socket_ev.data.fd = fourth_socket_fd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, fourth_socket_fd, &fourth_socket_ev) == -1) {
        perror("Error adding fourth socket to epoll");
        exit(EXIT_FAILURE);
    }else{
        cout << "Sucessfull adding fourth socket to epoll" << endl;
    }
#endif

#ifdef FIFTH_PAIR
    struct epoll_event fifth_serial_ev;
    fifth_serial_ev.events = EPOLLIN;
    fifth_serial_ev.data.fd = fifth_serial_fd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, fifth_serial_fd, &fifth_serial_ev) == -1) {
        perror("Error adding fifth serial to epoll");
        exit(EXIT_FAILURE);
    }else{
        cout << "Sucessfull adding fifth serial to epoll" << endl;
    }

    struct epoll_event fifth_socket_ev;
    fifth_socket_ev.events = EPOLLIN;
    fifth_socket_ev.data.fd = fifth_socket_fd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, fifth_socket_fd, &fifth_socket_ev) == -1) {
        perror("Error adding fifth socket to epoll");
        exit(EXIT_FAILURE);
    }else{
        cout << "Sucessfull adding fifth socket to epoll" << endl;
    }
#endif

#ifdef SIXTH_PAIR
    struct epoll_event sixth_serial_ev;
    sixth_serial_ev.events = EPOLLIN;
    sixth_serial_ev.data.fd = sixth_serial_fd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sixth_serial_fd, &sixth_serial_ev) == -1) {
        perror("Error adding sixth serial to epoll");
        exit(EXIT_FAILURE);
    }else{
        cout << "Sucessfull adding sixth serial to epoll" << endl;
    }

    struct epoll_event sixth_socket_ev;
    sixth_socket_ev.events = EPOLLIN;
    sixth_socket_ev.data.fd = sixth_socket_fd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sixth_socket_fd, &sixth_socket_ev) == -1) {
        perror("Error adding sixth socket to epoll");
        exit(EXIT_FAILURE);
    }else{
        cout << "Sucessfull adding sixth socket to epoll" << endl;
    }
#endif


    static int ret_val = 0;
    static int idx = 0;
    //*******************************************************
    for(;;) {
        number_of_file_descriptors = epoll_wait(epollfd, events, MAX_EVENTS, -1);
#ifdef DEBUG_MAIN_LOOP
        cout << idx++ << " epoll_wait = " << number_of_file_descriptors << endl;
#endif
        if (number_of_file_descriptors == -1) {
#ifdef DEBUG_MAIN_LOOP
            perror("epoll_wait");
#endif
            exit(EXIT_FAILURE);
        }else if(number_of_file_descriptors == 0){
            //cout << "epoll_wait timeout" << endl;
        }else if(number_of_file_descriptors > 0){

            for (int n = 0; n < number_of_file_descriptors; ++n) {
#ifdef FIRST_PAIR
                if (events[n].data.fd == first_serial_fd) {
#ifdef DEBUG_MAIN_LOOP
                    cout << "Parse first_serial_fd event" << endl;
#endif
                    first_rozmiarOdebranychDanych = read( first_serial_fd, &first_serial_rx_buffer, BUFLEN);
                    if(first_rozmiarOdebranychDanych > 0){
                        if (sendto(first_socket_fd, first_serial_rx_buffer, first_rozmiarOdebranychDanych, 0, (struct sockaddr*) &first_sendAddress, lenght_ofAdressStruct) == -1){
                            die("sendto()");
                        }
                    }
                    continue;
                }
                if (events[n].data.fd == first_socket_fd) {
#ifdef DEBUG_MAIN_LOOP
                    cout << "Parse first_socket event" << endl;
#endif
                    first_recv_len = recvfrom(first_socket_fd, first_socket_rx_buffer, BUFLEN, 0, NULL, NULL);
#ifdef DEBUG_MAIN_LOOP
                    cout << "   Read data from socket_fd = " << first_socket_fd << " with resul = " << first_recv_len << endl;
#endif
                    if(first_recv_len == -1){
                        //cout << "Read Error " << endl;
                        int errsv = errno;
                        if(errsv == EAGAIN){
                            //cout << "EAGAIN" << endl;
                        }else if(errsv == EWOULDBLOCK){
                            //cout << "EWOULDBLOCK" << endl;
                        }else{
                            die("recvfrom()");
                        }
                    }else{
                        //cout << "Received data from socket" << endl;
                        //printf("Received packet from %s:%d\n", inet_ntoa(second_si_other.sin_addr), ntohs(second_si_other.sin_port));

                        ret_val = write(first_serial_fd, first_socket_rx_buffer, first_recv_len);
#ifdef DEBUG_MAIN_LOOP
                        cout << "   Write data to serial_fd = " << first_serial_fd << " with result = " << ret_val << endl;
#endif
                    }
                    continue;
                }
#endif
#ifdef SECOND_PAIR
                if (events[n].data.fd == second_serial_fd) {
#ifdef DEBUG_MAIN_LOOP
                    cout << "Parse second_serial_fd event" << endl;
#endif
                    second_rozmiarOdebranychDanych = read( second_serial_fd, &second_serial_rx_buffer, BUFLEN);
                    if(second_rozmiarOdebranychDanych > 0){
                        if (sendto(second_socket_fd, second_serial_rx_buffer, second_rozmiarOdebranychDanych, 0, (struct sockaddr*) &second_sendAddress, lenght_ofAdressStruct) == -1){
                            die("sendto()");
                        }

                    }
                    continue;
                }
                if (events[n].data.fd == second_socket_fd) {
#ifdef DEBUG_MAIN_LOOP
                    cout << "Parse second_socket event" << endl;
#endif
                    second_recv_len = recvfrom(second_socket_fd, second_socket_rx_buffer, BUFLEN, 0, NULL, NULL);
#ifdef DEBUG_MAIN_LOOP
                    cout << "   Read data from socket_fd = " << second_socket_fd << " with resul = " << second_recv_len << endl;
#endif
                    if(second_recv_len == -1)
                    {
                        //cout << "Read Error " << endl;
                        int errsv = errno;
                        if(errsv == EAGAIN){
                            //cout << "EAGAIN" << endl;
                        }else if(errsv == EWOULDBLOCK){
                            //cout << "EWOULDBLOCK" << endl;
                        }else{
                            die("recvfrom()");
                        }
                    }else{
                        //printf("Received packet from %s:%d\n", inet_ntoa(second_si_other.sin_addr), ntohs(second_si_other.sin_port));
                        ret_val = write(second_serial_fd, second_socket_rx_buffer, second_recv_len);
#ifdef DEBUG_MAIN_LOOP
                        cout << "   Write data to serial_fd = " << second_serial_fd << " with result = " << ret_val << endl;
#endif
                    }
                    continue;
                }
#endif
#ifdef THIRD_PAIR
                if (events[n].data.fd == third_serial_fd) {
#ifdef DEBUG_MAIN_LOOP
                    cout << "Parse third_serial_fd event" << endl;
#endif
                    third_rozmiarOdebranychDanych = read( third_serial_fd, &third_serial_rx_buffer, BUFLEN);
                    if(third_rozmiarOdebranychDanych > 0){
                        if (sendto(third_socket_fd, third_serial_rx_buffer, third_rozmiarOdebranychDanych, 0, (struct sockaddr*) &third_sendAddress, lenght_ofAdressStruct) == -1){
                            die("sendto()");
                        }

                    }
                    continue;
                }
                if (events[n].data.fd == third_socket_fd) {
#ifdef DEBUG_MAIN_LOOP
                    cout << "Parse third_socket event" << endl;
#endif
                    third_recv_len = recvfrom(third_socket_fd, third_socket_rx_buffer, BUFLEN, 0, NULL, NULL);
#ifdef DEBUG_MAIN_LOOP
                    cout << "   Read data from socket_fd = " << third_socket_fd << " with resul = " << third_recv_len << endl;
#endif
                    if(third_recv_len == -1)
                    {
                        //cout << "Read Error " << endl;
                        int errsv = errno;
                        if(errsv == EAGAIN){
                            //cout << "EAGAIN" << endl;
                        }else if(errsv == EWOULDBLOCK){
                            //cout << "EWOULDBLOCK" << endl;
                        }else{
                            die("recvfrom()");
                        }
                    }else{
                        //printf("Received packet from %s:%d\n", inet_ntoa(third_si_other.sin_addr), ntohs(third_si_other.sin_port));
                        ret_val = write(third_serial_fd, third_socket_rx_buffer, third_recv_len);
#ifdef DEBUG_MAIN_LOOP
                        cout << "   Write data to serial_fd = " << third_serial_fd << " with result = " << ret_val << endl;
#endif
                    }
                    continue;
                }
#endif
#ifdef FOURTH_PAIR
                if (events[n].data.fd == fourth_serial_fd) {
#ifdef DEBUG_MAIN_LOOP
                    cout << "Parse fourth_serial_fd event" << endl;
#endif
                    fourth_rozmiarOdebranychDanych = read( fourth_serial_fd, &fourth_serial_rx_buffer, BUFLEN);
                    if(fourth_rozmiarOdebranychDanych > 0){
                        if (sendto(fourth_socket_fd, fourth_serial_rx_buffer, fourth_rozmiarOdebranychDanych, 0, (struct sockaddr*) &fourth_sendAddress, lenght_ofAdressStruct) == -1){
                            die("sendto()");
                        }

                    }
                    continue;
                }
                if (events[n].data.fd == fourth_socket_fd) {
#ifdef DEBUG_MAIN_LOOP
                    cout << "Parse fourth_socket event" << endl;
#endif
                    fourth_recv_len = recvfrom(fourth_socket_fd, fourth_socket_rx_buffer, BUFLEN, 0, NULL, NULL);
#ifdef DEBUG_MAIN_LOOP
                    cout << "   Read data from socket_fd = " << fourth_socket_fd << " with resul = " << fourth_recv_len << endl;
#endif
                    if(fourth_recv_len == -1)
                    {
                        //cout << "Read Error " << endl;
                        int errsv = errno;
                        if(errsv == EAGAIN){
                            //cout << "EAGAIN" << endl;
                        }else if(errsv == EWOULDBLOCK){
                            //cout << "EWOULDBLOCK" << endl;
                        }else{
                            die("recvfrom()");
                        }
                    }else{
                        //printf("Received packet from %s:%d\n", inet_ntoa(fourth_si_other.sin_addr), ntohs(fourth_si_other.sin_port));
                        ret_val = write(fourth_serial_fd, fourth_socket_rx_buffer, fourth_recv_len);
#ifdef DEBUG_MAIN_LOOP
                        cout << "   Write data to serial_fd = " << fourth_serial_fd << " with result = " << ret_val << endl;
#endif
                    }
                    continue;
                }
#endif
#ifdef FIFTH_PAIR
                if (events[n].data.fd == fifth_serial_fd) {
#ifdef DEBUG_MAIN_LOOP
                    cout << "Parse fifth_serial_fd event" << endl;
#endif
                    fifth_rozmiarOdebranychDanych = read( fifth_serial_fd, &fifth_serial_rx_buffer, BUFLEN);
                    if(fifth_rozmiarOdebranychDanych > 0){
                        if (sendto(fifth_socket_fd, fifth_serial_rx_buffer, fifth_rozmiarOdebranychDanych, 0, (struct sockaddr*) &fifth_sendAddress, lenght_ofAdressStruct) == -1){
                            die("sendto()");
                        }

                    }
                    continue;
                }
                if (events[n].data.fd == fifth_socket_fd) {
#ifdef DEBUG_MAIN_LOOP
                    cout << "Parse fifth_socket event" << endl;
#endif
                    fifth_recv_len = recvfrom(fifth_socket_fd, fifth_socket_rx_buffer, BUFLEN, 0, NULL, NULL);
#ifdef DEBUG_MAIN_LOOP
                    cout << "   Read data from socket_fd = " << fifth_socket_fd << " with resul = " << fifth_recv_len << endl;
#endif
                    if(fifth_recv_len == -1)
                    {
                        //cout << "Read Error " << endl;
                        int errsv = errno;
                        if(errsv == EAGAIN){
                            //cout << "EAGAIN" << endl;
                        }else if(errsv == EWOULDBLOCK){
                            //cout << "EWOULDBLOCK" << endl;
                        }else{
                            die("recvfrom()");
                        }
                    }else{
                        //printf("Received packet from %s:%d\n", inet_ntoa(fifth_si_other.sin_addr), ntohs(fifth_si_other.sin_port));
                        ret_val = write(fifth_serial_fd, fifth_socket_rx_buffer, fifth_recv_len);
#ifdef DEBUG_MAIN_LOOP
                        cout << "   Write data to serial_fd = " << fifth_serial_fd << " with result = " << ret_val << endl;
#endif
                    }
                    continue;
                }
#endif

#ifdef SIXTH_PAIR
                if (events[n].data.fd == sixth_serial_fd) {
#ifdef DEBUG_MAIN_LOOP
                    cout << "Parse sixth_serial_fd event" << endl;
#endif
                    sixth_rozmiarOdebranychDanych = read( sixth_serial_fd, &sixth_serial_rx_buffer, BUFLEN);
                    if(sixth_rozmiarOdebranychDanych > 0){
                        if (sendto(sixth_socket_fd, sixth_serial_rx_buffer, sixth_rozmiarOdebranychDanych, 0, (struct sockaddr*) &sixth_sendAddress, lenght_ofAdressStruct) == -1){
                            die("sendto()");
                        }

                    }
                    continue;
                }
                if (events[n].data.fd == sixth_socket_fd) {
#ifdef DEBUG_MAIN_LOOP
                    cout << "Parse sixth_socket event" << endl;
#endif
                    sixth_recv_len = recvfrom(sixth_socket_fd, sixth_socket_rx_buffer, BUFLEN, 0, NULL, NULL);
#ifdef DEBUG_MAIN_LOOP
                    cout << "   Read data from socket_fd = " << sixth_socket_fd << " with resul = " << sixth_recv_len << endl;
#endif
                    if(sixth_recv_len == -1)
                    {
                        //cout << "Read Error " << endl;
                        int errsv = errno;
                        if(errsv == EAGAIN){
                            //cout << "EAGAIN" << endl;
                        }else if(errsv == EWOULDBLOCK){
                            //cout << "EWOULDBLOCK" << endl;
                        }else{
                            die("recvfrom()");
                        }
                    }else{
                        //printf("Received packet from %s:%d\n", inet_ntoa(sixth_si_other.sin_addr), ntohs(sixth_si_other.sin_port));
                        ret_val = write(sixth_serial_fd, sixth_socket_rx_buffer, sixth_recv_len);
#ifdef DEBUG_MAIN_LOOP
                        cout << "   Write data to serial_fd = " << sixth_serial_fd << " with result = " << ret_val << endl;
#endif
                    }
                    continue;
                }
#endif
            }

        }
    }
#ifdef FIRST_PAIR
    close(first_socket_fd);
    close(first_serial_fd);
#endif
#ifdef SECOND_PAIR
    close(second_socket_fd);
    close(second_serial_fd);
#endif
#ifdef THIRD_PAIR
    close(third_socket_fd);
    close(third_serial_fd);
#endif
#ifdef FOURTH_PAIR
    close(fourth_socket_fd);
    close(fourth_serial_fd);
#endif
#ifdef FIFTH_PAIR
    close(fifth_socket_fd);
    close(fifth_serial_fd);
#endif
#ifdef SIXTH_PAIR
    close(sixth_socket_fd);
    close(sixth_serial_fd);
#endif
    return 0;
}


void die(const char *s)
{
    perror(s);
    exit(1);
}

static int make_socket_non_blocking (int sfd)
{
    int flags, s;

    flags = fcntl (sfd, F_GETFL, 0);
    if (flags == -1)
    {
        perror ("fcntl");
        return -1;
    }

    flags |= O_NONBLOCK;
    s = fcntl (sfd, F_SETFL, flags);
    if (s == -1)
    {
        perror ("fcntl");
        return -1;
    }

    return 0;
}


