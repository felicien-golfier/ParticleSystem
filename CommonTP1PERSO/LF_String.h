#ifndef LF_String_h
#define LF_String_h


#include "Types.h"

#include <ostream>


namespace lf
{

class String
{
    public:
        String();
        String( const String & );
        ~String();
        String & operator=( const String & );

        String & operator+=( const String & );
        String operator+( const String & ) const;

        String( const char* );
        String & operator=( const char* );
        String & operator+=( const char* );
        String operator+( const char* ) const;

        String & operator+=( uint32 );
        String operator+( uint32 ) const;

        String & operator+=( uint64 );
        String operator+( uint64 ) const;

        bool operator<( const String & ) const;

		char & operator[]( uint32 i );

        const char* c_str() const;
		char* str();
        uint32 getLength() const;

        uint32 findFirstChar( char, bool = false ) const;
        uint32 findLastChar( char, bool = false ) const;

        bool find( const char* ) const;

        String getSubString( uint32 first ) const;
        String getSubString( uint32 first, uint32 size ) const;

        void replace( char, char );

        bool isInside( uint32 ) const;

        friend std::ostream & operator<<( std::ostream &, const String & );


    protected:
        uint32 m_Size;
        char* m_Content;
};

}


#endif
