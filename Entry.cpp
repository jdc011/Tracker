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
#include <iostream>
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
      std :: vector<std :: string>(this->get_amt(), (std :: string) "");

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

std :: vector<std :: string> Entry :: add_vals(std :: ofstream & data, 
                                               const std :: 
                                               vector<std :: string> values)
{
   std :: ifstream reader;
   std :: ofstream vals;
   std :: string data_dir = getenv("HOME");
   data_dir = data_dir + DATA_DIR + itos(this->occupancy); 
   
   data.open(data_dir.c_str(), std :: ios_base :: app);
  
   for(unsigned int index = 0; index < values.size(); ++index)
      data << values[index] << TAB;
   
   data.close();

   return values;
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

unsigned int Entry :: assign_occ()
{
   std :: ifstream reader;
   std :: string file_dir = getenv("HOME");
   unsigned int occ;

   file_dir = file_dir + OCC_DIR;
   reader.open(file_dir.c_str());
   reader >> occ;
   reader.close();

   return occ;
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
   this->occupancy = this->assign_occ();
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
Entry :: Entry(std :: vector<std :: string> & vals, std :: ofstream & data)
{
   std :: string occ_file = getenv("HOME");
   
   occ_file = occ_file + OCC_DIR;
   ++this->occupancy;   
   data.open(occ_file.c_str());
   data << this->occupancy;
   data.close();
   this->vals = this->add_vals(data, vals);
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
                                               (std :: string) "");
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
                                                     (std :: string) "");
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
   int current;
   std :: ofstream data_reader,
                   fields_reader,
                   amt_reader,
                   occ_reader;
   std :: string data_dir = getenv("HOME");
   std :: string fields_dir = getenv("HOME");
   std :: string amt_dir = getenv("HOME");
   std :: string occ_dir = getenv("HOME");

   for(current = 1; current <= this->occupancy; ++current)
   {
      data_dir = data_dir + DATA_DIR + itos(current);
      data_reader.open(data_dir.c_str());
      data_reader << "";
      data_reader.close();
      data_dir = getenv("HOME");
   }

   fields_dir = fields_dir + FIELDS_DIR;
   amt_dir = amt_dir + AMT_DIR;
   occ_dir = occ_dir + OCC_DIR; 
   fields_reader.open(fields_dir.c_str());
   amt_reader.open(amt_dir.c_str());
   occ_reader.open(occ_dir.c_str());
   fields_reader << "";
   amt_reader << 0;
   occ_reader << 0;
   fields_reader.close();
   amt_reader.close();
   occ_reader.close();
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

unsigned int Entry :: get_occupancy()
{
   return this->occupancy;
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
