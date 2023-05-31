#pragma once

class Sequence {
public:
    virtual int get(int index) = 0;
    virtual void set(int index, int value) = 0;
    virtual void add(int value) = 0;
    virtual int get_size() = 0;
    virtual ~Sequence() { };
};
