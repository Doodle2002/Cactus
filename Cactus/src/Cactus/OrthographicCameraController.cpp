#include "cactus_pch.h"

#include "OrthographicCameraController.h"
#include "Cactus/Core/Input.h"
#include "Cactus/Core/Time.h"
#include "Cactus/Core/KeyCodes.h"

namespace Cactus {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: camera(-aspectRatio * zoomLevel, aspectRatio* zoomLevel, -zoomLevel, zoomLevel), aspectRatio(aspectRatio), rotation(rotation)
	{

	}
	void OrthographicCameraController::OnUpdate()
	{
		float dt = Time::GetDeltaTime();

		if (Input::KeyDown(CACTUS_KEY_W))
			cameraPosition.y += cameraTranslationSpeed * zoomLevel * dt;
		if (Input::KeyDown(CACTUS_KEY_S))
			cameraPosition.y -= cameraTranslationSpeed * zoomLevel * dt;
		if (Input::KeyDown(CACTUS_KEY_D))
			cameraPosition.x += cameraTranslationSpeed * zoomLevel * dt;
		if (Input::KeyDown(CACTUS_KEY_A))
			cameraPosition.x -= cameraTranslationSpeed * zoomLevel * dt;

		if (rotation)
		{
			if (Input::KeyDown(CACTUS_KEY_E))
				cameraRotation -= cameraRotationSpeed * dt;
			if (Input::KeyDown(CACTUS_KEY_Q))
				cameraRotation += cameraRotationSpeed * dt;
		}
		else
		{
			cameraRotation = 0.0f;
		}


		if (Input::KeyPressed(CACTUS_KEY_R))
			cameraRotation = 0.0f;
		if (Input::KeyPressed(CACTUS_KEY_T))
			cameraPosition = { 0.0,0.0,0.0 };

		camera.SetPosition(cameraPosition);
		camera.SetRotation(cameraRotation);
	}


	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(CACTUS_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(CACTUS_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		zoomLevel -= e.GetYOffset()*zoomStep * zoomLevel;
		zoomLevel = std::max(zoomLevel, minZoom);
		zoomLevel = std::min(zoomLevel, maxZoom);
		camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		

		if (autoResize)
		{
			Resize(e.GetWidth(), e.GetHeight());
		}
		return false;
	}

	void OrthographicCameraController::Resize(float width, float height)
	{
		aspectRatio = width / height;
		camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
	}
}
