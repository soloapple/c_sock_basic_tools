#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *mystrtok(char *s,const char *delim, char **l_last, char **p_store) 
{
    static char *last;
    char *tok;
    char *ucdelim;
    char *spanp;
    int c,sc;

    if (s == NULL && (s = last) == NULL)
        return NULL;
  
    
    int found = 0;
    
    cont:
    c=*s++;
    for (spanp = (char *)delim;(sc = *spanp++) != 0;)
    {
		printf ( "c:%d, sc:%d, *s++:%c, *spanp++:%c\n", c, sc, *s, *spanp );
        if (c == sc)
		{
			printf ( "qutra!\n" );
            goto cont;
		}
    }
    if (c == 0) 
    {
        last = NULL;
        return NULL;
    }

    tok = s-1;
    while (!found && *s != '\0') 
    {
        ucdelim = (char *) delim;
        while (*ucdelim) 
        {
            if (*s == *ucdelim) 
            {
                found = 1;
                *s = '\0';
				strncpy(*p_store, tok, strlen(tok));
                last = s + 1;
				printf ( "last:%s\n", last );
				*l_last = last;
				*s = *ucdelim;
                break;
            }
            ucdelim++;
        }
        if (!found)
        {
            s++;
            if(*s=='\0')
                last = NULL;
        }
    }

    return tok;
}

int 
main()
{
	char *l_last = NULL;
	char s[] = "23,45+67";
	char *ns = (char*)malloc(128);
	char *k1, *k2;
//	char *store = (char*)malloc(128);
	char store[128] = {0};
	char *p_store = store;

	k1 = mystrtok(s, ",+", &l_last, &p_store);
	if (l_last != NULL)
		printf ( "l_last:%s\n", l_last );
	printf ( "p_store:%s\n", p_store );

	k2 = mystrtok(l_last, ",+", &l_last, &p_store);
	if (l_last != NULL)
		printf ( "l_last:%s\n", l_last );
	printf ( "p_store:%s\n", p_store );

//	free(store);
	free(ns);

	return 0;
}
