obj-m+=Hello.o

all :
	make -C /lib/modules/4.4.38-v7+/build/ M=$(PWD) modules
clean:
	make -C /lib/modules/4.4.38-v7+/build/ M=$(PWD) clean

