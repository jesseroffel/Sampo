#pragma once
#include "core_defines.h"
#include <string>
namespace Rakas
{
	class Data
	{
	public:
		//Getting the value
		operator bool() const;
		operator int() const;
		operator unsigned int() const;
		//Add primitive type U8/I8 to U64/I64
		operator float() const;
		operator double() const;
		operator char() const;
		operator unsigned char() const;
		operator std::string() const;


		//Assigning thevalue
		Data(bool a_Bool);
		Data(unsigned int a_UInt);
		Data(int a_Int);
		Data(float a_Float);
		Data(double a_Double);
		Data(unsigned char a_UChar);
		Data(char a_Char);
		Data(std::string a_String);

		enum class DataType
		{
			TYPE_NULL,
			TYPE_BOOL,
			TYPE_INT,
			TYPE_DECIMAL,
			TYPE_STRING
		};

		DataType GetType() const { return m_Type; }

	private:
		DataType m_Type = TYPE_NULL;

		union 
		{
			bool m_Bool;
			I64 m_Int;
			double m_Decimal;
			//Transform m_Transform;
			//Matrix m_Matrix;
			U8 m_memory[sizeof(I64)];
		} m_Data;
	};
}
