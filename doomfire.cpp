#include "doomfire.h"

#define FIRE_ALIGN 4

class DoomFire::Priv{

public:

    Priv(int _w, int _h) : w(_w), h(_h) {
        if (_w % FIRE_ALIGN)
            aligned_w = _w + FIRE_ALIGN - (_w % FIRE_ALIGN);
        else
            aligned_w = _w;

        vector_len = aligned_w * h;
        firevalue = new uchar[vector_len];

        memset(firevalue, 0, vector_len*sizeof(uchar));

    }
    ~Priv() {
        delete[] firevalue;
    }

    int getIdx(int i, int j) {
        return i + aligned_w * j;
    }

    int w;
    int h;
    int aligned_w;
    int vector_len;

    uchar* firevalue;
};

DoomFire::DoomFire(int w, int h)
{
    d = new Priv(w, h);
}

DoomFire::~DoomFire()
{
    delete d;
}

const uchar* DoomFire::getAlignedFireVector()
{
    return d->firevalue;
}

int DoomFire::witdh()
{
    return d->w;
}

int DoomFire::height()
{
    return d->h;
}

void DoomFire::createFire()
{
    for (int i=0; i<d->w; i++) {
        d->firevalue[d->getIdx(i, d->h-1)] = 36;
    }
}

void DoomFire::destroyFire()
{
    for (int i=0; i<d->w; i++) {
        d->firevalue[d->getIdx(i, d->h-1)] = 0;
    }
}

void DoomFire::propagateFire()
{
    for (int j=0; j<(d->h-1); j++) {
        for (int i=0; i<d->w; i++) {
            int decay = rand() % 2;
            int new_value = d->firevalue[d->getIdx(i, j+1)] - decay;
            if (new_value < 0)
                new_value = 0;
            int new_i = i;
            int new_j = j;
            if (new_i < (d->w-1) && rand()%2)
                new_i++;
            if (new_j > 0 && rand()%2)
                new_j--;
            d->firevalue[d->getIdx(new_i, new_j)] = (uchar)new_value;
        }
    }
}

void DoomFire::resetFire()
{
    memset(d->firevalue, 0, d->vector_len*sizeof(uchar));
}

void DoomFire::printFire()
{
    for (int j=0; j<d->h; j++) {
        for (int i=0; i<d->w; i++) {
            fprintf(stderr, "%3d", d->firevalue[d->getIdx(i, j)]);
        }
        fprintf(stderr, "\n");
    }
    fprintf(stderr, "\n");
}
