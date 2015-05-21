/*#########################################################################

    LIBRARY : RandomNumberGenerator

    Mersenne Twister Random Number Generator

    ---------------------------------------------------------------------

    Author(s) : Fabrice LAURI
    Creation Date : 2009/11/18
    Last Update : 2011/02/01

#########################################################################*/


#include "RandomNumberGenerator.h"


#include <math.h>
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>

#include "MemDefns.h"

using namespace std;


//#pragma warning( disable : 4244 ) // disable conversions to lower precision


uint32 RandomNumberGenerator::state[n] = { 0x0UL };
int32 RandomNumberGenerator::p = 0;


// inline for speed, must therefore reside in header file
uint32
RandomNumberGenerator::twiddle( uint32 u, uint32 v)
{
    return (((u & 0x80000000UL) | (v & 0x7FFFFFFFUL)) >> 1) ^ ((v & 1UL) ? 0x9908B0DFUL : 0x0UL);
}


uint32
RandomNumberGenerator::rand_int32()
{ // generate 32 bit random int
    if (p == n)
    {
        gen_state(); // new state vector needed
    }

    // gen_state() is split off to be non-inline, because it is only called once
    // in every 624 calls and otherwise irand() would become too big to get inlined
    uint32 x = state[p++];
    x ^= (x >> 11);
    x ^= (x << 7) & 0x9D2C5680UL;
    x ^= (x << 15) & 0xEFC60000UL;

    return x ^ (x >> 18);
}


void
RandomNumberGenerator::gen_state()
{ // generate new state vector
    for (int i = 0; i < (n - m); ++i)
    {
        state[i] = state[i + m] ^ twiddle(state[i], state[i + 1]);
    }

    for (int i = n - m; i < (n - 1); ++i)
    {
        state[i] = state[i + m - n] ^ twiddle(state[i], state[i + 1]);
    }

    state[n - 1] = state[m - 1] ^ twiddle(state[n - 1], state[0]);
    p = 0; // reset position
}


void
RandomNumberGenerator::initSeed( uint32 s )
{  // init by 32 bit seed
    if (s == 0)
    {
        s = time( NULL );
    }

    state[0] = s & 0xFFFFFFFFUL; // for > 32 bit machines
    for (int i = 1; i < n; ++i)
    {
        state[i] = 1812433253UL * (state[i - 1] ^ (state[i - 1] >> 30)) + i;
        // see Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier
        // in the previous versions, MSBs of the seed affect only MSBs of the array state
        // 2002/01/09 modified by Makoto Matsumoto
        state[i] &= 0xFFFFFFFFUL; // for > 32 bit machines
    }
    p = n; // force gen_state() to be called for next random number

    zigset( s );
}


//*****************************************************************************
//
//  Ziggurat algorithm
//
//*****************************************************************************


/*--------This procedure sets the seed and creates the tables------*/

static unsigned long jz,jsr=123456789;

#define SHR3 (jz=jsr, jsr^=(jsr<<13), jsr^=(jsr>>17), jsr^=(jsr<<5),jz+jsr)
#define UNI (.5 + (signed) SHR3*.2328306e-9)
#define IUNI SHR3

static long hz;
static unsigned long iz, kn[128], ke[256];
static float wn[128],fn[128], we[256],fe[256];


void
RandomNumberGenerator::zigset( uint32 jsrseed )
{
    const float64 m1 = 2147483648.0, m2 = 4294967296.;
    float64 dn=3.442619855899,tn=dn,vn=9.91256303526217e-3, q;
    float64 de=7.697117470131487, te=de, ve=3.949659822581572e-3;
    int32 i;
    jsr^=jsrseed;

    /* Set up tables for RNOR */
    q=vn/exp(-.5*dn*dn);
    kn[0]=(dn/q)*m1;
    kn[1]=0;

    wn[0]=q/m1;
    wn[127]=dn/m1;

    fn[0]=1.;
    fn[127]=exp(-.5*dn*dn);

    for(i=126;i>=1;i--)
    {
        dn=sqrt(-2.*log(vn/dn+exp(-.5*dn*dn)));
        kn[i+1]=(dn/tn)*m1;
        tn=dn;
        fn[i]=exp(-.5*dn*dn);
        wn[i]=dn/m1;
    }

    /* Set up tables for REXP */
    q = ve/exp(-de);
    ke[0]=(de/q)*m2;
    ke[1]=0;

    we[0]=q/m2;
    we[255]=de/m2;

    fe[0]=1.;
    fe[255]=exp(-de);

    for(i=254;i>=1;i--)
    {
        de=-log(ve/de+exp(-de));
        ke[i+1]= (de/te)*m2;
        te=de;
        fe[i]=exp(-de);
        we[i]=de/m2;
    }
}


float nfix()
{
    const float r = 3.442620f;     /* The start of the right tail */
    static float x, y;
    for(;;)
    {
        x=hz*wn[iz];      /* iz==0, handles the base strip */
        if(iz==0)
        {
            do
            {
                x=-log(UNI)*0.2904764; y=-log(UNI);
            }	/* .2904764 is 1/r */
            while(y+y<x*x);

            return (hz>0)? r+x : -r-x;
        }

        /* iz>0, handle the wedges of other strips */
        if( fn[iz]+UNI*(fn[iz-1]-fn[iz]) < exp(-.5*x*x) ) return x;

        /* initiate, try to exit for(;;) for loop*/
        hz=SHR3;
        iz=hz&127;
        if(fabs( (float) hz)<kn[iz]) return (hz*wn[iz]);
    }
}


float32
RandomNumberGenerator::getFloat32Normal()
{
    hz=SHR3;
    iz=hz&127;

    return (fabs( (float) hz)<kn[iz]) ? hz*wn[iz] : nfix();
}



/* efix() generates variates from the residue when rejection in REXP occurs. */
float efix()
{
    float x;

    for(;;)
    {
        if(iz==0) return (7.69711-log(UNI));          /* iz==0 */
        x=jz*we[iz];
        if( fe[iz]+UNI*(fe[iz-1]-fe[iz]) < exp(-x) ) return (x);

        /* initiate, try to exit for(;;) loop */
        jz=SHR3;
        iz=(jz&255);
        if(jz<ke[iz]) return (jz*we[iz]);
    }
}

float32
RandomNumberGenerator::getFloat32Exp()
{
    jz=SHR3;
    iz=jz&255;

    return (jz < ke[iz]) ? jz*we[iz] : efix();
}
