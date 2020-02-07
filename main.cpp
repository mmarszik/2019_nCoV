#include <iostream>
#include <random>
#include <sstream>
#include <cstring>

#include <MRndCPP/rnd.h>

//using TRnd = std::ranlux48;
using ftyp = double;
using cftyp = const ftyp;
using utyp = unsigned int;
using ultyp = unsigned long long;

constexpr utyp SIZE_PRMS =  7;
constexpr utyp SIZE_DATA = 17;

struct Solve {
    ftyp params[SIZE_PRMS];
};

ftyp formula( cftyp x , cftyp params[SIZE_PRMS] ) {
    return params[0] * pow(x , params[1] ) + params[2] * pow(x , params[3] ) + params[4] * pow(x , params[5] ) + params[6];
}

ftyp eval( cftyp params[SIZE_PRMS], cftyp data[SIZE_DATA], cftyp bigPenal ) {
    ftyp e = 0;
    for( utyp i=1 ; i<SIZE_DATA ; i++ ) {
        e += fabs( data[i] - formula( data[i-1] , params ) ) / data[i];
    }
    for( utyp i=0 ; i<SIZE_PRMS ; i++ ) {
        e += params[i] * params[i] * bigPenal;
    }
    return e;
}

void initParams( TRnd &rnd, ftyp params[SIZE_PRMS] ) {
    std::uniform_real_distribution<ftyp> d1(-1000,+1000);
    std::uniform_real_distribution<ftyp> d2(-20,+20);
    std::uniform_real_distribution<ftyp> d3(-20000,+20000);
    params[0] = d1(rnd);
    params[1] = d2(rnd);
    params[2] = d1(rnd);
    params[3] = d2(rnd);
    params[4] = d1(rnd);
    params[5] = d2(rnd);
    params[6] = d3(rnd);
}

static void chaos1( TRnd &rnd, ftyp params[SIZE_PRMS], bool total ) {
    if( total ) {
        switch( rnd() % 7 ) {
            case 0: params[0] = rnd.getFloat(-1000,+1000); break;
            case 1: params[1] = rnd.getFloat(-10,+10); break;
            case 2: params[2] = rnd.getFloat(-1000,+1000); break;
            case 3: params[3] = rnd.getFloat(-10,+10); break;
            case 4: params[4] = rnd.getFloat(-1000,+1000); break;
            case 5: params[5] = rnd.getFloat(-10,+10); break;
            case 6: params[6] = rnd.getFloat(-30000,+30000); break;
        }
    } else {
        utyp r = rnd() % SIZE_PRMS;
        params[r] += rnd.getFloat( -0.01 * params[r] , +0.01 * params[r] );
    }
}

static ftyp compute(
    TRnd &rnd,
    Solve &best
) {
    static cftyp data[SIZE_DATA] = {282,314,579,843,1337,2014,2798,4593,6065,7818,9826,11953,14557,17391,20630,24554,28276};
    ftyp bigPenal = 1E-14;
    ftyp e = eval( best.params , data , bigPenal );
    Solve solve = best;

    for( ultyp loop=0 ; loop <= 0xFFFFFu*20 ; loop++ ) {
        chaos1( rnd , solve.params , loop < 0xFFFFFu*3 );
        cftyp tmp = eval( solve.params , data , bigPenal );
        if( tmp <= e ) {
            best = solve;
            e = tmp;
        } else if( rnd() % 5 == 0 ) {
            solve = best;
        }
        if( ! (loop & 0xFFFFF) ) {
            std::cout << loop << " [" << e << "] ";
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
    ultyp loops = 0xFFFFFFFFFFFFFFFFull;
    if( argc > 1 ) {
        std::istringstream ss(argv[1]);
        ss >> loops;
    }
    std::cout << "mainSeed: " << seed << std::endl;
    TRnd rnd( seed );
    ftyp e;
    Solve best,solve;
    solve.params[0] = -6530.51;
    solve.params[1] = -0.402183;
    solve.params[2] = -1110.89;
    solve.params[3] = -0.322757;
    solve.params[4] = 1.65745;
    solve.params[5] = 0.962681;
    solve.params[6] = 790.465;

    time_t start = time(NULL);
    for( utyp loop=0 ; loop < loops ; loop++ ) {
        cftyp tmp = compute( rnd, solve );
        if( loop == 0 || tmp < e ) {
            best = solve;
            e = tmp;
        }
        std::cout << "----------------------------------" << std::endl;
        std::cout << loop << " " << (time(NULL)-start) << "s  [" << e << "] ";
        for( utyp i=0 ; i<SIZE_PRMS ; i++ ) {
            std::cout << best.params[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "----------------------------------" << std::endl;
        initParams( rnd , solve.params );
    }
    return 0;
}

