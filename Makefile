all:hdd_rw.c.bin hdds.c.bin

hdd_rw.c.bin:hdd_rw.c 
	gcc hdd_rw.c -o hdd_rw.c.bin 
hdds.c.bin:hdds.c 
	gcc hdds.c -o hdds.c.bin 
