#pragma once
#include "Entity.h"
#include "Bullet.h"
#include <vector>
#include "Player.h"
#include <SFML/Graphics.hpp>

#define ENEMY_H


class Enemy : public Entity
{
private:
	sf::RectangleShape healthBar;
	static const int MAX_BULLETS = 100;
	Bullet* bullets[MAX_BULLETS];
	int bulletCount;
	int health;
	float fireDelay; 
	float fireCooldown;
	int damage;

public:
	Enemy(int health);
	~Enemy();
	void TakeDamage(int damage);    
	void Update(float deltaTime) override;
	void Fire();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual sf::FloatRect getGlobalBounds() const;
	int getHealth() const;
	Bullet* getBullet(int index) const;
	int getBulletCount() const;
	void switchSprite();  
};



//Enemy différent


