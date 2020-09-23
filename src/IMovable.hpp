
#ifndef IMOVABLE_H
#define IMOVABLE_H


class IMovable {
    public:
        virtual void move(int dX, int dY) = 0;
        virtual void move() = 0;
};


#endif // IMOVABLE_H