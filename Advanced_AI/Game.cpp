#include "Game.h"
#include "Timer.h"
#include "Assets.h"
#include "AnimSpriteComponent.h"
#include "BackgroundSpriteComponent.h"
#include <iostream>
#include "Maths.h"
#include "Dijkstra.h"
#include "Astar.h"

bool Game::initialize()
{
    bool isWindowInit = window.initialize();
    bool isRenderInit = renderer.initialize(window);
    return isWindowInit && isRenderInit;
}

void Game::load()
{
    // Load textures
    Assets::loadTexture(renderer, "Res\\astarTile.png", "AstarTile");
    Assets::loadTexture(renderer, "Res\\defaultTile.png", "DefaultTile");
    Assets::loadTexture(renderer, "Res\\dijkstraTile.png", "DijkstraTile");
    Assets::loadTexture(renderer, "Res\\endTile.png", "EndTile");
    Assets::loadTexture(renderer, "Res\\obstacleTile.png", "ObstacleTile");
    Assets::loadTexture(renderer, "Res\\researchTile.png", "ResearchTile");
    Assets::loadTexture(renderer, "Res\\startTile.png", "StartTile");

    srand(time(nullptr));

    vector<vector<int>> graph{
        {0, 2, 1000000, 12},
        {1000000, 0, 10, 5},
        {1000000, 1000000, 0, 1000000},
        {12, 1000000, 8, 0}
    };

    vector<vector<int>> graph2{
        {1, 1, 1, 1, 1},
        {1, 1, 0, 0, 1},
        {1, 0, 0, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1}
    };

    vector<vector<int>> translated = translate(&graph2);

    /*
    for (size_t i = 0; i < translated.size(); i++)
    {
        for (size_t j = 0; j < translated.at(i).size(); j++)
        {
            cout << translated.at(i).at(j) << ", ";
        }
        cout << endl;
    }
    cout << endl;
    */

    /*
    Dij* dij = new Dij(&graph, 0);
    dij->Dijkstra();
    dij->Destination(3);
    */
    Dijkstra* dij = new Dijkstra(&translated, 0);
    dij->Research();
    dij->Destination(19);

    cout << endl;

    Astar* ast = new Astar(&graph2, &translated);
    ast->mostShortWay(0, 19);

    grid = new Grid();

    /*
    vector<vector<int>> circuit
    {   { 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 },
        { 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
        { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 1, 1, 1, 1, 2, 2, 3, 1, 1, 1, 1, 1, 1, 0, 0, 1 },
        { 1, 0, 0, 1, 1, 0, 0, 1, 1, 3, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1 },
        { 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1 },
        { 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1 },
        { 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1 },
        { 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1 },
        { 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1 },
        { 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 1, 2, 1, 1, 1, 1, 1, 3, 1, 0, 0, 0, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 3, 3, 2, 3, 2, 2, 2, 1, 1, 1, 1, 1, 3 }
    };

    //grid = new Grid();
    grid = new Grid(&circuit);

    moto = new Moto();
    moto->setPosition({ 80, 400 });
    moto->setRotation(Maths::toRadians(90));
    //moto->setRotation(1.57f);    
    
    */
    score = 8 * 6;
}

void Game::loop()
{
    Timer timer;
    float dt = 0;
    while (isRunning)
    {
        float dt = timer.computeDeltaTime() / 1000.0f;
        processInput();
        update(dt);
        render();
        timer.delayTime();
    }
}

void Game::unload()
{
    // Delete actors
    // Because ~Actor calls RemoveActor, have to use a different style loop
    while (!actors.empty())
    {
        delete actors.back();
    }

    // Resources
    Assets::clear();
}

void Game::close()
{
    renderer.close();
    window.close();
    SDL_Quit();
}

void Game::addActor(Actor* actor)
{
    if (isUpdatingActors)
    {
        pendingActors.emplace_back(actor);
    }
    else
    {
        actors.emplace_back(actor);
    }
}

void Game::removeActor(Actor* actor)
{
    // Erase actor from the two vectors
    auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
    if (iter != end(pendingActors))
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, end(pendingActors) - 1);
        pendingActors.pop_back();
    }
    iter = std::find(begin(actors), end(actors), actor);
    if (iter != end(actors))
    {
        std::iter_swap(iter, end(actors) - 1);
        actors.pop_back();
    }
}

void Game::setScore(int scoreP)
{
    score = scoreP;
}

void Game::endGame()
{
    partyIsEnd = true;
    //ball->setBallLock(true);
    std::cout << "Press ENTER to reset" << std::endl << std::endl;
}

