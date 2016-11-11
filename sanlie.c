/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: sanlie.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   11/03/16 04:24:22
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   11/03/16                  build this moudle  
 ***************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FILE_HASH 10
#define SAME 0

struct f
{
    char *fname;
    struct f *flink;
};

typedef struct f *file;

file file_hash_table[FILE_HASH];

int hash_filename(char *s)
{
   int length = strlen(s); 
   return (length + 4 * (s[0] + 4 * s[length / 2])) % FILE_HASH;
}

file 
allocate_file(char *s)
{
    file f = (file)malloc(sizeof(struct f));
    f->fname = s;
    return f;
}

file 
find_filename(char *s)
{
   int hash_value = hash_filename(s);
   file f;

   for(f = file_hash_table[hash_value];f != NULL;f = f->flink)
   {
      if(strcmp(f->fname,s) == SAME)
      {
         return f;
      }
   }

   f = allocate_file(s);
   f->flink = file_hash_table[hash_value];
   file_hash_table[hash_value] = f;
   return f;
}

int 
main() 
{

	file f;

	while(1)
	{
		char input[10];
		fgets(input,10 - 1,stdin);

		f = find_filename(input);
		printf("filename:%shashvalue:%d \n",f->fname,hash_filename(f->fname));
	}

	return 0;
}

