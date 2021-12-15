#ifndef _ProcessCmd_H_
#define _ProcessCmd_H_

#include "TypeDefine.h"

int ProcessCmd(ST_INPUT_CMD  *sInputCmd,FILE* f_out,int pos=0);
int DecodeInputLine(char *buf,ST_INPUT_CMD &t_set);

#endif