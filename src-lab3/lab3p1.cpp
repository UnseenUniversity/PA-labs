#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "BooleanExpression.h"

#define NMAX 1024

int A[NMAX][NMAX][2];

using namespace std;

int count_modes(const std::vector<BooleanExpression::Lexem>& expr)
{
	  /* TODO: Numarati modurile in care se pot pune paranteze paranteze in
	   * expresie astfel incat sa se obtina rezultatul "true".
	   *
	   * OBS: Este obligatoriu sa puneti in expresie un numar de paranteze egal
	   * cu numarul de operatori prezenti (adica parantezarea sa fie completa).
	   *
	   * OBS: Asa cum scrie si in documentatie, Lexem este un tip de enumerare ce
	   * poate avea valorile: 
	   *
	   * BooleanExpression::True, 
	   * BooleanExpression::False, 
	   * BooleanExpression::Or, 
	   * BooleanExpression::Xor, 
	   * BooleanExpression::And 
	   *
	   * (sunt constante numerice, valoare reala nu este importanta).
	   */

	/*
	   A[i][j][0] - nr de modalitati de parantezare pentru termenii din 
	 		intervalul [ i,j ], astfel incat rezultatul sa fie 0

	   A[i][j][1] - acelasi lucru, astfel incat rez. sa fie 1
	
 	   op  -> un vector unde retin operatorii ( and,or,not,xor ) 
 	          in ordine din expresia
	   val -> retin valorile de adevar din expresia ( true, false )
	
	*/
	
	  vector< int > op,val;
	  

	  for( int i=0; i<expr.size(); ++i )
	  {
		if( !(i%2==0) )
			op.push_back( expr[i] );
		else
			val.push_back( expr[i] ); 
	  }

	  int n=val.size();
	  int l,i,j,k;

 	// initializez dinamica
 	// A[i][i][1] = 1 daca valoarea i din expresie e true
 	// altfel A[i][i][0] = 1
 	
 	// val[i] = 0 pentru true si 1 pentru false ( am pierdut 30 de min sa
 	// descopar asta la lab -> do use BooleanExpression::variable !

	  for( int i=0; i<n; ++i )
		A[i][i][ 1-val[i] ] = 1; 
	
	  for( l=1; l<n; ++l )	// aleg o dimensiune interval
		for( i=0; i+l<n; ++i )	// analizez intervalul i,i+l
		{
			int j = i+l;
			A[i][j][0] = A[i][j][1] = 0;
			for( k=i; k<j; ++k ) // analizez toate posibilitatile de
			{	             // parantezare din interval

				switch( op[k] )
				{				
					case BooleanExpression::Or: 
						A[i][j][0] += A[i][k][0]*A[k+1][j][0];
						A[i][j][1] += A[i][k][1]*A[k+1][j][0] + 
							      A[i][k][0]*A[k+1][j][1] +
							      A[i][k][1]*A[k+1][j][1]; // |
						break;	
		
					case BooleanExpression::And:	
						A[i][j][0] += A[i][k][1]*A[k+1][j][0] +
							      A[i][k][0]*A[k+1][j][1] +
							      A[i][k][0]*A[k+1][j][0];				
						A[i][j][1] += A[i][k][1]*A[k+1][j][1]; // & 
						break;
					
					case BooleanExpression::Xor:
						A[i][j][0] += A[i][k][0]*A[k+1][j][0] +
							      A[i][k][1]*A[k+1][j][1];
						A[i][j][1] += A[i][k][1]*A[k+1][j][0] +
							      A[i][k][0]*A[k+1][j][1];	// ^
						break;				
				}
			}
		}
		
         return A[0][n-1][1]; // nr de modalitati de parantezare pentru a obtine
         		      // true pe intregul interval [ 0 n-1 ]
}

int main()
{
  /* Citim si interpretam o expresie de la tastatura */
  BooleanExpression booleanExpression;
  std::cin >> booleanExpression;

  /* Daca este corecta gramatical, afisam rezultatul */
  if (booleanExpression.is_valid()){
    std::cout << "Numarul de moduri in care se poate obtine rezultatul "
        << "\"true\" este: \n\t"
        << count_modes(booleanExpression.to_vector()) << "\n";
  }

  return 0;
}

