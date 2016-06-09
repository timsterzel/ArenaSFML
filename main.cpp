#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.hpp"
/*
class Base
{
    public:
        virtual void print() const
        {
            std::cout << "Class Base" << std::endl;
        }
};

class ChildA : public Base
{
    public:
        virtual void print() const
        {
            std::cout << "Class ChildA" << std::endl;
        }
};

class ChildB : public Base
{
    public:
        virtual void print() const
        {
            std::cout << "Class ChildB" << std::endl;
        }
};

void printClassText(Base *a, Base *b)
{
    std::cout << "Function parameters: Base Base" << std::endl;
}

void printClassText(ChildA *a, ChildB *b)
{
    std::cout << "Function parameters: ChildA ChildB" << std::endl;
}
*/

int main()
{
    /*
    Base *a = new ChildA();
    Base *b = new ChildB();
    printClassText(a, b);

    delete a;
    delete b;
    */

    Game game(true);
    game.run();

    return 0;
}
