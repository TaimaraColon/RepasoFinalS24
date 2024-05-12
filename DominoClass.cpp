  
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Domino {
    private:
        int valorIzquierdo; // dots left-hand side
        int valorDerecho;   // dots right-hand side

    public:
        Domino(int valorIzquierdo, int valorDerecho) {
        this->valorIzquierdo = valorIzquierdo;
        this->valorDerecho = valorDerecho;
    }

    int getValorIzquierdo() {
        return valorIzquierdo;
    }

    int getValorDerecho() {
        return valorDerecho;
    }

    // Imprime domino con formato: [valorIzquierdo , valorDerecho]
    void ficha(){
        cout << "[" <<  getValorIzquierdo() <<  "," << getValorDerecho() <<  "] " << endl;
    }

};


/* 
 * EXERCISE #1
 * Determines if the parameter sequence of dominoes is valid.  
 * A sequence is valid if all adjacent domino sides have the same number.
 * For example: [2 3][4 2][2 2][3 5] is not valid, dominoes 1-2 & 3-4 don't match.
 * Whereas, the following sequence is valid [2 3][3 5][5 4][4 5].
*/
bool sequenciaValida(vector<Domino> dominos)
{
    for(int i = 0; i < dominos.size()-1; i++){

        // en el momento que el lado derecho del domino ACTUAL sea diferente al lado izquierdo del PROXIMO domino, devolvemos falso
        if(dominos[i].getValorDerecho() != dominos[i+1].getValorIzquierdo()){
            return false;
        } 
    }
    // si terminamos de iterar y nunca entramos en la condicion significa que es un domino valido
    return true; 
}




/* 
 * EXERCISE #2 
 * Method that orders dominos from smallest (less dots) to largest (more dots).
 * 
 * You task is to fix/complete the following method.  The following defective method
 * uses a dummy function named myFunction.  Your task is to replace the call to 
 * myfuntion with an embedded lambda expression.  You should consider that one domino
 * is less than another (or comes first) when it has less points (dots) that the other.
 * 
 * Hint see: http://www.cplusplus.com/reference/algorithm/sort/
*/ 

//IDEA: la suma de puntos de ambos lados del primer domino SIEMPRE debe ser menor a la suma de puntos de ambos lados del segundo domino
bool myfunction (Domino d1, Domino d2) {return d1.getValorDerecho() + d1.getValorIzquierdo() < d2.getValorDerecho() + d2.getValorIzquierdo();}

void ordenarDominos(vector<Domino> &dominos)
{
    // Incomplete version to be fixed/completed, beware some tests may SEEM to pass
    sort(dominos.begin(), dominos.end(), myfunction); 
}


/* 
 * EXERCISE #3
 * The recursive cuantosDobles method returns the number of dominos that are
 * "doubles" (the left and right values are the same) in a given vector of dominoes.
 * Your task is to complete the doblesHelper method.
 * It MUST be recursive.
 */
int doblesHelper(vector<Domino> v, int i)
{
    //BASE CASE: el indice en el que estoy es mayor que el size? si es asi significa que ya se acabo el vector y no encontre ningun doble, asi que devuelvo 0.
    if(i >= v.size()){
        return 0;
    }

    //Si ambos lados son iguales es una ficha doble asi que le incremento 1 y me muevo al proximo elemento (i+1)
    if(v[i].getValorDerecho() == v[i].getValorIzquierdo()){
        return 1 + doblesHelper(v,i+1);
    }
    return doblesHelper(v,i+1);
}

int cuantosDobles(vector<Domino> dominos)
{
    return doblesHelper(dominos, 0);
}



int main()
{

    // NOTE:  These test-cases may be different from those in Moodle!
    // Testcases #1 -----------------------------------------------------------------------------------
    vector<Domino> secuenciaUno {Domino(2, 3), Domino(3, 3), Domino(2, 5), Domino(2, 4)};
    vector<Domino> secuenciaDos {Domino(2, 3), Domino(3, 1), Domino(1, 5), Domino(5, 2), Domino(2, 0) };        
    //cout << "EX #1 Test cases" << endl;
    cout << "Sequencia valida: " << ( sequenciaValida(secuenciaUno) == false ? "Passed" : "Failed" ) << endl;
    cout << "Sequencia valida: " << ( sequenciaValida(secuenciaDos) == true  ? "Passed" : "Failed" ) << endl;


    //Testcases #2 -----------------------------------------------------------------------------------
    cout << "EX #4 -- Sort Test cases" << endl;
    vector<Domino> enMano41 {Domino(6,1), Domino(3,1), Domino(4,1), Domino(5,1), Domino(1,1), Domino(2,1)};
    cout << "Before sorting" << endl;
    for (Domino d: enMano41) d.ficha();
    ordenarDominos(enMano41);
    cout << "After sorting" << endl;
    for (Domino d: enMano41) d.ficha();

    vector<Domino> enMano42 {Domino(4,3), Domino(3,2), Domino(4,5), Domino(2,2), Domino(1,1), Domino(0,0)};
    cout << "Before sorting" << endl;
    for (Domino d: enMano42) d.ficha();
    ordenarDominos(enMano42);
    cout << "After sorting" << endl;
    for (Domino d: enMano42) d.ficha();


    // Testcases #3 -----------------------------------------------------------------------------------
    //cout << "EX #5 Test cases" << endl;
    vector<Domino> enMano51 {Domino(6,1), Domino(3,1), Domino(4,1), Domino(5,1), Domino(1,1), Domino(2,1)}; //1
    vector<Domino> enMano52 {Domino(6,6), Domino(3,3), Domino(4,4), Domino(5,5), Domino(1,1), Domino(2,2)}; //6
    vector<Domino> enMano53 {Domino(6,1), Domino(3,1), Domino(4,1), Domino(5,1), Domino(1,0), Domino(2,1)}; //0
    cout << "Doubles: " << ( cuantosDobles(enMano51) == 1  ? "Passed" : "Failed") << endl;
    cout << "Doubles: " << ( cuantosDobles(enMano52) == 6  ? "Passed" : "Failed") << endl;
    cout << "Doubles: " << ( cuantosDobles(enMano53) == 0  ? "Passed" : "Failed") << endl; 
    
    return 0;       
}


/*
All dominoes ... for testing
Domino(6,6)
Domino(6,5), Domino(5,5)
Domino(6,4), Domino(5,4), Domino(4,4)
Domino(6,3), Domino(5,3), Domino(4,3),Domino(3,3), 
Domino(6,2), Domino(5,2), Domino(4,2),Domino(3,2), Domino(2,2)
Domino(6,1), Domino(5,1), Domino(4,1),Domino(3,1), Domino(2,1), Domino(1,1)
Domino(6,0), Domino(5,0), Domino(4,0),Domino(3,0), Domino(2,0), Domino(1,0), Domino(0,0)
*/


