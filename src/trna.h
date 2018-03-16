#ifndef __TRNA_H
#define __TRNA_H

class gene {
public:

    /// position of the tRNA
    float locus ;
    
    /// function
    float function ;
    
    /// u rates per locus
    float somatic ;
    float germline ;
    
    // sort function
    bool operator <(const gene &g1 ) {
        return g1.locus > locus ;
    }

} ;

#endif
