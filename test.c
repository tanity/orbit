#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define G 6.67384e-11

// coordinates (m)
double p[3][3] = {
	{0.0,0.0,0.0},
	{1.49597870700E11,0.0,0.0},
	{1.49597870700E11,3.840E8,0.0}
};

// velocity (km/h)
double v[3][3] = {
	{0.0,0.0,0.0},
	{0.0,29.76E3,0.0},
	{-1.022E3,29.76E3,0.0}
};

double m[3] = {
	1.98892E30,
	5.9742E24,
	7.36E22
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
		for(i=0; i<3; i++)
		{
			speed = distance(v[i],o);
			for(j=0; j<3; j++)
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
		if(t % 86400 == 0)
			printf("Earth (%E,%E,%E, %lf km/h) - Earth-Moon : %E km\n", 
					p[1][0],p[1][1],p[1][2],
					distance(v[1],o)/1000,
					distance(p[1],p[2])/1000
					);
	}

	return 0;
}
