/*=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
File:          itos.cpp

Author:        Jeremy Cruz

Date:          6-12-16
-------------------------------------------------------------------------------
Description:   This is a helper function that serves to convert integers to
               strings. This assumes that the integer is unsigned and will not
               compile if a negative value is passed into this function. This is
               useful for hopping from file to file within the file system
               because this program will be named by numbers inside unique
               directories. Integers are easy to manipulate and countable so
               integers will be used to keep track of files in the database
               and these integers will be formatted as strings in order for
               the program to be able to access the correct corresponding file
               upon operations.
=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~*/

#include <stack> /* used for reversing the parsed integer */
#include <string> /* we have to return a string */

static const int MOD = 10; /* number used for integer parsing helped by mod */
static const int CHAR = 48; /* decimal conversion number to char data type */

/*..............................................................................
Name:       itos

Parameters: x: unsigned int to be converted to string format

Return:     ret_str: string form of unsigned int x

Purpose:    This will convert an unsigned int to a string format. It uses a 
            stack to parse the integer characters by dividing by mod. This
            sequence creates a reverse order that will be popped back into 
            regular order from the FILO data structure. When popping from the 
            stack, ret_str gets appended in correct order char by char by adding
            CHAR to the corresponding current int storing this into a char
            casted variable.
..............................................................................*/
std :: string itos(unsigned int x)
{
   std :: stack<unsigned int> ints; /* stack of parsed input */
   std :: string ret_str = ""; /* string to return */
   char current; /* current character in parsing sequence for conversion */

   /* push digits into the stack */
   do
   {
      ints.push(x % MOD);
      x /= MOD;
   }
   while(x != 0);

   /* pop char converted forms of digits from stack appending them to ret_str */
   while(!ints.empty())
   {
      current = ints.top() + CHAR;
      ret_str += current;
      ints.pop();
   }

   /* return the string format of x */
   return ret_str;
}
