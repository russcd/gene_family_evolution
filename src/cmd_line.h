#ifndef __CMD_LINE_H
#define __CMD_LINE_H

/// command line information and global parameters
class cmd_line {
public:
    
    /// population size, constant for now
    int n ;
    
    /// number of generations
    int generations ;
    
    /// number of genes at start
    int start_count ;
    
    /// amount of function for any fitness
    double min_function ;
    
    /// mutation rates
    double germline_rate ;
    double somatic_rate ;
    
    /// duplicate and deletion rates
    double deletion_rate ;
    double duplication_rate ;
    
    /// rng seed
    int seed ;
    
    /// read relevant information
    void read_cmd_line ( int argc, char *argv[] ) ;
    
    /// variable mutation/transcription rates
    /// for now, we'll assume these are correlated 
    bool variable ;
    
} ;

void cmd_line::read_cmd_line ( int argc, char *argv[] ) {
    
    /// set parameter defaults
    n = 1000 ;
    generations = 100000 ;
    germline_rate = 1e-5 ;
    somatic_rate = 1e-2 ;
    deletion_rate = 1e-5 ;
    duplication_rate = 1e-5 ;
    seed = time(NULL) ;
    min_function = 1 ;
    start_count = 1 ; 
    variable = false ;
    
    /// accept command line parameters
    for (int i=1; i<argc; i++) {

        if ( strcmp(argv[i],"-n") == 0 ) {
            n = atoi(argv[++i]) ;
        }
        if ( strcmp(argv[i],"-g") == 0 ) {
            generations = atoi(argv[++i]) ;
        }
        if ( strcmp(argv[i],"--ug") == 0 ) {
            germline_rate = atof(argv[++i]) ;
        }
        if ( strcmp(argv[i],"--us") == 0 ) {
            somatic_rate = atof(argv[++i]) ;
        }
        // make these separate options later
        if ( strcmp(argv[i],"-d") == 0 ) {
            duplication_rate = atof(argv[++i]) ;
            deletion_rate = duplication_rate ;
        }
        if ( strcmp(argv[i],"--del") == 0 ) { 
            deletion_rate = atof(argv[++i]) ;
        }
        if ( strcmp(argv[i],"--dup") == 0 ) { 
            duplication_rate = atof(argv[++i]) ;
        }
        if ( strcmp(argv[i],"-s") == 0 ) {
            seed = atoi(argv[++i]) ;
        }
        if ( strcmp(argv[i],"--start") == 0 ) {
            start_count = atoi(argv[++i]) ;
        }
        if ( strcmp(argv[i],"--min-function") == 0 ) {
            min_function = atoi(argv[++i]) ;
        }
        if ( strcmp(argv[i],"-v") == 0 ) {
            variable = true ;
        }
    }
    
    return ;
}


#endif
