#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define G 6.67384e-11
#define N 10
#define clrscr() printf("\e[1;1H\e[2J");

// coordinates (m)
double p[N][3] = {
	{0, 0, 0},
	{1.49597870700E11, 0, 0},
	{1.49597870700E11, 3.84E8, 0},
	{7.8E11, 0, 0},
	{14.0E11, 0, 0},
	{46.0E11, 0, 0},
	{28.8E11, 0, 0},
	{1.06E11, 0, 0},
	{2.28E11, 0, 0},
	{0.58E11, 0, 0}
};

// velocity (m/s)
double v[N][3] = {
	{0, -16.010, 0}, // -16.010
	{0, 29.7874857E3, 0},
	{-1.0189718E3, 29.7874857E3, 0},
	{0, 13.045155E3, 0},
	{0, 9.7371651E3, 0},
	{0, 5.3717728E3, 0},
	{0, 6.7889140E3, 0},
	{0, 35.386990E3, 0},
	{0, 24.128434E3, 0},
	{0, 47.839051E3, 0}
};

char name[N][255] = {
	"Sun",
	"Earth",
	"Moon",
	"Jupiter",
	"Saturn",
	"Neptune",
	"Uranus",
	"Venus",
	"Mars",
	"Mecury"
};

double m[N] = {
	1.98892E30, // Sun
	5.9742E24, // Earth
	0.0736E24, // Moon
	18.99E26, // Jupiter
	5.6846E26, // Saturn
	1.0243E26, // Neptune
	0.86832E26, // Uranus
	4.8685E24, // Venus
	0.64185E24, //Mars
	0.33302E24, //Mecury
};



// How much precision required for the calculation of the orbits
//  and we will decide this from the initial values 
//  at the very beginning of this program.
//
// The absolute timing will be replaced by the ticks
//  and the ticks will be basically expressed as the divided timings
//  we can calculate how much absolute time (seconds) have passed
//  from the ticks,
//

unsigned short precision[N] = {16, };
unsigned long long tick = 0;

// Grouping is hard, so we won't use it.
// Just order and calculate it tick by tick. and will work
short porder[N];
// double group[N];
// double gp[N][3];
// double gm[N][3];


// We can calculate tick += 2^precision from this realm.
//
// how we calculate the ticks!
//
// for example, it can be expressed like this.
//
// 2^0 = 1 tick = 1 seconds
// 2^4 = 16 tick = 1 seconds
// 2^5 = 32 tick = 1 seconds
// 2^7 = 128 tick = 1 seconds
// 2^8 = 256 tick = 1 seconds
// 2^10 = 1024 tick = 1 seconds
// 2^16 = 65536 tick = 1 seconds
//
// If it is the case, the max precision will be limited.
//  and we already have limited precision 
//  because of the double floating point
// 
// So we should use subtotal 
//  for more the precise calculation.
// 
// We will use 65536 tick per 1 second as the default value.
//  and use unsigned long long, 
//  so max time will be 891 million years,
//  if more, we also can use 

// Max Time Lendered is the case, 
//   and double floating point might not be the problem.
// we will use subtotal for the more precise calculation.

// we can assume 


// All Masses
double M = 0;

double distance(double p1[3], double p2[3])
{
	return sqrt(pow(p2[0]-p1[0],2)+pow(p2[1]-p1[1],2)+pow(p2[2]-p1[2],2));
}

double speed(double v[3])
{
	double o[3]={0,0,0};
	return distance(v,o);
}

void sort_precision()
{
	int i, j, t;
	for (i=1; i<N; i++)
	{
		t = precision[porder[i]];
		j = i-1;
		while( (j >= 0) && (precision[porder[j]] < t) )
		{
			porder[j+1] = porder[j];
			j--;
		}
		porder[j+1] = t;
	}
}

void get_precisionr()
{
	short i, j;
	
	//sort_precision();
}


void centroid(double *center)
{
	int i, n;
		
	for (n=0;n<3;n++)
	{
		center[n] = 0;
		for (i=0; i<N; i++)
		{
			center[n]+=p[i][n]*m[i];
		}
		center[n]/=M;
	}

}

int main()
{
	//subtotal of displacement
	double sd[N]={0,};
	unsigned short calc_n; 
	register double factor;
	register int i, j, c, d;
	double c[3];
	

	M = 0;
	for(i=0;i<N;i++)
	{
		M += m[i];
		porder[i] = i;
	}
	
	//for(long int t=0; t<(long int)86400*32*3652422; t++)
	//{
	while (true)
	{
		get_precision();
		
		for (c=0; c<N; c++)
		{
			//i = porder[c];
			i = c;
			for (j=0; j<N; j++)
			{
				if (i==j) continue;
				factor = G * m[j] / pow(distance(p[i], p[j]),3);

				for (d=0; d<3; d++)
				{
					v[i][d] += (p[j][d]-p[i][d]) * factor / 2^precision[i];
				}
			}
			for (d=0; d<3; d++)
			{
				p[i][d]+=v[i][d] * 0.03125;
			}
		}
		if (!( (t >> 16) % (3600*24)))
		{
			clrscr();
			printf("======================\n");
			printf("* Position / Velocity(km/s)\n");
			centroid(c);
			for(i=0;i<N;i++)
			{
				printf("%s (%E, %E, %E) - (%lf, %lf, %lf)\n",name[i], p[i][0], p[i][1], p[i][2], v[i][0]/1000, v[i][1]/1000, v[i][2]/1000);
			}
			printf("= Center of the mass (%E, %E, %E)\n", c[0], c[1], c[2]);
			printf("Moon from the Earth (%E, %E, %E)\n", p[2][0]-p[1][0], p[2][1]-p[1][1], p[2][2]-p[1][2]);
			printf("Earth from the Jupiter (%E, %E, %E)\n", p[1][0]-p[3][0], p[1][1]-p[3][1], p[1][2]-p[3][2]);
			printf("\n");

			printf("* Speed\n");
			for(i=0;i<N;i++)
			{
				printf("%s : %lf km/s\n", name[i], speed(v[i])/1000);
			}
			printf("\n");


			printf("* Distance\n");
			for (i=0; i<N; i++)
			{
				for (j=i+1; j<4; j++)
				{
					printf("%s-%s : %E km\n", name[i], name[j], distance(p[i],p[j])/1000);
				}
			}
			printf("Center of the mass and Sun : %d km\n", (int)(distance(c,p[0])/1000));

			printf("\n");

			printf("* Mechanical Energy\n");
			double Em[N];
			double Ep[N];
			double Ek[N];
			double Esum = 0;

			for (i=1; i<N; i++)
			{
				Ek[i] = (m[i] * pow(speed(v[i]),2) / 2);
				Ep[i] = -G*m[0]*m[i]/distance(p[0],p[i]);
				Em[i] = Ek[i] + Ep[i];
				Esum += Em[i];
			}
			printf("All : %1.16e\n", Esum);
			printf("Earth + Moon : %E\n", Em[1]+Em[2]);
			printf("Earth + Moon + Jupiter : %E\n", Em[1]+Em[2]+Em[3]);
		}
	}

	return 0;
}
