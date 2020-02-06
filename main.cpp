#include <iostream>
#include <random>
#include <sstream>

#include <MRndCPP/rnd.h>

//using TRnd = std::ranlux48;
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
    std::uniform_real_distribution<ftyp> d1(-200,+200);
    std::uniform_real_distribution<ftyp> d2(-20,+20);
    std::uniform_real_distribution<ftyp> d3(-10000,+10000);
    params[0] = d1(rnd);
    params[1] = d2(rnd);
    params[2] = d1(rnd);
    params[3] = d2(rnd);
    params[4] = d1(rnd);
    params[5] = d2(rnd);
    params[6] = d3(rnd);
}

void chaos( TRnd &rnd, ftyp params[SIZE_PRMS] , cftyp s ) {
    params[ rnd() % SIZE_PRMS ] += rnd.getFloat(-s,+s);
}

static cftyp data[SIZE_DATA] = {282,314,579,843,1337,2014,2798,4593,6065,7818,9826,11953,14557,17391,20630,24554};

ftyp compute(
    Solve &best
) {
    ftyp bigPenal = 1E-8;
    ftyp e = eval( best.params , data , bigPenal );
    ftyp steps[SIZE_PRMS];
    ftyp norm=0;
    for( utyp i=0 ; i<SIZE_PRMS ; i++ ) {
        steps[i] = 0.1;
        norm += steps[i]*steps[i];
    }
    norm = sqrt( norm / SIZE_PRMS );

    for( ultyp loop=1 ; norm > 1E-7 ; loop++ ) {
        for( utyp i=0 ; i<SIZE_PRMS ; i++ ) {
            if( fabs(steps[i]) < 1E-8 ) { steps[i] = 1E-8; }
            if( fabs(steps[i]) > 1E+1 ) { steps[i] = 1E+1; }
            best.params[i] += steps[i];
            cftyp tmp = eval( best.params , data , bigPenal );
            if( tmp >= e ) {
                best.params[i] -= steps[i] * 2;
                cftyp tmp = eval( best.params , data , bigPenal );
                if( tmp >= e ) {
                    best.params[i] += steps[i];
                    steps[i] *= 0.6;
                } else {
                    steps[i] *= -2;
                    e = tmp;
                }
            } else {
                e = tmp;
                steps[i] *= 2;
            }
        }
        if( ! (loop & 0xFF) ) {
            norm=0;
            for( utyp i=0 ; i<SIZE_PRMS ; i++ ) {
                norm += steps[i]*steps[i];
            }
            norm = sqrt( norm );
        }

        if( ! (loop & 0xFFFF) ) {
            std::cout << loop << " " << e << " [" << norm << "] " << " [" << bigPenal << "] ";
            for( utyp i=0 ; i<SIZE_PRMS ; i++ ) {
                std::cout << best.params[i] << " ";
            }
            std::cout << std::endl;
        }
    }
    return e;
}

ftyp compute(
    TRnd &rnd,
    Solve &best
) {
    Solve solve;
    solve = best;
    ftyp bigPenal = 1E-9;
    ftyp e = eval( best.params , data , bigPenal );
    ftyp s = 1;
    ftyp lastE = e;
    for( ultyp loop=1 ; s > 0.000001 ; loop++ ) {
        chaos( rnd , solve.params , s );
        cftyp tmp = eval( solve.params , data , bigPenal );
        if( tmp <= e ) {
            if( tmp < e ) {
                e = tmp;
            }
            best = solve;
        } else if( rnd() % 3 == 0 ) {
            solve = best;
        }
//        s *= 0.99999995;
        if( ! (loop & 0xFF) ) {
            cftyp tmp = lastE - e;
            if( tmp < 0.001 ) {
                s *= 0.995;
            }
            lastE = e;
        }
        if( ! (loop & 0xFFF) ) {
            std::cout << loop << " " << e << " [" << s << "] "<< " [" << bigPenal << "] ";
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
    Solve best;
    time_t start = time(NULL);
    for( utyp loop=0 ; loop < loops ; loop++ ) {
        Solve s;
        initParams( rnd , s.params );
        cftyp tmp = compute( s );
        if( loop == 0 || tmp < e ) {
            best = s;
            e = tmp;
        }
        std::cout << "----------------------------------" << std::endl;
        std::cout << loop << " " << (time(NULL)-start) << "s  [" << e << "] ";
        for( utyp i=0 ; i<SIZE_PRMS ; i++ ) {
            std::cout << best.params[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "----------------------------------" << std::endl;
    }
    return 0;
}

