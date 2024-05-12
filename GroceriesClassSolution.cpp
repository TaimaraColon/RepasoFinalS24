#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <algorithm>
#include <cassert>

using namespace std;

class Groceries{

    private:
    double price;
    string productName;
    bool vegetable;
    bool fruit;
    bool drink;

    public:
    double getPrice() const { return price; }
    string getProductName() { return productName; }
    bool isVegetable() { return vegetable; }
    bool isFruit() { return fruit; }
    bool isDrink() { return drink; }
    Groceries(double price, string productName, bool vegetable, bool fruit, bool drink) : price(price), productName(productName), vegetable(vegetable), fruit(fruit), drink(drink) {}

};

/**
 * EXERCISE 1 
 * 
 * Create a map where the key is the price and the value is the productName.
*/
map<double, string> mapProductToPrice(vector<Groceries> products){

    map<double, string> result;
    
    for(Groceries product : products){
        result[product.getPrice()] = product.getProductName(); // Recordando que el sintax para guardar key/values en un mapa es: map[key] = value
    }

    return result; //dummy return
}

/**
 * EXERCISE 2
 *  
 * Sort the vector using the sort() method in increasing price order. You must use a lambda a expression.
 * Este enlace tiene una buena explicacion del sintaxis para el lambda expression : https://learn.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=msvc-170
 * 
*/
void sortGroceriesByPrice(vector<Groceries>& products) {
    // El sintax de un lambda expression es: [](Type a, Type b) { LAMBDA BODY -- AQUI VAN LAS OCNDICIONES Y EL RETURN}
    //en el caso del sort, queremos que el producto a sea menor que el b ya que esto nos devuelve un order CRECIENTE, 
    //entiendase que si lo queremos de forma DECRECIENTE pues la idea seria que entonces a > b.
    sort(products.begin(), products.end(), [](Groceries a,  Groceries b) {
        return a.getPrice() < b.getPrice();
    });
}


/**
 * EXERCISE 3
 * 
 * Traverse the map and return a new map with the type of prduct as key (drink, fruit or vegetable) and the count of each as value.
*/
map<string, int> groceryCart(map<int, Groceries> groceries) {
    map<string, int> result;

    for (auto pair : groceries) {
        // object.first te da el primer elemento del mapa, object.second el segundo.
        Groceries product = pair.second;  //En este caso el producto a comparar esta en object.second 
                                         //(IMPORTANTE simepre mirar los parametros de los metodos para saber con lo que estamos trabajando)

        //IDEA: si encontramos un producto vegetal se añade al nuevo mapa y su value sera el incremento de counts
        if (product.isVegetable()) {
            result["Vegetable"] += 1;
        }
        if (product.isFruit()) {
            result["Fruit"] += 1;
        }
        if (product.isDrink()) {
            result["Drink"] +=1 ;
        }
    }

    return result;
}

/**
 * TEST CASES
*/

//TEST EXERCISE 1
void testMapProductToPrice() {
    vector<Groceries> products = {
        Groceries(1.99, "Apple", false, true, false),
        Groceries(0.99, "Carrot", true, false, false)
    };
    map<double, string> result = mapProductToPrice(products);
    assert(result[1.99] == "Apple" && "Price to product mapping failed for Apple");
    assert(result[0.99] == "Carrot" && "Price to product mapping failed for Carrot");
    cout << "EXERCISE 1 tests passed." << endl;
}



//TEST EXERCISE 2
void testSortGroceriesByPrice() {
    vector<Groceries> products = {
        Groceries(1.99, "Apple", false, true, false),
        Groceries(0.99, "Carrot", true, false, false),
        Groceries(0.50, "Banana", false, true, false)
    };
    sortGroceriesByPrice(products);
    assert(products[0].getPrice() == 0.50 && "Sorting failed for Banana");
    assert(products[1].getPrice() == 0.99 && "Sorting failed for Carrot");
    assert(products[2].getPrice() == 1.99 && "Sorting failed for Apple");
    cout << "EXERCISE 2 tests passed." << endl;
}


//TEST EXERCISE 3

int main() {
    testMapProductToPrice();
    testSortGroceriesByPrice();
    map<int, Groceries> groceryStore = {
        {1, Groceries(1.99, "Apple", false, true, false)},
        {2, Groceries(0.99, "Carrot", true, false, false)},
        {3, Groceries(2.50, "Orange Juice", false, false, true)}
    };

    map<string, int> cartSummary = groceryCart(groceryStore);
    for (const auto& [type, count] : cartSummary) {
        cout << type << ": " << count << endl;
    }

    return 0;
    return 0;
}
