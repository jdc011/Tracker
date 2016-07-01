/*=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
File:          Entry.hpp

Author:        Jeremy Cruz

Date:          6-14-16
-------------------------------------------------------------------------------
Description:   This contains all the implementation for entry type data. Fields
               can be inserted and removed dynamically. There is implementation
               for creating this class, and inserting specific instances of this
               class. Entry implements file reading features that save its data
               to a hard disk and removes data accordingly saving every state
               recorded in RAM to the disk.
=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~*/
#include "Entry.hpp"
#include <stdlib.h> /* needed for getenv function to retrieve file reading 
                       directories */
#include "itos.cpp" /* function turning integers to string formats */

/*..............................................................................
Name:       assign_fields

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
std :: vector<std :: string> Entry :: assign_fields()
{
   std :: ifstream reader;
   std :: string file_dir = getenv("HOME");
   char character;
   std :: string all_data = "";
   std :: vector<std :: string> ret_vector = 
      std :: vector<std :: string>(this->get_amt(), (std :: string) 0);

   file_dir = file_dir + FIELDS_DIR;
   reader.open(file_dir.c_str());

   for(unsigned int index = 0; index < this->get_amt(); ++index)
   {
      while(TRUE)
      {
         character = reader.get();

         if(!reader.good())
            break;
         else
         {
            if(character == TAB)
               break;
            else
               all_data += character;
         }
      }

      ret_vector[index] = all_data;
      all_data = "";
   }

   reader.close();

   return ret_vector;
}

/*..............................................................................
Name:       assign_amt

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
unsigned int Entry :: assign_amt()
{
   std :: ifstream reader;
   std :: string file_dir = getenv("HOME");
   unsigned int amt;

   file_dir = file_dir + AMT_DIR;
   reader.open(file_dir.c_str());
   reader >> amt;
   reader.close();

   return amt;
}

/*..............................................................................
Name:       Entry

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
Entry :: Entry()
{
   this->field_amt = this->assign_amt();
   this->fields = this->assign_fields();
}

/*..............................................................................
Name:       Entry

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
Entry :: Entry(std :: vector<std :: string> & vals, 
               std :: ofstream & data)
{
   std :: string current_file = getenv("HOME");
   this->vals = std :: vector<std :: string>(this->get_amt(), 
                                             (std :: string) 0);

   for(int index = 0; index < this->get_amt(); ++index)
   {
      current_file = current_file + DATA_DIR + itos(index);
      this->fields[index] = vals[index];
      data.open(current_file.c_str());
      data << this->fields[index] << TAB;
      data.close();
   }
}

/*..............................................................................
Name:       add_field

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
long Entry :: add_field(std :: ofstream & data, const std :: string & arg)
{
   std :: ifstream reader;
   std :: ofstream amt;
   std :: string amt_dir = getenv("HOME");
   std :: string file_dir = getenv("HOME");
   unsigned int current = this->get_amt();
   long inserted = FALSE;
   char character;
   std :: string all_data = "";

   for(unsigned int index = 0; index < this->get_amt(); ++index)
   {
      if(this->fields[index] == arg)
         return inserted;
   }

   ++this->field_amt;
   amt_dir = amt_dir + AMT_DIR;
   amt.open(amt_dir.c_str());
   amt << this->field_amt;
   amt.close();
   this->fields = std :: vector<std :: string>(this->get_amt(), 
                                               (std :: string) 0);
   file_dir = file_dir + FIELDS_DIR;
   data.open(file_dir.c_str(), std :: ios_base :: app);
   data << arg << TAB;
   data.close();
   inserted = TRUE;
   reader.open(file_dir.c_str());

   for(unsigned int index = 0; index < this->get_amt(); ++index)
   {
      while(TRUE)
      {
         character = reader.get();

         if(!reader.good())
            break;
         else
         {
            if(character == TAB)
               break;
            else
               all_data += character;
         }
      }

      this->fields[index] = all_data;
      all_data = "";  
   }

   reader.close();

   return inserted;
}

/*..............................................................................
Name:       remove_field

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
long Entry :: remove_field(std :: ofstream & data, const std :: string & arg)
{
   std :: ifstream reader;
   std :: ofstream amt;
   std :: string amt_dir = getenv("HOME");
   std :: string file_dir = getenv("HOME");
   unsigned int current = this->get_amt();
   long removed = FALSE;
   char character;
   std :: string all_data = "";

   for(unsigned int index = 0; index < this->get_amt(); ++index)
   {
      if(this->fields[index] == arg)
      {
         file_dir = file_dir + FIELDS_DIR;
         data.open(file_dir.c_str());

         for(unsigned int track = 0; track < this->get_amt() - 1; ++track)
         {
            if(track == index)
            {
               --track;
               continue;
            }

            data << arg << TAB;
         }
         
         data.close();
         removed = TRUE;
         --this->field_amt;
         amt_dir = amt_dir + AMT_DIR;
         amt.open(amt_dir.c_str());
         amt << this->field_amt;
         amt.close();
         this->fields = std :: vector<std :: string>(this->get_amt(),
                                                     (std :: string) 0);
         break;
      }

      continue;
   }

   if(!removed)
      return removed;

   reader.open(file_dir.c_str());

   for(unsigned int index = 0; index < this->get_amt(); ++index)
   {
      while(TRUE)
      {
         character = reader.get();

         if(!reader.good())
            break;
         else
         {
            if(character == TAB)
               break;
            else
               all_data += character;
         }
      }

      this->fields[index] = all_data;
      all_data = "";
   }

   reader.close();

   return removed;
}

/*..............................................................................
Name:       reset

Parameters: none

Return:     void

Purpose:    This will convert an unsigned int to a string format. It uses a 
            stack to parse the integer characters by dividing by mod. This
            sequence creates a reverse order that will be popped back into 
            regular order from the FILO data structure. When popping from the 
            stack, ret_str gets appended in correct order char by char by adding
            
..............................................................................*/
void Entry :: reset()
{
   std :: ofstream fields_reader,
                   amt_reader;
   std :: string fields_dir = getenv("HOME");
   std :: string amt_dir = getenv("HOME");

   fields_dir = fields_dir + FIELDS_DIR;
   amt_dir = amt_dir + AMT_DIR;
   fields_reader.open(fields_dir.c_str());
   amt_reader.open(amt_dir.c_str());
   fields_reader << "";
   amt_reader << 0;
   fields_reader.close();
   amt_reader.close();
   this->field_amt = this->assign_amt();
   this->fields = this->assign_fields();
}

/*..............................................................................
Name:       get_amt

Parameters: none

Return:     field_amt: amount of fields for every entry

Purpose:    Access the amount of fields for every instance of this class.
..............................................................................*/
unsigned int Entry :: get_amt()
{
   /* return the field_amt datafield */
   return this->field_amt;
}

/*..............................................................................
Name:       get_fields

Parameters: none

Return:     fields: general datafield variables for all instances of this class

Purpose:    Access field variables for every instance of this class.
..............................................................................*/
std :: vector<std :: string> Entry :: get_fields()
{
   /* return thie fields datafield */
   return this->fields;
}

/*..............................................................................
Name:       get_vals

Parameters: none

Return:     vals: specific datafield values for a specific instance of this 
                  class

Purpose:    Access the specific data values of a specific instance of this 
            class.
..............................................................................*/
std :: vector<std :: string> Entry :: get_vals()
{
   /* return the vals datafield */
   return this->vals;
}
