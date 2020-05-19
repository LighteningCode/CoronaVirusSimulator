#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int population;
int age;
int recoveries;
int dead;
int infected;
int sick;
float spread_probability;
float recovery_probability;

int days;

struct vertex
{
    string name;
    int age;
    float spread_probability;
    float disease_probability;
    bool is_infected;
    bool is_sick;
    bool is_alive;
    int daysInfected;
    vector<string> neighbor;
};

struct edge
{
    string current;
    string recieve;
};

vector<vertex> insert_node(string pop_file)
{
    vector<vertex> test;
    vertex people;

    ifstream file(pop_file);
    if (!file)
    {
        cerr << "File not available" << endl;
    }
    else
    {
        string var_name;
        string var_age;
        string spread_prob;
        while (file >> var_name >> var_age >> spread_prob)
        {
            int age1 = stoi(var_age);
            float prob = stof(spread_prob);
            people.name = var_name;
            people.age = age1;
            people.spread_probability = prob;
            people.is_infected = false;
            people.is_alive = true;
            people.is_sick = false;
            people.daysInfected = 0;
            test.push_back(people);
        }
    }
    return test;
};

float diseaseProbability(int age, int maxAge)
{
    return age / maxAge;
}

float chanceToRecover(float diseaseProbability){
    return 1 - diseaseProbability;
}

vector<edge> insert_connections(string conn_file)
{
    vector<edge> connections;
    edge people;
    ifstream file(conn_file);
    if (!file)
    {
        cerr << "File not available" << endl;
    }
    else
    {
        string current;
        string recieve;
        while (file >> current >> recieve)
        {
            people.current = current;
            people.recieve = recieve;
            // if (edges[i].name == current)
            // {
            //     edges[i].neighbor.push_back(recieve);
            // }
            connections.push_back(people);
        }
        return connections;
    }
}

void print(vector<vertex> &display)
{
    for (int i = 0; i < display.size(); i++)
    {
        cout << display[i].name << "->"
             << " [Age: " << display[i].age << ", Spread Probability: " << display[i].spread_probability << ", infected: "<< display[i].is_infected <<"]";

        cout << endl;
    }
}

void print(vector<edge> &Connections)
{

    for (int i = 0; i < Connections.size(); i++)
    {
        cout << "Connection " << i << ":" << Connections[i].current << "->" << Connections[i].recieve;
        cout << endl;
    }
}

int getMaxAge(vector<vertex> &population)
{
    int maxAge = 0;
    for (int i = 0; i < population.size(); i++)
    {
        if (population[i].age > maxAge)
        {
            maxAge = population[i].age;
        }
    }
    return maxAge;
}

int count_edges(vector<vertex> &edges)
{
    int sum = 0;

    for (int i = 0; i < edges.size(); i++)
        ;
}
