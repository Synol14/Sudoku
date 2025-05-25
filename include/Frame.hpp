#pragma once

#include <vector>

class Frame
{
private:
    int value;
    int user_value;
    bool is_fixed;

public:
    /* Contructors */
    Frame();
    Frame(int val, int user_val = 0, bool displayed = false);

    /* Getters */
    int getValue() const;
    int getUserValue() const;
    bool isFixed() const;

    /* Setters */
    Frame &setValue(int val);
    Frame &setUserValue(int val);
    Frame &fixed(bool val);

    /* Methods */
    bool checkUserValue();
};