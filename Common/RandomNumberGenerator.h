#ifndef RandomNumberGenerator_h
#define RandomNumberGenerator_h


#include "Types.h"


class RandomNumberGenerator
{
    public:
        static void initSeed( uint32 );

        // generates integer numbers in the [0, max-1]
        static int32 getRandomNumber( int32 max )
        {
                return rand_int32() % max;
        }

        // generates integer numbers in the [min, max-1]
        static int32 getRandomNumber( int32 min, int32 max )
        {
                return min+(rand_int32() % (max-min));
        }

        // generates floating point numbers in the [0, 1]
        static float32 getFloat32Probability()
        {
                return static_cast<float32>(rand_int32()) * (1.0f / 4294967295.0f); // divided by 2^32
        }

        // generates floating point numbers in the [0, 1]
        static float64 getFloat64Probability()
        {
                return static_cast<float64>(rand_int32()) * (1.0 / 4294967295.0); // divided by 2^32
        }

        // generates floating point numbers in the [0, 1)
        static float32 getFloat32()
        {
                return static_cast<float32>(rand_int32()) * (1.0f / 4294967296.0f); // divided by 2^32
        }

        // generates double floating point numbers in [0, 1)
        static float64 getFloat64()
        {
                return static_cast<float64>(rand_int32()) * (1.0 / 4294967296.0); // divided by 2^32
        }

        static float32 getRandomNumber( float32 max )
        {
                return getFloat32()*max;
        }

        static float32 getRandomNumber( float32 min, float32 max )
        {
                return min+(getFloat32()*(max-min));
        }

        static float64 getRandomNumber( float64 max )
        {
                return getFloat64()*max;
        }

        static float64 getRandomNumber( float64 min, float64 max )
        {
                return min+(getFloat64()*(max-min));
        }

        static float32 getFloat32Normal();
        static float32 getFloat32Exp();


    protected: // used by derived classes, otherwise not accessible; use the ()-operator
        static uint32 rand_int32(); // generate 32 bit random integer

    private:
        static void zigset( uint32 );

    private:
        static const int32 n = 624, m = 397; // compile time constants
        // the variables below are static (no duplicates can exist)
        static uint32 state[n]; // state vector array
        static int32 p; // position in state array

        // private functions used to generate the pseudo random numbers
        static uint32 twiddle( uint32, uint32 ); // used by gen_state()
        static void gen_state(); // generate new state
};


#endif
