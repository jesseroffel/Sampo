#pragma once

namespace Sampo
{
	class ConsoleArguments
	{
	public:
		ConsoleArguments(int aArgc, char* aArgv[]);
		~ConsoleArguments() = default;

		static bool Create(int aArgc, char* aArgv[]);
		static ConsoleArguments& GetInstance();
		static void Shutdown();

		void Clear();

		bool HasArgument(const std::string_view anArgumentKey) const;

		bool GetIntValue(const std::string_view anArgumentKey, int& outReturnValue) const;
		bool GetStringValue(const std::string_view anArgumentKey, std::string& outReturnValue) const;
		bool GetStringValue(const std::string_view anArgumentKey, std::string_view& outReturnValue) const;
	private:
		/* Heterogeneous lookup for unordered_map in C++20 to prevent allocations when checking values*/
		struct StringHash
		{
			using is_transparent = void;
			[[nodiscard]] size_t operator()(const char* s) const { return std::hash<std::string_view>{}(s); }
			[[nodiscard]] size_t operator()(std::string_view s) const { return std::hash<std::string_view>{}(s); }
			[[nodiscard]] size_t operator()(const std::string& s) const { return std::hash<std::string_view>{}(s); }
		};

		void ParseArguments(int argc, char* argv[]);

		std::string_view FindArgument(const std::string_view& anArgumentKey) const;

		std::unordered_map<std::string, std::string, StringHash, std::equal_to<>> myArguments;

		static ConsoleArguments* s_Instance;
	};
}