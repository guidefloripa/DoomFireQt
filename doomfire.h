#ifndef DOOMFIRE_H
#define DOOMFIRE_H

#include <qglobal.h>

class DoomFire
{
public:
    DoomFire(int w, int h);
    ~DoomFire();

    const uchar* getAlignedFireVector();
    int witdh();
    int height();

    void createFire();
    void destroyFire();
    void propagateFire();

    void resetFire();
    void printFire();

private:
    class Priv;
    Priv *d;
};

#endif // DOOMFIRE_H
