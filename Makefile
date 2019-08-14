#FILE:= dropper
#SEC:= .text
FILE:= udp
SEC:= loopback_main


all:
	clang -O2 -target bpf -c ${FILE}.c -o ${FILE}.o
load:
	ip link set dev p6p1 xdp obj ${FILE}.o sec ${SEC}
unload:
	ip link set dev p6p1 xdp off
show:
	ip link show dev p6p1
clean:
	rm -rf *.o
