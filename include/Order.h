//Gabriel Goldstein
//gjg180000
#ifndef ORDER_H
#define ORDER_H

#include "TheaterSeat.h"

class Order
{
public:
    Order();
    Order(int, TheaterSeat*, int, int, int);
    virtual ~Order();
    void setNextOrder(Order* ord)
    {
        nextOrder = ord;

    }
    Order* getNextOrder()
    {
        return this->nextOrder;
    }
    int getAdultTickets()
    {
        return numAdultTickets;
    }
    int getChildTickets()
    {
        return numChildTickets;
    }
    int getSeniorTickets()
    {
        return numSeniorTickets;
    }
    void setNumAdults(int a)
    {
        numAdultTickets = a;
    }
    void setNumChildren(int c)
    {
        numChildTickets = c;
    }
    void setSeniorTickets(int s)
    {
        numSeniorTickets = s;
    }
    int getAuditorium()
    {
        return auditorium;
    }
    TheaterSeat* getStartingSeat()
    {
        return startingSeat;
    }
    void deleteTicket(TheaterSeat ts);
    void increaseOrder(TheaterSeat, int, int, int);
    bool exists(TheaterSeat);
protected:

private:
    int auditorium;
    TheaterSeat* startingSeat;
    int numAdultTickets;
    int numChildTickets;
    int numSeniorTickets;
    Order * nextOrder;
};

#endif // ORDER_H
