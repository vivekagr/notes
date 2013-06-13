// This file contains the important structs and functions used for network programming in C.
// Taken from http://beej.us/guide/bgnet/


// This is the main struct which we get when calling getaddrinfo()

struct addrinfo {
    int              ai_flags;     // AI_PASSIVE, AI_CANONNAME, etc.
    int              ai_family;    // AF_INET, AF_INET6, AF_UNSPEC
    int              ai_socktype;  // SOCK_STREAM, SOCK_DGRAM
    int              ai_protocol;  // use 0 for "any"
    size_t           ai_addrlen;   // size of ai_addr in bytes
    struct sockaddr *ai_addr;      // struct sockaddr_in or _in6
    char            *ai_canonname; // full canonical hostname
    struct addrinfo *ai_next;      // linked list, next node
};

// ai_flags can be set to `AI_PASSIVE` to set it to assign the address of localhost
// ai_family can be set to `AF_UNSPEC` to be use whatever (IP-version agnostic)

// In the above struct, there is another struct `sockaddr`

struct sockaddr {
    unsigned short    sa_family;    // address family, AF_xxx
    char              sa_data[14];  // 14 bytes of protocol address
};

// sa_data contains a destination address and port number for the socket. This is rather unwieldy since you don't want to tediously pack the address in the sa_data by hand.

// To deal with struct sockaddr, programmers created a parallel structure: struct sockaddr_in (“in” for “Internet”) to be used with IPv4.

// A pointer to a struct sockaddr_in can be cast to a pointer to a struct sockaddr and vice-versa.

// (IPv4 only--see struct sockaddr_in6 for IPv6)
struct sockaddr_in {
    short int          sin_family;  // Address family, AF_INET
    unsigned short int sin_port;    // Port number
    struct in_addr     sin_addr;    // Internet address
    unsigned char      sin_zero[8]; // Same size as struct sockaddr
};

// Now this contains yet another struct sin_addr

// Internet address (a structure for historical reasons)
struct in_addr {
    uint32_t s_addr; // that's a 32-bit int (4 bytes) in Network Byte Order
};

// Now the IPv6 versions

struct sockaddr_in6 {
    u_int16_t       sin6_family;   // address family, AF_INET6
    u_int16_t       sin6_port;     // port number, Network Byte Order
    u_int32_t       sin6_flowinfo; // IPv6 flow information
    struct in6_addr sin6_addr;     // IPv6 address
    u_int32_t       sin6_scope_id; // Scope ID
};

struct in6_addr {
    unsigned char   s6_addr[16];   // IPv6 address
};

// Struct sockaddr_storage that is designed to be large enough to hold both IPv4 and IPv6 structures.

struct sockaddr_storage {
    sa_family_t  ss_family;     // address family
    // all this is padding, implementation specific, ignore it:
    char      __ss_pad1[_SS_PAD1SIZE];
    int64_t   __ss_align;
    char      __ss_pad2[_SS_PAD2SIZE];
};

// What's important is that you can see the address family in the ss_family field—check this to see if it's AF_INET or AF_INET6 (for IPv4 or IPv6). Then you can cast it to a struct sockaddr_in or struct sockaddr_in6 if you wanna.

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

// Filling in the IP address into ``sockaddr_in`` with function
// inet_pton means presentation to network

struct sockaddr_in sa; // IPv4
struct sockaddr_in6 sa6; // IPv6

inet_pton(AF_INET, "192.0.2.1", &(sa.sin_addr)); // IPv4
inet_pton(AF_INET6, "2001:db8:63b3:1::3490", &(sa6.sin6_addr)); // IPv6

// Getting IP address string from ``sockaddr_in``
// Two macros conveniently hold the size of the string you'll need
// to hold the largest IPv4 or IPv6 address: INET_ADDRSTRLEN and INET6_ADDRSTRLEN.

// IPv4
char ip4[INET_ADDRSTRLEN];  // space to hold the IPv4 string
struct sockaddr_in sa;      // pretend this is loaded with something
inet_ntop(AF_INET, &(sa.sin_addr), ip4, INET_ADDRSTRLEN);
printf("The IPv4 address is: %s\n", ip4);

// IPv6:
char ip6[INET6_ADDRSTRLEN]; // space to hold the IPv6 string
struct sockaddr_in6 sa6;    // pretend this is loaded with something
inet_ntop(AF_INET6, &(sa6.sin6_addr), ip6, INET6_ADDRSTRLEN);
printf("The address is: %s\n", ip6);

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

// getaddrinfo() prototype
// this returns any error as a non-zero value
// the error message can be fetched as string by passing the value to gai_strerror()

int getaddrinfo(const char *node,     // e.g. "www.example.com" or IP
                const char *service,  // e.g. "http" or port number
                const struct addrinfo *hints, // either NULL or an addrinfo structure with the relevant information
                struct addrinfo **res); // pointer that will point to a new addrinfo structure with the information requested



// socket() prototype
// used no matter we are the client or server
// returns a socket descriptor that can be used in later system calls
// returns -1 on error and global variable errno is set to error's value

int socket(int domain, int type, int protocol);

sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol); // example call



// bind() prototype
// used when we want to bind at a certain port number (and listen in future)
// returns -1 on error and global variable errno is set to error's value

int bind(int sockfd, struct sockaddr *my_addr, int addrlen);

bind(sockfd, res->ai_addr, res->ai_addrlen); // example call



// connect() prototype
// used when we are the client need to connect to remote host
// returns -1 on error and global variable errno is set to error's value

int connect(int sockfd, struct sockaddr *serv_addr, int addrlen);

