/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: macro_struct.cc
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017��02��24�� 06ʱ40��21��
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017��02��24��                  build this moudle  
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
