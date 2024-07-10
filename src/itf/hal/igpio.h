#ifndef IGPIO_H
#define IGPIO_H

class IGpio
{
public:
    virtual void set() {set(true);}
    virtual void reset() {set(false);}
    virtual void set(bool state) = 0;
    virtual bool get() const = 0;
};

#endif