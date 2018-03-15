#ifndef __FITNESS_H
#define __FITNESS_H

/// compute fitness
void compute_fitness( double fitness[], vector<individual> &population, cmd_line &options ) {

    for ( int i = 0 ; i < population.size() ; i ++ ) {
        
        double total_function = 0 ;
        
        for ( int g = 0 ; g < population[i].trnas.size() ; g ++ ) {
            total_function += population[i].trnas[g].function * population[i].trnas[g].knockout ;
        }
                
        /// simple fitness function for now
        if ( total_function >= 0.9999 ) {
            fitness[ i ] = 1 ;
        }
        else {
            fitness[ i ] = 0 ;
        }
    }
}

#endif
