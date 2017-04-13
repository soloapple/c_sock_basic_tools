#include "common.h"

void putcbuf(unsigned char *buf, int s, int e)
{
	printf("%2s", " ");
	while (s < e) {
		if (isprint(buf[s]))
			printf("%c", buf[s]);
		else
			printf(".");
		s++;
	}
	printf("\n");
}

void putbuf(unsigned char *buf, int len)
{
	int            i = 0, t = 0, s = len;
	unsigned char *ps = buf;

	while (s--) {
		printf("%02x ", *ps);
		i++ ;

		if (i == 8)
			printf(" ");

		if (!(i % 16)) {
			putcbuf(buf, t, t + i);
			t += i;
			i = 0;
		}
		ps++ ;
	}

	/* printf leave content */
	if (i > 0) {
		s = i;
		while (s++ < 16) {
			if (s == 8)
				printf(" ");
			printf("%3s", " ");
		}
		putcbuf(buf, t, t + i);
	}
}

#define RE_ONE 0x01
#define RE_ALL 0x02
#define Y_FIND 0x03
#define N_FIND 0x04

typedef struct memreplace {
	void  *ps;
	int    xlen;
	int    find;    /* search string need to find */
	struct memreplace *next, *tail;
} mem_re;

void mr_init(mem_re *mr)
{
	if (mr != NULL)
		memset(mr, 0, sizeof(mem_re));
}

mem_re *mr_gethead(mem_re *mr)
{
	return mr->next;
}

int mr_add(mem_re *mr, void *ps, int xlen, int xfind)
{
	mem_re *mrn;

	if ((mrn = calloc(1, sizeof(mem_re))) == NULL)
		return -1;

	mrn->ps   = ps;
	mrn->xlen = xlen;
	mrn->find = xfind;

	if (mr->next == NULL)
		mr->next = mr->tail = mrn;
	else {
		mr->tail->next = mrn;
		mr->tail = mrn;
	}
	return 1;
}

void mr_destroy(mem_re *mr)
{
	mem_re *mrn = mr->next;

	while (mrn != NULL) {
		mr->next = mr->next->next;
		free(mrn);
		mrn = mr->next;
	}
}

/*
 * function:     memreplace
 * description:  string replace
 * input:        buf - string content
 *               len - string length
 *               ss  - source string
 *               ds  - dest string
 * output:       null
 * return:       -1 - error;
 * others:       null
 */
int __memreplace(char **pstr, int *len, char *src, int nsrc,
		char *dst, int ndst, int re_times)
{
	char   *find, *end = *pstr + *len;
	char   *ps = *pstr, *newstr, *ptmp;
	int     ret = -1;
	mem_re  mr, *mrn;

	if (NULL == *pstr || *len <= 0)
		return -1;

	if (nsrc == ndst && !memcmp(src, dst, nsrc))
		return 1;

	mr_init(&mr);

	while ((find = memmem(ps, end - ps, src, nsrc)) != NULL) {
		if (mr_add(&mr, ps, find - ps, Y_FIND) == -1)
			goto __end;

		ps = find + nsrc;
		*len += (ndst - nsrc);

		if (re_times == RE_ONE)
			break ;
	}
	
	if ((mrn = mr_gethead(&mr)) == NULL)  /* not find the string which need to replace */
		return 1;

	if (*ps != '\0') { 
		/* did not reach the end of string */
		if (mr_add(&mr, ps, end - ps, N_FIND) == -1) /* add the remaining string */
			goto __end;
	}

	if ((newstr = calloc(1, *len + 1)) == NULL)
		goto __end;

	for (ptmp = newstr; mrn != NULL; mrn = mrn->next) {
		memcpy(ptmp, mrn->ps, mrn->xlen);

		if (mrn->find == N_FIND)
			break ;

		memcpy(ptmp + mrn->xlen, dst, ndst);
		ptmp += (mrn->xlen + ndst);
	}

	free(*pstr);
	*pstr = newstr;
	(*pstr)[*len] = 0;
	ret = 1;

__end:
	mr_destroy(&mr);
	return ret;
}

int memreplace(char **pstr, int *len, char *src, int nsrc,
		char *dst, int ndst)
{
	/* default to replace all info of have src */
	return __memreplace(pstr, len, src, nsrc, dst, ndst, RE_ALL);
}

int memreplace_one(char **pstr, int *len, char *src, int nsrc,
		char *dst, int ndst)
{
	/* replace the first data */
	return __memreplace(pstr, len, src, nsrc, dst, ndst, RE_ONE);
}

int replacekey(char **buffer, int *buflen, char *srckey, char *srcvalue,
		char *dstkey, char *dstvalue)
{
	char src[64];
	char dst[64];

	sprintf(src, "%s%s", srckey, srcvalue);
	sprintf(dst, "%s%s", dstkey, dstvalue);

	return memreplace_one(buffer, buflen, src, strlen(src), dst,
			strlen(dst));
}
