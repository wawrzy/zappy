
#ifndef EGG_HPP__
# define EGG_HPP__

#include <string>

class Egg
{
    private:

    std::string _num;
    bool _status;
    int _x;
    int _y;

    public:
    Egg(std::string num,int x, int y);
    ~Egg();
    std::string getNum() const;
    void setStatus(bool status);
    bool getStatus() const;
    int getPosX() const;
     int getPosY() const;
    
};

#endif /* !EGG_HPP__ */