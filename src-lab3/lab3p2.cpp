#include <iostream>
#include <vector>
#include <cstring>

#include "VectorIO.h"
#include "PairIO.h"

/* Vom considera o matrice ca o pereche de intregi (nr_linii, nr_coloane). */
typedef std::pair<int, int> Matrice;

#define NMAX 1024
#define inf 0x3f3f3f
int A[NMAX][NMAX];

using namespace std;

int min_multiplications(std::vector<Matrice>& v)
{
  /* Tiparim efectiv lantul parantezat si intoarcem numarul minim de operatii de
   * inmultire elementare. */
   
   // A[i][j] - numarul minim de parantezari pentru a inmulti matricile din 
   //	        intervalul [ i,j ]
   
   int n = v.size(),i,j,k;
   for( i=0; i<n; ++i )
   	A[i][i]=0;
   
   for( k=1; k<n; ++k ) // fixez dim. intervalului analizat
   {
   	for( i=0; i+k<n; ++i ) // incerc sa minimizez costul pentru intervalul [i, i+k]
   	{
   		int l = i+k;
   		A[i][l]=inf;
   		
   		for( j=i; j<l; ++j )
   		{
   			int ans = A[i][j] + A[j+1][l] + v[i].first * v[j].second * v[l].second;
   			A[i][l] = min( A[i][l], ans );
   		}	
   	 }
   }
   
  return A[0][n-1];
}

int main()
{
  /* Declaram si citim un vector de matrice de la consola. */
  std::vector<Matrice> v;
  std::cin >> v;

  /* Verificam intai ca lantul de matrice chiar se poate inmulti. */
  for (unsigned int i = 0; i < v.size() - 1; ++i) {
    if (v[i].second != v[i + 1].first) {
      std::cerr << "Fail! Nu se pot inmulti matricele " << i << " si "
          << (i + 1) << " de dimensiuni: " << v[i] << ", respectiv "
          << v[i + 1] << std::endl;
      return 0;
    }
  }

  /* Afisam numarul minim de operatii. */
  std::cout << "Numarul minim de operatii de inmultire elementare este: "
      << min_multiplications(v) << std::endl;

  return 0;
}

