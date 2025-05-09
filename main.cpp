#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

#include "Board.h"
#include "Player.h"
#include "Wall.h"
#include "TownHall.h"
#include "GoldMine.h"
#include "ElixirCollector.h"
#include "Raider.h"

const int MAP_WIDTH = 40;
const int MAP_HEIGHT = 20;
const int TILE_SIZE = 32;

const int SCREEN_WIDTH = MAP_WIDTH * TILE_SIZE;
const int SCREEN_HEIGHT = MAP_HEIGHT * TILE_SIZE;

SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& path) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
    if (!texture) std::cerr << "Failed to load " << path << ": " << IMG_GetError() << std::endl;
    return texture;
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    SDL_Window* window = SDL_CreateWindow("Village Under Attack", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    srand(static_cast<unsigned int>(time(nullptr)));

    Board board(MAP_WIDTH, MAP_HEIGHT);
    Player* player = new Player(Position(10, 10));
    player->setTexture(loadTexture(renderer, "assets/Player.png"));
    board.setPlayer(player);

    std::vector<Raider*> raiders;
    Uint32 lastSpawnTime = SDL_GetTicks() - 5000;
    bool placingWalls = false;
    Position lastWallPos(-1, -1);
    bool running = true;

    SDL_Event e;
    while (running) {
        // EVENTS
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;

            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:    player->moving(board, 0, -1); break;
                    case SDLK_DOWN:  player->moving(board, 0, 1); break;
                    case SDLK_LEFT:  player->moving(board, -1, 0); break;
                    case SDLK_RIGHT: player->moving(board, 1, 0); break;

                    case SDLK_g: {
                        GoldMine* g = new GoldMine(player->getPosition());
                        g->setTexture(loadTexture(renderer, g->getTexturePath()));
                        board.AddBuilding(g);
                        break;
                    }
                    case SDLK_e: {
                        ElixirCollector* ec = new ElixirCollector(player->getPosition());
                        ec->setTexture(loadTexture(renderer, ec->getTexturePath()));
                        board.AddBuilding(ec);
                        break;
                    }
                    case SDLK_w:
                        placingWalls = !placingWalls;
                        break;

                    case SDLK_t: {
                        TownHall* th = new TownHall(player->getPosition());
                        th->setTexture(loadTexture(renderer, th->getTexturePath()));
                        board.AddBuilding(th);
                        break;
                    }

                    case SDLK_c:
                        player->Interact(board);
                        break;
                }
            }
        }

        // PLACING WALLS
        if (placingWalls && player->getResources().getGold() >= 5) {
            Position pos = player->getPosition();
            if (pos != lastWallPos) {
                bool occupied = false;
                for (Building* b : board.getBuildings()) {
                    if (b->collidesWith(pos)) {
                        occupied = true;
                        break;
                    }
                }
                if (!occupied) {
                    Wall* w = new Wall(pos);
                    w->setTexture(loadTexture(renderer, w->getTexturePath()));
                    board.AddBuilding(w);
                    player->getResources().spendGold(5);
                    lastWallPos = pos;
                }
            }
        }

        // SPAWN RAIDERS
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastSpawnTime > 5000) {
            int x = rand() % (MAP_WIDTH - 2) + 1;
            int y = rand() % (MAP_HEIGHT - 2) + 1;
            Raider* r = new Raider(Position(x, y));
            r->setTexture(loadTexture(renderer, r->getTexturePath()));
            raiders.push_back(r);
            lastSpawnTime = currentTime;
        }

        // UPDATE RAIDERS
        for (Raider* r : raiders) {
            r->Update(board);
            if (r->getPosition() == player->getPosition()) {
                std::cout << "Game Over: Raider killed the Player!" << std::endl;
                running = false;
            }
        }

        // CHECK GAME OVER
        if (board.getTownHall() && board.getTownHall()->getHealth() <= 0) {
            std::cout << "Game Over: Town Hall destroyed!" << std::endl;
            running = false;
        }

        // RENDER
        SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
        SDL_RenderClear(renderer);

        board.render(renderer, TILE_SIZE);
        for (Raider* r : raiders) r->render(renderer, TILE_SIZE);
        player->render(renderer, TILE_SIZE);

        SDL_RenderPresent(renderer);
        SDL_Delay(30);
    }

    delete player;
    for (auto* r : raiders) delete r;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
