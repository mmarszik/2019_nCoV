#include <iostream>
#include <random>
#include <algorithm>

using TRnd = std::ranlux48;
using ftyp = double;
using cftyp = const ftyp;
using utyp = unsigned int;
using ultyp = unsigned long long;

constexpr utyp SIZE_PRMS =  7;
constexpr utyp SIZE_DATA = 16;

struct Solve {
    ftyp params[SIZE_PRMS];
};

ftyp formula( cftyp x , cftyp params[SIZE_PRMS] ) {
    return params[0] * pow(x , params[1] ) + params[2] * pow(x , params[3] ) + params[4] * pow(x , params[5] ) + params[6];
}

ftyp eval( cftyp params[SIZE_PRMS], cftyp data[SIZE_DATA], cftyp bigPenal ) {
    ftyp e = 0;
    for( utyp i=1 ; i<SIZE_DATA ; i++ ) {
        cftyp tmp = data[i] - formula( data[i-1] , params );
        e += tmp * tmp;
    }
    e = sqrt( e / (SIZE_DATA-1) );
    for( utyp i=0 ; i<SIZE_PRMS ; i++ ) {
        e += params[i] * params[i] * bigPenal;
    }
    return e;
}

void initParams( TRnd &rnd, ftyp params[SIZE_PRMS] ) {
    std::uniform_real_distribution<ftyp> d(-20,+20);
    for( utyp i=0 ; i<SIZE_PRMS ; i++ ) {
        params[i] = d(rnd);
    }
}

void chaos( TRnd &rnd, ftyp params[SIZE_PRMS] , cftyp s ) {
    std::uniform_int_distribution<utyp> d2(0,SIZE_PRMS-1);
    std::uniform_real_distribution<ftyp> d1(-1,+1);
    params[ d2(rnd) ] += d1(rnd) * s;
}


ftyp compute(
    TRnd &rnd,
    Solve &best
) {
    static cftyp data[SIZE_DATA] = {282,314,579,843,1337,2014,2798,4593,6065,7818,9826,11953,14557,17391,20630,24554};
    Solve solve;
    solve = best;
    ftyp bigPenal = 0.000001;
    ftyp e = eval( best.params , data , bigPenal );
    ftyp s = 1;
    ftyp avg = 1;
    for( ultyp loop=0 ; avg > 0.00000001 ; loop++ ) {
        chaos( rnd , solve.params , s );
        cftyp tmp = eval( solve.params , data , bigPenal );
        if( e < 1000 ) {
            cftyp d = tmp >= e ? 0 : e - tmp;
            avg = avg * 0.999999 + d * 0.000001;
        }
        if( tmp <= e ) {
            if( tmp < e ) {
                e = tmp;
            }
            best = solve;
        } else if( rnd() % 2 == 0 ) {
            solve = best;
            s *= 0.9999995;
        }
        if( bigPenal > 0.000000000001 ) {
            bigPenal *= 0.9999995;
        }
        if( ! (loop & 0xFFFFF) ) {
            std::cout << loop << " " << e << " [" << s << "] "<< " [" << bigPenal << "] [" << avg << "] ";
            for( utyp i=0 ; i<SIZE_PRMS ; i++ ) {
                std::cout << best.params[i] << " ";
            }
            std::cout << std::endl;
        }
    }

    return e;
}

int main(int argc, char *argv[]) {
    std::random_device rd;
    ultyp seed = rd();
    std::cout << "mainSeed: " << seed << std::endl;
    TRnd rnd( seed );
    ftyp e;
    Solve best;
    for( utyp loop=0 ; true ; loop++ ) {
        Solve s;
        initParams( rnd , s.params );
        cftyp tmp = compute( rnd, s );
        if( loop == 0 || tmp < e ) {
            best = s;
            e = tmp;
        }
        std::cout << "----------------------------------" << std::endl;
        std::cout << loop << " [" << e << "] ";
        for( utyp i=0 ; i<SIZE_PRMS ; i++ ) {
            std::cout << best.params[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "----------------------------------" << std::endl;
    }
    return 0;
}

