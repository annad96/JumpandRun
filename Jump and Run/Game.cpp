#include <iostream>
#include "Game.h"

Game::Game(Terminal& term) : _term(term)
{
    _reset();
}

bool Game::isDone() const
{
    return _isDone;
}

void Game::update(float dt)
{
    char pressed = _term.get_key();
    switch (pressed)
    {
    case ' ':
        _player->jump();
        break;
    case 'r':
        _reset();
        break;
    case 'q':
        _term.close();
        break;
    default:
        break;
    }

    _elapsedTime += dt;
    if (!_gameOver)
    {
        for (size_t i = 0; i < _obstacles.size(); i++)
        {
            GameObject* obj = _obstacles[i];
            obj->update(dt);
            // A3: Wenn das Hindernis verschwunden ist, erzeuge ein neues
        }
        _floor->update(dt);
        _player->update(dt);
    }

    if (_player->isDead())
        _gameOver = true;
    else
        _score++;
}

void Game::draw()
{
    _term.clear();
    if (!_gameOver) {
        _camera.width = _term.width();
        _camera.height = _term.height();
        _camera.x++;
    }

    for each (GameObject * obj in _obstacles)
    {
        obj->draw(_term, _camera);
    }
    _floor->draw(_term, _camera);
    _player->draw(_term, _camera);

    _term.draw_text(0, 0, "Score:");
    _term.draw_text(7, 0, std::to_string(_score));

    if (_gameOver) drawGameOver();

    _term.sleep(40);

}

void Game::drawGameOver()
{
    std::string score_text = "Game Over! You got '" + std::to_string(_score) + "' points.";
    std::string reset_text = "Press 'r' to restart.";

    int half_width = _term.width() / 2;
    int half_height = _term.height() / 2;

    _term.draw_text(half_width - score_text.size() / 2, half_height, score_text);
    _term.draw_text(half_width - reset_text.size() / 2, half_height + 1, reset_text);
}

std::vector<GameObject*> Game::obstacles() const
{
    return _obstacles;
}

Dino* Game::player() const
{
    return _player;
}

GameObject* Game::floor() const
{
    return _floor;
}

Rectangle Game::camera() const
{
    return _camera;
}

GameObject* Game::_newObstacle()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis_x(Game::minDistanceBetweenObstacles, Game::maxDistanceBetweenObstacles);

    int x = _lastObstacleX + dis_x(gen);
    if (x < _camera.right()) x = _camera.right() + 1;
    int width = 2;
    _lastObstacleX = x + width;
    return BoxObstacle(this, x, _floor->top() - 3, width, 3);
}

void Game::_reset()
{
    _releaseResources();

    _obstacles.clear();
    _elapsedTime = 0.f;
    _score = 0;
    _gameOver = false;
    _isDone = false;
    _camera = Rectangle(0, 0, _term.width(), _term.height());
    _lastObstacleX = 0;

    _floor = new Floor(this, _term.height(), _term.width());
    _player = new Dino(this, 2, _floor->top() - Dino::HEIGHT, Dino::WIDTH, Dino::HEIGHT);
    for (size_t i = 1; i < 5; i++)
    {
        GameObject* box = _newObstacle();
        _obstacles.push_back(box);
    }
}

Game::~Game()
{
    _releaseResources();
}

void Game::_releaseResources()
{
    for (size_t i = 0; i < _obstacles.size(); i++)
    {
        delete _obstacles[i];
    }
    delete _floor;
    delete _player;
}
