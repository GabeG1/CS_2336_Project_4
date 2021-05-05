//Gabriel Goldstein
//gjg180000
#include "Auditorium.h"
#include <fstream>
#include <string>
Auditorium::Auditorium(std::string audName)
{
    //Confirm that the file is open
    std::ifstream auditorium(audName);
    if(auditorium.is_open())
    {

        std::string lineBelow = "";
        numRows = 1;

        //Get the first line in the file (the first row)
        getline(auditorium, lineBelow);
        numSeats = (int)lineBelow.length();

        //Make sure the row is not empty
        if(lineBelow != "")
        {
            //If the first seat is empty
            if(lineBelow[0] == '.')
            {
                first = new TheaterSeat(1, 'A', false, '.');

            }
            //If the first seat is reserved
            else
            {
                first = new TheaterSeat(1, 'A', true, lineBelow[0]);
            }
            first->setRight(nullptr);
            first->setDown(nullptr);
            first->setLeft(nullptr);
            first->setUp(nullptr);
        }
        else
        {
            first = nullptr;
        }

        //Make sure first seat exists
        if(first != nullptr)
        {
            TheaterSeat* firstSeatInCurrentRow = first;
            TheaterSeat* currentSeat;

            //Run while the row being checked exists
            while(lineBelow != "")
            {
                std::string lineAbove = "";
                char seatLetter = 'B';

                //Get the line above the row being checked
                getline(auditorium, lineAbove);

                currentSeat = firstSeatInCurrentRow;

                //Starting from the first seat in the row, create the seat to the right,
                //And connect that seat back to the seat to the left using the left pointer
                for (int i = 1; i < (int)lineBelow.length(); i++)
                {
                    currentSeat->setRight(new TheaterSeat(numRows, seatLetter, lineBelow[i] != '.', lineBelow[i]));
                    currentSeat->getRight()->setLeft(currentSeat);
                    currentSeat = currentSeat->getRight();
                    seatLetter++;

                    //If the last seat in the row is reached, set the seat to the right to be null.
                    if(i == (int)lineBelow.length() - 1)
                    {
                        currentSeat->setRight(nullptr);
                    }
                }

                //If there is only one seat in the row, set the seat to the right to be null
                if(lineBelow.length() == 1)
                {
                    firstSeatInCurrentRow->setRight(nullptr);
                }
                //Move to the row above by setting row below equal to row above.
                lineBelow = lineAbove;

                //If the new row is empty, set the up pointer (which in this case refers to the next row: e.g. the row above 4 is 5
                //in this program) to be null.
                if(lineBelow == "")
                {
                    firstSeatInCurrentRow->setUp(nullptr);
                    continue;
                }
                //If the next row exists, create the first seat in the row above by using up pointer
                firstSeatInCurrentRow->setUp(new TheaterSeat(numRows + 1, 'A', lineAbove[0] != '.', lineAbove[0]));
                firstSeatInCurrentRow->getUp()->setDown(firstSeatInCurrentRow);
                firstSeatInCurrentRow = firstSeatInCurrentRow->getUp();
                firstSeatInCurrentRow->setLeft(nullptr);
                numRows++;

            }

            //Now that the rows have been connected horizontally (outside of the first seats, which are connect vertically as well)
            //now connect all the seats vertically using the up and down pointers
            TheaterSeat* secondSeatInCurrentRow = first->getRight();

            //Run until all the rows have been gone through
            while(secondSeatInCurrentRow != nullptr)
            {
                currentSeat = secondSeatInCurrentRow;

                //Run until all the seats in the row have been gone through
                while(currentSeat != nullptr)
                {
                    //If this is the first row, make the down pointer null for each seat
                    if(secondSeatInCurrentRow->getLeft()->getDown() == nullptr)
                    {

                        currentSeat->setDown(nullptr);

                    }
                    //If this is the last row, make the up pointer null for each seat
                    if(secondSeatInCurrentRow->getLeft()->getUp() == nullptr)
                    {

                        currentSeat->setUp(nullptr);
                        currentSeat = currentSeat->getRight();
                        continue;

                    }
                    //Otherwise, connect the current seat to the seat above through the up pointer,
                    currentSeat->setUp(currentSeat->getLeft()->getUp()->getRight());

                    //Connect the seat above to the seat below using the down pointer
                    currentSeat->getUp()->setDown(currentSeat);
                    //Move to the next seat in the row
                    currentSeat = currentSeat->getRight();
                }
                //Move to the next row
                secondSeatInCurrentRow = secondSeatInCurrentRow->getUp();
            }

        }

        auditorium.close();
    }

}



Auditorium::~Auditorium()
{
    TheaterSeat* tempPointerOne = nullptr;
    TheaterSeat* tempPointerTwo = nullptr;

    //Make sure that the first seat exists
    if(first != nullptr)
    {
        //Set a pointer equal to the first seat in the row above the current row being deleted
        tempPointerTwo = first->getUp();
    }

    //Run until the first seat is null
    while (first != nullptr)
    {
        //Set a temp pointer to first, mover first to the next seat, and then delete the temp pointer
        tempPointerOne = first;
        first = first->getRight();
        tempPointerOne = nullptr;
        delete tempPointerOne;

        //Once first reaches the end of the row, move to the next row.
        if (first == nullptr)
        {
            first = tempPointerTwo;

            //Make sure the next row exists
            if(first != nullptr)
            {
                tempPointerTwo = first->getUp();
            }
            else
            {
                break;
            }
        }
    }
    delete tempPointerTwo;
}

//Check if the auditorium is empty
bool Auditorium::isEmpty()
{
    return first == nullptr;
}


void Auditorium::changeSeatStatus(int row, char seat, bool isReserved, char ticketType)
{
    TheaterSeat* cur = first;
    while(cur->getRow() != row)
    {
        cur = cur->getUp();
    }
    while(cur->getSeat() != seat)
    {
        cur = cur->getRight();
    }
    cur->setReserved(isReserved);
    cur->setTicketType(ticketType);
}
