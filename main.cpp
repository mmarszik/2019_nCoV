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
constexpr utyp SIZE_DATA = 33;

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
    static cftyp data[SIZE_DATA] = {282,314,581,846,1300,2000,2800,4600,6100,7800,9800,12000,14600,17400,20600,24600,28300,31500,34900,37600,40600,43100,45200,60400,64500,67200,69300,71400,73400,75300,75800,76800,77800};
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

    solve.params[0] = -15450.711398867;
    solve.params[1] = -0.26841337343384;
    solve.params[2] = 31.707675024933;
    solve.params[3] = 0.71824119131701;
    solve.params[4] = -547.64880276297;
    solve.params[5] = 0.36761641976919;
    solve.params[6] = 45200.000016499;
    solve.params[7] = -9371.6820032069;
    solve.params[8] = 43100.000001988;
    solve.params[9] = 13136.931397227;
    solve.params[10] = 6368.1257908809;

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

