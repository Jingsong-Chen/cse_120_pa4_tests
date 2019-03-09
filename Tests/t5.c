// Author: Tianheng "Oliver" Liu

#include "../aux.h"
#include "../umix.h"
#include "../mycode4.h"

// notice this value is smaller than the STACKSIZE in mycode4.c
#define STACKSIZE 60000

void WriteAndYield(int p);
void CreateAndYield(int p);
void YieldTo(int p);
void DoNothing(int p);

void Main() {
	int i;
	int t;
/*
	Printf("*************************************************************\n");
	Printf("Thread 0 creates threads 1-9.\n");
	Printf("Thread 0 yields to thread 2 from near the top of its stack.\n");
	Printf("Thread 2 yields back to thread 0,\n");
	Printf("Thread 0 exits.\n");
	Printf("Thread 1 should be scheduled to run.\n");
	Printf("Thread 1 creates a variable something = 1.\n");
	Printf("Thread 1 creates thread 0 again and yields to it.\n");
	Printf("Thread 0 writes on its stack then yiedls back to thread 1.\n");
	Printf("Thread 1 checks if the value of something has been changed.\n");
	Printf(" ***: the values of something on those lines should be equal.\n");
	Printf("Compare the output with the output of r5.\n");
	Printf("*************************************************************\n");
*/
	MyInitThreads();

	for(i = 0; i < MAXTHREADS; i++) {
		if(i == 0) {		// thread 1
			MyCreateThread(CreateAndYield, MyGetThread());

		} else if(i == 1) {	// thread 2
			t = MyCreateThread(YieldTo, MyGetThread());

		} else {
			MyCreateThread(DoNothing, -1);
		}
	}

	char stack[STACKSIZE];
	if(((int)&stack[STACKSIZE - 1]) - ((int)&stack[0]) + 1 != STACKSIZE) {
		Printf("Failed to create the stack\n");
		Exit();
	}

	YieldTo(t);
	
	Printf("Thread %d: exiting.\n", MyGetThread());
	MyExitThread();
}

void WriteAndYield(p)
	int p;
{
	int i;
	char stack[STACKSIZE];

	Printf("Thread %d: writing on my own stack.\n", MyGetThread());

	for(i = 0; i < STACKSIZE; i++) {
		stack[i] = 'c';
	}

	Printf("Thread %d: yielding to %d.\n", MyGetThread(), p);
	MyYieldThread(p);
}


void CreateAndYield(p)
	int p;
{
	int something = 1;
	int t;
	Printf("Thread %d: created something = %d.\t***\n", MyGetThread(), something);
	Printf(
		"Thread %d: creating and yielding to thread %d.\n",
		MyGetThread(),
		(t = MyCreateThread(WriteAndYield, MyGetThread()))
	);

	t = MyYieldThread(t);

	Printf("Thread %d: resumed by %d.\n", MyGetThread(), t);
	Printf("Thread %d: my something is now %d.\t***\n", MyGetThread(), something);
}

void YieldTo(p)
	int p;
{
	int t;

	Printf("Thread %d: yielding to thread %d.\n", MyGetThread(), p);

	t = MyYieldThread(p);

	Printf("Thread %d: resumed by thread %d.\n", MyGetThread(), t);
}

void DoNothing(p)
	int p;
{
	// do nothing
}
