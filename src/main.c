#include "arp.h"
#include "globals.h"
#include "route_table.h"
#include "socket_util.h"
#include "util.h"

/*
void init_network_id() {
    char *network_LAN0 = LAN0_NETWORK;
    char *network_LAN1 = LAN1_NETWORK;
    char *network_rtr1 = RTR1_NETWORK;
    char *network_rtr2 = RTR2_NETWORK;

    memset(&globals.sock_network_LAN0, 0, sizeof(struct in_addr));
    memset(&globals.sock_network_LAN1, 0, sizeof(struct in_addr));
    memset(&globals.sock_network_rtr1, 0, sizeof(struct in_addr));
    memset(&globals.sock_network_rtr2, 0, sizeof(struct in_addr));

    inet_aton(network_LAN0, &(globals.sock_network_LAN0));
    inet_aton(network_LAN1, &(globals.sock_network_LAN1));
    inet_aton(network_rtr1, &(globals.sock_network_rtr1));
    inet_aton(network_rtr2, &(globals.sock_network_rtr2));
}
*/

/**
 * Router's interfaces and its mac addresss
 * Needed to sniff only certain interfaces
 */
void init_mac_addr(){

    interface_addr(globals.send_sock_fd, INF0, globals.eth1_mac);
    interface_addr(globals.send_sock_fd, INF1, globals.eth2_mac);
    interface_addr(globals.send_sock_fd, INF2, globals.eth3_mac);

}

int main(int argc, char *argv[]){

    /* Initiliaze all the network ids in the topo as sock */
    //init_network_id();

    /* Create file descriptor to write the packet */
    create_log_file();

    /* Descriptor used for sending packets */
    globals.send_sock_fd = get_socket();

    /* Get MAC address of all the three interfaces */
    init_mac_addr();

    /* Build the arp table */
    init_build_arp_cache();

    /* Print the arp table */
    print_arp_cache_table();

    /* Building initial routing table */
    init_build_route_table();

    print_route_table();

    sniff();

    return 0;
}
