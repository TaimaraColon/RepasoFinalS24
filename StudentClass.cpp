  
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <algorithm>

using namespace std;

class Student {

    private:
    int id;
    string firstName;
    string lastName;
    string homeTown;

    public:
    int getId() const { return id; }
    string getFirstName() { return firstName; }
    string getLastName() { return lastName; }
    string getHomeTown() { return homeTown; }
    Student(int id, string fn, string ln, string ht): id(id), firstName(fn), lastName(ln), homeTown(ht) {}

    bool operator<(const Student &s2) const
    {
        return (this->getId() < s2.getId());
    }

};

// EXERCISE 4
// Returns a set of strings including all the unique towns where all the
// different students live.
set<string> uniqueHomeTowns(const vector<Student> &students)
{
    set<string> result;

    //Iteramos por el vector e insertamos los valores al set, 
    //el set tiene como propiedad que solo contiene elementos unicos por lo tanto el solo darle insert es suficiente para quedarnos con los eleemtos que no se repitan
    for(Student s: students){
        result.insert(s.getHomeTown());
    }
    return result; 
}


// EXERCISE 5
// Returns a NEW vector of students sorted in telephone directory order, meaning that
// they should be sorted by last name first and then by first name.  Names should be
// sorted lexicopgraphically using the default < operator of the string class.
// FOR FULL CREDIT YOU MUST USE THE sort FUNCTION IN THE ALGORHTM.H module of the STL
// AND PRIVIDE AN APPROPRIATE LAMBDA EXPRESSION TO THIS FUNCTION TO ACCOMPLISH THE 
// SORTING
vector<Student> sortByPhoneDirectory(const vector<Student> &students)
{
    vector<Student> sortedStudents = students; 

    sort(sortedStudents.begin(), sortedStudents.end(),
        
        //SINTAX DE UN LAMBDA EXPRESSION -- [](TYPE a, TYPE b) { LAMBDA BODY -- AQUI VAN LAS CONDICIONES Y EL RETURN }
        [](Student s1, Student s2) {
            if(s1.getLastName() != s2.getLastName()) return s1.getLastName()<s2.getLastName();
            
            return (s1.getFirstName() < s2.getFirstName());
            
            
        }
    );
    return sortedStudents;
}



// EXERCISE 6
// Returns a NEW stack of students containing only the students who live in
// the given parameter home town.  The order of the students in the new stack
// should be preserved.  That is students in the new stack should remain below
// students who were higher up in the original stack.  See tests for examples.
stack<Student> homeTownStack(stack<Student> &students, string homeTown)
{
    //REPASANDO: La idea de un stack es como tener una torre de galletas, solo tienes acceso a la galleta the arriba, y solo vas tomando una a la vez.
    // Cuando ponemos las galletas cada una va una encima de la otra. A esto le llamamos Last In First Out porque la ultima galleta que pusimos es la primera que vamos a tomar.

    stack<Student> tempStack; //aqui tendremos el stack invertido (al añadir a los estudiantes el stack se invertira ya que los añadimos uno encima del otro)
    stack<Student> newStack;   // es por esto que tenemos el newStack, este sera el stack final

    //En un stack solo tenemos acceso al tope, por lo tanto en cada iteracion debemos verificar si el stack esta vacio, 
    //si no pues accedemos al top, hacemos las comparaciones que queramos hacer, lo añadimos a tempStack y le damos pop.
    while (!students.empty()) {
        Student current = students.top(); 
        
        if (current.getHomeTown() == homeTown) {
            tempStack.push(current); 
        }
        students.pop(); //al darle pop, eliminamos el elemento en el q estamos y nos movemos al proximo
    }

    // Este loop revierte el orden para que se preserve el orden del stack original
    while (!tempStack.empty()) {
        newStack.push(tempStack.top());
        tempStack.pop();
    }

    return newStack;
}


