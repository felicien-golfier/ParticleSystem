#include "LF_String.h"


#include "MemDefns.h"

#include <stdio.h>
#include <string>
#include <iostream>


namespace lf
{

String::String()
{
	m_Content = NULL;
	m_Size = 0;
}

String::String( const String & str )
{
	m_Size = str.m_Size;
	if (m_Size)
	{
		m_Content = new char [m_Size+1];
		strcpy( m_Content, str.m_Content );
	}
	else
	{
		m_Content = NULL;
	}
}

String::~String()
{
	SafeDeleteArray( m_Content );
}

String &
String::operator=( const String & str )
{
	SafeDeleteArray( m_Content );

	m_Size = str.m_Size;
	if (m_Size)
	{
		m_Content = new char [m_Size+1];
		strcpy( m_Content, str.m_Content );
	}
	else
	{
		m_Content = NULL;
	}

	return (*this);
}


String &
String::operator+=( const String & str )
{
	if (str.m_Content)
	{
		char* ptr;

		m_Size += strlen( str.m_Content );

		ptr = new char [m_Size+1];
		if (m_Content)
		{
			strcpy( ptr, m_Content );
			delete [] m_Content;
			strcat( ptr, str.m_Content );
		}
		else
		{
			strcpy( ptr, str.m_Content );
		}

		m_Content = ptr;
	}

	return (*this);
}

String
String::operator+( const String & str ) const
{
	String res( m_Content );

	res += str.m_Content;

	return res;
}


String::String( const char* str )
{
	if (str)
	{
		m_Size = strlen( str );
		m_Content = new char [m_Size+1];
		strcpy( m_Content, str );
	}
	else
	{
		m_Size = 0;
		m_Content = NULL;
	}
}

String &
String::operator=( const char* str )
{
	SafeDeleteArray( m_Content );

	if (str)
	{
		m_Size = strlen( str );
		m_Content = new char [m_Size+1];
		strcpy( m_Content, str );
	}
	else
	{
		m_Size = 0;
		m_Content = NULL;
	}

	return (*this);
}

String &
String::operator+=( const char* str )
{
	if (str)
	{
		char* ptr;

		m_Size += strlen( str );

		ptr = new char [m_Size+1];
		if (m_Content)
		{
			strcpy( ptr, m_Content );
			delete [] m_Content;
			strcat( ptr, str );
		}
		else
		{
			strcpy( ptr, str );
		}

		m_Content = ptr;
	}

	return (*this);
}

String
String::operator+( const char* str ) const
{
	String res( m_Content );

	res += str;

	return res;
}


String &
String::operator+=( uint32 scalar )
{
	char str[32];

	sprintf( str, "%d", scalar );
	return this->operator+=( str );
}

String
String::operator+( uint32 scalar ) const
{
	char str[32];

	sprintf( str, "%d", scalar );
	return this->operator+( str );
}


String &
String::operator+=( uint64 scalar )
{
	char str[32];

	sprintf( str, "%lld", scalar );
	return this->operator+=( str );
}

String
String::operator+( uint64 scalar ) const
{
	char str[32];

	sprintf( str, "%lld", scalar );
	return this->operator+( str );
}


bool
String::operator<( const String & str ) const
{
	return (strcmp( c_str(), str.c_str() ) < 0);
}


char &
String::operator[]( uint32 i )
{
	return m_Content[i];
}


const char*
String::c_str() const
{
	if (m_Content)
	{
		return m_Content;
	}
	else
	{
		return "";
	}
}

char*
String::str()
{
	if (m_Content)
	{
		return m_Content;
	}
	else
	{
		return "";
	}
}


uint32
String::getLength() const
{
	return m_Size;
}


bool
String::find( const char* sub_string ) const
{
	return (strstr( m_Content, sub_string ) != NULL);
}


uint32
String::findFirstChar( char c, bool cond_unfound ) const
{
	if (m_Content)
	{
		uint32 i;

		i = 0;
		while (i < m_Size && m_Content[i] != c)
		{
			++i;
		}

		if (m_Content[i] == c)
		{
			return i;
		}
		else
		{
			if (cond_unfound)
			{
				return 0xFFFFFFFF;
			}
			else
			{
				return m_Size;
			}
		}
	}
	else
	{
		return 0xFFFFFFFF;
	}
}

uint32
String::findLastChar( char c, bool cond_unfound ) const
{
	if (m_Content)
	{
		uint32 i;

		i = m_Size-1;
		while (i > 0 && m_Content[i] != c)
		{
			--i;
		}

		if (m_Content[i] == c)
		{
			return i;
		}
		else
		{
			if (cond_unfound)
			{
				return 0xFFFFFFFF;
			}
			else
			{
				return m_Size;
			}
		}
	}
	else
	{
		return 0xFFFFFFFF;
	}
}


String
String::getSubString( uint32 first ) const
{
	if (isInside( first ))
	{
		return String( m_Content+first );
	}
	else
	{
		return String( m_Content );
	}
}


String
String::getSubString( uint32 first, uint32 last ) const
{
	String res;

	if (isInside( first ))
	{
		uint32 size;

		if (isInside( last ))
		{
			size = last-first+1;
		}
		else
		{
			size = m_Size-first+1;
		}

		if (size)
		{
			res.m_Size = size;
			res.m_Content = new char [size+1];
			strncpy( res.m_Content, m_Content+first, size );
			res.m_Content[size] = '\0';
		}
	}

	return res;
}


bool
String::isInside( uint32 loc ) const
{
	return (loc < m_Size);
}


void
String::replace( char src, char dest )
{
    for( uint32 i = 0; i < m_Size; ++i )
    {
        if (m_Content[i] == src)
        {
            m_Content[i] = dest;
        }
    }
}


std::ostream &
operator<<( std::ostream & os, const String & s )
{
	if (s.m_Content)
	{
		return os << s.m_Content;
	}
	else
	{
		return os;
	}
}

}
