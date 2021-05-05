//Gabriel Goldstein
//gjg180000
#include "Order.h"

Order::Order()
{

}
Order::Order(int audNum, TheaterSeat* ts, int numAdult, int numChild, int numSenior)
{
    auditorium = audNum;
    numAdultTickets = numAdult;
    numChildTickets = numChild;
    numSeniorTickets = numSenior;
    startingSeat = ts;
    TheaterSeat* cur = startingSeat;

    //Set the new order by adding the seats to it (except the first seat, which has already been added above)
    for(int i = 0; i < (numAdult + numChild + numSenior - 1); i++)
    {

        //Add all adult seats
        if(i < numAdultTickets - 1)
            cur->setRight(new TheaterSeat(cur->getRow(), (char)(cur->getSeat() + 1), true, 'A'));

        //Then add all child seats
        else if (i < (numAdultTickets + numChildTickets - 1))
        {
            cur->setRight(new TheaterSeat(cur->getRow(), (char)(cur->getSeat() + 1), true, 'C'));
        }
        //Then add all the senior seats
        else
        {
            cur->setRight(new TheaterSeat(cur->getRow(), (char)(cur->getSeat() + 1), true, 'S'));
        }
        cur = cur->getRight();
    }
    cur->setRight(nullptr);
}

Order::~Order()
{

}

//Remove a ticket from an order
void Order::deleteTicket(TheaterSeat ts)
{
    TheaterSeat* trailCur = nullptr;
    TheaterSeat* cur = startingSeat;

    //While the seat to be removed has not been found
    while(cur)
    {
        //If the seat in the order is found
        if((cur->getRow() == ts.getRow()) && (cur->getSeat() == ts.getSeat()))
        {

            //Decrease the appropriate ticket type by 1.
            if(cur->getTicketType() == 'A')
            {
                numAdultTickets--;
            }
            else if(cur->getTicketType() == 'C')
            {
                numChildTickets--;
            }
            else
            {
                numSeniorTickets--;
            }
            if(!trailCur)
            {
                startingSeat = startingSeat->getRight();
            }
            else
            {
                trailCur->setRight(cur->getRight());
            }
            cur->setRight(nullptr);
            delete cur;
        }
        trailCur = cur;
        cur = cur->getRight();
    }

}

//Increase an order
void Order::increaseOrder(TheaterSeat seat, int adults, int children, int seniors)
{
    TheaterSeat* trailCur = nullptr;
    TheaterSeat* cur = startingSeat;

    //Traverse the order until the row of the seat to be added is
    //greater than the existing rows in the order
    while(cur && (seat.getRow() > cur->getRow()))
    {
        trailCur = cur;
        cur = cur->getRight();
    }

    //If there are already seats in the order from that same row
    if(cur && (seat.getRow() == cur->getRow()))
    {

        //Traverse the list until the seat to be added is greater than
        //the seats in the row already reserved
        while (cur && (seat.getSeat()  > cur->getSeat()))
        {
            trailCur = cur;
            cur = cur->getRight();
        }
    }

    //Add the seats to the order
    for(int i = 0; i < (adults + children + seniors); i++)
    {

        TheaterSeat* newSeat;

        //Add the adult tickets first
        if(i < adults)
        {
            newSeat = new TheaterSeat(seat.getRow(), (char)(seat.getSeat() + i), true, 'A');

        }

        //Then add the child tickets
        else if (i < (adults + children))
        {
            newSeat = new TheaterSeat(seat.getRow(), (char)(seat.getSeat() + i), true, 'C');
        }

        //Then add the senior tickets
        else
        {
            newSeat = new TheaterSeat(seat.getRow(), (char)(seat.getSeat() + i), true, 'S');
        }

        //If this is the first seat in the order (in terms of location in auditorium),
        //make it the new starting seat in the order
        if(!trailCur)
        {
            newSeat->setRight(startingSeat);
            startingSeat = newSeat;
        }
        //Otherwise, input the seat in the appropriate location in the order
        else
        {
            trailCur->setRight(newSeat);
            newSeat->setRight(cur);
        }
        trailCur = newSeat;
    }
    numAdultTickets += adults;
    numChildTickets += children;
    numSeniorTickets += seniors;
}

//Check to see if a seat exists in a certain order
bool Order::exists(TheaterSeat ts)
{
    TheaterSeat* cur = startingSeat;
    while(cur)
    {
        //If the seat is found, return true
        if((cur->getRow() == ts.getRow()) && (cur->getSeat() == ts.getSeat()))
        {
            return true;
        }
        cur = cur->getRight();
    }

    //If the seat is not found, return false
    return false;
}
