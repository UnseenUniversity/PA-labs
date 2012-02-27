#include <iostream>
#include <vector>

#define CEIL(a, b) ((a) / (b) + ((a) % (b) ? 1 : 0))
using namespace std;

/* Modelam o fractie ca fiind o pereche (numarator, numitor). */
typedef pair<long long, long long> Fractie;

long long gcd( long long x, long long y )
{
	if( !y ) return x;
	return gcd( y, x%y );
}


vector<Fractie> descompunere_fractii_egiptene(long long x, long long y)
{
  vector<Fractie> v;
   
  int T=0;
  while( x )
  {
  	if( x == 1 )
  	{
  		v.push_back( Fractie(1,y) );
  		break;
  	}
  	
  	v.push_back( Fractie(1, CEIL(y,x) ) );
	
	long long x1=x,y1=y;
	x= x1 - y1 % x1;
	y= y1*( CEIL(y1,x1) );
	
	long long gcd_ = gcd( x,y );
	x/=gcd_;
	y/=gcd_;
  }
 
  return v;
}

int main()
{
  /* Citim x si y. */
  long long x, y;
  std::cin >> x >> y;

  /* Calculam descompunerea in fractii egiptene. */
  std::vector<Fractie> v;
  v = descompunere_fractii_egiptene(x, y);

  /* Si o afisam. */
  std::cout << x << "/" << y << " = ";
  for (unsigned int i = 0; i < v.size(); ++i) {
    std::cout << (i > 0 ? " + " : "") << v[i].first << "/" << v[i].second;
  }
  std::cout << std::endl;

  return 0;
}

