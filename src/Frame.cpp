#include "Frame.hpp"

/* Contructors */
Frame::Frame()
: value(0), user_value(0), is_displayed(false) 
{}

Frame::Frame(int val, int user_val, bool displayed)
: value(val), user_value(user_val), is_displayed(displayed) 
{}

/* Getters */
int Frame::getValue()
{
    return this->value;
}
int Frame::getUserValue()
{
    return this->user_value;
}
bool Frame::isDisplayed()
{
    return this->is_displayed;
}

/* Setters */
Frame &Frame::setValue(int val)
{
    this->value = val;
    return *this;
}
Frame &Frame::setUserValue(int val)
{
    this->user_value = val;
    return *this;
}
Frame &Frame::display(bool val)
{
    this->is_displayed = val;
    return *this;
}

/* Methods */
bool Frame::checkUserValue()
{
    return this->value == this->user_value;
}