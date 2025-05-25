#include "Frame.hpp"

/* Contructors */
Frame::Frame()
: value(0), user_value(0), is_fixed(true) 
{}

Frame::Frame(int val, int user_val, bool fixed)
: value(val), user_value(user_val), is_fixed(fixed) 
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
bool Frame::isFixed()
{
    return this->is_fixed;
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
Frame &Frame::fixed(bool val)
{
    this->is_fixed = val;
    return *this;
}

/* Methods */
bool Frame::checkUserValue()
{
    return this->value == this->user_value;
}