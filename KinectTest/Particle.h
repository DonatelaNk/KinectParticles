#pragma once

#include <SDL.h>
#include <deque>
#include <queue>
#include <glm\glm.hpp>

#include "Constants.h"
#include "PhysicsActor.h"
#include "Sprite.h"

Uint8 inline convertColor(float a)
{
	return Uint8(255.0f * a);
}

//Defines an object that is spawned, has a limited life span, and interacts with the physics system
//Does not necessarily collide with other particles

//Particles are lightweight and passed by value. They do not hold any resources that need to be released
class Particle : public PhysicsActor
{
public:
	Particle();
	Particle(float lifeSpan, glm::vec3 color, Vector pos, Vector velocity, float tailLength = 1.0f);
	virtual ~Particle();

	void Update(float dt);
	void Render(SDL_Renderer* renderer);

	//Physics interface is made public for particles
	void ApplyForce(Vector f);
	void ApplyImpulse(Vector f);
	void SetPosition(Vector p);
	void MarkForDelete();
	Vector PreviousPosition() const;

	//Const interface
	bool IsAlive() const;
	float InverseMass() const;

private:
	//Rendering data
	glm::vec3 color;
	float alpha;
	int renderRadius;
	float tailLength;
	float maxTailLength;
	std::deque<std::pair<Vector, float>> renderPositions;
	Sprite sprite;

	//Physics data
	Vector previousPosition;

	//Creation destruction stuff
	float lifeSpan;
	float age;
};

