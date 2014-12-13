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
double fi(double a, double b, int n, int i, double x)
{	
	long double sX = x;
	long double sX2 = sX*sX;
	long double sX4 = sX2*sX2;
	long double sX8 = sX4*sX4;
	
	switch( i )
	{
		case 0:
			return 1;
		case 1:
			return sX;
		case 2:
			return (3*sX2-1)/2;
		case 3:
			return (5*sX2*sX-3*sX)/2;
		case 4:
			return (35*sX4-30*sX2+3)/8;
		case 5:
			return (63*sX4*sX-70*sX2*sX+15*sX)/8;
		case 6:
			return (231*sX4*sX2-315*sX4+105*sX2-5)/16;
		case 7:
			return (429*sX4*sX2*sX-693*sX4*sX+315*sX2*sX-35*sX)/16;
		case 8:
			return (6435*sX8-12012*sX4*sX2+6930*sX4-1260*sX2+35)/128;
		case 9:
			return (12155*sX8*sX-25740*sX4*sX2*sX+18018*sX4*sX-4620*sX2*sX+315*sX)/128;
		case 10:
			return (46189*sX8*sX2-109395*sX8+90090*sX4*sX2-30030*sX4+3465*sX2-63)/256;
		case 11:
			return (88179*sX8*sX2*sX-230945*sX8*sX+218790*sX4*sX2*sX-90090*sX4*sX+15015*sX2*sX-693*sX)/256;
	}


	return 0;
}

/* Pierwsza pochodna fi */
double
dfi(double a, double b, int n, int i, double x)
{
	long double sX = x;
	long double sX2 = sX*sX;
	long double sX4 = sX2*sX2;
	long double sX8 = sX4*sX4;

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
			return (140*sX2*sX-60*sX)/8;
		case 5:
			return (315*sX4-210*sX2+15)/8;
		case 6:
			return (1386*sX4*sX-1260*sX2*sX+210*sX)/16;
		case 7:
			return (3003*sX4*sX2-3465*sX4+945*sX2-35)/16;
		case 8: 
			return (51480*sX4*sX2*sX-72072*sX4*sX+27720*sX2*sX-2520)/128;
		case 9:
			return (109395*sX8-180180*sX4*sX2+90090*sX4-13860*sX2+315)/128;
		case 10:
			return (461890*sX8*sX-875160*sX4*sX2*sX+540540*sX4*sX-120120*sX2*sX+6930*sX)/256;
		case 11:
			return (969969*sX8*sX2-2078505*sX8+901530*sX4*sX2-450450*sX4+45045*sX2-693)/256;
	}

	return 0;
}

/* Druga pochodna fi */
double
d2fi(double a, double b, int n, int i, double x)
{
	long double sX = x;
	long double sX2 = sX*sX;
	long double sX4 = sX2*sX2;
	long double sX8 = sX4*sX4;

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
			return (1260*sX2*sX-410*sX)/8;
		case 6:
			return (6930*sX4-3780*sX2+210)/16;
		case 7:
			return (18018*sX4*sX-13860*sX2*sX+1890*sX)/16;
		case 8:
			return (360360*sX4*sX2-360360*sX4+83160*sX2)/128;
		case 9:
			return (875160*sX4*sX2*sX-1081080*sX4*sX+360360*sX2*sX-27720)/128;
		case 10:
			return (4157010*sX8-6126120*sX4*sX2+2702700*sX4-360360*sX2+6930)/256;
		case 11:
			return (9699690*sX8*sX-16628040*sX4*sX2*sX+5409180*sX4*sX-1801800*sX2*sX+90090*sX)/256;
	}

	return 0;
}

