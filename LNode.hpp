#ifndef LNODE_HPP
#define LNODE_HPP
#include "Entry.hpp"

class LNode
{
   private:
      LNode * previous;
      LNode * next;
      Entry * entry;

   friend class List;

   public:
      LNode(Entry *);
      Entry * get_entry(void);
      void print_node(void);
};

#endif
