class IPv4
{
	//function
	provides packets delivery function for_ TCP \ UDP \ SCTP \ ICMP \ IGMP


};

class IPv6
{
	//funciton
	provides packet delivery service for_ TCP UDP SCTP ICMPv6
};

class TCP
{

	it can use either IPv4 IPv6

	//features
	1 ConnectionOriented
	2 reliability
	3 ByteStream with sequences
	4 FlowControl
	5 FullDuplex
	//related
	UDP

	//usage
	ByteStream ---> TCPSegment---> IPDataGram	

	//related
	TCPConnection
	TCPOptions
};


class TCPOptions
{
	1 MSS
	2 WindowScale
	3 Time Stamp

};



class MSS
{
	aka MaximumSegmentSize
	//properties
	the maximum amount of data it is willing to accept in a TCPSegment
	the sender uses the receiver`s MSS value

	//goal
	to avoid Fragmentation
		usually set to MTU - sizeof(IPv4DataGramHeader) - sizeof(TCPHeader)

};

typedef MSS MaximumSegmentSize;

class TCPConnection
{
	identified by a SocketPair

	
	//related
	TCPConnectionEstablishment
	TCPConnectionTermination

	SCTPConnection
};

class TCPConnectionEstablishment
{
	//related
	ThreeWayHandShake

};

class ThreeWayHandShake
{
	//process
	1 client connect called		--->		server accept called
	2 client connect returns	<---		server accept called
	3 client connect returns	--->		server accept returns
};

class PassiveOpen
{
	//done by server calling 
	socket --> bind --> listen

	//related
	ActiveOpen
};

class ActiveOpen
{
	//done by client calling
	connect

	//related
	PassiveOpen
};

int socket(int family, int type, int protocol)
{
	//analogy
	having a phone to use

	type 
		SOCK_STREAM
		SOCK_STREAM
		SOCK_SEQPACKET
		SOCK_RAW
	protocol
		often set to 0

}

class AF_INET
{};

class AF_INET6
{};

class AF_LOCAL
{};

class SOCK_STREAM
{
	TCP can use only this

};

class SOCK_DGRAM
{};

class SOCK_SEQPACKET
{};

class SOCK_RAW
{};
int bind(int sockfd, const struct sockaddr * s, socklen_t st)
{

	//analogy
	telling other people the telephone number

	//attention
	for client
		often kernel choose an ephemeral port for it\
			but it (client) can also call bind
		kernel also choose the IP for the client

	for server
		if wildcard IP address is chosen\
			the real IP address is not obtained until the TCPConnection is ESTABLISHED
		
}

class INADDR_ANY
{
	//
	wildcard

	indicated the kernel would choose the IP address

	value == all zero

};

int listen(int server_listening_sockfd, int backlog)
{

	//analogy
	turn on the ringer

	//parameter
	backlog	
		maximum number of connections the kernel should queue for the server_listening_sockfd
			sizeof IncompleteConnectionQueue

		dont set to 0
			otherwise you should close the server_listening_sockfd

	server_listening_sockfd
		it maintains two queue
			1>IncompleteConnectionQueue
			2>CompletedConnectionQueue

	//function
	turn the Socket from CLOSED to LISTEN

	//attention
	should be called after bind and before accept
}

class IncompleteConnectionQueue
{
	containes an entry for a client whose SYN has arrived
	the Socket that are in SYN_RCVD\awaiting ThreeWayHandShake to complete

};

class CompletedConnectionQueue
{
	the Socket in ESTABLISHED
};

int connect(int client_sockfd, struct sockaddr * server_addr, socklen_t server_addr_len)
{
	//function for TCP
	1 send a SYN Segment
	2 then wait (block)
	3 send a ACK

	//analogy
	know the phone numbe and dial it

	//attention
	the client does not have to call bind \ 
		the kernel will choose both IP and port for it 

	if connect fails\ the client_sockfd is no longer usable

	//funciton for SCTP
	1 send a INIT

	//returns
	for TCP
		only when the the TCPConnection is ESTABLISHED\ or an error occurs

	//possible errors
	for TCP
		1 if no ACK to the SYN is received by the client | ETIMEOUT
		2 if RST(cause 1)  is received by client as a response to SYN | ECONNREFUSED
			indicates that no process is waiting for TCPConnection on that {IPv4 + Port}
		3 EHOSTUNREACH
	
	 
}

class RST: public TCPSegment
{
	indicates something is wrong

	//causes
	1 the server port is not listened
	2 TCP wants to abort_ a connection
	3 TCP receives a TCPSegment for a TCPConnection that does not exist
};

class Message
{};

class INIT: public Message
{
	//function
	used by client to tell the server
	1 client`s list of IP addresses
	2 initial sequence number
	3 initiation tag (VerificationTag) to identify all packets in this_ association
	4 number of outbound streams the client is requring
	5 number of inbound streams the client can support

};

