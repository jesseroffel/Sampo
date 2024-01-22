#include "sampo_pch.hpp"
#include "console_arguments.hpp"

namespace Sampo
{
	ConsoleArguments* ConsoleArguments::s_myInstance = nullptr;

	ConsoleArguments::ConsoleArguments(int argc, char* argv[])
	{
		if (s_myInstance)
		{
			SAMPO_CORE_CRITICAL("ConsoleArgument already exists!");
			return;
		}
		s_myInstance = this;
		ParseArguments(argc, argv);
	}

	bool ConsoleArguments::HasArgument(const std::string_view anArgument) const
	{
		return myArguments.contains(anArgument.data());
	}

	std::string_view ConsoleArguments::GetArgumentValue(const std::string_view anArgumentKey) const
	{
		if (!HasArgument(anArgumentKey))
			return std::string_view{};

		const auto& result = myArguments.find(anArgumentKey);
		if (result == myArguments.end())
			return std::string_view{};

		return std::string_view(result->second);
	}

	void ConsoleArguments::ParseArguments(int argc, char* argv[])
	{
		if (argc <= 1)
			return;

		for (int i = 1; i < argc; i++)
		{
			if (i + 1 == argc)
				continue;

			std::string_view key = argv[i];
			if (!key.starts_with('-'))
				continue;

			std::string_view value = argv[i+1];
			if (value.starts_with('-'))
				continue;

			key.remove_prefix(1);
			myArguments.emplace(key, value);
			i++;
		}
	}
}