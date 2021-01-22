
#include "run.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int main(int argc, char ** argv) {

	if(argc >= 2){
		if(strcmp(argv[1],"0") == 0 && argc == 5)
			return run_one(argc, argv);
		else if(strcmp(argv[1],"1") == 0 && argc == 4)
			return run_multi(argv[3], argv[2]);
		else{
			printf("Incorrect input");
			return 1;
		}
	}
	else{
		printf("Incorrect input");
		return 1;
	}

	return 0;
}