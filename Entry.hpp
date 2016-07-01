/*=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
File:          Entry.hpp

Author:        Jeremy Cruz

Date:          6-14-16
-------------------------------------------------------------------------------
Description:   This class is used for creating an instance object of an entry,
               and to insert specific entries into a data structure via 
               overloaded constructor. Fields are dynamically assigned via 
               vector both for general variable assignment, and specific value
               assignment.
=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~*/
#ifndef ENTRY_HPP
#define ENTRY_HPP

#include <vector> /* container to keep track of fields and values */
#include <string> /* insertion to containers and data to be stored */
#include <fstream> /* file reading capabilities */
#include "Macros.hpp" /* include defined constants */

/*------------------------------------------------------------------------------
Class:      Entry

Purpose:    Entries are pieces of data inserted into the overall data structure
            to be implemented via list and binary tree for this initial project.
            Entries contain fields that are stored in vectors which can be
            dynamically inserted, removed, and reset.

Functions:  assign_fields: assign the fields all entries have

            assign_amt:    assign specific values to each field for this entry

            Entry:         default constructor is for creating this object,
                           overloaded constructor is for inserting instances
                           of this object into the data base

            add_field:     insert type of field for all entries     

            remove_field:  remove a particular field for all entries

            get_amt:       return amount of fields

            get_fields:    return fields for all entries

            get_val:       return specific field values for specific entry


Fields:     fields:     vector of fields for entries

            vals:       field values for a specific entry

            field_amt:  amount of fields in all entries
------------------------------------------------------------------------------*/
class Entry
{
   /* fields */
   private:
      std :: vector<std :: string> fields; 
      std :: vector<std :: string> vals;
      unsigned int field_amt;

      /* helper functions in initializing fields */
      std :: vector<std :: string> assign_fields(void);
      unsigned int assign_amt(void);

   /* functions */
   public:
      Entry(void);
      Entry(std :: vector<std :: string> &, std :: ofstream &);
      long add_field(std :: ofstream &, const std :: string &);
      long remove_field(std :: ofstream &, const std :: string &);
      void reset(void);
      unsigned int get_amt(void);
      std :: vector<std :: string> get_fields(void);
      std :: vector<std :: string> get_vals(void);
};

#endif
