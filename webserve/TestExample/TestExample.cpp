//
// Created by Sehoon Jang on 3/29/23.
//

#include "TestExample.hpp"

TestExample::TestExample() : _number(0) {}

TestExample::TestExample(int number) : _number(number) {}

TestExample::TestExample(const TestExample &testExample)
{
    if (this == &testExample)
        return ;
    _number = testExample.getNumber();
}

TestExample::~TestExample() {}

TestExample &TestExample::operator=(const TestExample &testExample)
{
    if (this == &testExample)
        return (*this);
    _number = testExample.getNumber();
    return (*this);
}


int TestExample::getNumber() const
{
    return (_number);
}

void    TestExample::setNumber(int number)
{
    _number = number;
}

int TestExample::sum(int number)
{
    return (_number + number);
}

int TestExample::sub(int number)
{
    return (_number - number);
}

int TestExample::mul(int number)
{
    return (_number * number);
}

int TestExample::div(int number)
{
    if (number == 0)
        return (0);
    return (_number / number);
}
