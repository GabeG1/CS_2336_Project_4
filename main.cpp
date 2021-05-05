//Gabriel Goldstein
//gjg180000
#include <iostream>
#include <limits>
#include "Auditorium.h"
#include "TheaterSeat.h"
#include <math.h>
#include <fstream>
#include <iomanip>
#include <unordered_map>
#include <string>
#include "User.h"

using namespace std;
void displayAuditorium(Auditorium*);
bool checkAvailability(Auditorium*, int, char, int);
void reserveSeats(Auditorium*, int, char, int, int, int);
TheaterSeat* bestAvailable(Auditorium*, int);
void displayReport(Auditorium*, Auditorium*, Auditorium*);
void writeToFile(Auditorium*, Auditorium*, Auditorium*);

int main()
{
    bool isLoggedIn = false;
    int menuOption = 0;
    int orderSelection = 0;
    string username = "";
    Auditorium* aud;
    Auditorium aud1 = Auditorium("A1.txt");
    Auditorium aud2 = Auditorium("A2.txt");
    Auditorium aud3 = Auditorium("A3.txt");
    unordered_map<string, User> users;
    ifstream usersFile("userdb.dat");
    string line = "";
    int audNum = 0;
    if(usersFile.is_open())
    {

        //Read each line of the user file
        while(!usersFile.eof())
        {

            //Get the username by finding the string before the space and the password is the string after the space
            getline(usersFile, line);
            string username = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ") + 1);
            string password = line;
            users[username] = User(username, password);
        }
    }

    do
    {

        //Have the user log in
        if(isLoggedIn == false)
        {
            int numAttempts = 0;
            cout << "Username: ";
            getline(cin, username);
            cout << endl;
            string password = "";

            //The user gets three attempts to enter their password
            while (numAttempts < 3 && isLoggedIn == false)
            {
                numAttempts++;
                cout << "password: ";
                getline(cin, password);
                cout << endl;

                //If the password is correct, the user has successfully logged in
                if(users[username] == User(username, password))
                {
                    isLoggedIn = true;
                }
                else
                {
                    cout << "\n\nIncorrect Password" << "\n";
                }
            }
        }
        if(isLoggedIn == false)
        {
            continue;
        }
        string input = "";

        //If the user is not an admin
        if(username != "admin")
        {

            //Make sure the user enters one of the five possible options
            while (menuOption != 1 && menuOption != 2 && menuOption != 3 && menuOption != 4 && menuOption != 5)
            {
                cout << "Press 1 to Reserve Seats. \nPress 2 to View Orders."
                     << "\nPress 3 to Update Order." << "\nPress 4 to Display Receipt."
                     << "\nPress 5 to Log Out." << endl;
                try
                {
                    getline(cin, input);
                    cout << endl;
                    if (input != "1" && input!="2" && input!="3"  && input!="4"  && input!="5")
                    {
                        cout << "\nInvalid Input" << "\n\n";
                        continue;
                    }

                    menuOption = stoi(input);


                }
                catch(exception e)
                {
                    cout << "Invalid Input" << "\n\n";

                }
            }
            //If the user wants to reserve seats or update an order
            if(menuOption == 1 || menuOption == 3)
            {
                int subMenuOption = 0;

                //If the user chooses to update an order
                if(menuOption == 3)
                {
                    if(users[username].getNumOrders() == 0)
                    {
                        menuOption = 0;
                        continue;
                    }
                    users[username].printOrders();
                    input = "";

                    //Make sure the user selects an order that exists
                    while(orderSelection <= 0 || orderSelection > users[username].getNumOrders())
                    {
                        cout << "Choose an order to update: " << "\n\nOrder Number: ";
                        getline(cin, input);
                        try
                        {
                            orderSelection = stoi(input);
                            if(input != to_string(orderSelection))
                            {
                                cout << "\nInvalid Input" << endl;
                                orderSelection = 0;
                                continue;
                            }
                        }
                        catch(exception e)
                        {
                            orderSelection = 0;
                            cout << "\nInvalid Input" << "\n\n";
                        }
                    }

                    //If the user want to update an order, have them choose one of three actions possible
                    while(subMenuOption != 1 && subMenuOption != 2 && subMenuOption != 3)
                    {
                        cout << "\nPress 1 to add tickets to order"
                             << "\nPress 2 to delete ticket from order"
                             << "\nPress 3 to cancel order" << endl;
                        try
                        {
                            getline(cin, input);
                            cout << endl;
                            if (input != "1" && input!="2" && input!="3")
                            {
                                cout << "\nInvalid Input" << "\n\n";
                                continue;
                            }
                            subMenuOption = stoi(input);
                        }
                        catch(exception e)
                        {
                            cout << "Invalid Input" << "\n\n";
                            continue;
                        }
                    }

                    //If the user wishes to delete a ticket form the order
                    if(subMenuOption == 2)
                    {
                        input = "";
                        int selectedRow = 0;
                        char selectedStartingSeat = '\0';

                        //Get the user to input a row. Loop until the user enters a row that is listed on the console
                        while(!(selectedRow >= 1 && selectedRow <= aud->getNumRows()))
                        {
                            cout << "\nWhat row would you like to remove from your order?\nRow Number: ";
                            try
                            {
                                getline(cin, input);
                                cout << endl;
                                selectedRow = stoi(input);

                                //If the user enters a decimal number, then the input will not match the integer that the decimal gets rounded to.
                                //Therefore, go back to the while loop
                                if(input != to_string(selectedRow))
                                {
                                    cout << "Please enter a valid row" << endl;
                                    selectedRow = 0;
                                    continue;
                                }
                                if(!(selectedRow >= 1 && selectedRow <= aud->getNumRows()))
                                {
                                    cout << "Please enter a valid row" << endl;
                                    continue;
                                }
                            }
                            catch(const exception& e)
                            {
                                cout << "Please enter a valid row" << endl;
                            }
                        }

                        //Have the user enter a seat letter. If the letter written does not match the seat letters displayed to the console,
                        //keep requesting the user to enter a valid starting seat letter
                        while(!(selectedStartingSeat >= 'A' && selectedStartingSeat <= (aud->getNumSeats() + (int)'A' - 1)))
                        {
                            cout << "What seat would you like to remove from your order?\nSeat Letter: ";

                            try
                            {

                                getline(cin, input);
                                cout << endl;

                                if (input.length() != 1)
                                {
                                    cout << "Please enter a valid seat letter\n" << endl;
                                    continue;
                                }
                                selectedStartingSeat = (char)toupper(input[0]);
                                if(!(selectedStartingSeat >= 'A' && selectedStartingSeat <= (aud->getNumSeats() + (int)'A' - 1)))
                                {
                                    cout << "Please enter a valid seat letter\n" << endl;
                                }

                            }
                            catch(exception e)
                            {
                                cout << "Please enter a valid seat letter\n" << endl;
                            }

                        }

                        //If the user entered seats that they ordered
                        if(users[username].getOrder(orderSelection)->exists(TheaterSeat(selectedRow, selectedStartingSeat)))
                        {
                            users[username].getOrder(orderSelection)->deleteTicket(TheaterSeat(selectedRow, selectedStartingSeat));
                            audNum = users[username].getOrder(orderSelection)->getAuditorium();

                            //Get the auditorium pertaining to this order
                            if(audNum == 1)
                            {
                                aud = &aud1;
                            }
                            else if(audNum == 2)
                            {
                                aud = &aud2;
                            }
                            else if(audNum == 3)
                            {
                                aud = &aud3;
                            }
                            aud->changeSeatStatus(selectedRow, selectedStartingSeat, false, '.');
                            if(!users[username].getOrder(orderSelection)->getStartingSeat())
                            {
                                Order* order = users[username].cancelOrder(orderSelection);
                                delete order;
                            }

                            //If the seat is deleted, set the input back to default numbers in order to return the main menu
                            orderSelection = 0;
                            audNum = 0;
                            menuOption = 0;
                            cout << "Seat successfully removed from order.\n" << endl;
                        }

                        //If the user did not enter valid seats, return to the update action submenu
                        else
                        {
                            cout << "\nInvalid Input.\n" << endl;
                        }
                        continue;
                    }

                    //If the user wants to add to the order (will send them to reserve seats option)
                    else if(subMenuOption == 1)
                    {

                        //determine the auditorium to be dealt with for the reserve seats section
                        audNum = users[username].getOrder(orderSelection)->getAuditorium();
                    }

                    //If the user wants to cancel the order
                    else if(subMenuOption == 3)
                    {
                        //Cancel the order
                        Order* order = users[username].cancelOrder(orderSelection);
                        TheaterSeat* trailTemp = nullptr;
                        TheaterSeat* temp = order->getStartingSeat();

                        //Determine the auditorium that needs to be updated
                        if(order->getAuditorium() == 1)
                        {
                            aud = &aud1;
                        }
                        else if(order->getAuditorium() == 2)
                        {
                            aud = &aud2;
                        }
                        else if(order->getAuditorium() == 3)
                        {
                            aud = &aud3;
                        }
                        //Delete the memory that the order used and change the status of the auditorium for those canceled seats.
                        while(temp)
                        {
                            trailTemp = temp;
                            temp = temp->getRight();
                            aud->changeSeatStatus(trailTemp->getRow(), trailTemp->getSeat(), false, '.');
                            delete trailTemp;
                        }

                        //Reset the input numbers back to default in order to return to the main menu
                        menuOption = 0;
                        delete order;
                        orderSelection = 0;
                        audNum = 0;
                        cout << "The order has been canceled.\n" << endl;
                        continue;
                    }

                }
                //Reserve seats section (if the user is updating the menu, the auditorium number
                //has already been retrieved so the request for an auditorium number is skipped
                input = "";
                while(audNum != 1 && audNum != 2 && audNum != 3)
                {
                    cout << "Press 1 for Auditorium 1" << "\nPress 2 for Auditorium 2"
                         << "\nPress 3 for Auditorium 3" << endl;
                    getline(cin, input);
                    if(input == "1")
                    {
                        aud = &aud1;
                        audNum = 1;
                    }
                    else if(input == "2")
                    {
                        aud = &aud2;
                        audNum = 2;
                    }
                    else if(input == "3")
                    {
                        aud = &aud3;
                        audNum = 3;
                    }
                }
                cout << endl;
                displayAuditorium(aud);

                input = "";
                int selectedRow = 0;
                char selectedStartingSeat = '\0';

                //Get the user to input a row. Loop until the user enters a row that is listed on the console
                while(!(selectedRow >= 1 && selectedRow <= aud->getNumRows()))
                {
                    cout << "\nIn what row would you like to be seated?\nRow Number: ";
                    try
                    {

                        getline(cin, input);
                        cout << endl;
                        selectedRow = stoi(input);

                        //If the user enters a decimal number, then the input will not match the integer that the decimal gets rounded to.
                        //Therefore, go back to the while loop
                        if(input != to_string(selectedRow))
                        {
                            cout << "Please enter a valid row" << endl;
                            selectedRow = 0;
                            continue;
                        }
                        if(!(selectedRow >= 1 && selectedRow <= aud->getNumRows()))
                        {
                            cout << "Please enter a valid row" << endl;
                            continue;
                        }

                    }
                    catch(const exception& e)
                    {
                        cout << "Please enter a valid row" << endl;
                    }
                }

                //Have the user enter a seat letter. If the letter written does not match the seat letters displayed to the console,
                //keep requesting the user to enter a valid starting seat letter
                while(!(selectedStartingSeat >= 'A' && selectedStartingSeat <= (aud->getNumSeats() + (int)'A' - 1)))
                {
                    cout << "What seat would you like to start with in Row " << selectedRow << "?\nSeat Letter: ";

                    try
                    {

                        getline(cin, input);
                        cout << endl;

                        if (input.length() != 1)
                        {
                            cout << "Please enter a valid seat letter\n" << endl;
                            continue;
                        }
                        selectedStartingSeat = (char)toupper(input[0]);
                        if(!(selectedStartingSeat >= 'A' && selectedStartingSeat <= (aud->getNumSeats() + (int)'A' - 1)))
                        {
                            cout << "Please enter a valid seat letter\n" << endl;
                        }


                    }
                    catch(exception e)
                    {
                        cout << "Please enter a valid seat letter\n" << endl;
                    }



                }
                int adultTickets = -1;
                int childTickets = -1;
                int seniorTickets = -1;

                //Each of the three while loops that follow the user input checks
                //to see if user entered a quantity less than zero or a non-integer input.
                while(adultTickets < 0)
                {
                    cout << "How many Adult tickets would you like?\nAdult Tickets: ";
                    try
                    {
                        getline(cin, input);
                        cout << endl;
                        adultTickets = stoi(input);

                        //Checks to see if user wrote decimal. If so, request user to enter a valid adult quantity.
                        if(input != to_string(adultTickets))
                        {
                            cout << "\nInvalid Input" << endl;
                            adultTickets = -1;
                            continue;
                        }
                        if(adultTickets < 0)
                        {
                            cout << "\nInvalid Input" << endl;

                        }
                    }
                    catch (exception e)
                    {

                        cout << "\nInvalid Input" << endl;
                    }


                }

                while(childTickets < 0)
                {
                    cout << "How many Child tickets would you like?\nChild Tickets: ";
                    try
                    {
                        getline(cin, input);
                        cout << endl;
                        childTickets = stoi(input);

                        //Checks to see if user wrote decimal. If so, request user to enter a valid child quantity.
                        if(input != to_string(childTickets))
                        {
                            cout << "\nInvalid Input" << endl;
                            childTickets = -1;
                            continue;
                        }
                        if(childTickets < 0)
                        {
                            cout << "\nInvalid Input" << endl;

                        }
                    }
                    catch (exception e)
                    {
                        cout << "\nInvalid Input" << endl;

                    }

                }

                while(seniorTickets < 0)
                {

                    cout << "How many Senior tickets would you like?\nSenior Tickets: ";
                    try
                    {
                        getline(cin, input);
                        cout << endl;
                        seniorTickets = stoi(input);

                        //Checks to see if user wrote decimal. If so, request user to enter a valid senior quantity.
                        if(input != to_string(seniorTickets))
                        {
                            cout << "\nInvalid Input" << endl;
                            seniorTickets = -1;
                            continue;
                        }
                        if(seniorTickets < 0)
                        {
                            cout << "\nInvalid Input" << endl;

                        }
                    }
                    catch(exception e)
                    {
                        cout << "\nInvalid Input" << endl;
                    }

                }

                //Determine if the seats the user requested are available.
                bool isAvailable = checkAvailability(aud, selectedRow, selectedStartingSeat, adultTickets + childTickets + seniorTickets);

                //If the seats are available, reserve those seats
                if(isAvailable == true)
                {
                    reserveSeats(aud, selectedRow, selectedStartingSeat, adultTickets, childTickets, seniorTickets);
                    cout << "Thanks for doing business with us! " << "\n\n";

                    //If the user is adding to a current order
                    if(menuOption == 3)
                    {

                        //Add to the order
                        users[username].addToOrder(orderSelection, selectedRow, selectedStartingSeat, adultTickets, childTickets, seniorTickets);
                    }

                    //If the user is creating a new order
                    else
                    {

                        //Create a new order
                        users[username].addOrder(audNum, selectedRow, selectedStartingSeat, adultTickets, childTickets, seniorTickets);
                    }

                    //Set input values to default (allows program to return to main menu)
                    menuOption = 0;
                    orderSelection = 0;
                    audNum = 0;
                }

                //If seats not available, determine the best available seats (if any) and suggest those to the user
                else
                {
                    cout << "We could not reserve those seats. \n";

                    //If seats
                    if(menuOption == 3)
                    {
                        continue;
                    }
                    TheaterSeat* bestAvailStartingSeat = bestAvailable(aud, adultTickets + childTickets + seniorTickets);
                    if(bestAvailStartingSeat != nullptr)
                    {

                        //If the total quantity of seats requested is one (done for grammatical purposes)
                        if(adultTickets + childTickets + seniorTickets == 1)
                        {

                            cout << "Would you instead like to reserve seat " << bestAvailStartingSeat->getSeat()
                                 << " in row " << bestAvailStartingSeat->getRow() << "." << endl;
                        }
                        else
                        {
                            cout << "Would you instead like to reserve seats " << bestAvailStartingSeat->getSeat() << " through "
                                 << (char)(bestAvailStartingSeat->getSeat() + adultTickets + childTickets + seniorTickets - 1)
                                 << " in row  " << bestAvailStartingSeat->getRow() << "." << endl;

                        }

                        input = "";

                        //Loop until the user enters a Y or N (not case sensitive) to accept or decline, respectively, the best available seat/s.
                        while(input != "Y" && input != "N" && input != "y" && input != "n")
                        {
                            cout << "\nEnter Y to accept or N to decline. " << endl;
                            getline(cin, input);
                            cout << endl;
                            if(input != "Y" && input != "N" && input != "y" && input != "n")
                            {
                                cout << "\nInvalid Input" << endl;

                            }

                        }

                        //If the user accepts the best available seats, reserve those seats
                        if(input == "Y" || input == "y")
                        {
                            reserveSeats(aud, bestAvailStartingSeat->getRow(), bestAvailStartingSeat->getSeat(), adultTickets, childTickets, seniorTickets);
                            cout << "Thanks for doing business with us! " << "\n\n";
                            users[username].addOrder(audNum, bestAvailStartingSeat->getRow(), bestAvailStartingSeat->getSeat(), adultTickets, childTickets, seniorTickets);

                        }
                        else
                        {
                            cout << "Sorry we couldn't do business with you. " << "\n\n";

                        }
                    }
                    else
                    {
                        cout << "Sorry we couldn't do business with you. " << "\n\n";

                    }
                    menuOption = 0;
                    audNum = 0;
                }


            }

            //If user wants to view orders
            if(menuOption == 2)
            {
                users[username].printOrders();
                menuOption = 0;
            }

            //If user wants to see the receipt
            if(menuOption == 4)
            {
                Order* cur = users[username].getFirstOrder();
                float totalAmount = 0;
                int orderNum = 1;

                //While there is an order, display the order number, auditorium number,
                //row, seat, ticket types, cost per order and total cost
                while(cur)
                {
                    TheaterSeat* seat = cur->getStartingSeat();
                    int row = seat->getRow();
                    cout << "Order: " << right <<  setw(13) << orderNum << "\n";
                    cout << "Auditorium: " << right <<  setw(8) << cur->getAuditorium() << endl;

                    cout << "Seats: " << right <<  setw(13) << seat->getRow() << ":";

                    while(seat)
                    {
                        if(seat->getRow() != row)
                        {
                            cout << "   " << seat->getRow() << ":";
                            row = seat->getRow();

                        }
                        cout << " " << seat->getSeat();
                        seat = seat->getRight();
                    }
                    cout << "\nAdult Tickets: " << right <<  setw(5) << cur->getAdultTickets()
                         << "\nChild Tickets: " << std::right <<  setw(5) << cur->getChildTickets()
                         << "\nSenior Tickets: " << right <<  setw(4) << cur->getSeniorTickets() << endl;
                    cout << "Cost: " << std::right <<  setw(14) << "$" << fixed << setprecision(2) << (float)(cur->getAdultTickets() * 10)
                         + (float)(cur->getChildTickets() * 5) + (float)cur->getSeniorTickets() * 7.50
                         << "\n\n";
                    totalAmount += (float)(cur->getAdultTickets() * 10)   + (float)(cur->getChildTickets() * 5) + (float)(cur->getSeniorTickets() * 7.50);
                    cur = cur->getNextOrder();
                    orderNum++;
                }
                cout << "\nTotal Cost: " << right <<  setw(8) << "$" << fixed << setprecision(2) << totalAmount << "\n\n";
                menuOption = 0;

            }

            //If the user wants to log out
            if(menuOption == 5)
            {
                isLoggedIn = false;
                menuOption = 0;
            }
        }

        //If the admin logged in
        else
        {

            //Have the admin select either 1, 2, or 3
            while (menuOption != 1 && menuOption != 2 && menuOption != 3)
            {
                cout << "Press 1 to Print Report. \nPress 2 to Log Out."
                     << "\nPress 3 to Exit." << endl;
                try
                {
                    getline(cin, input);
                    cout << endl;
                    if (input != "1" && input!="2" && input!="3")
                    {
                        cout << "\nInvalid Input" << "\n\n";
                        continue;
                    }

                    menuOption = stoi(input);

                }
                catch(exception e)
                {
                    cout << "Invalid Input" << "\n\n";

                }
            }

            //If the admin wants to print the report
            if(menuOption == 1)
            {
                displayReport(&aud1, &aud2, &aud3);
                menuOption = 0;
            }

            //If the admin wants to log out
            if(menuOption == 2)
            {
                isLoggedIn = false;
                menuOption = 0;
            }

            //if the admin wants to exit
            if(menuOption == 3)
            {
                isLoggedIn = false;
            }
        }
    }
    while(menuOption != 3 || username != "admin");
    writeToFile(&aud1, &aud2, &aud3);
    return 0;
}

