#include <stdio.h>

struct Saros{
    int beginMonth,beginYear,beginDay,daysPerPeriod;
};
struct userRequest{
    int month, day,year,area;
};


long int getDays(int days, int month, int year,struct Saros saros136)
{
    long int NumberOfDays=0;
    int regularYearDays=365;
    int biYearDays=366;
    int daysPerMonth[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    for(int i=saros136.beginYear;i<year;i++)
    {
        if( (i % 4 == 0 && i % 100 != 0) || i % 400 == 0)
        {
            NumberOfDays+=biYearDays;
        }
        else NumberOfDays+=regularYearDays;
    }
    for(int i=1;i<month;i++)
    {
        if(month==2 && ( (i % 4 == 0 && i % 100 != 0) || i % 400 == 0 ) )
        {
            NumberOfDays+=29;
        }
        else NumberOfDays+=daysPerMonth[i];
    }
    return NumberOfDays+days;
}


int willHaveEclipse(int days, struct Saros saros136)
{
    float division=(days+0.0)/(saros136.daysPerPeriod+0.0);
    int d=division;
    int cicles= days/saros136.daysPerPeriod;
    int area=1;
    float mod=division-d;
    if(mod>=0.0208 && mod<=0.022)
    {
        switch(cicles%3)
        {
            case 0: area=3;
            break;
            case 1: area=2;
            break;
            case 2: area=1;
            break;
        }
        return area;
    }
    else{
       return 0;
    }
}


int main()
{
    struct Saros saros136;
    long int days;

    saros136.beginDay=18;
    saros136.beginMonth=5;
    saros136.beginYear=1901;
    saros136.daysPerPeriod=6585;

    struct userRequest request;

    printf("Calculadora de eclipses\n");
    printf("Ingrese la fecha a calcular en formato DD/MM/AAAA separado por espacios: ");
    scanf("%d %d %d",&request.day,&request.month,&request.year);
    printf("\t--Areas del Saros --136\n");
    printf("1.-America  2.-Europa,Africa  3.-Asia,Oceania\n\n");
    printf("Ingrese el area  en que se encuentra: ");
    scanf("%d",&request.area);

    days= getDays(request.day,request.month,request.year,saros136);
    if(willHaveEclipse(days,saros136))
    {
        if(willHaveEclipse(days,saros136)==request.area)
        {
            printf("Habra un eclipse al menos en ese mes en tu area\n");
        }
        else printf("No habra un eclipse en tu area pero si en el area %d", willHaveEclipse(days,saros136));
    }
    else printf("No habra un eclipse en el mes de esa fecha\n");
    return 0;
}

