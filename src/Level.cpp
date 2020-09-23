#include "Level.hpp"


Level::Level(std::istream &is, Tileset *tileset) 
    : IDrawable(), tileset {tileset} {
    int h, w;

    char rectCode;

    is >> h >> w;

    for(int i = 0; i < h; i++){
        level.push_back(LevelRow());
        for(int j = 0; j < w; j++){
            is >> rectCode;
            level[i].push_back(rectCode);
        }
    }
}

void Level::draw(SDL_Renderer *renderer){
    for(size_t i = 0; i < level.size(); i++){
        for(size_t j = 0; j < level[i].size(); j++){
            tileset->draw(level[i][j], j*32, i*32, renderer);
        }
    }
}








const Level::LevelMatrix& Level::getLevelMatrix() const { return level; }