//Print the auditorium to the user.
void displayAuditorium(Auditorium *aud)
{
    cout << "   ";
    TheaterSeat* currentSeat = aud->getFirstSeat();

//Writing the column headers to the console
    while(currentSeat != nullptr)
    {
        cout << currentSeat->getSeat();
        currentSeat = currentSeat->getRight();

    }

    cout << endl;

    TheaterSeat* firstSeatInCurrentRow = aud->getFirstSeat();

    //Run until all the rows have been gone through
    while(firstSeatInCurrentRow != nullptr)
    {
        currentSeat = firstSeatInCurrentRow;

        //The following if else statements are done so that
        //the auditorium is displayed in a straight line (not jagged).
        if(firstSeatInCurrentRow->getRow() < 10)
        {
            cout << firstSeatInCurrentRow->getRow() << "  ";
        }
        else
        {
            cout << firstSeatInCurrentRow->getRow() << " ";
        }

        //Run until all the seats in the row have been displayed to the console.
        while(currentSeat != nullptr)
        {
            //Write a hashtag to the console if the seat is reserved
            if(currentSeat->isReserved() == true)
            {
                cout << "#";
            }

            //Write a period to the console if the seat is not reserved
            else
            {
                cout << currentSeat->getTicketType();
            }

            //Move seat to the next seat (seat to the right)
            currentSeat = currentSeat->getRight();
        }
        cout << endl;

        //Once all the seats in the row have been displayed. Move to the row above. Note that
        //"row above" refers to the next row. For example, for 2 is considered the row above
        //row 1 in this code.
        firstSeatInCurrentRow = firstSeatInCurrentRow->getUp();
    }

}

