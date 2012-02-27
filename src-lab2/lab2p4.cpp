#include <iostream>
#include <vector>
#include <algorithm>

#include "VectorIO.h"
#include "PairIO.h"

#define UNDEF -1
using namespace std;

/* Un material este o pereche (greutate, valoare). */
typedef pair<int, int> Mobila;

int val_max(int t, vector<Mobila>& v)
{
  vector < int > viz( t, 0 );
  int ans=0;
  
  for( int i=0; i<v.size(); ++i )
  {
	int weight = v[i].first;
	int value  = v[i].second;

	for( int j=t; j-weight>=0; --j )
	{
		if( !(j-weight) || viz[j-weight] )
		{
			viz[j]=max( viz[j], viz[j-weight]+value );
			ans   =max( ans, viz[j] );
		}
	}
   }
  
  return ans;
}

int main()
{
  /* Declaram capacitatea camionului si un vector care sa retina tipurile de
   * mobila sub forma de perechi (greutate, valoare) si citim datele de intrare.
   */
  int t;
  vector<Mobila> v;
  cin >> t >> v;

  /* Afisam valoarea maxima transportabila de catre camion. */
  cout << "Valoarea maxima a mobilierului transportabil: "
            << val_max(t, v) << std::endl;

  return 0;
}

