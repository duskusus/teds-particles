#include <iostream>
#include <stdlib.h>

int main(int argc, char **argv){
	unsigned int dimensions = 0;
	if(argv[1]){
		dimensions = atoi(argv[1]);
	} else {
		printf("error: provide number of dimensions\n");
		return 0;
	}
	printf("Using %d dimensions\n", dimensions);
	return 0;
}
	

