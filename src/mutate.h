#ifndef __MUTATE_H
#define __MUTATE_H

void mutate( vector<individual> &population, cmd_line &options ) {
    
    // add germline mutations
    for ( int i = 0 ; i < population.size() ; i ++ ) {
        for ( int g = 0 ; g < population[i].trnas.size() ; g ++ ) {
            if ( gsl_ran_bernoulli( rng, population[i].trnas[g].germline ) ) {
                population[i].trnas[g].function = 0 ;
            }
        }
    }
    
    // delete tRNAs
    for ( int i = 0 ; i < population.size() ; i ++ ) {
        for ( int g = population[i].trnas.size() -1 ; g > -1 ; g -- ) {
            if ( gsl_ran_bernoulli( rng, options.deletion_rate ) ) {
                population[i].trnas.erase( population[i].trnas.begin() + g ) ;
            }
        }
    }

    // duplicate tRNAs
    for ( int i = 0 ; i < population.size() ; i ++ ) {
        for ( int g = 0 ; g < population[i].trnas.size() ; g ++ ) {
            if ( gsl_ran_bernoulli( rng, options.duplication_rate ) ) {
                
                /// copy current gene copy
                gene new_gene = population[i].trnas[g] ;
                
                /// pick a new location at random
                new_gene.locus = gsl_rng_uniform( rng ) ;
                
                /// store it
                population[i].trnas.push_back( new_gene ) ;
                
                /// sort the array of trnas
                sort( population[i].trnas.begin() , population[i].trnas.end() ) ;
            }
        }
    }
}

#endif
