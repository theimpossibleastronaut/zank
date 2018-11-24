/** \file utils.c
 */

#include <limits.h>
#include "utils.h"

 /* reverse:  reverse string s in place */
static void
reverse (char s[])
{
  int i, j;
  for (i = 0, j = strlen (s) - 1; i < j; i++, j--)
  {
    char c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

 /* itoa:  convert n to characters in s */
void
itoa (int n, char s[])
{
  int i, sign;

  if ((sign = n) < 0)           /* record sign */
    n = -n;                     /* make n positive */
  i = 0;
  do
  {                             /* generate digits in reverse order */
    s[i++] = n % 10 + '0';      /* get next digit */
  }
  while ((n /= 10) > 0);        /* delete it */
  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse (s);
}

/*
 *
 * del_char_shift_left():
 *
 * Erases characters from the beginning of a string
 * (i.e. shifts the remaining string to the left
 *
 */
void
del_char_shift_left (const char c, char **str)
{
  while (**str == c)
    (*str)++;

  return;
}

/** Generate a unique game user id.
 *
 * When the return value of time(NULL) is used to seed the random
 * number generator (as is done in main), 2 clients connecting at the
 * same moment would get the same guid. This function uses the address
 * of guid as the key to "encrypt" a randomly generated string. This
 * prevents the likelihood that 2 guids would ever be the same.
 *
 * FIXME:
 * It should be noted that this function, though it works, is horribly written
 * due to Andy's inexperience with cryptography and math.
 * @param[in,out] guid
 * @return void
 */
void
generate_guid (char *guid)
{
  char guid_key[BUF_SIZE];
  snprintf  (guid_key, BUF_SIZE, "%p",
            (void*)&guid);

  int guid_pos = 0;
  while (guid_pos < GID_LEN - 1)
  {
    int tmp_char = 0;
    do
    {
      tmp_char = rand() % (UCHAR_MAX);
    }while (!isalnum (tmp_char));

    guid[guid_pos] = (char)tmp_char;
    guid_pos++;
  }

  int guid_key_pos = 0;

  while (guid_key[guid_key_pos] != '\0')
  {
    guid_pos = 0;
    while (guid[guid_pos] != '\0')
    {
      do
      {
        unsigned int offset = guid_key[guid_key_pos] - ('0' - 1);
        if (offset > 'z' - '0' - 1)
          offset = rand () % guid_key[guid_key_pos];

        guid[guid_pos] += offset;

        if (guid[guid_pos] > 'z')
        {
          guid[guid_pos] -= offset;
        }
      } while (! isalnum (guid[guid_pos]));
      guid_pos++;
    }
    guid_key_pos++;
  }

  printf ("game_id = %s\n", guid);
}
