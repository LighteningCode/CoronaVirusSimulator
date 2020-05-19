#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include "graph.h"

using namespace std;

/* You can use this function to simulate
probabilities */

vector<vertex> infectRandomPerson(vector<vertex> pop)
{

    int random = rand() % pop.size();

    for (int i = 0; i < pop.size(); i++)
    {
        if (random == i)
        {
            cout << pop[i].name << " << -- >> Got himself infected" << endl;
            pop[i].is_infected = true;
        }
    }
    return pop;
}

void createSpace(int num)
{
    for (int i = 0; i < num; i++)
    {
        cout << " " << endl;
    }
}

vector<vertex> applyPolicies(int percentage, vector<vertex> data)
{
    // convert percentage
    float reduceProbability = percentage / 100;

    int countQuarantied = 0;
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i].is_infected && data[i].is_alive)
        {
            float newSpreadProbability;
            newSpreadProbability = data[i].spread_probability - reduceProbability;
            if (newSpreadProbability < 0)
            {
                newSpreadProbability = 0;
            }
            data[i].spread_probability = newSpreadProbability;
            countQuarantied++;
        }
    }
    cout << "Number of people quarantined: " << countQuarantied << endl;
    return data;
}

bool simulate_prob(float prob)
{

    prob = prob * 1000.0;

    srand(time(NULL));

    if (rand() % 1000 <= prob)
        return true;

    return false;
}

int main()
{
    /* The number of days simulation will run for */
    int days_to_simulate = 100;
    
    /* Ask the user for the population and
    connections files */

    // space
    cout << "   " << endl;
    cout << "   " << endl;

    cout << "Welcome to CoronaSim!" << endl;
    string pop_file, conn_file;
    // cout << "Enter population file name: ";
    // cin >> pop_file;
    pop_file = "smallpopulation.dat";
    // cout << "Enter connections file name: ";
    // cin >> conn_file;
    conn_file = "smallconnections.dat";

    // TODO: Populate your graph data structure
    srand(time(NULL));
    bool is_populated = false;
    vector<vertex> Population;
    vector<edge> Connections;
    Population = insert_node(pop_file);
    Connections = insert_connections(conn_file);

    cout << "Who didnt wear his/her face mask before going out today?" << endl;
    Population = infectRandomPerson(Population);

    while (true)
    {

        int choice;

        /* Print menu of things that your application can do*/
        cout << "*** *** *** *** *** *** *** *** *" << endl;
        cout << "What would you like to do?" << endl;
        cout << "1. Print population" << endl;
        cout << "2. Simulate" << endl;
        cout << "3. Summarize population" << endl;
        cout << "4. Implement policy and simulate" << endl;
        cout << "5. Exit" << endl;
        cout << "*** *** *** *** *** *** *** *** *" << endl;
        cout << "Your selection: ";

        /* TODO: You should feel free to add other
        items to the menu above for your demo video */

        cin >> choice;

        /*Ideally inside the various cases of the switch
        statement below, you will call specific functions
        supported by your graph data structure and your
        simulation algorithm. You can design all these
        functions as you like.*/

        switch (choice)
        {

        case 1:

            /* TODO: Print your population. Use
                any format you like.*/
            cout << "Maximum Age: " << getMaxAge(Population) << endl;
            print(Population);

            createSpace(3);
            cout << "<<Connections>>" << endl;
            print(Connections);
            break;

        case 2:

            /* TODO: Run simulation as described
                in the handout.*/
            createSpace(3);
            // Simulate infected person is going to be infected

            cout << "After 100 Days: " << endl;

            int maxiAge;
            maxiAge = getMaxAge(Population);

            for (int i = 0; i < days_to_simulate; i++)
            {
                
                for (int j = 0; j < Population.size(); j++)
                {
                    // get disease probability for person
                    float diseaseProb = diseaseProbability(Population[j].age, maxiAge);

                    // simulate recovery of people
                    if (Population[j].is_infected && Population[j].is_alive)
                    {
                        if (simulate_prob(chanceToRecover(diseaseProb)))
                        {
                            Population[j].is_sick = true;
                            Population[j].is_infected = true;
                        }
                        else
                        {
                            recoveries++;
                            Population[j].is_sick = false;
                            Population[j].is_infected = false;
                        }
                    }

                    // simulate connections (edges) with each other for infections to take place

                    // check if current person had contacted any infected people
                    for (int w = 0; w < Connections.size(); w++)
                    {
                        // if person is not alive skip
                        string pers ;
                        pers= Population[j].name;
                        if (Population[j].is_alive == false)
                        {
                            break;
                        }

                        if (Population[j].name == Connections[w].current)
                        {

                            // check if the reciever person is infected
                            for (int checkPop = 0; checkPop < Population.size(); checkPop++)
                            {
                                // find person from population
                                if (Connections[j].recieve == Population[checkPop].name)
                                {

                                    if (Population[checkPop].is_infected)
                                    {
                                        // infect the current person based on the probability
                                        if (simulate_prob(Population[checkPop].spread_probability))
                                        {
                                            Population[j].is_infected = true;
                                            Population[j].is_sick = true;
                                        }
                                    }
                                    break;
                                }
                            }
                        }

                        // if person is infected
                        if (Population[j].is_infected == true)
                        {
                            // increase days infected
                            Population[j].daysInfected++;
                            if (Population[j].daysInfected >= 7)
                            {
                                //person dies
                                Population[j].is_alive = false;
                            }
                        }
                    }
                }
            }

            // check if the infection is working
            for (int o = 0; o < Population.size(); o++)
            {
                cout << Population[o].name << "  <-States->  ";
                cout << "[is_infected -" << Population[o].is_infected << "-]";
                cout << "[is_sick -" << Population[o].is_sick << "-]";
                cout << "[is_alive -" << Population[o].is_alive << "-]" << endl;
            }

            createSpace(3);
            break;

        case 3:

            /* TODO: Print a summary of the population
                here. Design the summary as you like.
                Print at least the number of people
                infected, sick, recovered, dead etc.*/

            int inf;
            inf = 0;
            int si;
            si = 0;
            int de;
            de = 0;

            for (int f = 0; f < Population.size(); f++)
            {
                if (Population[f].is_infected)
                {
                    inf++;
                }
                if (Population[f].is_sick)
                {
                    si++;
                }
                if (!Population[f].is_alive)
                {
                    de++;
                }
            }

            infected = inf;
            sick = si;
            dead = de;
            createSpace(3);
            cout << "Population: ";
            cout << Population.size() << endl;

            cout << "Infected: ";
            cout << infected << endl;

            cout << "Sick: ";
            cout << sick << endl;

            cout << "Recovries: ";
            cout << recoveries << endl;

            cout << "Dead: ";
            cout << dead << endl;
            createSpace(3);

            break;

        case 4:
            createSpace(3);
            /* // TODO: Implement your own policy and
                re-simulate.*/
            int percentage;
            // get all infected  people and reduce their spread probability by point 0.2
            cout << "Policy to reduce spread probability is to -QUARANTINE THEM-" << endl;
            cout << "By what percentage does infection rate reduce (Percentage):";
            cin >> percentage;
            cout << endl;

            applyPolicies(percentage, Population);
            createSpace(3);
            break;

        case 5:

            /* // TODO: Here de-allocate all dynamically
                allocated variables before exiting*/
            int main();
            break;
        }
    }
}
