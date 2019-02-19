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
        wind_speed = 1;
        vertical_randomness = 3;

        resetFire();

    }
    ~Priv() {
        delete[] firevalue;
    }

    void resetFire() {
        size_t len = static_cast<size_t>(vector_len)*sizeof(uchar);
        memset(firevalue, 0, len);
    }

    int getIdx(int i, int j) {
        return i + aligned_w * j;
    }

    void setIdx(int i, int j, uchar value) {
        if (i >= 0 && i < w && j >= 0 && j < h)
            firevalue[getIdx(i, j)] = value;
    }

    int w;
    int h;
    int aligned_w;
    int vector_len;
    int wind_speed;
    int vertical_randomness;

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

int DoomFire::windSpeed()
{
    return d->wind_speed;
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
            int decay = rand() % 3;
            int new_value = d->firevalue[d->getIdx(i, j+1)] - (decay > 1 ? 1 : 0);
            if (new_value < 0)
                new_value = 0;
            int new_i = i;
            int new_j = j;

            // lateral effect (wind)
            if (d->wind_speed > 0 && rand()%2) {
                new_i += d->wind_speed;
            }
            else if (d->wind_speed < 0 && rand()%2) {
                new_i += d->wind_speed;
            }

            // vertical space effect
            //if (new_j > 0 && (rand()%d->vertical_randomness)==0)
            //    new_j--;

            d->setIdx(new_i, new_j, static_cast<uchar>(new_value));
        }
    }
}

void DoomFire::resetFire()
{
    d->resetFire();
}

void DoomFire::decreaseWindSpeed()
{
    if (d->wind_speed > -3)
        d->wind_speed--;
}

void DoomFire::increaseWindSpeed()
{
    if (d->wind_speed < 3)
        d->wind_speed++;
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
