#ifndef LEVEL_H
#define LEVEL_H

#include <memory>
#include <iostream>
#include <vector>


#include "IDrawable.hpp"
#include "Tileset.hpp"


class Level : public IDrawable {
    
    public:
        typedef std::vector<std::vector<char>> LevelMatrix;
        typedef std::vector<char> LevelRow;

    private:
        std::shared_ptr<Tileset> tileset;
        LevelMatrix level;
    public:

        Level(std::istream &is, Tileset *tileset);
        virtual void draw(SDL_Renderer *renderer);
        const LevelMatrix& getLevelMatrix() const;


};


#endif // LEVEL_H