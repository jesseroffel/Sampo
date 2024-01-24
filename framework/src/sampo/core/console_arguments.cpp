#include "sampo_pch.hpp"
#include "console_arguments.hpp"

namespace Sampo
{
	ConsoleArguments* ConsoleArguments::s_myInstance = nullptr;

	ConsoleArguments::ConsoleArguments(int aArgc, char* aArgv[])
	{
		ParseArguments(aArgc, aArgv);
	}

	bool ConsoleArguments::Create(int aArgc, char* argv[])
	{
		if (s_myInstance)
			return false;

		s_myInstance = new ConsoleArguments(aArgc, argv);
		return true;
	}

	bool ConsoleArguments::HasArgument(const std::string_view anArgument) const
	{
		return myArguments.contains(anArgument.data());
	}

	bool ConsoleArguments::GetIntValue(const std::string_view anArgumentKey, int& outReturnValue) const
	{
		const std::string_view foundArgument = FindArgument(anArgumentKey);
		if (foundArgument.empty())
			return false;

		outReturnValue = atoi(foundArgument.data());
		return true;
	}

	bool ConsoleArguments::GetStringValue(const std::string_view anArgumentKey, std::string& outReturnValue) const
	{
		const std::string_view foundArgument = FindArgument(anArgumentKey);
		if (foundArgument.empty())
			return false;

		outReturnValue = foundArgument;
		return true;
	}

	bool ConsoleArguments::GetStringValue(const std::string_view anArgumentKey, std::string_view& outReturnValue) const
	{
		const std::string_view foundArgument = FindArgument(anArgumentKey);
		if (foundArgument.empty())
			return false;

		outReturnValue = foundArgument;
		return true;
	}

	void ConsoleArguments::ParseArguments(int argc, char* argv[])
	{
		if (argc <= 1)
			return;

		for (int i = 0; i < argc; i++)
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

	std::string_view ConsoleArguments::FindArgument(const std::string_view& anArgumentKey) const
	{
		if (!HasArgument(anArgumentKey))
			return std::string_view();

		const auto& result = myArguments.find(anArgumentKey);
		if (result == myArguments.end())
			return std::string_view();

		return result->second;
	}
}