bb: bb-harness.o bb-sync.o bb-cs.o putDown.o pickUp.o utility.o
	gcc -o bb *.o -lpthread

bb-harness.o: bb-sync.h

bb-cs.o: bb-cs.h buffer.h

bb-sync.o: bb-sync.h buffer.h

putDown.o: bb-cs.h bb-sync.h buffer.h utility.h

pickUp.o: bb-cs.h bb-sync.h buffer.h utility.h

utility.o: utility.h

clean:
	rm bb *.o
