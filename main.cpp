#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.hpp"
/*
class Base
{
    public:
        virtual void print()
        {
            std::cout << "Class Base" << std::endl;
        }
};

class ChildA : public Base
{
    public:
        virtual void print()
        {
            std::cout << "Class ChildA" << std::endl;
        }
};

class ChildB : public Base
{
    public:
        virtual void print()
        {
            std::cout << "Class ChildB" << std::endl;
        }
};

void printClassText(Base &a, Base &b)
{
    a.print();
    b.print();
}

void printClassText(ChildA &a, Base &b)
{
    std::cout << "ChildA function" << std::endl;
    a.print();
    b.print();
}
*/

int main()
{
    //Base a = ChildA();
    //Base b = ChildB();
    //printClassText(a, b);

    Game game(true);
    game.run();

    return 0;
}
