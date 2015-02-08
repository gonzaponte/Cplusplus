#include <iostream>
#include <string>
#include <vector>

using namespace std;

class person
{
    string name, lastname, job;
    int age, bros, sons;
    float height, weight;
    
public:
    string GetFullName(){ return ( name + " " + lastname ); }
    string GetJob(){ return job; }
    int GetAge(){ return age; }
    float GetHeight(){ return height; }
    float GetWeight(){ return weight; }
    void Add( void );
    void Erase( void );
    void SetName( string n ){ name = n; }
    void SetLastname( string l ){ lastname = l; }
    void SetJob( string j ){ job = j; }
    void SetAge( int a ){ age = a; }
};

void wait ( void );
void printlist( vector < person > p );

void person::Add( void )
{
    string temp;
    int tempint;
    
    cout << "Introduce the name of the person: " << endl << endl;
    cin >> temp;
    SetName( temp );
    cout << endl << endl;
    cout << "Introduce the last name of the person: " << endl << endl;
    cin >> temp;
    SetLastname( temp );
    cout << endl << endl;
    cout << "Introduce the job of the person: " << endl << endl;
    cin >> temp;
    SetJob( temp );
    cout << endl << endl;
    cout << "Introduce the age of the person: " << endl << endl;
    cin >> tempint;
    SetAge( tempint );
    cout << endl << endl;
}

void wait(void)
{
    cout << endl << "Press <Enter> to finish" << endl;
    cin.get();
    cin.ignore(255, '\n');  // rexeitar caracteres introducidos antes de <Enter>
}

void printlist( vector < person > p )
{
    cout << endl << endl;
    cout << "      Name      " << "     Job    " << "    Age    " << endl << endl;

    for ( int i=0; i<p.size(); i++ )
    {
        cout << p[i].GetFullName() << "   "   <<    p[i].GetJob() << "   " <<   p[i].GetAge()  << endl;
    }
}

int main( void )
{
    bool more=true;
    vector < person > people;
    cout << endl << "This program creates a list of people with their data" << endl << endl;
    while ( more )
    {
        person p;
        
        
        p.Add();
        people.push_back( p );
        
        cout << "Do you want to add more people? (0 = no, 1 = yes)" << endl << endl;
        
        int condition;
        
        cin >> condition;
        if (!condition) more = false;
        
    }
    
    int print;
    cout << endl << "Do you want to print the list? (0 = no, 1 = yes)" << endl << endl;
    cin  >> print;
    
    if (print) printlist( people );
    wait();
    return 0;
    
}



