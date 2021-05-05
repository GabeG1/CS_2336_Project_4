//Gabriel Goldstein
//gjg180000
#ifndef BASENODE_H
#define BASENODE_H


class BaseNode
{
public:
    BaseNode();
    BaseNode(int, char, bool, char);
    BaseNode(int r, char s)
    {
       row = r;
       seat = s;
    }
    virtual ~BaseNode();
    int getRow()
    {
        return row;
    }
    char getSeat()
    {
        return seat;
    }
    bool isReserved()
    {
        return reserved;
    }
    char getTicketType()
    {
        return ticketType;
    }
    virtual void setReserved(bool) = 0;
    void setTicketType(char tt)
    {
        ticketType = tt;
    }

protected:
    bool reserved;
private:
    int row;
    char seat;
    char ticketType;
};

#endif // BASENODE_H