//Confirm that the seats the user requested are available.
bool checkAvailability(Auditorium *aud, int row, char seat, int totalQuantity)
{

    TheaterSeat* seatToBeChecked = aud->getFirstSeat();

    //Run until the starting seat to be checked goes to the first seat in the row that contains the seat the user requested
    while(seatToBeChecked->getRow() != row)
    {
        seatToBeChecked = seatToBeChecked->getUp();
    }

    //Run until the starting seat to be checked goes to the correct seat that the user requested in the row
    while(seatToBeChecked->getSeat() != seat)
    {
        seatToBeChecked = seatToBeChecked->getRight();
    }

    //Run until all the seats are checked.
    for(int seatNum = 0; seatNum < totalQuantity; seatNum++)
    {
        //If seat requests go past seats in the row, then return false, signifying that the seats are not available
        if(seatToBeChecked == nullptr)
        {
            return false;
        }
        //If a seat is reserved, then return false
        if(seatToBeChecked->isReserved() == true)
        {
            return false;
        }

        //Move to to the next seat (the seat to the right)
        seatToBeChecked = seatToBeChecked->getRight();

    }
    return true;

}

//Reserve seats that either the user requested or accepted.
void reserveSeats(Auditorium *aud, int row, char seat, int adultQuantity, int childQuantity, int seniorQuantity)
{
    TheaterSeat* seatToBeReserved = aud->getFirstSeat();

    //Send the theater seat pointer to the correct row of the seats to be reserved
    while(seatToBeReserved->getRow() != row)
    {
        seatToBeReserved = seatToBeReserved->getUp();
    }
    //Send the theater seat pointer to the correct starting seat in that row
    while(seatToBeReserved->getSeat() != seat)
    {
        seatToBeReserved = seatToBeReserved->getRight();

    }

    //The following three for statements reserve adult tickets, then child tickets, and then senior tickets
    for(int i = 0; i < adultQuantity; i++)
    {
        seatToBeReserved->setSeat(TheaterSeat(row, seat, true, 'A'));
        seat++;
        seatToBeReserved = seatToBeReserved->getRight();
    }
    for(int i = 0; i < childQuantity; i++)
    {
        seatToBeReserved->setSeat(TheaterSeat(row, seat, true, 'C'));
        seat++;
        seatToBeReserved = seatToBeReserved->getRight();
    }
    for(int i = 0; i < seniorQuantity; i++)
    {
        seatToBeReserved->setSeat(TheaterSeat(row, seat, true, 'S'));
        seat++;
        seatToBeReserved = seatToBeReserved->getRight();
    }
}

