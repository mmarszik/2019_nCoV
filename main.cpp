#include <iostream>
#include <random>
#include <sstream>
#include <cstring>
#include <iomanip>
#include <MRndCPP/rnd.h>

//using TRnd = std::ranlux48;
using ftyp  = double;
using cftyp = const ftyp;
using utyp  = unsigned int;
using ultyp = unsigned long long;
using cltyp = const ultyp;

constexpr utyp SIZE_PRMS = 11;
constexpr utyp SIZE_DATA = 36;

struct Solve {
    ftyp params[SIZE_PRMS];
};

static ftyp formula( cftyp x , cftyp params[SIZE_PRMS] ) {
    return
        params[0] * pow(x , params[1] ) +
        params[2] * pow(x , params[3] ) +
        params[4] * pow(x , params[5] ) +
        ( x > params[6] ? params[7] : 0 ) +
        ( x > params[8] ? params[9] : 0 ) +
        params[10]
    ;
}

static ftyp eval( cftyp params[SIZE_PRMS], cftyp data[SIZE_DATA], cftyp bigPenal ) {
    ftyp e = 0;
    for( utyp i=1 ; i<SIZE_DATA ; i++ ) {
        cftyp tmp = data[i-0] - formula( data[i-1] , params );
        e += tmp * tmp;
    }
    e = sqrt( e / (SIZE_DATA-1) );
    for( utyp i=0 ; i<SIZE_PRMS ; i++ ) {
        e += params[i] * params[i] * bigPenal;
    }
    return e;
}

void initParams( TRnd &rnd, ftyp params[SIZE_PRMS] ) {
    std::uniform_real_distribution<ftyp> d1(-100000,+100000);
    std::uniform_real_distribution<ftyp> d2(-2,+2);
    std::uniform_real_distribution<ftyp> d3(-100000,+100000);
    std::uniform_real_distribution<ftyp> d4(0,+100000);
    std::uniform_real_distribution<ftyp> d5(-100000,+100000);

    params[0] = d1(rnd);
    params[1] = d2(rnd);

    params[2] = d1(rnd);
    params[3] = d2(rnd);

    params[4] = d1(rnd);
    params[5] = d2(rnd);

    params[6] = d4(rnd);
    params[7] = d5(rnd);

    params[8] = d4(rnd);
    params[9] = d5(rnd);

    params[10] = d3(rnd);
}

static void chaos( TRnd &rnd, ftyp params[SIZE_PRMS], cftyp step ) {
    if( step == 0.1 ) {
        switch( rnd() % SIZE_PRMS ) {
            case  0: params[ 0] = rnd.getFloat(-100000,+100000); break;
            case  1: params[ 1] = rnd.getFloat(-2,+2); break;
            case  2: params[ 2] = rnd.getFloat(-100000,+100000); break;
            case  3: params[ 3] = rnd.getFloat(-2,+2); break;
            case  4: params[ 4] = rnd.getFloat(-100000,+100000); break;
            case  5: params[ 5] = rnd.getFloat(-2,+2); break;
            case  6: params[ 6] = rnd.getFloat(0,+100000); break;
            case  7: params[ 7] = rnd.getFloat(-100000,+100000); break;
            case  8: params[ 8] = rnd.getFloat(0,+100000); break;
            case  9: params[ 9] = rnd.getFloat(-100000,+100000); break;
            case 10: params[10] = rnd.getFloat(-100000,+100000); break;
        }
    } else {
        utyp r = rnd() % SIZE_PRMS;
        params[r] += rnd.getFloat( -step * params[r] , +step * params[r] );
    }
}

static ftyp compute(
    TRnd &rnd,
    Solve &best
) {
    static cftyp data[SIZE_DATA] = {282,314,579,843,1337,2014,2798,4593,6065,7818,9826,11953,14557,17391,20630,24554,28276,31481,34886,37558,40554,43103,45171,46997,49053,50580,51512,71429,73322,75204,75748,76769,77794,78811,79331,80239};
    ftyp bigPenal = 1E-8;
    ftyp e = eval( best.params , data , bigPenal );
    Solve solve = best;
    cftyp step_start = 0.1;
    cftyp step_end   = 0.001;
    cltyp part       = ((1u<<23)-1);
    cltyp loops      = part*50u;
    ultyp full_rand  = part*2u;
    cftyp ratio      = pow(step_end/step_start,1.0/(loops-full_rand) );
    ftyp step        = step_start;
    ftyp last        = e;
    cftyp minInc     = 0.0001;

    for( ultyp loop=0 ; loop <= loops ; loop++ ) {
        if( loop > full_rand ) {
            step *= ratio;
        }
        chaos( rnd , solve.params , step );
        cftyp tmp = eval( solve.params , data , bigPenal );
        if( tmp <= e ) {
            best = solve;
            e = tmp;
        } else if( rnd() % 3 == 0 ) {
            solve = best;
        }
        if( ! (loop & part) || loop == loops ) {
            std::cout << loop << " [" << e << "] " << " {" << step << "} ";
            for( utyp i=0 ; i<SIZE_PRMS ; i++ ) {
                std::cout << best.params[i] << " ";
            }
            std::cout << std::endl;
            if( loop > full_rand && (last - e) < minInc ) {
                break;
            }
            last = e;
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
    if( argc > 2 ) {
        std::istringstream ss(argv[2]);
        ss >> seed;
    }
    std::cout << "mainSeed: " << seed << std::endl;
    TRnd rnd( seed );
    ftyp e;
    Solve best, solve;

    solve.params[0] = -14895.165844253;
    solve.params[1] = -0.25590340399202;
    solve.params[2] = 32.426116590946;
    solve.params[3] = 0.71841485400613;
    solve.params[4] = -465.33420277425;
    solve.params[5] = 0.38747655529922;
    solve.params[6] = 45200.000015003;
    solve.params[7] = -9429.915763172;
    solve.params[8] = 43100.000001988;
    solve.params[9] = 13103.358962318;
    solve.params[10] = 6217.1578173683;

    time_t start = time(NULL);
    for( utyp loop=0 ; loop < loops ; loop++ ) {
        cftyp tmp = compute( rnd, solve );
        if( loop == 0 || tmp < e ) {
            best = solve;
            e = tmp;
        }
        std::cout << "----------------------------------" << std::endl;
        std::cout << loop << " " << (time(NULL)-start) << "s  [" << std::setw(14) << std::setprecision(14) << e << "] ";
        for( utyp i=0 ; i<SIZE_PRMS ; i++ ) {
            std::cout << std::setw(14) << std::setprecision(14) << best.params[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "----------------------------------" << std::endl;
        if( time(NULL) - start < 2*3600 || !(loop & 3) ) {
            solve = best;
            chaos( rnd , solve.params , 0.5 );
        } else {
            initParams( rnd , solve.params );
        }
    }
    return 0;
}

