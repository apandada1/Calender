/* Calender
An application written in C, inspired by Unix "cal".
Copyright (C) 2017  Archisman Panigrahi

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see http://www.gnu.org/licenses/gpl.html.*/
#include <stdio.h>

int leap(int);
int validdate(int,int,int);
int daysgoneby(int);
int doy(int,int,int);
int daysinmonth(int,int);
int cal(int,int);

void main()
{
	int x, y, z;
	printf("Enter the day:  ");
	scanf("%d",&x);
	printf("Enter the month:  ");
	scanf("%d",&y);
	printf("Enter the year:  ");
	scanf("%d",&z);
	printf("\n");	
	if(validdate (x,y,z)==0)
	{
		printf("Invalid Date\n");
		return;
	}
	cal(y,z); 
	printf("\n\n");
}
int leap(int a) /* Checks whether the given year is leap year */
{
	if (a%400==0)
		return 1;
	else if (a%100==0)
		return 0;
	else if (a%4==0)
		return 1;
	else
		return 0;
}
int validdate(int d, int m, int y) /* Checks whether the entered date is valid */
{
	if (y<1800 || m<1 || m>12)
		return 0;
	else if (m==2)
		if(leap(y)==1)
			if (d>29)
				return 0;
			else 
				return 1;
		else
			if (d>28)
				return 0;
			else
				return 1;
	else if (m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12)
		if(d>31)
			return 0;
	else if (m==4 || m==6 || m==9 || m==11)
		if(d>30)
			return 0;
	else
		return 1;
}
int daysgoneby(int y) /* Counts the no of days elapsed since 1800 to the end of the previous year */
{
	int a;
	int b;
	a=y-1800;
	b=365*a+(y-1)/400-1800/400-(a-1)/100+(a-1)/4;
	/*We use (a-1) so that the days of the given year are not counted. 
	In case of division by 400, (y-1) and 1800 are separated (instead of a-1) as in c, 
	2000/400-1800/400=5-4=1, but (2000-1800)/400=0*/
	return b;
}
int doy(int d, int m, int y) /* Counts the days elapsed in the given year, including the given date */
{
	int a;
	if (m==1)
		a=d;
	else if (m==2)
		a=d+31;
	else if (m==3)
		a=d+31+28+leap(y);
	else if (m==4)
		a=d+31+28+31+leap(y);
	else if (m==5)
		a=d+31+28+31+30+leap(y);
	else if (m==6)
		a=d+31+28+31+30+31+leap(y);
	else if (m==7)
		a=d+31+28+31+30+31+30+leap(y);
	else if (m==8)
		a=d+31+28+31+30+31+30+31+leap(y);
	else if (m==9)
		a=d+31+28+31+30+31+30+31+31+leap(y);
	else if (m==10)
		a=d+31+28+31+30+31+30+31+31+30+leap(y);
	else if (m==11)
		a=d+31+28+31+30+31+30+31+31+30+31+leap(y);
	else if (m==12)
		a=d+31+28+31+30+31+30+31+31+30+31+30+leap(y);
	return a;
}
int daysinmonth(int m, int y) /* Returns the total no of days in different months */
{
	if(m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12)
	{
		return 31;
	}
	if(m==2)
	{
		if(leap(y)==1)
		{
			return 29;
		}
		else 
		{
			return 28;
		}
	}
	if(m==4 || m==6 || m==9 || m==11)
	{
		return 30;
	}
}
void printnameofmonth(int m) /* Prints the name of month */
{
	printf("   ");
	if(m==1)
		printf("January"); 
	else if(m==2)
		printf("February"); 
	else if(m==3)
		printf("March"); 
	else if(m==4)
		printf("April"); 
	else if(m==5)
		printf("May"); 
	else if(m==6)
		printf("June"); 
	else if(m==7)
		printf("July"); 
	else if(m==8)
		printf("August"); 
	else if(m==9)
		printf("September"); 
	else if(m==10)
		printf("October");
	else if(m==11)
		printf("November"); 
	else if(m==12)
		printf("December"); 		
}
int cal(int m, int y) /* Prints the calender of the month */
{
	int p;
	int q;
	p=(daysgoneby(y)+doy(1,m,y));
	/* doy(1,m,y) is taken so that the calender counts the weekday of 
	the first date of the month and starts printing from that day */
	q=p%7;
	printnameofmonth(m);
	printf(" %d\n",y); /* THese two line prints the name of the month and year */
	printf("Su Mo Tu We Th Fr Sa\n");
	int i=1;
	int j=0;
	while(j<((2+q)%7)) 
	/*Adds 2 so that there are already two spaces (Under Su and Mo). Since doy(1,1,1800)=1, 
	there will be total 3 spaces, and 1/1/1800 will become wednesday.
	(2+q)%7 is used instead of (2+q), so that if q=5,6, or 7, the first line of calender will
	just under Su Mo ... */
	{
		printf("   ");
		j=j+1;
	}
	while(i<=daysinmonth(m,y))
	{
		if(i<10) /*So that 1 digit and 2 digit dates are alined */
		{
			printf(" ");
		}
		printf("%d ",i);
		i=i+1;
		if((q+2+i)%7==1)
		{
			printf("\n");
		}
	}
}