int main() {

    // EXERCISE #4 Tests
    vector<Student> testStudents;
    testStudents.push_back( Student(10, "Bienve", "Velez", "Mayaguez"));
    testStudents.push_back( Student(25, "Juan", "Perez", "Humacao"));
    testStudents.push_back( Student(21, "Amanda", "Vazquez", "Guaynabo"));
    testStudents.push_back( Student(32, "Fernando", "Davis", "Guaynabo"));
    testStudents.push_back( Student(65, "Joshua", "Cruz", "Ponce"));
    testStudents.push_back( Student(43, "Alejandra", "Munoz", "Guaynabo"));
    testStudents.push_back( Student(54, "Fatima", "Puig", "Cabo Rojo"));
    testStudents.push_back( Student(11, "Diego", "Maradona", "Ponce"));
    testStudents.push_back( Student(99, "Ana", "Cruz", "Hormigueros"));
    testStudents.push_back( Student(76, "Rey", "Cotto", "Hormigueros"));

    set<string> uniqueHTs = uniqueHomeTowns(testStudents);
    cout << "Count of Unique Home Towns: " << ((uniqueHTs.size() == 6) ? "Passed" : "Failed") << endl;
    cout << "Home Town Exists: " << ((count(uniqueHTs.begin(), uniqueHTs.end(), "Mayaguez") == 1) ? "Passed" : "Failed") << endl;
    cout << "Home Town Exists: " << ((count(uniqueHTs.begin(), uniqueHTs.end(), "Humacao") == 1) ? "Passed" : "Failed") << endl;
    cout << "Home Town Exists: " << ((count(uniqueHTs.begin(), uniqueHTs.end(), "Guaynabo") == 1) ? "Passed" : "Failed") << endl;
    cout << "Home Town Exists: " << ((count(uniqueHTs.begin(), uniqueHTs.end(), "Ponce") == 1) ? "Passed" : "Failed") << endl;
    cout << "Home Town Exists: " << ((count(uniqueHTs.begin(), uniqueHTs.end(), "Cabo Rojo") == 1) ? "Passed" : "Failed") << endl;
    cout << "Home Town Exists: " << ((count(uniqueHTs.begin(), uniqueHTs.end(), "Hormigueros") == 1) ? "Passed" : "Failed") << endl;


    // EXERCISE #5 Tests
    testStudents.clear();
    testStudents.push_back( Student(10, "Bienve", "Velez", "Mayaguez"));
    testStudents.push_back( Student(25, "Juan", "Perez", "Humacao"));
    testStudents.push_back( Student(21, "Amanda", "Vazquez", "Guaynabo"));
    testStudents.push_back( Student(32, "Fernando", "Davis", "Guaynabo"));
    testStudents.push_back( Student(65, "Joshua", "Cruz", "Ponce"));
    testStudents.push_back( Student(43, "Alejandra", "Munoz", "Guaynabo"));
    testStudents.push_back( Student(54, "Fatima", "Puig", "Cabo Rojo"));
    testStudents.push_back( Student(11, "Diego", "Maradona", "Ponce"));
    testStudents.push_back( Student(99, "Ana", "Cruz", "Hormigueros"));
    testStudents.push_back( Student(76, "Rey", "Cotto", "Hormigueros"));

    vector<Student> sortedStudents = sortByPhoneDirectory(testStudents);
    cout << "Sorted Vector Size:" << ((sortedStudents.size() == 10) ? "Passed" : "Failed") << endl;
    cout << "Student 0 in Sorted Vector:" << ((sortedStudents[0].getId() == 76) ? "Passed" : "Failed") << endl;
    cout << "Student 1 in Sorted Vector:" << ((sortedStudents[1].getId() == 99) ? "Passed" : "Failed") << endl;
    cout << "Student 2 in Sorted Vector:" << ((sortedStudents[2].getId() == 65) ? "Passed" : "Failed") << endl;
    cout << "Student 3 in Sorted Vector:" << ((sortedStudents[3].getId() == 32) ? "Passed" : "Failed") << endl;
    cout << "Student 4 in Sorted Vector:" << ((sortedStudents[4].getId() == 11) ? "Passed" : "Failed") << endl;
    cout << "Student 5 in Sorted Vector:" << ((sortedStudents[5].getId() == 43) ? "Passed" : "Failed") << endl;
    cout << "Student 6 in Sorted Vector:" << ((sortedStudents[6].getId() == 25) ? "Passed" : "Failed") << endl;
    cout << "Student 7 in Sorted Vector:" << ((sortedStudents[7].getId() == 54) ? "Passed" : "Failed") << endl;
    cout << "Student 8 in Sorted Vector:" << ((sortedStudents[8].getId() == 21) ? "Passed" : "Failed") << endl;
    cout << "Student 9 in Sorted Vector:" << ((sortedStudents[9].getId() == 10) ? "Passed" : "Failed") << endl;

    // EXERCISE #6 Tests
    stack<Student> studentsStack;
    studentsStack.push( Student(10, "Bienve", "Velez", "Mayaguez"));
    studentsStack.push( Student(65, "Juan", "Perez", "Humacao"));
    studentsStack.push( Student(21, "Amanda", "Vazquez", "Guaynabo"));
    studentsStack.push( Student(32, "Fernando", "Davis", "Guaynabo"));
    studentsStack.push( Student(65, "Joshua", "Cruz", "Ponce"));
    studentsStack.push( Student(43, "Alejandra", "Munoz", "Guaynabo"));
    studentsStack.push( Student(54, "Fatima", "Puig", "Cabo Rojo"));
    studentsStack.push( Student(65, "Diego", "Maradona", "Ponce"));
    studentsStack.push( Student(65, "Ana", "Cruz", "Hormigueros"));
    studentsStack.push( Student(76, "Rey", "Cotto", "Hormigueros"));

    stack<Student> filteredStack = homeTownStack(studentsStack, "Guaynabo");
    cout << "Filtered Stack Size:" << ((filteredStack.size() == 3) ? "Passed" : "Failed") << endl;
    cout << "Student at top in Filtered Sstack:" << ((filteredStack.top().getId() == 43) ? "Passed" : "Failed") << endl;
    filteredStack.pop();
    cout << "Student at top in Filtered Sstack:" << ((filteredStack.top().getId() == 32) ? "Passed" : "Failed") << endl;
    filteredStack.pop();
    cout << "Student at top in Filtered Sstack:" << ((filteredStack.top().getId() == 21) ? "Passed" : "Failed") << endl;
    filteredStack.pop();
    cout << "Filtered Stack After Pops Size:" << ((filteredStack.size() == 0) ? "Passed" : "Failed") << endl;

}

