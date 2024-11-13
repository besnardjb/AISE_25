#include "mystring.h"

int main(int argc, char ** argv)
{
    string s = str_create("LOL MOI CONTENT");
    string s2 = str_create("LOL MOI CONTENT PLUS LONG QUE AVANT");


    str_print(s);
    str_copy(s, s2);
    str_print(s);

    str_append(s, s);

    str_print(s);

    string toslice = str_create("01234");
    string slice = str_slice(toslice, 3, 3);
    str_print(slice);


    str_free(toslice);
    str_free(s);
    str_free(s2);
    str_free(slice);

}