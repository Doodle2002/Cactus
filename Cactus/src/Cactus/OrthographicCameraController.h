#pragma once

#include "Cactus/Renderer/OrthographicCamera.h"
#include "Cactus/Events/ApplicationEvent.h"
#include "Cactus/Events/MouseEvent.h"

#include <glm/glm.hpp>
namespace Cactus {
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		
		void OnUpdate();
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return camera; }
		const OrthographicCamera& GetCamera() const { return camera; }

		float GetZoomLevel() const { return zoomLevel; }
		void SetZoomLevel(float level) { zoomLevel = level; }

		float GetAspectRatio() const { return aspectRatio; }
		

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float aspectRatio;
		float zoomLevel = 1.0f;
		bool rotation = false;

		OrthographicCamera camera;

		glm::vec3 cameraPosition = { 0.0f, 0.0f, 0.0f };
		float cameraRotation = 0.0f;
		
		float cameraTranslationSpeed = 2.5f, cameraRotationSpeed = 180.0f, zoomStep = 0.15f, minZoom = 0.1f, maxZoom = 100.0f;
	};
}