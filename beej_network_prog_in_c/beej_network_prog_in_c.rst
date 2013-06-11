Beej's Network Programming in C
===============================

Socket is a way to speak to other programs using Unix file descriptors. Any I/O in Unix is done by reading/writing to a file descriptor (it is an integer associated with an open file).

Three kind of sockets -

- DARPA Internet addresses (Internet Sockets)
- Path names on a local node (Unix Sockets)
- CCITT X.25 addresses (X.25 Sockets)

We only care about the Internet Sockets.

Two types of Internet Sockets that we're going to use - ``SOCK_STREAM`` and ``SOCK_DGRAM``.

``SOCK_STREAM`` - Reliable two-way connected communication stream. They use TCP protocol which makes it reliable.

``SOCK_DGRAM`` - They are connectionless (no need to keep the two-way conn open) and unreliable. A datagram packet may or may not arrive at the destination, can be out of order, but if it arrives then it would be error-free. They use UDP (User Datagram Protocol). They are used because of much better speed since no track is kept whether the packet has arrived or is it in order.

**Example of how a SOCK_DGRAM packet is built**

[Ethernet[IP[UDP[TFTP[Data]]]]]

Data is wrapped in a header by first protocol (say TFTP), then whole thing is encapsulated by next protocol (UDP). Then by IP and finally by Physical layer. When another computer receives the packet, the hardware strips the Ethernet header, the kernel strips the IP and UDP headers, the TFTP program strips the TFTP header, and it finally has the data.

The network layer model in Unix -

- Application Layer (telnet, ftp, etc.)
- Host-to-Host Transport Layer (TCP, UDP)
- Internet Layer (IP and routing)
- Network Access Layer (Ethernet, wi-fi, etc.)



IPv6 and IPv6
-------------

IPv4 addresses are made up of 4 bytes (4 octets) in format ``A.B.C.D`` where A, B, C and D range from 0 to 255.

IPv6 addresses are made up of 128 bytes (eight chunks of 2 byte hexadecimal numbers separated by a colon).

Example - ``2001:0db8:c9d2:0012:0000:0000:0000:0051`` or ``2001:0db8:c9d2:12::51.``.

Addresses ``127.0.0.1`` (IPv4) and ``::1`` (IPv6) are loopback addresses which refers to the machine itself.


Subnets
-------

For organizational reasons, it's sometimes convenient to declare that “this first part of this IP address up through this bit is the network portion of the IP address, and the remainder is the host portion.

For instance, with IPv4, you might have ``192.0.2.12``, and we could say that the first three bytes (``192.0.2``) are the network and the last byte (``12``) was the host.

The network portion of the IP address is described by something called the netmask, which you bitwise-AND with the IP address to get the network number out of it. The netmask usually looks something like ``255.255.255.0``. (E.g. with that netmask, if your IP is ``192.0.2.12``, then your network is ``192.0.2.12`` AND ``255.255.255.0`` which gives ``192.0.2.0``)

There can even be netmasks such as ``255.255.255.252``, which is 30 bits of network, and 2 bits of host allowing for four hosts on the network. There is a better way to represent this. You just put a slash after the IP address, and then follow that by the number of network bits in decimal. Like this: ``192.0.2.12/30``.


Port Numbers
------------

Say you want to have a computer that handles incoming mail AND web services—how do you differentiate between the two on a computer with a single IP address? Well, different services on the Internet have different well-known port numbers. It's a 16-bit number.

HTTP (the web) is port 80, telnet is port 23, SMTP is port 25, the game DOOM13 used port 666, etc. and so on. Ports under 1024 are often considered special, and usually require special OS privileges to use.


Byte Order
----------

Suppose a hexadecimal number ``b34f``. Some computers (including Intex processors) store it in reverse order, ``4f`` followed by ``4f``. This ordering is called Little Endian. And the other way is called Big Endian. The order followed by a particular computer is called its **Host Byte Order**.

But there is a separate convention for networks called **Network Byte Order**. Only Big Endian is followed so the Little Endian machines first need to convert the data it wants to send to Big Endian format.

But how can you do this if you don't know the native Host Byte Order? Good news! You just get to assume the Host Byte Order isn't right, and you always run the value through a function to set it to Network Byte Order. The functions for convertion are -

- ``htons()`` **h**ost **to** **n**etwork **s**hort
- ``htonl()`` **h**ost **to** **n**etwork **l**ong
- ``ntohs()`` **n**etwork **to** **h**ost **s**hort
- ``ntohl()`` **n**etwork **to** **h**ost **l**ong

Basically, you'll want to convert the numbers to Network Byte Order before they go out on the wire, and convert them to Host Byte Order as they come in off the wire.


Check ``reference.c`` for the rest of the important structs and function prototypes for reference.