//Find the best available seats in the auditorium (the seats closest to the center of the auditorium, if any)
TheaterSeat* bestAvailable(Auditorium *aud, int totalQuantity)
{
    TheaterSeat* suggestedSeat = nullptr;
    TheaterSeat* currentRow = aud->getFirstSeat();
    float smallestDistance = -1;
    float distance = -1;

    //Go through each row to see what seats may be available
    for(int row = 0; row < aud->getNumRows(); row++)
    {
        TheaterSeat* startingSeat = currentRow;

        //Check each seat in a row until fewer seats remain than the user is requesting
        for(int seat = 0; seat < (aud->getNumSeats() - totalQuantity + 1); seat++)
        {
            TheaterSeat* currentSeat = startingSeat;

            //Starting from each possible seat, check all the subsequent seats up until the end of the total quantity
            //to see if they are open or not.
            for(int i = 0; i < totalQuantity; i++)
            {

                //If a seat is reserved, then the seats are not available so move to the next starting seat
                if(currentSeat->getTicketType() != '.')
                {
                    break;
                }
                currentSeat = currentSeat->getRight();

                //If all the seats that were going to be checked are all available, calculate their distance to the center
                //of the auditorium
                if(i == totalQuantity - 1)
                {
                    //distance formula (using pythagorean formula)
                    distance = (float)sqrt((float)pow(((float)seat + (float)((float)seat + (float)totalQuantity - 1.0)) /(float) 2.0 - ((float)(aud->getNumSeats() - 1.0) / (float)2.0), (float)2.0) + (float)pow((float)((float)startingSeat->getRow() - ((float)(aud->getNumRows() + 1.0) / (float)2.0)), (float)2.0));

                    //If these are the first best available seat/s found
                    if(smallestDistance == -1)
                    {
                        smallestDistance = distance;
                        suggestedSeat = startingSeat;
                    }

                    //If the current distance is smaller than the smallest distance found,
                    //make the smallest distance equal to the current distance
                    else if (distance < smallestDistance)
                    {
                        smallestDistance = distance;
                        suggestedSeat = startingSeat;
                    }

                    //If there is a tie for smallest distance
                    else if (distance == smallestDistance)
                    {
                        //If the row number of the current set of seats being checked is closer to the center row than the
                        //the row of the suggested best available seats is, then make these current seats the new best available
                        if ((float)abs((float)startingSeat->getRow() - (float)(aud->getNumRows() + 1) / (float)2) < (float)abs((float)suggestedSeat->getRow() - (float)(aud->getNumRows() + 1) / (float)2))
                        {
                            smallestDistance = distance;
                            suggestedSeat = startingSeat;
                        }

                    }
                }

            }


            //Move the starting seat to be checked to the next seat (the seat to the right)
            startingSeat = startingSeat->getRight();
        }

        //Once all the seats have been checked in a row, move to the next row
        currentRow = currentRow->getUp();
    }

    return suggestedSeat;
}

