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
    Frame(int val, int user_val = 0, bool displayed = false);

    /* Getters */
    int getValue();
    int getUserValue();
    bool isDisplayed();

    /* Setters */
    Frame &setValue(int val);
    Frame &setUserValue(int val);
    Frame &display(bool val);

    /* Methods */
    void generate(std::vector<int> forbiden_values);
    bool checkUserValue();
};