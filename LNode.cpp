#include "LNode.hpp"

LNode :: LNode(Entry * entry)
{
   this->entry = entry;
   this->previous = this->next = 0;
}

Entry * LNode :: get_entry()
{
   return this->entry;
}

void print_node()
{

}
