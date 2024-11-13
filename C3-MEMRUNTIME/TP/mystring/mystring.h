#ifndef MYSTRING_H
#define MYSTRING_H

#include <stdio.h>
/**
 * @file mystring.h
 * @brief Custom string manipulation functions.
 *
 * This header file provides a set of functions for working with strings in C.
 * The functions are designed to be safe and efficient, and include features like
 * dynamic memory allocation and bounds checking.
 */

struct string_internal_s
{
    char *s;
    size_t l;
};

typedef struct string_internal_s * string;

/**
 * @brief Creates a new string by dynamically allocating memory for the given character array.
 *
 * @param s The character array to copy into the new string.
 * @return A pointer to the newly created string.
 */
string str_create(char *s);

/**
 * @brief Frees the memory allocated for the given string.
 *
 * @param s The string to free.
 */
void str_free(string s);

/**
 * @brief Copies one string into another, up to a maximum length of strlen(src) + 1 characters.
 *
 * @param dest The destination string to copy into.
 * @param src The source string to copy from.
 * @return 0 on success, or an error code if the operation fails.
 */
int str_copy(string dest, string src);

/**
 * @brief Compares two strings lexicographically.
 *
 * @param a The first string to compare.
 * @param b The second string to compare.
 * @return A negative integer if a < b, 0 if a == b, or a positive integer if a > b.
 */
int str_compare(string a, string b);

/**
 * @brief Appends one string to the end of another.
 *
 * @param to The destination string to append to.
 * @param add The source string to append from.
 * @return 0 on success, or an error code if the operation fails.
 */
int str_append(string to, const string add);

/**
 * @brief Extracts a substring from the given string, starting at the specified offset and ending at the specified length.
 *
 * @param targ The original string to extract from.
 * @param start The starting offset of the substring.
 * @param end The ending offset of the substring (exclusive).
 * @return A pointer to the newly created substring.
 */
string str_slice(string targ, size_t start, size_t end);


/**
 * @brief Prints the contents of a string to the standard output stream.
 * @param str The string to print.
 * @return 0 on success, or an error code if the operation fails.
 */
int str_print(string str);

/**
 * Note: This function does not perform any bounds checking or error handling
 * for the input string. It is assumed that the caller has already verified
 * the integrity of the string data before passing it to this function.
 */

#endif /* MYSTRING_H */