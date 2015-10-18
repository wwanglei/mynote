class IPv4SocketAddressStructure
{
	//related
	sockaddr_in
};

struct sockaddr_in
{
	//for ipv4
	uint8_t sin_len;
	sa_family_t sin_family;//AF_INET
	in_port_t sin_port;
	struct in_addr sin_addr;/*network byte order*/
	char sin_zero[8];
};

struct in_addr_t
{};

struct in_addr
{
	in_addr_t s_addr;
};

class GenericSocketAddressStructure
{
	//related
	sockaddr
	
};

struct sockaddr
{

	attention
	//it is generic sock address structure
	so it often needs a socklen_t nlen with it
	

	uint8_t sin_len;
	sa_family_t sin_family;	
	char sa_data[14];

////////////////////////////////////
	//related
	bind
	
};



class IPv6SocketAddressStructure
{
	sockaddr_in6
};


class ValueResultArgument
{

	//related
	accept
};

struct sockaddr_in6
{
	uint8_t sin6_len;
	sa_family_t sin6_family;//AF_INET6
	in_port_t sin6_port;
	uint32_t sin6_flowinfo;
	struct in6_addr sin6_addr;//network byte order
	uint32_t sin6_scope_id;
};

uint16_t htons(uint16 h16)
{
	//often
	htons(port_number)
}

uint16_t ntohs(uint16 s16)
{}


uint32_t htonl(uint32 h32)
{
	//often
	htonl(INADDR_ANY)
}

uint32_t ntohl(uint32 s32)
{}





