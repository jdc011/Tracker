#include <iostream>
#include <fstream>
#include "List.hpp"
#include <stdlib.h> /* needed for getenv function to retrieve file reading 
                       directories */

static unsigned int find_index(const std :: string &);

List :: List()
{
   this->head = this->tail = 0;
   this->occupancy = 0;
}

LNode * List :: set_head(LNode * current)
{
   while(current->previous)
      current = current->previous;

   return current;
}

LNode * List :: set_tail(LNode * current)
{
   while(current->next)
      current = current->next;

   return current;
}

long List :: equals(Entry & lhs, Entry & rhs, Entry & instance)
{
   long is_equal = TRUE;
   std :: vector<std :: string> lvals = lhs.get_vals();
   std :: vector<std :: string> rvals = rhs.get_vals();

   for(unsigned int index = 0; index < instance.get_amt(); ++index)
   {
      if(lvals[index] == rvals[index])
         continue;
      else
      {
         is_equal = FALSE;
         break;
      }
   }

   return is_equal;
}

long List :: insert(Entry & entry, const std :: string & field, 
                    Entry & instance)
{
   std :: vector<std :: string> entry_value = entry.get_vals();
   std :: vector<std :: string> current_value;
   Entry * temp_entry;
   LNode * current = 0;
   LNode * adjustment = 0;
   long inserted = FALSE;
   unsigned int index = find_index(field);

   if(index == 0)
      return inserted;
   
   if(this->empty())
   {
      this->head = new LNode(&entry);
      this->tail = head;
      inserted = TRUE;
   }
   else
   {
      current = this->head;

      while(TRUE)
      {
         temp_entry = current->get_entry();
         current_value = temp_entry->get_vals();

         if(equals(*(temp_entry), entry, instance))
            return inserted;

         if(current_value[index] == entry_value[index])
         {
            if(index == instance.get_amt() - 1)
               index = 0;
            else 
               ++index;
         }

         if(current_value[index] < entry_value[index])
         {
            if(current->next)
            {
               current = current->next;
               continue;
            }
            else
               break;
         }
         else
            break;
      }
      
      if(current == this->head)
      {
         if(current_value[index] > entry_value[index])
         {
            current->previous = new LNode(&entry);
            current->previous->next = current;
            inserted = TRUE;
         }
         else if(current_value[index] < entry_value[index] 
                 && !current->next)
         {
            current->next = new LNode(&entry);
            current->next->previous = current;
            inserted = TRUE;
         }
      }
      else if(current == this->tail)
      {
         if(current_value[index] < entry_value[index])
         {
            current->next = new LNode(&entry);
            current->next->previous = current;
            inserted = TRUE;
         }
         else if(current_value[index] > entry_value[index] 
                 && !current->previous)
         {
            current->previous = new LNode(&entry);
            current->previous->next = current;
            inserted = TRUE;
         }
      }
      if(!inserted)
      {
         if(current_value[index] > entry_value[index])
         {
            adjustment = current->previous;
            current->previous = new LNode(&entry);
            current->previous->next = current;
            current->previous->previous = adjustment;
            adjustment->next = current->previous;
         }
         else if(current_value[index] < entry_value[index])
         {
            adjustment = current->next;
            current->next = new LNode(&entry);
            current->next->previous = current;
            current->next->next = adjustment;
            adjustment->previous = current->next;
         }

         inserted = TRUE;
      }
   }
      
   ++this->occupancy;

   if(current)
   {
      this->head = this->set_head(current);
      this->tail = this->set_tail(current);
   }

   return inserted;
}

long List :: remove(Entry & entry, const std :: string & field, 
                    Entry & instance)
{
   return 0;
}

long List :: find(Entry & instance, const std :: string & field, 
                  const std :: string & val)
{
   std :: vector<std :: string> entry_value;
   std :: vector<std :: string> entry_field = instance.get_fields();
   long found = FALSE;
   LNode * current = this->head;
   unsigned int index = find_index(field);

   if(index == 0)
      return found;

   while(TRUE)
   {
      entry_value = current->get_entry()->get_vals();

      if(entry_value[index] != val)
         continue;
      else
      {
         found = TRUE;

         if(entry_value[index] == val)
            current->print_node();
      }
      
      if(current->next)
         current = current->next;
      else
         break;
   }

   return found;
}

long List :: empty()
{
   long empty = FALSE;

   if(this->occupancy == 0)
      empty = TRUE;

   return empty;
}

void List :: print_list()
{

}

unsigned int find_index(const std :: string & field)
{
   std :: ifstream reader;
   std :: string all_data = "";
   char character;
   unsigned int index = 0;
   std :: string fields_dir = getenv("HOME");

   fields_dir = fields_dir + FIELDS_DIR;
   reader.open(fields_dir.c_str());

   while(TRUE)
   {
      character = reader.get();

      if(!reader.good())
         break;
      else
      {
         if(character == TAB)
         {
            if(all_data == field)
               break;

            all_data = "";
            ++index;
         }
         else
            all_data += character;
      }
   }

   reader.close();

   return index;
}

int main()
{
   std :: ofstream fio;
   Entry entry;
   std :: string one = "name";
   std :: string two = "number";
   std :: string & rone = one;
   std :: string & rtwo = two;
   entry.add_field(fio, rone);
   entry.add_field(fio, rtwo);

   std :: vector<std :: string> args1 = std :: vector<std :: string>(2, (std :: string) 0);
   std :: vector<std :: string> args2 = std :: vector<std :: string>(2, (std :: string) 0);

   args1[0] = "John";
   args1[1] = "123";
   args2[0] = "Britney";
   args2[1] = "324";

   Entry data1(args1, fio);
   Entry data2(args2, fio);

   List list;
   list.insert(data1, rone, entry);
   list.insert(data2, rone, entry);
      
   return 0;
}