void Game::processInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;
        }
    }

    // Keyboard status
    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

    if (keyboardState[SDL_SCANCODE_ESCAPE])
    {
        isRunning = false;
    }

    /*
    if (keyboardState[SDL_SCANCODE_RETURN] && partyIsEnd)
    {
        std::cout << "rest" << std::endl;
        newParty();
    }
    */

    int x, y;
    Uint32 buttons = SDL_GetMouseState(&x, &y);
    if (SDL_BUTTON(buttons) & SDL_BUTTON_LEFT)
    {
        grid->processClick(x, y);
    }

    // Actor input
    isUpdatingActors = true;
    for (auto actor : actors)
    {
        if(!partyIsEnd)
            actor->processInput(keyboardState);
    }
    isUpdatingActors = false;
}

void Game::update(float dt)
{
    // Update actors 
    isUpdatingActors = true;
    for (auto actor : actors)
    {
        actor->update(dt);
    }
    isUpdatingActors = false;

    // Move pending actors to actors
    for (auto pendingActor : pendingActors)
    {
        actors.emplace_back(pendingActor);
    }
    pendingActors.clear();

    // Delete dead actors
    vector<Actor*> deadActors;
    for (auto actor : actors)
    {
        if (actor->getState() == Actor::ActorState::Dead)
        {
            deadActors.emplace_back(actor);
        }
    }
    for (auto deadActor : deadActors)
    {
        delete deadActor;
    }
}

void Game::render()
{
    renderer.beginDraw();
    renderer.draw();
    renderer.endDraw();
}

void Game::neightbours(vector<vector<int>>* graph, vector<vector<int>>* trans, int x, int y)
{
    int cptx = -1;
    while (cptx < 2)
    {
        if (x + cptx >= 0 && x + cptx < graph->size())
        {
            int cpty = -1;
            while (cpty < 2)
            {
                if (y + cpty >= 0 && y + cpty < graph->at(0).size())
                {
                    if (x + cptx == x && y + cpty == y)
                    {
                        trans->at(x * graph->at(0).size() + y).at((x + cptx) * graph->at(0).size() + y + cpty) = 0;
                        //cout << "trans->at(" << x * graph->at(0).size() + y << ").at(" << (x + cptx) * graph->at(0).size() + y + cpty << ") = 0;" << endl;
                    }
                    else
                    {
                        if (graph->at(x + cptx).at(y + cpty) != 0)
                        {
                            if (cptx != 0 && cpty != 0)
                            {
                                if ((cptx == -1 && cpty == -1 && ((graph->at(x + cptx + 1).at(y + cpty) == 1) || (graph->at(x + cptx).at(y + cpty + 1) == 1))) ||
                                    (cptx == -1 && cpty == 1 && ((graph->at(x + cptx + 1).at(y + cpty) == 1) || (graph->at(x + cptx).at(y + cpty - 1) == 1))) ||
                                    (cptx == 1 && cpty == -1 && ((graph->at(x + cptx - 1).at(y + cpty) == 1) || (graph->at(x + cptx).at(y + cpty + 1) == 1))) ||
                                    (cptx == 1 && cpty == 1 && ((graph->at(x + cptx - 1).at(y + cpty) == 1) || (graph->at(x + cptx).at(y + cpty - 1) == 1))))
                                {
                                    trans->at(x * graph->at(0).size() + y).at((x + cptx) * graph->at(0).size() + y + cpty) = 14;
                                }
                                else
                                {
                                    trans->at(x * graph->at(0).size() + y).at((x + cptx) * graph->at(0).size() + y + cpty) = 1000000;
                                }
                            }
                            else
                            {
                                trans->at(x * graph->at(0).size() + y).at((x + cptx) * graph->at(0).size() + y + cpty) = 10;
                            }
                        }
                        else
                        {
                            trans->at(x * graph->at(0).size() + y).at((x + cptx) * graph->at(0).size() + y + cpty) = 1000000;
                        }
                    }
                }
                cpty++;
            }
        }
        cptx++;
    }
}

vector<vector<int>> Game::translate(vector<vector<int>>* graph)
{
    int size = graph->size() * graph->at(0).size();
    vector<vector<int>> trans;
    for (size_t i = 0; i < size; i++)
    {
        vector<int> temp;
        for (size_t j = 0; j < size; j++)
        {
            temp.push_back(1000000);
        }
        trans.push_back(temp);
    }

    for (size_t i = 0; i < graph->size(); i++)
    {
        for (size_t j = 0; j < graph->at(i).size(); j++)
        {
            neightbours(graph, &trans, i, j);
        }
    }

    return trans;
}
