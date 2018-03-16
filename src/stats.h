#ifndef __STATS_H
#define __STATS_H

void print_stats ( double fitness[], const vector<individual> &population, int g ) {
    
    float trna_count = 0 ;
    float trna_pseudogenes = 0 ;
    float mean_fitness = 0 ;
    
    map<float,float> loci_counts ;
    
    for ( int i = 0 ; i < population.size() ; i ++ ) {
        
        mean_fitness += fitness[i] ;
        
        for ( int g = 0 ; g < population[i].trnas.size() ; g ++ ) {
            if ( population[i].trnas[g].function > 0 ) {
                trna_count ++ ;
                loci_counts[population[i].trnas[g].locus] += 1 ;
            }
            else {
                trna_pseudogenes ++ ;
            }
        }
    }
    
    cout << g << "\t" ;
    cout << trna_count/population.size() << "\t" ;
    cout << trna_pseudogenes/population.size() << "\t" ;
    cout << mean_fitness/population.size() << "\t" ;
    cout << loci_counts.size() ;
    
    for ( map<float,float>::iterator it = loci_counts.begin() ; it != loci_counts.end() ; ++it ) {
        cout << "\t" << it->first << "\t" << it->second/population.size() ;
    }
    cout << endl ;
}

#endif
