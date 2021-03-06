#ifndef ENTROPY_H
#define ENTROPY_H

#include <map>
#include <memory>
#include <vector>
#include <string>
#include <utility>

class Entropy
{
public:
    Entropy();
    Entropy( int alphabet_size );
    virtual ~Entropy(){}

    double getCoeff( int N ) const;// compute g(N). 
    // Without the sample splitting required by theory
    double estimate() const; // Hist must be given
    double estimate_non_zero() const; // Only use fingerprint f_j for j>=1. In other words, g(0)=0.
    double estimate_plug() const;
    double estimate_Miller_Madow() const;

    void setAlphabetSize( int alphabet_size ) { k = alphabet_size; }
    void setThreshold( double N_threshold ){ N_thr = N_threshold; }
    void setInterval( double rEnd ){ Ratio = rEnd; }
    void setDegree( int deg ); // also update the coefficients array
    // set fingerprint, also update sample size
    void setFin( std::shared_ptr< const std::map<int, int> > fin ); 
    void setFin( const std::string filename );
    void setFin( const std::vector<int> &freq, const std::vector<int> &cnt );
    // set fingerprint through histogram, also update sample size
    void setHist( const std::vector<int> &hist );
    void setHist( const std::string filename );
    
    int getAlphabetSize() const{ return k; }
    int getSampleSize() const{ return n; }
    int getDegree() const{ return L; }
    double getThreshold() const{ return N_thr; }
    double getInterval() const{ return Ratio; }
private:
    double N_thr; // =c2*log(k). Plug-in threshold
    double Ratio; // =c1*log(k). Approximation over [0,c1*log(k)/n]
    int L; // =c0*log(k). Degree of polynomial
    int n; // Sample size
    int k; // Alphabet size
    std::vector< std::pair<int, int> > fin; // Fingerprint(profile)
    std::vector<double> a; // polynomial coefficients
	
	
};


#endif