class VerificationTag
{
	//function
	to be in every packet send by the peer for_ the life of the association
	no need TIME_WAIT
};

class INIT_ACK: public Message
{
	//function used by server
	all 5 points in INIT
	plus 
		6 StateCookie
};

class StateCookie
{
	//function
	S----this------>C
	contains all the state that the server needs to ensure the association is valid \ used by client to set up an association with server

};

class COOKIE_ECHO: public Message
{
	//function
	client echo the StateCookie from server

};

class DenialOfService
{
	
};

class COOKIE_ACK: public Message
{
	//function
	the server acknowledge the StateCookie is correct
};


int accept(int server_listen_sockfd, struct sockaddr * client_addr, socket_t * client_addr_len)
{
	//function
	send SYN + ACK

	//analogy
	answer the phone

	//returns
	what
		1>the next completed connection (connected Socket) from the CompletedConnectionQueue
		if CompletedConnectionQueue is empty
			process is put to sleep_
		2> client_addr + client_addr_len
}

class Segment
{};

class ACK:public Segment
{
	ACK(int i){}

	//function
	acknowledge the peer that I want ith byte \ indicating that 0 - i-1 bytes received 
};

class SYN: public Segment
{
	SYN(int i){}

	//properties
	this Segment uses 1 byte \ so the ACK to this SYN will have a value of i+1

	//function
	tells the other peer the initial sequence number it will send
};

class TCPConnectionTermination
{
	//process
	1 ActiveClose
	2 PassiveClose


};

class DescriptorReferenceCount
{
	//why useful
	one FileDescriptor is shared between parent and child

};

int close(int sockfd)
{
	//function
	decrease DescriptorReferenceCount by 1 \if DescriptorReferenceCount reaches 0 \  initiate FourWayHandshake (send a FIN )
		the end first called this function is called ActiveClose 

	//related
	ActiveClose
	PassiveClose
	shutdown
}

int shutdown()
{
	send a FIN directly on a TCPConnection
}

class PassiveClose
{
	//
	the end received FIN generated by ActiveClose is called PassiveClose
		the FIN must be acknowleged (ACK)
		the FIN indicates EOF

		this end call close

	//related
	HalfClose
};

class FIN: public Segment
{
	//function
	this end is finished sending data

	it takes 1 byte so ACK to this will be value + 1

	//related
	SYN ACK
};

class HalfClose
{};

class ActiveClose
{
	//definition
	first close a TCPConnection

	//properties
	both client and server can perform ActiveClose

	//related
	ActiveOpen
	TIME_WAIT
};

class TCPState
{

};

class FIN_WAIT_1 : public TCPState
{
	after client send FIN before receive ACK to the FIN

};

class FIN_WAIT_2: public TCPState
{
	be in FIN_WAIT_1 \ then receives ACK \ goto this state
};

class SYN_SENT: public TCPState
{};

class CLOSED: public TCPState
{};

class LISTEN: public TCPState
{};

class LAST_ACK: public TCPState
{
	the PassiveClose close by server causes it to LAST_ACK
};

