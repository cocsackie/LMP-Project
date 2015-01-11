#include "makespl.h"
#include "piv_ge_solver.h"

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

/* UWAGA: liczbę używanych f. bazowych można ustawić przez wartość
          zmiennej środowiskowej APPROX_BASE_SIZE
*/

/*
 * Funkcje bazowe: n - liczba funkcji a,b - granice przedzialu aproksymacji i
 * - numer funkcji x - wspolrzedna dla ktorej obliczana jest wartosc funkcji
 */
double fi(int i, double x)
{	
	long double sX = x;
	long double sX2 = sX*sX;
	long double sX3 = sX2*sX;
	long double sX4 = sX3*sX;
	long double sX5 = sX4*sX;
	long double sX6 = sX5*sX;
	long double sX7 = sX6*sX;
	long double sX8 = sX7*sX;
	long double sX9 = sX8*sX;
	long double sX10 = sX9*sX;
	long double sX11 = sX10*sX;

	switch( i )
	{
		case 0:
			return 1;
		case 1:
			return sX;
		case 2:
			return (3*sX2-1)/2;
		case 3:
			return (5*sX3-3*sX)/2;
		case 4:
			return (35*sX4-30*sX2+3)/8;
		case 5:
			return (63*sX5-70*sX3+15*sX)/8;
		case 6:
			return (231*sX6-315*sX4+105*sX2-5)/16;
		case 7:
			return (429*sX7-693*sX5+315*sX3-35*sX)/16;
		case 8:
			return (6435*sX8-12012*sX6+6930*sX4-1260*sX2+35)/128;
		case 9:
			return (12155*sX9-25740*sX7+18018*sX5-4620*sX3+315*sX)/128;
		case 10:
			return (46189*sX10-109395*sX8+90090*sX6-30030*sX4+3465*sX2-63)/256;
		case 11:
			return (88179*sX11-230945*sX9+218790*sX7-90090*sX5+15015*sX3-693*sX)/256;
	}


	return 0;
}

/* Pierwsza pochodna fi */
double dfi(int i, double x)
{
	long double sX = x;
	long double sX2 = sX*sX;
	long double sX3 = sX2*sX;
	long double sX4 = sX3*sX;
	long double sX5 = sX4*sX;
	long double sX6 = sX5*sX;
	long double sX7 = sX6*sX;
	long double sX8 = sX7*sX;
	long double sX9 = sX8*sX;
	long double sX10 = sX9*sX;
	long double sX11 = sX10*sX;

	switch( i )
	{
		case 0:
			return 0;
		case 1:
			return 1;
		case 2:
			return 3*sX;
		case 3:
			return (15*sX2-3)/2;
		case 4:
			return (140*sX3-60*sX)/8;
		case 5:
			return (315*sX4-210*sX2+15)/8;
		case 6:
			return (1386*sX5-1260*sX3+210*sX)/16;
		case 7:
			return (3003*sX6-3465*sX4+945*sX2-35)/16;
		case 8: 
			return (51480*sX7-72072*sX5+27720*sX3-2520*sX)/128;
		case 9:
			return (109395*sX8-180180*sX6+90090*sX4-13860*sX2+315)/128;
		case 10:
			return (461890*sX9-875160*sX7+540540*sX5-120120*sX3+6930*sX)/256;
		case 11:
			return (969969*sX10-2078505*sX8+1531530*sX6-450450*sX4+45045*sX2-693)/256;
	}

	return 0;
}

