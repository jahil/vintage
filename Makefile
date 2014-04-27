obj-m += vintage.o
vintage-y = vintage_main.o
vintage-y+= tracks/trk1.o
vintage-y+= tracks/trk2.o
vintage-y+= tracks/trk3.o
vintage-y+= tracks/trk4.o
vintage-y+= tracks/trk5.o
vintage-y+= tracks/trk6.o

KERNELDIR	?=  /lib/modules/$(shell uname -r)/build
PWD		:= $(shell pwd)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
