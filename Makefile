all: lottery_scheduler 

clean:
	rm -f lottery_scheduler

lottery_scheduler:
	g++ -o lottery_scheduler lot_sched.cpp -Wall

run: lottery_scheduler
	./lottery_scheduler
