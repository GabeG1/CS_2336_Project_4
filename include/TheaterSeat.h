//Gabriel Goldstein
//gjg180000
#ifndef THEATERSEAT_H
#define THEATERSEAT_H
#include "BaseNode.h"

class TheaterSeat: public BaseNode
{
public:
    TheaterSeat();
    TheaterSeat(TheaterSeat*, TheaterSeat*, TheaterSeat*, TheaterSeat*);
    TheaterSeat(int, char, bool, char);
    TheaterSeat(int, char, bool, char, int);
    TheaterSeat(int, char);
    TheaterSeat(TheaterSeat* &ts);
    virtual ~TheaterSeat();
    void setReserved(bool b)
    {
        reserved = b;
    }
    bool getReserved()
    {
        return reserved;
    }
    void setRight(TheaterSeat* r)
    {
        right = r;
    }
    void setLeft(TheaterSeat* l)
    {
        left = l;
    }
    void setUp(TheaterSeat* u)
    {
        up = u;
    }
    void setDown(TheaterSeat* d)
    {
        down = d;
    }
    TheaterSeat* getRight()
    {
        return right;
    }
    TheaterSeat* getLeft()
    {
        return left;
    }
    TheaterSeat* getUp()
    {
        return up;
    }
    TheaterSeat* getDown()
    {
        return down;
    }
    void setSeat(TheaterSeat);


protected:

private:
    TheaterSeat* up;
    TheaterSeat* down;
    TheaterSeat* right;
    TheaterSeat* left;

};

#endif // THEATERSEAT_H