//Display the pertinent information related to the auditorium
void displayReport(Auditorium *aud1, Auditorium *aud2, Auditorium *aud3)
{
    int totalOpenSeats = 0;
    int totalReservedSeats = 0;
    float totalTicketSales = 0;
    int totalAdultTickets = 0;
    int totalChildTickets = 0;
    int totalSeniorTickets = 0;

    //Display the information for each auditorium
    for(int i = 1; i <= 3; i++)
    {
        Auditorium* aud;

        //first auditorium
        if(i == 1)
        {
            aud = aud1;
        }

        //second auditorium
        else if(i == 2)
        {
            aud = aud2;
        }

        //third auditorium
        else
        {
            aud = aud3;
        }

        TheaterSeat* currentRow = aud->getFirstSeat();
        TheaterSeat* currentSeat = nullptr;
        int adultTickets = 0;
        int childTickets = 0;
        int seniorTickets = 0;


        //Run until all the rows have been gone through
        while(currentRow != nullptr)
        {
            currentSeat = currentRow;

            //Go through each seat in the row, display the ticket type to the file,
            //and count the appropriate quantity (adult, child, or senior)
            for(int i = 0; i < aud->getNumSeats(); i++)
            {
                if(currentSeat->getTicketType() == 'A')
                {
                    adultTickets++;
                }
                else if(currentSeat->getTicketType() == 'C')
                {
                    childTickets++;
                }
                else if(currentSeat->getTicketType() == 'S')
                {
                    seniorTickets++;
                }
                currentSeat = currentSeat->getRight();
            }
            currentRow = currentRow->getUp();
        }
        totalAdultTickets += adultTickets;
        totalChildTickets += childTickets;
        totalSeniorTickets += seniorTickets;


        //Print out the information related to the auditorium to the console
        float totalSales = (float)(adultTickets * 10 + childTickets * 5 + seniorTickets * 7.50);
        totalTicketSales += totalSales;
        totalOpenSeats += (aud->getNumRows() * aud->getNumSeats() - (adultTickets + childTickets + seniorTickets));
        totalReservedSeats += adultTickets + childTickets + seniorTickets;
        cout << "Auditorium " << i  << ": ";
        //Open Seats
        cout << right <<  setw(5) <<  aud->getNumRows() * aud->getNumSeats() - (adultTickets + childTickets + seniorTickets);
        //Total Reserved Seats
        cout << right <<  setw(5) << adultTickets + childTickets + seniorTickets;
        cout << right << setw(5) << adultTickets
             << right << setw(5) << childTickets
             << right << setw(5) << seniorTickets;
        //Ticket Sales
        string temp = to_string((int)totalSales);
        cout << right << setw(8 -(int)temp.length()) << "$" << fixed << setprecision(2) << totalSales;
        cout << "\n";
    }
    cout << "Total: ";
    //Open Seats
    cout << right <<  setw(12) <<  totalOpenSeats;
    //Total Reserved Seats
    cout << right << setw(5) << totalReservedSeats;
    cout << right << setw(5) << totalAdultTickets
         << right << setw(5)
         << totalChildTickets  << right << setw(5) << totalSeniorTickets;
    //Ticket Sales
    string temp = to_string((int)totalTicketSales);
    cout << right << setw(8 - (int)temp.length()) << "$" << fixed << setprecision(2) << totalTicketSales;
    cout << "\n" << endl;

}