/* Trzecia pochodna fi */
double
d3fi(double a, double b, int n, int i, double x)
{
	long double sX = x;
	long double sX2 = sX*sX;
	long double sX4 = sX2*sX2;
	long double sX8 = sX4*sX4;

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
			return (27720*sX2*sX-7560)/16;
		case 7:
			return (90090*sX4-41580*sX2+1890)/16;
		case 8:
			return (2162160*sX4*sX-1441440*sX2*sX+166320*sX)/128;
		case 9:
			return (6126120*sX4*sX2-5405400*sX4+1081080*sX2*sX-720720*sX)/128;
		case 10:
			return (33256080*sX4*sX2*sX-36756720*sX4*sX+1081080*sX2*sX-720720*sX)/256;
		case 11:
			return (87297210*sX8-116396280*sX4*sX2+27045900*sX4-5405400*sX2+90090)/256;
	}

	return 0;
}
/* Pomocnicza f. do rysowania bazy */
double
xfi(double a, double b, int n, int i, FILE *out)
{
	double		h = (b - a) / (n - 1);
	double		h3 = h * h * h;
	int		hi         [5] = {i - 2, i - 1, i, i + 1, i + 2};
	double		hx      [5];
	int		j;

	for (j = 0; j < 5; j++)
		hx[j] = a + h * hi[j];

	fprintf( out, "# nb=%d, i=%d: hi=[", n, i );
	for( j= 0; j < 5; j++ )
		fprintf( out, " %d", hi[j] );
	fprintf( out, "] hx=[" );
	for( j= 0; j < 5; j++ )
		fprintf( out, " %g", hx[j] );
	fprintf( out, "]\n" );
}

void
make_spl(points_t * pts, spline_t * spl)
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

#ifdef DEBUG
#define TESTBASE 500
	{
		FILE           *tst = fopen("debug_base_plot.txt", "w");
		double		dx = (b - a) / (TESTBASE - 1);
		for( j= 0; j < nb; j++ )
			xfi( a, b, nb, j, tst );
		for (i = 0; i < TESTBASE; i++) {
			fprintf(tst, "%g", a + i * dx);
			for (j = 0; j < nb; j++) {
				fprintf(tst, " %g", fi  (a, b, nb, j, a + i * dx));
				fprintf(tst, " %g", dfi (a, b, nb, j, a + i * dx));
				fprintf(tst, " %g", d2fi(a, b, nb, j, a + i * dx));
				fprintf(tst, " %g", d3fi(a, b, nb, j, a + i * dx));
			}
			fprintf(tst, "\n");
		}
		fclose(tst);
	}
#endif

	for (j = 0; j < nb; j++) {
		for (i = 0; i < nb; i++)
			for (k = 0; k < pts->n; k++)
				add_to_entry_matrix(eqs, j, i, fi(a, b, nb, i, x[k]) * fi(a, b, nb, j, x[k]));

		for (k = 0; k < pts->n; k++)
			add_to_entry_matrix(eqs, j, nb, y[k] * fi(a, b, nb, j, x[k]));
	}

#ifdef DEBUG
	write_matrix(eqs, stdout);
#endif

	if (piv_ge_solver(eqs)) {
		spl->n = 0;
		return;
	}
#ifdef DEBUG
	write_matrix(eqs, stdout);
#endif

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
				spl->f[i]  += ck * fi  (a, b, nb, k, xx);
				spl->f1[i] += ck * dfi (a, b, nb, k, xx);
				spl->f2[i] += ck * d2fi(a, b, nb, k, xx);
				spl->f3[i] += ck * d3fi(a, b, nb, k, xx);
			}
		}
	}

#ifdef DEBUG
	{
		FILE           *tst = fopen("debug_spline_plot.txt", "w");
		double		dx = (b - a) / (TESTBASE - 1);
		for (i = 0; i < TESTBASE; i++) {
			double yi= 0;
			double dyi= 0;
			double d2yi= 0;
			double d3yi= 0;
			double xi= a + i * dx;
			for( k= 0; k < nb; k++ ) {
							yi += get_entry_matrix(eqs, k, nb) * fi(a, b, nb, k, xi);
							dyi += get_entry_matrix(eqs, k, nb) * dfi(a, b, nb, k, xi);
							d2yi += get_entry_matrix(eqs, k, nb) * d2fi(a, b, nb, k, xi);
							d3yi += get_entry_matrix(eqs, k, nb) * d3fi(a, b, nb, k, xi);
			}
			fprintf(tst, "%g %g %g %g %g\n", xi, yi, dyi, d2yi, d3yi );
		}
		fclose(tst);
	}
#endif

}
