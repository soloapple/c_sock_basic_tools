/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: packet_mmap.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年01月01日 20时11分39秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年01月01日                  build this moudle  
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <linux/if_packet.h>
#include <netinet/if_ether.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "/revive/git/c_sock_basic_tools/include/colorpt.h"

#define BLOCKNO 1
#define NETDEV_NAME "eth0"

//static const int tpacket_version = TPACKET_V1;


int main (int argc, char **argv)
{
	struct tpacket_hdr *tphdr, *last;
	struct ether_arp *arpmsg;
	struct tpacket_req cpargs;
	char ipsender[4];
	int pd;
	void *addrmap;

	int i;

	if (-1 == (pd = socket (PF_PACKET, SOCK_DGRAM, htons (ETH_P_ARP))))
	{
		fprintf (stderr, "create socket failure: %s.\n", strerror (errno));
		return 1;
	}

//	if (-1 == setsockopt (pd, SOL_PACKET, PACKET_VERSION, &tpacket_version, sizeof (int)))
//	{
//		fprintf (stderr, "set tpacket version failure: %s.\n", strerror (errno));
//		goto close_pd;
//	}

	/* bind to device. */
	if (-1 == setsockopt (pd, SOL_SOCKET, SO_BINDTODEVICE, NETDEV_NAME, sizeof (NETDEV_NAME)))
	{
		fprintf (stderr, "bind to %s failure: %s.\n", NETDEV_NAME, strerror (errno));
		goto close_pd;
	}

	cpargs.tp_block_size = getpagesize();
	cpargs.tp_block_nr = BLOCKNO;

	cpargs.tp_frame_size = TPACKET_HDRLEN + TPACKET_ALIGN (sizeof (struct ether_arp));

	cpargs.tp_frame_nr = (cpargs.tp_block_size / cpargs.tp_frame_size * cpargs.tp_block_nr);

	if (-1 == setsockopt (pd, SOL_SOCKET, PACKET_RX_RING, &cpargs, sizeof (struct tpacket_req)))
	{
		fprintf (stderr, "set packet ring failure: %s.\n", strerror (errno));
		goto close_pd;
	}


	addrmap = mmap (NULL, cpargs.tp_block_size * BLOCKNO,		\
			PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, pd, 0);

	if ((void *) -1 == addrmap)
	{
		fprintf (stderr, "map packet failure: %s.\n", strerror (errno));
		goto close_pd;
	}

	while (1)
	{
		last = (struct tpacket_hdr *) addrmap;
		for (i = 0; i < cpargs.tp_frame_nr; i++)
		{
			tphdr = last++;
			while (!tphdr->tp_status);

			fprintf (stderr, "haha.\n");

			arpmsg = (struct ether_arp *) ((void *) tphdr + tphdr->tp_net);

			memcpy (ipsender, arpmsg->arp_spa, 4);
			fprintf (stderr, "send ipaddr: %u.%u.%u.%u.\n",		\
					ipsender[0], ipsender[1], ipsender[2], ipsender[3]);
		}

		tphdr->tp_status = TP_STATUS_KERNEL;

	}

close_pd:
	close (pd);

	return 1;
}

