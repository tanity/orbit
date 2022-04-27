#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define G 6.67384e-11
#define N 4
// coordinates (m)
double p[N][3] = {
	{0, 0, 0},
	{1.49597870700E11, 0, 0},
	{1.49597870700E11, 3.840E8, 0},
	{2.2425E11, 0, 5.0E8}
};

// velocity (m/s)
double v[N][3] = {
	{0, 0, 0},
	{0, 29.76E3, 0},
	{-1.022E3, 29.76E3, 0},
	{0, 24.0E3, 0}
};

double m[N] = {
	1.98892E30,
	5.9742E24,
	7.36E22,
	1.898E27
};


double distance(double p1[3], double p2[3])
{
	return sqrt(pow(p2[0]-p1[0],2)+pow(p2[1]-p1[1],2)+pow(p2[2]-p1[2],2));
}


int main()
{
	register double factor;
	register double speed;
	register int i,j;
	double o[3]={0,0,0};

	for(long int t=0; t<(long int)86400*(long int)3652422; t++)
	{
		for(i=0; i<N; i++)
		{
			speed = distance(v[i],o);
			for(j=0; j<N; j++)
			{
				if (i==j) continue;
				factor = G * m[j] / pow(distance(p[i],p[j]),3);

				for(int n=0;n<3;n++)
				{
					//printf("[x%d]speed: %E (p[%d]-%E p[%d]-%E) v[%d][%d] - %E (%E)\n",n,speed,i,p[i][n],j,p[j][n],i,n,v[i][n],(p[i][n]-p[j][n])*factor);
					v[i][n] += (p[j][n]-p[i][n]) * factor;
				}
			}
			for(int n=0;n<3;n++)
			{                                                                                   
				p[i][n]+=v[i][n];
			}
		}
		if (!(t % 86400))
		{
			printf("======================\n* Position \nEarth (%E, %E, %E)\n\n* Velocity \nSun : %lf km/s \nEarth : %lf km/s \nMoon : %lf km/s \nJupiter : %lf km/s \n\n* Distance \nSun-Earth : %E km\nSun-Moon : %E\nSun-Jupiter : %E\nEarth-Moon : %E km\nEarth-Jupiter : %E km\n", 
					p[1][0],p[1][1],p[1][2],
					distance(v[0],o)/1000,
					distance(v[1],o)/1000,
					distance(v[2],o)/1000,
					distance(v[3],o)/1000,
					distance(p[0],p[1])/1000,
					distance(p[0],p[2])/1000,
					distance(p[0],p[3])/1000,
					distance(p[1],p[2])/1000,
					distance(p[1],p[3])/1000
					);
		}
	}

	return 0;
}
