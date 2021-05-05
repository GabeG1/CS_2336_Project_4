//Gabriel Goldstein
//gjg180000
#include "User.h"
#include <string>
#include "TheaterSeat.h"
#include <iostream>
#include <iomanip>

User::User()
{
    //ctor
}

User::User(std::string u, std::string p)
{
    username = u;
    password = p;
    firstOrder = nullptr;
    numOrders = 0;
}

User::~User()
{
    //dtor
}

void User::addOrder(int audNum, int row, char startingSeat, int numAdult, int numChild, int numSenior)
{
    TheaterSeat* ts;
    if(numAdult > 0)
    {
        ts = new TheaterSeat(row, startingSeat, true, 'A');
    }
    else if (numChild > 0)
    {
        ts = new TheaterSeat(row, startingSeat, true, 'C');
    }
    else
    {
        ts = new TheaterSeat(row, startingSeat, true, 'S');
    }
    if(!firstOrder)
    {
        firstOrder = new Order(audNum, ts, numAdult, numChild, numSenior);
        firstOrder->setNextOrder(nullptr);
    }
    else
    {
        Order* cur = firstOrder;
        while(cur->getNextOrder())
        {
            cur = cur->getNextOrder();
        }
        cur->setNextOrder(new Order(audNum, ts, numAdult, numChild, numSenior));
        cur = cur->getNextOrder();
        cur->setNextOrder(nullptr);
    }
    numOrders++;

}
void User::printOrders()
{
    Order* cur = firstOrder;
    int orderNum = 1;
    while(cur)
    {
        TheaterSeat* seat = cur->getStartingSeat();
        int row = seat->getRow();
        std::cout << "Order: " << std::right <<  std::setw(13) << orderNum << "\n";
        std::cout << "Auditorium: " << std::right <<  std::setw(8) << cur->getAuditorium() << std::endl;

        std::cout << "Seats: " << std::right <<  std::setw(13) << seat->getRow() << ":";

        while(seat)
        {
            if(seat->getRow() != row)
            {
                std::cout << "   " << seat->getRow() << ":";
                row = seat->getRow();

            }
            std::cout << " " << seat->getSeat();
            seat = seat->getRight();
        }
        std::cout << "\nAdult Tickets: " << std::right <<  std::setw(5) << cur->getAdultTickets()
                  << "\nChild Tickets: " << std::right <<  std::setw(5) << cur->getChildTickets()
                  << "\nSenior Tickets: " << std::right <<  std::setw(4) << cur->getSeniorTickets() << std::endl;
        cur = cur->getNextOrder();
        orderNum++;
        std::cout << "\n";
    }

}

//Delete entire order
Order* User::cancelOrder(int orderNum)
{
    Order* trailOrder = getOrder(orderNum - 1);
    Order* order = getOrder(orderNum);

    //If the first order is the one to be deleted
    if(!trailOrder)
    {
        //Set the first order to be the next order
        firstOrder = firstOrder->getNextOrder();
    }

    //Otherwise, if it is not the first order
    else
    {
        //Make the previous order linked to the order after the one that is to be removed
        trailOrder->setNextOrder(order->getNextOrder());
        order->setNextOrder(nullptr);
    }
    numOrders--;
    return order;
}

//Increase an order
void User::addToOrder(int numOrder, int row, char seat, int numAdults, int numChildren, int numSeniors)
{
    //Find order and increase it with the seats the user requests
    Order* order = getOrder(numOrder);
    order->increaseOrder(TheaterSeat (row, seat), numAdults, numChildren, numSeniors);
}

//Find the order
Order* User::getOrder(int orderNum)
{
    //If the order does not exist
    if(orderNum <= 0)
    {
        return nullptr;
    }
    Order* order = firstOrder;
    int i = 1;

    //Otherwise, search for the order until it is found
    while (order && i < orderNum)
    {
        order = order->getNextOrder();
        i++;
    }
    return order;
}
