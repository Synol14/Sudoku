#include "Chunk.hpp"

/* Contructors */
Chunk::Chunk() {}
Chunk::Chunk(Frame frames[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            this->frames[i][j] = frames[i][j];
        }
    }
}

/* Getters */
Frame &Chunk::getFrame(int cx, int cy)
{
    return this->frames[cx][cy];
}

/* Setters */
void Chunk::setFrame(Frame f, int cx, int cy)
{
    this->frames[cx][cy] = f;
}

/* Methods */
void Chunk::generate()
{
}