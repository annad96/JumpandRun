#include "Dino.h"
#include "Game.h"

Dino::Dino(Game* game, int x, int y, int width, int height) 
	: GameObject(game, x, y, width, height), 
	_isDead(false), 
	_isJumping(false),
	_velY(0) { }

bool Dino::isDead() const
{
	return _isDead;
}

void Dino::update(float dt)
{
	this->x++;
	_velY++;
	this->y += _velY;
	GameObject* floor = _game->floor();
 	if (floor->intersects(*this) || this->top() >= floor->bottom())
	{
		_velY = 0;
		this->y = _game->floor()->top() - Dino::HEIGHT;
		_isJumping = false;
	}

	// A4: Check for collision with
}

void Dino::draw(Terminal& term, const Rectangle& camera)
{
	GameObject::draw(term, camera);

	Vec2D screenCoords = upperLeft() - camera.upperLeft();
	term.draw_text(screenCoords.x, screenCoords.y, "  xx");
	term.draw_text(screenCoords.x, screenCoords.y+1, " xx ");
	term.draw_text(screenCoords.x, screenCoords.y+2, "x x ");
}

void Dino::jump()
{
	if (_isJumping) return;
	_velY -= 5;
	_isJumping = true;
}