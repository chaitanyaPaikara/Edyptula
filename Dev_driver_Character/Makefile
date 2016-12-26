obj-m+=char_dev.o

all :
	make -C /lib/modules/4.4.38-v7+/build/ M=$(PWD) modules
	$(CC) testchar.c -o test
clean:
	make -C /lib/modules/4.4.38-v7+/build/ M=$(PWD) clean
	rm test
