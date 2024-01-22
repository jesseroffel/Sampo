#pragma once

namespace Sampo
{
	class ConsoleArguments
	{
	public:
		ConsoleArguments(int argc, char* argv[]);

		static const ConsoleArguments* GetInstance() { return s_myInstance; }

		bool HasArgument(const std::string_view anArgumentKey) const;
		std::string_view GetArgumentValue(const std::string_view anArgumentKey) const;
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

		std::unordered_map<std::string, std::string, StringHash, std::equal_to<>> myArguments;

		static ConsoleArguments* s_myInstance;
	};
}