class ESTABLISHED: public TCPState
{};

class SYN_RCVD: public TCPState
{
	//related
	IncompleteConnectionQueue
};

class SIGCHLD
{
	sent to parent when child terminates\ server child
};

class CLOSE_WAIT
{
	//for server

};

class CLOSING: public TCPState
{
//for client

1 c---FIN -->s
2 before c receives the ACK \ it gets a FIN
3 C goto TIME_WAIT
//related
SimutaneousClose
};

class SimutaneousClose
{
	//related
	CLOSING
};

class TIME_WAIT : public TCPState
{
	//properties
	2 * MSL times after the ActiveClose has send the final ACK
	maintain the state information \ allowing to resend ACK

	// 2 reasons
	1 to implement FullDuplex TCPConnectionTermination reliably (reliability)
	2 to allow old duplicates Segment to expire
};

class MSL
{
	each TCP implementation should choose it

	//meaning
	the maximum amount of time that any given IPDataGram can live in a network
	it is a time limit \ TTL is a hop limit
	
	//related
	TTL
	RTT
};

class SocketPair
{
	//function
	identifies a TCPConnection

};

class TTL
{
	//properties
	8 bite
	hop limit

	//related
	IPDataGram
};

typedef MSL MaximumSegmentLifetime;


class FullDuplex
{};


class reliability
{
	acknowledgment
	retransmission
};

class FlowControl
{
	tells its peer how many bytes it is willing to accept

	//related
	Window

};

class ReceiveBuffer
{};

class Window
{
	//definiton
	the amount of room available in the ReceiveBuffer

	//properties
	changes dynamically
};

class ByteStream
{};

class RTT
{
	//properties	
	LAN: maybe milliseconds
	WAN: maybe seconds

	
};

the parent calls accept then calls fork 


class TCPSegment
{
	//related
	TCP

};



typedef RTT RoundTripTime;


class UDP
{
	//properties
	Connectionless
	it can use either IPv4 IPv6

	//usage
	UDPMessage ---> UDPDataGram ---> IPDataGram
};

class UDPMessage
{};

class UDPDataGram
{
	//properties
	has a length along with the data
};

class IPDataGram
{

	//related
	MSL
};

class IPv4DataGram
{

	//maximum size
	65535 (including IPv4DataGramHeader)
		16 bit in IPv4DataGramHeader
};

class IPv6DataGram
{
	//maximum size
	65575 = 65535( 16bit ) + 40 (40-byte IPv6DataGramHeader)
};

class IPv4DataGramHeader
{};

class IPv6DataGramHeader
{

	//properties
	length is fixed at 40 bytes
};

class MTU
{
	//meaning
	MaximumTransmissionUnit
	if the size of IPDataGram > MTU
		Fragmentation is performed


	//properties
	dictated by hardware

	//examples
	Ethernet MTU is 1500 B
	PPP MTU is configurable

	//related
	PathMTU
};

class Fragmentation
{
	//
	the fragments are not reassembled until they reach the final destination

	//difference
	Both IPv4 host and IPv4 router does Fragmentation \ but only IPv6 host does this\
		IPv6 router does not do this on the packets it is forwarding
			that is it can still do this on the packets it generates

	//related
	DF
};

MSS

class DF
{
	dont fragment

	it is in IPv4DataGramHeader

	what if_ size exceeds MTU?
		ICMP message "destination unreachable, fragmentation needed but DF bit set" ||
		ICMPv6 message "packet too long"
};

class PathMTU
{
	the smallest MTU in the path between two hosts

	oftern Ethernet MTU
};


class SCTP
{
	//properties
	ConnectionOriented
	FullDuplex reliable (reliability) association
	MultiHoming
	provides MessageService (MessageOriented)

	//related
	TCP

	//related
	SCTPConnection

	//pros
	1 can avoid DenialOfService attack
};

class SCTPConnection
{
	//identified by
	a set of local IP addresses + a local port +
	a set of foreign IP addresses + a foreign port

