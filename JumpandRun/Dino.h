#ifndef DINO_H
#define DINO_H

#include "GameObject.h"
#include "Terminal.h"
#include "Vec2D.h"

class Dino : public GameObject
{
public:
	Dino(Game* game, int x, int y, int width, int height);
	void update(float dt) override;
	void draw(Terminal& term, const Rectangle& camera) override;
	virtual void jump();
	virtual bool isDead() const;

	static const int WIDTH = 4;
	static const int HEIGHT = 3;
private:
	bool _isJumping;
	int _velY; // Velocity in y direction
	bool _isDead;
};

#endif // !DINO_H