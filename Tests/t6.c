// Author: Tianheng "Oliver" Liu

#include "../aux.h"
#include "../umix.h"
#include "../mycode4.h"

// notice this value is smaller than the STACKSIZE in mycode4.c
#define STACKSIZE 60000

void WriteAndYield(int p);
void CreateAndYield(int p);

void Main() {
	int t1, t2;
	MyInitThreads();
/*
	Printf("***************************************************************\n");
	Printf("Thread 0 creates thread 1 when it's at the top of its stack.\n");
	Printf("Thread 0 creates thread 2 when it's at the bottom of its stack.\n");
	Printf("Thread 2 creates a variable something = 1.\n");
	Printf("Thread 1 writes on its own stack.\n");
	Printf("Thread 2 checks the value of something.\n");
	Printf(" ***: the values of something on those lines should be equal.\n");
	Printf("Compare the output with the output of r6.\n");
	Printf("***************************************************************\n");
*/
	if(1) {
		char stack[STACKSIZE];
		if(((int)&stack[STACKSIZE - 1]) - ((int)&stack[0]) + 1 != STACKSIZE) {
			Printf("Stack space reservation failed.\n");
			Exit();
		}

		t1 = MyCreateThread(WriteAndYield, MyGetThread());
	}

	t2 = MyCreateThread(CreateAndYield, MyGetThread());

	MyYieldThread(t2);

	MyYieldThread(t1);
	
	MyYieldThread(t2);

	MyExitThread();
}

void WriteAndYield(p)
	int p;
{
	int i;
	Printf("Thread %d: writing on my own stack.\n", MyGetThread());
	char stack[STACKSIZE];
	for(i = 0; i < STACKSIZE; i++) {
		stack[i] = 'c';
	}

	MyYieldThread(p);
}

void CreateAndYield(p)
	int p;
{
	int something = 1;
	Printf("Thread %d: created something = %d.\t***\n", MyGetThread(), something);

	MyYieldThread(p);

	Printf("Thread %d: my something is now: %d.\t***\n", MyGetThread(), something);
}
