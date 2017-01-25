obj-m+=char_dev.o

all :
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
	$(CC) Testchar.c -o test
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm test
