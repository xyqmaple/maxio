#include <stdio.h>
#include "atomic.h"
#include "train_sw_desc.h"

int main(int argc, char *argv[])
{
	atomic_init();
	train_sw_desc_init();
	return 0;
}
