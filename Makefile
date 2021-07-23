#아래에 추가하고 싶은 c 파일들을 추가하세요
ADDITIONAL_SRC= Queue.c

.PHONY:schedule

schedule: util.o cpu.o host.o parser.o 
	gcc -o schedule scheduler.c cpu.o host.o parser.o util.o $(ADDITIONAL_SRC)

cpu.o: 
	gcc -c -o cpu.o src/cpu.c

host.o:
	gcc -c -o host.o src/host.c

parser.o:
	gcc -c -o parser.o src/parser.c

util.o:	
	gcc -c -o util.o src/util.c

clean:
	rm util.o cpu.o host.o parser.o schedule
