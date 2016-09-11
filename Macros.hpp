/*=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
File:          Macros.hpp

Author:        Jeremy Cruz

Date:          6-11-16
-------------------------------------------------------------------------------
Description:   This is a basic macros file with defined constants that will be 
               used throughout the program. It is included by every header class
               file found in this directory.
=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~*/

/* boolean flag constants for true and false */
#define TRUE 0
#define FALSE 1

/* exit code status constants for failure and success */
#define EXIT_PASS 0
#define EXIT_FAIL 1
#include <string>

const char TAB = '\t';
const std :: string DATA_DIR = "/tracker/data/";
const std :: string FIELDS_DIR = "/tracker/fields/fields";
const std :: string AMT_DIR = "/tracker/data/amt";
const std :: string OCC_DIR = "/tracker/data/occ";
