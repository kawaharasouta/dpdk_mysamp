/**
 * @file main.c
 * @brief this is main program file of my dpdk programs for practice.it is copied from dpdk samples.
 * @author khwarizmi
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <sys/queue.h>

#include <rte_memory.h>
#include <rte_launch.h>
#include <rte_eal.h>
#include <rte_per_lcore.h>
#include <rte_lcore.h>
#include <rte_debug.h>
#include<rte_mbuf.h>
#include<rte_ethdev.h>
#include<rte_cycles.h>

#define NUM_MBUFS 8191
#define MBUF_CACHE_SIZE 250
#define BURST_SIZE 32
#define RX_RING_SIZE 128
#define TX_RING_SIZE 512

#include"include/port_init.h"
//static int
//lcore_hello(__attribute__((unused)) void *arg)
//{
//	unsigned lcore_id;
//	lcore_id = rte_lcore_id();
//	printf("hello from core %u\n", lcore_id);
//	return 0;
//}

//static const struct rte_eth_conf port_conf_default ={
//	.rxmode = { .max_rx_pkt_len = ETHER_MAX_LEN }
//};
//
//static inline int
//port_init(uint16_t port, struct rte_mempool *mbuf_pool)
//{
//        struct rte_eth_conf port_conf = port_conf_default;
//        const uint16_t rx_rings = 1, tx_rings = 1;
//        uint16_t nb_rxd = RX_RING_SIZE;
//        uint16_t nb_txd = TX_RING_SIZE;
//        int retval;
//        uint16_t q;
//        struct rte_eth_dev_info dev_info;
//        struct rte_eth_txconf txconf;
//        if (port >= rte_eth_dev_count())
//                return -1;
//        rte_eth_dev_info_get(port, &dev_info);
//        if (dev_info.tx_offload_capa & DEV_TX_OFFLOAD_MBUF_FAST_FREE)
//                port_conf.txmode.offloads |=
//                        DEV_TX_OFFLOAD_MBUF_FAST_FREE;
//        /* Configure the Ethernet device. */
//        retval = rte_eth_dev_configure(port, rx_rings, tx_rings, &port_conf);
//        if (retval != 0)
//                return retval;
//        retval = rte_eth_dev_adjust_nb_rx_tx_desc(port, &nb_rxd, &nb_txd);
//        if (retval != 0)
//                return retval;
//        /* Allocate and set up 1 RX queue per Ethernet port. */
//        for (q = 0; q < rx_rings; q++) {
//                retval = rte_eth_rx_queue_setup(port, q, nb_rxd,
//                                rte_eth_dev_socket_id(port), NULL, mbuf_pool);
//                if (retval < 0)
//                        return retval;
//        }
//        txconf = dev_info.default_txconf;
//        txconf.txq_flags = ETH_TXQ_FLAGS_IGNORE;
//        txconf.offloads = port_conf.txmode.offloads;
//        /* Allocate and set up 1 TX queue per Ethernet port. */
//        for (q = 0; q < tx_rings; q++) {
//                retval = rte_eth_tx_queue_setup(port, q, nb_txd,
//                                rte_eth_dev_socket_id(port), &txconf);
//                if (retval < 0)
//                        return retval;
//        }
//        /* Start the Ethernet port. */
//        retval = rte_eth_dev_start(port);
//        if (retval < 0)
//                return retval;
//        /* Display the port MAC address. */
//        struct ether_addr addr;
//        rte_eth_macaddr_get(port, &addr);
//        printf("Port %u MAC: %02" PRIx8 " %02" PRIx8 " %02" PRIx8
//                           " %02" PRIx8 " %02" PRIx8 " %02" PRIx8 "\n",
//                        port,
//                        addr.addr_bytes[0], addr.addr_bytes[1],
//                        addr.addr_bytes[2], addr.addr_bytes[3],
//                        addr.addr_bytes[4], addr.addr_bytes[5]);
//        /* Enable RX in promiscuous mode for the Ethernet device. */
//        rte_eth_promiscuous_enable(port);
//        return 0;
//}

int main(int argc, char *argv[])
{
	int ret;
	unsigned nb_ports;
	struct rte_mempool *mbuf_pool;
	uint16_t portid;
	
	//ini
	ret = rte_eal_init(argc, argv);
	if (ret < 0)
		rte_panic("Cannot init EAL\n");

	/* call lcore_hello() on every slave lcore */
	//RTE_LCORE_FOREACH_SLAVE(lcore_id) {
	//	rte_eal_remote_launch(lcore_hello, NULL, lcore_id);
	//}

	//number of ports
	nb_ports = rte_eth_dev_count();
	//ini mbufpool
	mbuf_pool = rte_pktmbuf_pool_create("MBUF_POOL", NUM_MBUFS * nb_ports, MBUF_CACHE_SIZE, 0, RTE_MBUF_DEFAULT_BUF_SIZE, rte_socket_id());

//	for(portid = 0; portid < nb_ports; portid++){
//		rte_eth_dev_config(portid, NRXQ, NTXQ, &portconf);
//		
//		for
//	}

	/* call it on master lcore too */
	//lcore_hello(NULL);

	for(portid = 0; portid < nb_ports; portid++){
		port_init(portid, mbuf_pool);
	}

	rte_eal_mp_wait_lcore();
	return 0;
}
