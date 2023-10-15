/*FLUTURE Robert-Gabriel 313CB*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#ifndef _UTILS_
#define _UTILS_

typedef struct file
{
    char* name;

    struct directory* parent;

    struct file* st;

    struct file* dr;

} File, *AFile;

typedef struct directory
{ 
    char* name;

    struct file* FRoot;

    struct directory* SDRoot;

    struct directory* parent;

    struct directory* st;

    struct directory* dr;

} Dir, *ADir;


ADir AllocDir();
ADir InitRoot();

int InsertDir(ADir, ADir);
void Dtreeprint(ADir, int);
void ResetRoot(ADir root);
void FreeFileTree(AFile root);

#endif
