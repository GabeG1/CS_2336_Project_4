//Gabriel Goldstein
//gjg180000
#include "TheaterSeat.h"

TheaterSeat::TheaterSeat()
{
    up = nullptr;
    down = nullptr;
    right = nullptr;
    left = nullptr;
}
TheaterSeat::TheaterSeat(TheaterSeat* u, TheaterSeat* d, TheaterSeat* r, TheaterSeat* l)
{
    up = u;
    down = d;
    right = r;
    left = l;

}
TheaterSeat::TheaterSeat(int r, char s, bool res, char tt) : BaseNode::BaseNode(r, s, res, tt)
{


}

TheaterSeat::TheaterSeat(int r, char s) : BaseNode::BaseNode(r, s, false, '.')
{

}
TheaterSeat::TheaterSeat(TheaterSeat* &ts) : BaseNode::BaseNode(ts->getRow(), ts->getSeat(), ts->isReserved(), ts->getTicketType())
{


    right = ts->right;
    left = ts->left;
    up = ts->up;
    down = ts->down;

}
void TheaterSeat::setSeat(TheaterSeat ts)
{
    this->setTicketType(ts.getTicketType());
    this->setReserved(true);

}
TheaterSeat::~TheaterSeat()
{

}