	//related
	FourWayHandshake

};

class FourWayHandshake
{
	//process
	1 client calling connect (ActiveOpen)
	  C --------- INIT ----------> S
	2 C <------INIT_ACK ---------- S
	3 C ------COOKIE_ECHO--------> S
	4 C <------COOKIE_ACK--------- S
	//related
	ThreeWayHandShake
};


class Endpoint
{
	a ip address + a port = Socket
};

class Socket
{};

class MultiHoming
{
	//features
	mutiple IP addresses

};

class MessageOriented
{
	//related
	ConnectionOriented

	//function
	provides Sequenced Delivery of individual records
};

class ConnectionOriented
{
	//related
	MessageOriented
};

class association
{
	//features
	connections between two systems

	multiple streams
		each with its own reliable sequenced delivery of message
		a lost message in one stream doesnt block the delivery of messages in other streams
	
};

class MessageService
{
	//properties
	maitaines RecordBoundary
};

class ICMP
{
	//function
	handles error and control information between Routers and Hosts
	
};

class IGMP
{};

class ARP
{
	//properties
	used on BroadcastNetwork such as Ethernet TokenRing FDDI
	

	//function
	
};

class PointToPointNetwork
{};

class BroadcastNetwork
{
	//related
	PointToPointNetwork
};

class Ethernet : public BroadcastNetwork
{};

class TokenRing : public BroadcastNetwork
{}; 

class FDDI : public BroadcastNetwork
{}; 



class RARP
{};

class ICMPv6
{};

class BPF
{
	//properties
	used on BerkleyDerived Kernels

	//function
	provides access to DataLinkLayer
	
};

class DataLinkLayer
{};

class DLPI
{

	//function
	provides access to DataLinkLayer


	//related
	SVR4
};

class SVR4
{};


int inet_aton(const char * strptr, struct in_addr * addrptr)
{
	//for Ipv4
}

char * inet_ntoa(struct in_addr addr)
{
	//for IPv4

	//attention
	rare because it takes a structure rather than a pointer as its parameter
}

in_addr_t inet_addr(const char * strptr)
{
	//for IPv4

	returns 32 bit binary network order IPv4 address on success \ INADDR_NONE on error

	//attention
	255.255.255.255 can not be used by this function (INADDR_NONE)

	deprecated
}

int getsockname(int sockfd, struct sockaddr * localaddr, socklen_t * addrlen)
{
	//why usefull
	if the client didnt call bind\ it can use this_ function to get the IP address and local port assigned by the kernel

	//attention
	if the server wanna know the real IP address (wildcard address used)\ it calls this function\ sockfd should be the ConnectedSocket
}

int getpeername(int sockfd, struct sockaddr * peeraddr, socklen_t * addrlen)
{
	//usage
	if exec is called\ the only way the server can obtain the indentiy of the client is to call getpeername
	
}

class sockaddr_storage
{};

struct INADDR_NONE
{
	typically 32 one-bit
};


int inet_pton(int family, const char * strptr, void * addptr)
{
	//argument
	family\
		AF_INET
		AF_INET6

	store the result to addptr

	//returns
	1 OK
	0 strptr not valid presentation
	-1 on error


}

#define INET_ADDRSTRLEN 16
#define INET6_ADDRSTRLEN 46

const char * inet_ntop(int family, const void * addrptr, char * strptr, size_t nlen)
{
	//attention
	nlen is the size of the destination\ prevent overflow
		typicallu
		INET_ADDRSTRLEN\ INET6_ADDRSTRLEN

	//returns
	pointer to result if OK ( == strptr)
	NULL on error

	//problems
	still protocal-dependent
		to solve this
			sock_ntop
}

char * sock_ntop(const struct sockaddr * sockaddr, socklen_t addrlen)
{
	it uses its own static_ buffer /*maybhe static char t[1000]*/
		so it is not ReentrantFunction or ThreadSafe

}



