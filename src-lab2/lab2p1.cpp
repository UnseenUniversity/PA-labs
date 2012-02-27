#include <iostream>
#include <vector>
#include <algorithm>

#include "VectorIO.h"
#include "PairIO.h"

using namespace std;

/* Un material este o pereche (greutate, valoare). */
typedef pair<int, double> Material;

#define for_each(i,size) for( int i=0,sz=size; i<sz; ++i )

inline bool cmp( const Material& A, const Material& B )
{
	return (A.first/A.second)  < (B.first/B.second) ;
}

double val_max(int t, vector<Material>& v)
{

  sort( v.begin(), v.end(), cmp );  
  
  double ans=0;
  for_each( i, v.size() )
  {
  	if( !t ) break;
  	
  	int cant = min( t, v[i].first );
  	t   -= cant;
  	ans += ( cant * (v[i].second/v[i].first) );	
  }
  
  return ans;
}

int main()
{
  /* Declaram capacitatea camionului si un vector care sa retina tipurile
   * de material sub forma de perechi (greuate, valoare) si citim datele
   * de intrare.
   */
  int t;
  vector<Material> v;
  cin >> t >> v;

  /* Afisam valoarea maxima transportabila de catre camion. */
  cout << "Valoarea maxima a unui transport: "
      << val_max(t, v) << endl;

  return 0;
}

