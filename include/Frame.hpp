#pragma once

#include <vector>

class Frame
{
private:
    int value;
    int user_value;
    bool is_displayed;

public:
    /* Contructors */
    Frame();
    Frame(int val);

    /* Getters */
    int getValue();
    int getUserValue();
    bool isDisplayed();

    /* Setters */
    void setValue(int tval);

    /* Methods */
    void generate(std::vector<int> forbiden_values);

    /* Operators */
    bool operator==(const Frame &other);
};