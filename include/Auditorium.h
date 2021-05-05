//Gabriel Goldstein
//gjg180000
#ifndef AUDITORIUM_H
#define AUDITORIUM_H
#include "TheaterSeat.h"
#include <fstream>

class Auditorium
{
public:
    Auditorium()
    {

    }
     Auditorium(std::string);
    void printAuditorium();
    virtual ~Auditorium();
    TheaterSeat* getFirstSeat()
    {
        return first;
    }
    void setFirstSeat(TheaterSeat* f)
    {
        first = f;
    }
    bool isEmpty();
    int getNumRows()
    {
        return numRows;
    }
    int getNumSeats()
    {
        return numSeats;
    }
    void changeSeatStatus(int, char, bool, char);
protected:

private:
    TheaterSeat *first;
    int numSeats;
    int numRows;
};

#endif // AUDITORIUM_H
