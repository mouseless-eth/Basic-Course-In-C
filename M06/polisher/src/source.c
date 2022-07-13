#include "source.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "strings.h"
#include "string.h"

/**
 * \brief Removes the C comments from the input C code.
 *
 * \details The function polishes the code by */
//          - removing the block comments delimited by /* and */.
/*            These comments may span multiple lines.You should remove only */
//            characters starting with /* and ending with */. The characters,
/*            including white space characters (' ', \n, \r, \t), */
//            after */ should not be removed.
/*
 *          - remove the line comments starting with // until and including the
 *            newline character \n.
 *
 * \param input A code segment that contains some comments.It is a dynamically
 *              allocated string(array of characters).
 * \return A pointer to the polished code
 */

char *delete_comments(char *input)
{
  int length = 0;
  while (input[length] != '\0')  {
    length++;
  }
  char* clean_string = calloc((unsigned int)length+1, sizeof(char));
  if (clean_string == NULL)
    return NULL;
  
  bool single_line = false;
  bool multiple_line = false;

  unsigned int i;
  unsigned int counter = 0;

  // Traverse through whole input program
  for (i=0; i<(unsigned int)length; i++) 
  {
    if(single_line == true && input[i] == '\n')
      single_line = false;
    else if (multiple_line == true && input[i] == '*' && input[i+1] == '/')
      multiple_line = false, i++;

    else if (single_line || multiple_line)
      continue;

    else if (input[i] == '/' && input[i+1] == '/')
      single_line = true, i++;
    else if (input[i] == '/' && input[i+1] == '*')
      multiple_line = true, i++;
    else clean_string[counter] = input[i], counter++;
  }

  free(input);
  return clean_string;
}
