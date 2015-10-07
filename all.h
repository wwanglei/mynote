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
};

typedef MSS MaximumSegmentSize;

class TCPConnection
{
	
	//related
	TCPConnectionEstablishment
	TCPConnectionTermination
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
};

int socket()
{

	//analogy
	having a phone to use
}

int bind()
{

	//analogy
	telling other people the telephone number
}

int listen()
{

	//analogy
	turn on the ringer
}

int connect()
{
	//function
	1 send a SYN Segment
	2 then wait (block)
	3 send a ACK

	//analogy
	know the phone numbe and dial it
}

int accept()
{
	//function
	send SYN + ACK

	//analogy
	answer the phone
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

int close()
{
	//function
	send a FIN 
		the end first called this function is called ActiveClose 

	//related
	ActiveClose
	PassiveClose
}

class PassiveClose
{
	//
	the end received FIN generated by ActiveClose is called PassiveClose
		the FIN must be acknowleged (ACK)
		the FIN indicates EOF

		this end show call close

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

class TIME_WAIT
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
{};

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



class SCTP
{
	//properties
	ConnectionOriented
	FullDuplex reliable (reliability) association
	MultiHoming
	provides MessageService (MessageOriented)
	
};

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


