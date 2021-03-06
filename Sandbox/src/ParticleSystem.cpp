#include "ParticleSystem.h"

#include <Cactus.h>
#include <glm/gtx/compatibility.hpp>

ParticleSystem::ParticleSystem()
{
	particles.resize(200);
}


void ParticleSystem::OnUpdate()
{
	float dt = Cactus::Time::GetDeltaTime();

	for (auto& part : particles)
	{
		if (!part.active)
		{
			continue;
		}

		float t = (part.maxLifeTime - part.lifeTime) / part.maxLifeTime;

		part.position += part.velocity * dt;
		part.rotation += part.rotationSpeed * dt;
		part.lifeTime -= dt;

		if (part.lifeTime <= 0)
		{
			part.active = false;
		}
	}
}
void ParticleSystem::OnRender()
{

	for (int i = particles.size()-1; i >= 0; i--)
	{
		auto& part = particles[(index + i) % particles.size()];
		if (!part.active)
		{
			continue;
		}
		float t = (part.maxLifeTime - part.lifeTime) / part.maxLifeTime;

		glm::vec4 color = glm::lerp(part.color, part.endColor, t);
		glm::vec2 size = glm::lerp(part.size, part.endSize, t);

		Cactus::Renderer2D::DrawQuad({ part.position.x,part.position.y,0.0f },
			size,
			part.rotation, color);
	}
}
void ParticleSystem::Emit(ParticleData& data)
{
	Particle part;

	part.active = true;
	part.position = data.position;
	part.velocity = data.velocity;
	part.size = data.size;
	part.endSize = data.endSize;
	part.color = data.color;
	part.endColor = data.endColor;
	part.rotation = data.rotation;
	part.rotationSpeed = data.rotationSpeed;

	part.lifeTime = data.lifeTime;
	part.maxLifeTime = data.lifeTime;

	particles[index] = part;
	index = ++index % particles.size();
}