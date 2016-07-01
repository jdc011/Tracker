#ifndef LIST_HPP
#define LIST_HPP
#include "LNode.hpp"

class List
{
   private:
      LNode * tail;
      LNode * head;
      unsigned int occupancy;

      LNode * set_head(LNode *);
      LNode * set_tail(LNode *);
      long equals(Entry &, Entry &, Entry &);

   public:
      List(void);
      long insert(Entry &, const std :: string &, Entry &);
      long remove(Entry &, const std :: string &, Entry &);
      long find(Entry &, const std :: string &, const std :: string &);
      long empty(void);
      void print_list(void);
};

#endif
