#pragma once

namespace Sorix
{
	// Abstract class that will be implemented by the user;
	class Game
	{
	public:
		virtual ~Game() = default;
		Game() = default;

		// Delete copy and move constructors
		// The game should not be able to be moved or copied
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;

		Game(Game&&) = delete;
		Game& operator=(Game&&) = delete;

		virtual bool Initialize()		= 0;
		virtual bool Terminate()		= 0;

		virtual bool LoadContent()		= 0;
		virtual bool UnloadContent()	= 0;

		// Update and tick, tick runs once per sec
		virtual void Update(const float a_DeltaTime) = 0;
		virtual void Tick(const float a_DeltaTime) = 0;

		virtual void Render() = 0;
	};
}