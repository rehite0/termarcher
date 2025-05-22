#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/wait.h>

extern	 char* spawn(char** );
extern   int tcol();
extern   int tlin();
extern	 void ttozero();
extern   void tinit();
extern   void tdel();
