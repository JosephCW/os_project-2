.PHONY: clean

driver: cpu_sched.c  main.c  proc.c  schedulers.c
	gcc -std=c99 -Wall -g $? -o $@

test: cpu_sched.c  test.c  proc.c  schedulers.c
	gcc -std=c99 -Wall -g $? -o $@

clean:
	rm -rf driver test