//Write the auditoriums back to their respective files
void writeToFile(Auditorium* aud1, Auditorium* aud2, Auditorium* aud3)
{
    ofstream file;
    file.open("A1.txt");
    TheaterSeat* cur = aud1->getFirstSeat();
    TheaterSeat* firstSeat = cur;

    //Go through each seat in first auditorium
    while(cur)
    {
        file << cur->getTicketType();
        cur = cur->getRight();
        if(!cur)
        {
            cur = firstSeat->getUp();
            firstSeat = firstSeat->getUp();
            file << "\n";
        }
    }
    file.close();
    file.open("A2.txt");
    cur = aud2->getFirstSeat();
    firstSeat = cur;
    //Go through each seat in second auditorium
    while(cur)
    {
        file << cur->getTicketType();
        cur = cur->getRight();
        if(!cur)
        {
            cur = firstSeat->getUp();
            firstSeat = firstSeat->getUp();
            file << "\n";
        }
    }
    file.close();
    file.open("A3.txt");
    cur = aud3->getFirstSeat();
    firstSeat = cur;
    //Go through each seat in third auditorium
    while(cur)
    {
        file << cur->getTicketType();
        cur = cur->getRight();
        if(!cur)
        {
            cur = firstSeat->getUp();
            firstSeat = firstSeat->getUp();
            file << "\n";
        }
    }
    file.close();

}
