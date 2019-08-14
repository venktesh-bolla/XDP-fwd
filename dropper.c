#include <linux/bpf.h>

int main() {
	return XDP_DROP;
	//return XDP_TX;
}
