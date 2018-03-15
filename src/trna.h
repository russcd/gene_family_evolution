#ifndef __TRNA_H
#define __TRNA_H

class gene {
public:

    /// position of the tRNA
    double locus ;
    
    /// function
    double function ;
    
    /// u rates per locus
    double somatic ;
    double germline ; 
    
    /// somatic knockouts
    int knockout ;
    
    // sort function
    bool operator <(const gene &g1 ) {
        return g1.locus > locus ;
    }

} ;

#endif
