#pragma once

#include <Cactus.h>

struct ParticleData
{
	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec2 size, endSize;

	float rotation = 0.0f, rotationSpeed = 0.0f;
	glm::vec4 color, endColor;
	float lifeTime = 1.0f;
};

class ParticleSystem
{
public:
	ParticleSystem();

	void OnUpdate();
	void OnRender();
	void Emit(ParticleData& data);

private:
	
	struct Particle
	{
		bool active = false;
		glm::vec2 position;
		glm::vec2 velocity;
		glm::vec2 size, endSize;
		float rotation, rotationSpeed;

		glm::vec4 color, endColor;
		float lifeTime = 1.0f;
		float maxLifeTime = 1.0f;
	};

	std::vector<Particle> particles;
	int index = 0;
};
