#pragma once

#include "Frame.hpp"

class Chunk
{
private:
    Frame frames[3][3];

public:
    /* Contructors */
    Chunk();
    Chunk(Frame frames[3][3]);

    /* Getters */
    Frame &getFrame(int cx, int cy);

    /* Setters */
    void setFrame(Frame f, int cx, int cy);

    /* Methods */
    void generate();
};