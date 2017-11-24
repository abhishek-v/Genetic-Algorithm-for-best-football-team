#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<cstdio>
#define CROSSOVER_RATE 0.7
#define MUTATION_RATE 0.01
#define MAX_GENERATIONS 1000

#define RANDOM_NUM ((float)rand()/(RAND_MAX+1))
using namespace std;
int p,t;
struct individual
{
	float fitness;
	int rating[100];
	string players[100];
	individual(): fitness(0.0){};
};
//---------------------FUNCTION PROTOTYPE DECLARATIONS--------------------------//
int assignfitness(string);
individual roulettewheel(float,individual[],int);
void crossover(individual,individual,individual &);
//void findOptimalIndividual(individual [],int);
void find_best_team(individual[]);
//-----------------------------------------------------------------------------//

int main()
{
	individual teams[1000];
	unsigned seed = time(0);
	srand(seed);
	freopen("players.txt","r",stdin);
	//freopen("debug.txt","w",stdout);
	//cout<<"Enter number of number of teams and positions";
	cin>>t>>p;
	for(int i=0;i<t;i++)
    {
    	for(int j=0;j<p;j++)
    	{
    		//cout<<"Enter rating of position "<<j+1;
    		cin>>teams[i].rating[j];
    		cin>>teams[i].players[j];
    	}
    }
    int no_of_generations=0;
    while(no_of_generations<=MAX_GENERATIONS)
    {
    	cout<<"Generation "<<no_of_generations;
    	//assign fitness to population
    	float totalfitness=0;
    	for(int i=0;i<t;i++)
    	{

    		teams[i].fitness=0;
    		//second loop assigns fitness score to one individual in the population
    		for(int j=0;j<p;j++)
    		{
    			teams[i].fitness+=teams[i].rating[j];
		    }
		    teams[i].fitness/=p;
		    totalfitness+=teams[i].fitness;
		    //cout<<teams[i].fitness<<endl;
       	}
       	int pop_new=0;
       	individual parent1,parent2;
       	individual offspring[100];
       	//crossover
       	int i=0;
       	while(pop_new<t)
       	{
       		parent1=roulettewheel(totalfitness,teams,t);
       		parent2=roulettewheel(totalfitness,teams,t);
       		if (RANDOM_NUM < CROSSOVER_RATE)
             {
			 crossover(parent1,parent2,offspring[i]);
			 i++;
		     }
		     else
		     {
		     	offspring[i]=parent1;
		     	offspring[i+1]=parent2;
		     	i=i+2;
		     }
		     pop_new=i;
		}
		for(int i=0;i<pop_new;i++)
	    {
	    	teams[i]=offspring[i];
	    	teams[i].fitness=0;
	    }
	    t=pop_new;
	    if(no_of_generations==MAX_GENERATIONS)
	    {
	       break;
		}
       	no_of_generations++;
       	cout<<"\r";
	}
	cout<<endl;
	find_best_team(teams);
	return 0;
}


//------------------------ROULETTE WHEEL FUNCTION----------------------------------//
individual roulettewheel(float totalfitness,individual population[],int pop_n)
{
	float slice=(float)(RANDOM_NUM * totalfitness);
	//cout<<totalfitness<<endl;
	float fitness_t=0;
	//cout<<"total: "<<totalfitness<<endl;
	 for(int i=0;i<pop_n;i++)
	{
		fitness_t+=population[i].fitness;
		if(fitness_t>=slice)
		{
			//cout<<i<<endl;
		 return population[i];
		}
	}
}
//------------------------END OF ROULETTE WHEEL FUNCTION--------------------------//



void crossover(individual parent1,individual parent2,individual &offspring1)
{
	for(int i=0;i<p;i++)
	{
		if(parent1.rating[i]>parent2.rating[i])
		{
			offspring1.rating[i]=parent1.rating[i];
			offspring1.players[i]=parent1.players[i];
		}
		else
		{
			offspring1.rating[i]=parent2.rating[i];
			offspring1.players[i]=parent2.players[i];
		}
	}
}

void find_best_team(individual pop[])
{
	int best_team;
	float best_fitness=-1000;
	for(int i=0;i<t;i++)
	{
		if(pop[i].fitness>best_fitness)
		{
			best_team=i;
			best_fitness=pop[i].fitness;
		}
	}
	//print best individual
	for(int i=0;i<p;i++)
	{
		cout<<pop[best_team].players[i]<<"  -  "<<pop[best_team].rating[i];
		cout<<endl;
	}
	getchar();
}
