#include <iostream>
#include <vector>
#include <string>
#include <cstring>

#include "VectorIO.h"

using namespace std;

void greedy_format(unsigned int l, std::vector<std::string>& v)
{
  std::cout << "Greedy format:" << std::endl;
  unsigned int cost = 0;

  /* TODO: Calculati costul formatarii Greedy si afisati textul formatat
   * folosind aceasta strategie. Afisati cate "l" caractere pe o linie, urmate de
   * un caracter "|" inainte de terminatorul de linie. */

  // stiu ca m-am complicat inutil

  int len=0;
  unsigned int i=0;
  int ans1,ans2=0;
  
  while( i < v.size() )
  {
  	len=v[i].size(),ans1=0;
  	cout << v[i];
  	++i;
  	
  	while( i<v.size() && len+v[i].size()+1 <= l )
  	{
  		cout << " " << v[i];
  		len+=v[i].size()+1; 
  		++i;
  	}
  	
  	while( len < l )
  	{
  		 cout << " ";
  		 ++len, ++ans1;
  	}
  	cout << "|\n";
  	
  	ans2+= ans1*ans1;
  }

  cost = ans2;
  /* Afisam costul. */
  std::cout << "TOTAL COST: " << cost << std::endl;
}

#define NMAX 1024
#define inf 0x3f3f3f3f
int len_sum[NMAX];

// costul pentru asezarea cuvintelor [i,j] pe ultima linie, avand limita de l 
// caractere

int cost( int i, int j, int l )
{
	int ans = l - (j-i) - len_sum[j];
	if( i ) ans += len_sum[i-1];
	
	if( ans < 0 )
		return inf; // daca cuvintele nu incap, returnez infinit
	return ans*ans;
}

int A[NMAX];

void tex_format(unsigned int l, std::vector<std::string>& v)
{
  std::cout << "Tex format:" << std::endl;

  /* TODO: Calculati costul formatarii Tex si afisati textul formatat
   * folosind aceasta strategie. Afisati cate "l" caractere pe o linie, urmate de
   * un caracter "|" inainte de terminatorul de linie. */
 
  // http://en.wikipedia.org/wiki/Word_wrap

  int i,j;
  len_sum[0] = v[0].size();

   /*
	len_sum[i] -> suma lung. primelor i numere
	A[i] 	   -> costul pentru a aseza "frumos" in pagina primele i cuvinte
   */

  for( i=1; i<v.size(); ++i )
	len_sum[i] = len_sum[i-1] + v[i].size();

  for( i=0; i<v.size(); ++i )
  {
	A[i] = cost( 0, i , l ); // incerc sa pun toate cuvintele de la 0 la i, pe ultima linie
	for( j=1; j<=i; ++j )    // micsorez intervalul si incerc acelasi lucru
		A[i] = min( A[i], A[j-1] + cost( j,i, l ) );			
  }
  
  // cum poate fi optimizat usor codul de sus? Hint: --j

  /* Afisam costul total. */
  std::cout << "TOTAL COST: " << A[ v.size()-1 ] << std::endl;
}

int main()
{
  /* Declaram si citim lungimea unei linii si un vector de cuvinte. */
  unsigned int l;
  std::vector<std::string> word;
  std::cin >> l >> word;

  /* Verificam sa nu avem cuvinte mai lungi de o linie. */
  for (unsigned int i = 0; i < word.size(); ++i) {
    if (word[i].length() > l) {
      std::cerr << "Imposibil. Anumite cuvinte sunt mai lungi de o linie!"
          << std::endl;
      return 0;
    }
  }

  /* Afisam impartirea greedy. Se vor afisa L caractere pe o linie, urmate de un
   * caracter pipe ('|') la final. */
  greedy_format(l, word);
  std::cout << std::endl;

  /* Afisam impartirea folosind functia de cost din TeX. Se vor afisa L
   * caractere pe o linie, urmate de un caracter pipe ('|') la final.*/
  tex_format(l, word);

  return 0;
}