/* Druga pochodna fi */
double d2fi(int i, double x)
{
	long double sX = x;
	long double sX2 = sX*sX;
	long double sX3 = sX2*sX;
	long double sX4 = sX3*sX;
	long double sX5 = sX4*sX;
	long double sX6 = sX5*sX;
	long double sX7 = sX6*sX;
	long double sX8 = sX7*sX;
	long double sX9 = sX8*sX;

	switch( i )
	{
		case 0:
			return 0;
		case 1:
			return 0;
		case 2:
			return 3;
		case 3:
			return 30*sX/2;
		case 4:
			return (420*sX2-60)/8;
		case 5:
			return (1260*sX3-410*sX)/8;
		case 6:
			return (6930*sX4-3780*sX2+210)/16;
		case 7:
			return (18018*sX5-13860*sX3+1890*sX)/16;
		case 8:
			return (360360*sX6-360360*sX4+83160*sX2-2520)/128;
		case 9:
			return (875160*sX7-1081080*sX5+360360*sX3-27720*sX)/128;
		case 10:
			return (4157010*sX8-6126120*sX6+2702700*sX4-360360*sX2+6930)/256;
		case 11:
			return (9699690*sX9-16628040*sX7+9189180*sX5-1801800*sX3+90090*sX)/256;
	}

	return 0;
}

/* Trzecia pochodna fi */
double d3fi(int i, double x)
{
	long double sX = x;
	long double sX2 = sX*sX;
	long double sX3 = sX2*sX;
	long double sX4 = sX3*sX;
	long double sX5 = sX4*sX;
	long double sX6 = sX5*sX;
	long double sX7 = sX6*sX;
	long double sX8 = sX7*sX;

	switch( i )
	{
		case 0:
			return 0;
		case 1:
			return 0;
		case 2:
			return 0;
		case 3:
			return 15;
		case 4:
			return 105*sX;
		case 5:
			return (3780*sX2-410)/8;
		case 6:
			return (27720*sX3-7560*sX)/16;
		case 7:
			return (90090*sX4-41580*sX2+1890)/16;
		case 8:
			return (2162160*sX5-1441440*sX3+166320*sX)/128;
		case 9:
			return (6126120*sX6-5405400*sX4+1081080*sX2-27720)/128;
		case 10:
			return (33256080*sX7-36756720*sX5+1081080*sX3-720720*sX)/256;
		case 11:
			return (87297210*sX8-116396280*sX6+45945900*sX4-5405400*sX2+90090)/256;
	}

	return 0;
}

void make_spl(points_t * pts, spline_t * spl)
{

	matrix_t       *eqs= NULL;
	double         *x = pts->x;
	double         *y = pts->y;
	double		a = x[0];
	double		b = x[pts->n - 1];
	int		i, j, k;
	int		nb = pts->n - 3 > 12 ? 12 : pts->n - 3;
	char *nbEnv= getenv( "APPROX_BASE_SIZE" );

	if( nbEnv != NULL && atoi( nbEnv ) > 0 )
		nb = atoi( nbEnv );

	eqs = make_matrix(nb, nb + 1);

	for (j = 0; j < nb; j++) {
		for (i = 0; i < nb; i++)
			for (k = 0; k < pts->n; k++)
				add_to_entry_matrix(eqs, j, i, fi(i, x[k]) * fi(j, x[k]));

		for (k = 0; k < pts->n; k++)
			add_to_entry_matrix(eqs, j, nb, y[k] * fi(j, x[k]));
	}


	if (piv_ge_solver(eqs)) {
		spl->n = 0;
		return;
	}

	if (alloc_spl(spl, pts->n) == 0) {
		for (i = 0; i < spl->n; i++) {
			double xx = spl->x[i] = a + i*(b-a)/(spl->n-1);
			xx+= 10.0*DBL_EPSILON;  // zabezpieczenie przed ulokowaniem punktu w poprzednim przedziale
			spl->f[i] = 0;
			spl->f1[i] = 0;
			spl->f2[i] = 0;
			spl->f3[i] = 0;
			for (k = 0; k < nb; k++) {
				double		ck = get_entry_matrix(eqs, k, nb);
				spl->f[i]  += ck * fi  (k, xx);
				spl->f1[i] += ck * dfi (k, xx);
				spl->f2[i] += ck * d2fi(k, xx);
				spl->f3[i] += ck * d3fi(k, xx);
			}
		}
	}
}