connect(sockfd, res->ai_addr, res->ai_addrlen); // example call



// listen() prototype
// used when we want to listen to the incoming connections
// bind() needs to be called before listen()ing so that the server is running on a specific port
// returns -1 on error and global variable errno is set to error's value
// backlog is the number of connections allowed on the incoming queue

int listen(int sockfd, int backlog);



// accept() prototype
// used to accept the connections that we are listening with listen()
// returns -1 on error and global variable errno is set to error's value
// It'll return to you a brand new socket file descriptor to use for this single connection!
// This socket file descriptor will be used for sending and receiving data
// addr will usually be a pointer to a local struct sockaddr_storage
// addr is where the information about the incoming connection will go
// addrlen is a pointer to local integer variable that should be set to sizeof(struct sockaddr_storage)


int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

// example
struct sockaddr_storage their_addr;
socklen_t addr_size = sizeof their_addr;
int new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);



// send() and recv()
// for communicating over stream sockets or connected datagram sockets

// send() prototype
// sockfd is the socket file descriptor which we got from accept()
// msg is a pointer to the data you want to send
// len is the length of that data in bytes
// just set flags to 0
// returns the number of bytes actually sent out—this might be less than the number you told it to send!
// it'll fire off as much of the data as it can, and trust you to send the rest later
// if the value returned by send() doesn't match the value in len, it's up to you to send the rest of the string
// returns -1 on error and global variable errno is set to error's value

int send(int sockfd, const void *msg, int len, int flags);


// recv() prototype
// sockfd is the socket file descriptor which we got from accept()
// buf is the buffer to read the information into
// len is the maximum length of the buffer
// set flag to 0
// returns the number of bytes actually read into the buffer
// if the return value is 0, the remote side has closed the connection on you! D:
// returns -1 on error and global variable errno is set to error's value

int recv(int sockfd, void *buf, int len, int flags);



// sendto() and recvfrom()
// used for unconnected datagram sockets
// since its unconnected, we need to specify the destination address


// sendto() prototype
// basically the same as the call to send() with the addition of two other pieces of information
// to is a pointer to a struct sockaddr which contains the destination IP address and port
// tolen, an int deep-down, can simply be set tosizeof *toorsizeof(struct sockaddr_storage)
// To get your hands on the destination address structure, you'll probably either get it from getaddrinfo(), or from recvfrom(), below, or you'll fill it out by hand.
// just like with send(), sendto() returns the number of bytes actually sent
// returns -1 on error and global variable errno is set to error's value

int sendto(int sockfd, const void *msg, int len, unsigned int flags,
           const struct sockaddr *to, socklen_t tolen);


// recvfrom() prototype
// from is a pointer to a local struct sockaddr_storage that will be
// filled with the IP address and port of the originating machine
// fromlen is a pointer to a local int that should be initialized to sizeof *from or sizeof(struct sockaddr_storage)
// when the function returns, fromlen will contain the length of the address actually stored in from
// returns the number of bytes received, or -1 on error (with errno set accordingly.)

int recvfrom(int sockfd, void *buf, int len, unsigned int flags,
             struct sockaddr *from, int *fromlen);


// Why do we use struct sockaddr_storage as the socket type? Why not struct sockaddr_in? Because, you see, we want to not tie ourselves down to IPv4 or IPv6. So we use the generic struct sockaddr_storage which we know will be big enough for either.

// If you connect() a datagram socket, you can then simply use send() and recv() for all your transactions. The socket itself is still a datagram socket and the packets still use UDP, but the socket interface will automatically add the destination and source information for you.



// close()
// used to to close the connection on your socket descriptor
// this will prevent any more reads and writes to the socket. anyone attempting to read or write the socket on the remote end will receive an error.

close(sockfd);



// shutdown()
// provides a little more control than close()
// how can be 0 (further receives disallowed), 1 (further sends disallowed),
// 2 (further receives and sends are disallowed, just like close())
// return 0 on success and 1 on error (with errno set accordingly.)
// It's important to note that shutdown() doesn't actually close the file descriptor—it just changes its usability. To free a socket descriptor, you need to use close().

int shutdown(int sockfd, int how);



// getpeername()
// provides information about who is connected on the end of a stream socket
// sockfd is the descriptor of the connected stream socket,
// addr is a pointer to a struct sockaddr that will hold the information about the other side of the connection
// addrlen is a pointer to an int, that should be initialized to sizeof *addr or sizeof(struct sockaddr)
// returns -1 on error and sets errno accordingly


int getpeername(int sockfd, struct sockaddr *addr, int *addrlen);

// Once you have their address, you can use inet_ntop(), getnameinfo(), or gethostbyaddr() to print or get more information.




// gethostname()
// used to get the name of the computer that your program is running on
// hostname is a pointer to an array of chars that will contain the hostname upon the function's return
// size is the length in bytes of the hostname array
// returns 0 on successful completion, and -1 on error, setting errno as usual

int gethostname(char *hostname, size_t size);




// select() - synchronous i/o multiplexing
// used for listening as well as reading from the open connections
// gives you the power to monitor several sockets at the same time
// it'll tell you which ones are ready for reading, which are ready for writing, and which sockets have raised exceptions
// numfds should be set to the values of the highest file descriptor plus one
// returns 0 on successful completion, and -1 on error, setting errno as usual

int select(int numfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);

// Following are the function used to manupulate sets

FD_SET(int fd, fd_set *set);    // Add fd to the set
FD_CLR(int fd, fd_set *set);    // Remove fd from the set
FD_ISSET(int fd, fd_set *set);  // Return true if fd in set
FD_ZERO(fd_set *set);           // Clear all entries from set

