//Gabriel Goldstein
//gjg180000
#ifndef USER_H
#define USER_H

#include <string>
#include "Order.h"

class User
{
public:
    User();
    User(std::string, std::string);
    virtual ~User();
    void addOrder(int, int, char, int, int, int);
    bool operator!=(User u)
    {
        return ((username != u.username) || (password != u.password));
    }
    bool operator==(User u)
    {
        return ((username == u.username) && (password == u.password));
    }
    std::string getUsername()
    {
        return username;
    }
    std::string getPassword()
    {
        return password;
    }
    Order* getFirstOrder()
    {
        return firstOrder;
    }
    void setFirstOrder(Order* ord)
    {
      firstOrder = ord;
    }
    int getNumOrders()
    {
        return numOrders;
    }
    void printOrders();
    Order* cancelOrder(int);
    void addToOrder(int, int, char, int, int, int);
    Order* getOrder(int);
protected:

private:
    std::string username;
    std::string password;
    Order* firstOrder;
    int numOrders;
};

#endif // USER_H
