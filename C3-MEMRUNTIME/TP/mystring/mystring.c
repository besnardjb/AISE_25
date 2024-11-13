#include "mystring.h"

#include <string.h>
#include <stdlib.h>

string str_create(char *s)
{

    int len = strlen(s);

    string ret = malloc(sizeof(struct string_internal_s));
    ret->s = malloc(len + 1);
    ret->l = len + 1;

    if(! ret->s )
    {
        ret->s = NULL;
        ret->l = 0;
    }
    else
    {
        memcpy(ret->s, s, len + 1);
    }
    return ret;
}

void str_free(string str)
{
    printf("FREE %p\n", str->s);
    free(str->s);
    free(str);
}

int str_copy(string dest, string src)
{
    if(dest == src)
    {
        return 0;
    }

    dest->s = realloc(dest->s, src->l);
    
    if(!dest->s)
    {
        perror("realloc");
        return 1;
    }
    
    dest->l = src->l;
    memcpy(dest->s, src->s, src->l);

    return 0;
}

int str_compare(string a, string b)
{
    return strcmp(a->s, b->s);
}

int str_print(string str)
{
    printf("%s\n", str->s);
    return 0;
}

int str_append(string to, const string add)
{
    size_t prev_l = to->l;
    size_t new_size = to->l + add->l -1;
    to->s = realloc(to->s, new_size);


    memcpy(to->s + (prev_l - 1), add->s, add->l);

    to->l = new_size;

    return 0;
}

string str_slice(string targ, size_t start, size_t end)
{
    string str = str_create("");

    if(end < start)
    {
        return str;
    }

    if(targ->l <= end)
    {
        return str;
    }

    size_t len = (end - start) + 2;

    str->s = realloc(str->s, len);
    str->l = len;

    memcpy(str->s, targ->s + start, len - 1);
    str->s[str->l - 1] = '\0';

    return str;
}

