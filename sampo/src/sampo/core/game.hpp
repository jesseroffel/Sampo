#include "application.hpp"

namespace Sampo
{
	class Game : public Application
	{
	public:
		Game();
		~Game() = default;

	protected:
		virtual void Shutdown() {}

		void* m_WindowHandle;
	};
}