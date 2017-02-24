/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: macro_struct.cc
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年02月24日 06时40分21秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年02月24日                  build this moudle  
 *****************************************************************************/

#define CV_SEQUENCE\_FIELDS() \
int flags; \
int header_size; \
struct CvSeq* h_prev; \
struct CvSeq* h_next; \
struct CvSeq* v_prev; \
struct CvSeq* v_next; \
int total; \
int elem_size; \
char* block_max; \
char* ptr; \
int delta_elems; \
CvMemStorage* storage; \
CvSeqBlock* free_blocks; \
CvSeqBlock* first; \

typedef struct CvSeq 
{ 
	CV_SEQUENCE_FIELDS() 
} CvSeq;
