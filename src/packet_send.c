#include "packet_send.h"

void send_ethernet_packet() {
    int s; /*socketdescriptor*/
    char if_name[IFNAMSIZ] = "inf001";
    struct ifreq ifr;
    /*target address*/
    struct sockaddr_ll socket_address;

    /*other host MAC address*/
    unsigned char dest_mac[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x05};

    /*Create raw socket*/
    s = get_socket();

    /*Get current interface mac address*/
    unsigned char *src_mac = malloc(ETH_ALEN);
    interface_addr(s, if_name, src_mac);

    //Find src interface index
    int src_index = interface_index(s, if_name);

    /*prepare sockaddr_ll*/
    create_socket_address(&socket_address, src_index, dest_mac);

    /*buffer for ethernet frame*/
    void* packet = (void*)malloc(PACKET_SIZE);

    /*Create packet*/
    create_packet(packet, src_mac, dest_mac);

    /*send the packet*/
    int send_result = 0;
    send_result = sendto(s, packet, PACKET_SIZE , 0, (struct sockaddr*)&socket_address, sizeof(socket_address));
    if (send_result < 0){
	printf("ERROR: sendto\n");
	perror("sendto");
	exit(1);
    }
}

void send_icmp_packet(char *if_name, unsigned char *dest_mac, void *packet){
    int s; /*socketdescriptor*/
    struct ifreq ifr;
    /*target address*/
    struct sockaddr_ll socket_address;

    /*Create raw socket*/
    s = get_socket();

    /*Get current interface mac address*/
    unsigned char *src_mac = malloc(ETH_ALEN);
    interface_addr(s, if_name, src_mac);

    //Find src interface index
    int src_index = interface_index(s, if_name);

    /*prepare sockaddr_ll*/
    create_socket_address(&socket_address, src_index, dest_mac);

       /*send the packet*/
    int send_result = 0;
    send_result = sendto(s, packet, PACKET_SIZE , 0, (struct sockaddr*)&socket_address, sizeof(socket_address));
    if (send_result < 0){
	printf("ERROR: sendto\n");
	perror("sendto");
	exit(1);
    }
}