//Gabriel Goldstein
//gjg180000
#include "BaseNode.h"

BaseNode::BaseNode()
{
    row = 0;
}

BaseNode::BaseNode(int r, char s, bool res, char tt)
{
    row = r;
    seat = s;
    reserved = res;
    ticketType = tt;
}

BaseNode::~BaseNode()
{
    //dtor
}
