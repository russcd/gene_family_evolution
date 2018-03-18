/*
 
Need to rework a little for memmory efficiency
 >can stop storing knockout, just draw on the fly during fitness calcs
 >store all of the tRNAs w/ pointers and/or ints pointing towards vector positions
    > create tRNAs with an additional non-functional version one up on the list/vector
 
*/

/// standard headers
#include <string>
#include <string.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <map>
#include <set>
#include <utility>
#include <list>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
using namespace std ;

/// declare our gsl
const gsl_rng *rng ;

/// our headers
#include "cmd_line.h"
#include "trna.h"
#include "individual.h"
#include "mutate.h"
#include "fitness.h"
#include "reproduce.h" 
#include "stats.h"

/// main 
int main ( int argc, char **argv ) {

    //// read command line options
    cmd_line options ;
    options.read_cmd_line( argc, argv ) ;

    // initialize rng for gsl lookup table
    rng = gsl_rng_alloc( gsl_rng_taus2 ) ;
    gsl_rng_set( rng, (long) options.seed ) ;
    
    // create population of size n with two tRNAs of equivalent function
    gene blank ;
    blank.locus = 0 ;
    blank.function = 1 ;
    blank.somatic = options.somatic_rate ;
    blank.germline = options.germline_rate ; 
    individual ind_blank ;
    ind_blank.trnas.push_back(blank) ;
    
    /// if there's more htan one at the start, throw it into the array
    for ( int s = 1 ; s < options.start_count ; s ++ ) {
        blank.locus = gsl_rng_uniform( rng ) ;
        ind_blank.trnas.push_back(blank) ;
    }
    
    vector<individual> population ( options.n, ind_blank ) ;
    
    // fitness vector
    double fitness [options.n] ;
    
    // evolve the population forward in time
    for ( int g = 1 ; g < options.generations ; g ++ ) {
        
        /// vector to swap with
        vector<individual> new_population ( options.n ) ;
        
        /// somatic and germline mutations
        mutate( population, options ) ;

        /// compute fitness
        compute_fitness( fitness, population, options ) ;
        
        /// print stats
        if ( g % 100 == 0 ) {
            print_stats( fitness, population, g ) ;
        }
        
        /// reproduce w/ fitness + recombination
        reproduce( fitness, population, new_population, options ) ;
        
        /// swap populations
        swap( population, new_population ) ;

    }
    return(0) ;
}
