/** \file utils.h
 */

#include "zank.h"

#define GUID_LEN (32 + 1)

void itoa (int n, char s[]);
void del_char_shift_left (const char c, char **str);
void generate_guid (char *guid);
