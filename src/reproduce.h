#ifndef __REPRODUCE_H
#define __REPRODUCE_H

/// compute fitness
void reproduce( const double *fitness, vector<individual> &population, vector<individual> &new_population, cmd_line &options ) {
    
    // array to store draws
    unsigned int draws[ population.size() ] ;
    
    // populate parent multinomial samplings
    const gsl_ran_discrete_t *g = gsl_ran_discrete_preproc( population.size(), fitness ) ;
    
    /// iterate through all individuals and draw parents + recomb
    for ( int i = 0 ; i < population.size() ; i ++ ) {
    
        /// new individual
        individual new_ind ;
        
        /// grab mom and dad
        int mom = gsl_ran_discrete( rng, g ) ;
        int dad = gsl_ran_discrete( rng, g ) ;
    
        // now draw tRNAs from two parents
        int it1 = 0 ;
        int it2 = 0 ;
        
        while ( it1 < population[dad].trnas.size() || it2 < population[mom].trnas.size() ) {
            
            /// go through dad to end if mom is out
            if ( it2 == population[mom].trnas.size() ) {
                if ( gsl_ran_bernoulli( rng, 0.5 ) ) {
                    new_ind.trnas.push_back( population[dad].trnas[it1] ) ;
                    sort( new_ind.trnas.begin(), new_ind.trnas.end() ) ;
                }
                it1 ++ ;
            }
            
            /// go through mom to end if mom is out 
            else if ( it1 == population[dad].trnas.size() ) {
                if ( gsl_ran_bernoulli( rng, 0.5 ) ) {
                    new_ind.trnas.push_back( population[mom].trnas[it2] ) ;
                    sort( new_ind.trnas.begin(), new_ind.trnas.end() ) ;
                }
                it2 ++ ;
            }
            
            /// at the same place
            else if ( population[dad].trnas[it1].locus == population[mom].trnas[it2].locus ) {
                if ( gsl_ran_bernoulli( rng, 0.5 ) ) {
                    new_ind.trnas.push_back( population[mom].trnas[it2] ) ;
                }
                else {
                    new_ind.trnas.push_back( population[dad].trnas[it1] ) ;
                }
                it1 ++ ;
                it2 ++ ;
            }
            
            /// dad less but neither at end
            else if ( population[dad].trnas[it1].locus < population[mom].trnas[it2].locus ) {
                if ( gsl_ran_bernoulli( rng, 0.5 ) ) {
                    new_ind.trnas.push_back( population[dad].trnas[it1] ) ;
                    sort( new_ind.trnas.begin(), new_ind.trnas.end() ) ;
                }
                it1 ++ ;
            }
            /// mom less but neither at end
            else if ( population[mom].trnas[it2].locus < population[dad].trnas[it1].locus ) {
                if ( gsl_ran_bernoulli( rng, 0.5 ) ) {
                    new_ind.trnas.push_back( population[mom].trnas[it2] ) ;
                    sort( new_ind.trnas.begin(), new_ind.trnas.end() ) ;
                }
                it2 ++ ;
            }
        }
           
        swap( new_population[i], new_ind ) ;
    }
}

#endif
