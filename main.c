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

	//number of ports
	nb_ports = rte_eth_dev_count();
	//ini mbufpool
	mbuf_pool = rte_pktmbuf_pool_create("MBUF_POOL", NUM_MBUFS * nb_ports, MBUF_CACHE_SIZE, 0, RTE_MBUF_DEFAULT_BUF_SIZE, rte_socket_id());

	//ini every port
	for(portid = 0; portid < nb_ports; portid++){
		port_init(portid, mbuf_pool);
	}

	rte_eal_mp_wait_lcore();
	return 0;
}
