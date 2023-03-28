//
// Created by Sehoon Jang on 3/29/23.
//

#ifndef WEBSERVE_TESTEXAMPLE_HPP
#define WEBSERVE_TESTEXAMPLE_HPP


class TestExample
{
private:
    int _number;

public:
    TestExample();
    TestExample(int number);
    TestExample(const TestExample &testExample);
    ~TestExample();
    TestExample &operator=(const TestExample &testExample);

    int getNumber() const;
    void    setNumber(int number);

    int sum(int number);
    int sub(int number);
    int mul(int number);
    int div(int number);
};

#endif //WEBSERVE_TESTEXAMPLE_HPP
