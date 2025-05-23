#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "term.h"
#include "marc.h"

double timefs;

void cleanup(void){
    tdel();
}
void sigh(int snum){
    exit(0);
}
int main(){
    char charset[]={' ','.',',','+','*',';','o','e','$','@','#'};
    atexit(cleanup);
    sigaction(SIGINT, &((struct sigaction){.sa_handler=sigh}),0);
    tinit();
    int start=clock();
    while (1){
        ttozero();
	int xm=tcol()-1,ym=tlin()-1;
	timefs=(double)(clock()-start)/CLOCKS_PER_SEC;
	for (int y=0;y<ym;++y){
	    for (int x=0;x<xm;++x){
	        float nx,ny;
		nx=((float)x*2.0/(float)xm)-1.0;
		ny=((float)y*2.0/(float)ym)-1.0;
		float intensity= raymarch(nx,ny);
		printf("%c",charset[(int)(intensity*sizeof(charset))]);
	    }
	    printf("\n");
	}
    }
}



