.PHONY:ALL
ALL:myfile2 myfile
myfile2:myfile2.c	
	gcc -o $@ $^
myfile:myfile.c
	gcc -o $@ $^
.PHONY:clean
clean:
	rm -f myfile myfile2
