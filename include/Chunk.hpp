#pragma once

#include "Frame.h"

class Chunk
{
private:
    Frame frames[3][3];

public:
    /* Contructors */
    Chunk();

    /* Getters */
    Frame **getFrames();
    Frame &getFrame(int cx, int cy);

    /* Setters */
    void setFrame(Frame f, int cx, int cy);

    /* Methods */
    void generate();
};