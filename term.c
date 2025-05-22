#include "term.h"
#include <stdio.h>

int tcol(){
    char* prg[]={"tput","cols",0};
    char* out=spawn(prg);
    int ret;
    sscanf(out, "%d", &ret);
    free(out);
    return ret;
}
int tlin(){
    char* prg[]={"tput","lines",0};
    char* out=spawn(prg);
    int ret;
    sscanf(out, "%d", &ret);
    free(out);
    return ret;
}

void ttozero(){
    system("tput cup 0 0");
}

void tinit(){
    system("tput smcup");
    system("tput civis");
    //system("tput setaf 2");
    //system("tput setab 0");
}

void tdel(){
    system("tput rmcup");
    system("tput cnorm");
    system("tput srg0");
}

char* spawn(char** argv){
    int pip[2]={0};
    int e=pipe(pip);
    if(e==-1) {assert(0 && "pipe error"); exit(1);}
    int pid=fork();
    switch (pid){
	case -1:
	    assert(0 && "fork failed");
	    exit(1);
	case 0:
	    dup2(pip[1], 1);
	    close(pip[0]);
	    close(pip[1]);
	    execvp(argv[0], argv);
	    break;
	default:
	    close(pip[1]);
	    int fd=pip[0];
	    int buffsiz=256*sizeof(char);
	    char* ret=malloc(buffsiz);
	    char c=0;
	    int i=0;
	    while(read(fd,&c,1)&& i<buffsiz) ret[i++]=c;
	    ret[i]=0;
	    wait(0);
	    close(pip[0]);
	    return ret;
    }
    assert(0&&"spawn error");
    return 0;
}
