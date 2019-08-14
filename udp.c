#include <linux/bpf.h>
#include <linux/in.h>
#include <linux/if_ether.h>
#include <linux/ip.h>

#define SEC(NAME) __attribute__((section(NAME), used))

SEC("loopback_main")
int dropper(struct xdp_md *ctx) {
	int ipsize = 0;
	unsigned char buf[ETH_ALEN];

	void *data = (void *)(long)ctx->data;
	void *data_end = (void *)(long)ctx->data_end;

	struct ethhdr *eth = data;

	ipsize = sizeof(*eth);

	struct iphdr *ip = data + ipsize;
	ipsize += sizeof(struct iphdr);
	if (data + ipsize > data_end) {
		return XDP_PASS;
	}

#if 1
	if (ip->protocol == IPPROTO_UDP) {
		/*Rule for a specific DIP*/
#if 0
		if((ip->daddr & 0xffull) != 20)
			return XDP_DROP;
#endif
		
		/*Looping back to same port*/
#if 0
		memcpy(buf, eth->h_dest, ETH_ALEN);
		memcpy(eth->h_dest, eth->h_source, ETH_ALEN);
		memcpy(eth->h_source, buf, ETH_ALEN);
#else
		memcpy(eth->h_source, eth->h_dest, ETH_ALEN);
#endif
		return XDP_TX;
		
		//return XDP_DROP;
	}
#endif
	return XDP_PASS;
}

char _license[] SEC("license") = "GPL";
