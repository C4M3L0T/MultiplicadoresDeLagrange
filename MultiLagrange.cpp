//g++ -Wall -Wextra -std=c++17 -o programa archivo.cpp
//Angel Manuel Ruvalcaba Garcia
//Multiplicador de Lagrange
#include <iostream>
#include <vector>
#include <string>
using namespace std;
//Declaramos el bien 
struct Bien {
  string nombre;
  double precio; // p_i
  double preferencia; // a_i
  double cantidadOptima; // x_i*
  double gastoOptimo; // p_i * x_i*
};
//Declaramos el objeto principal, el cual 
//tiene todos los metodos y atributos necesarios para resolver
//el problema
class ProblemaPresupuesto {
  private:
    vector<Bien> bienes;
    double ingreso; // I
    double sumaPreferencias; // suma de a_j
    double lambda;
    double utilidadOptima;

  public:
    void agregarBien(string nombre, double precio, double preferencia);
    void establecerIngreso(double I);
    void resolver();
    double calcularUtilidad();
    double calcularLambda();
    bool validarRestriccion();
    void mostrarResultados();
};

//Este metodo declara todos los atributos que tiene el bien segun
//la preferencia del usuario 
void ProblemaPresupuesto::agregarBien(string nombre, double precio, double preferencia){
  Bien nuevoBien;
  nuevoBien.nombre = nombre;
  nuevoBien.precio = precio;
  nuevoBien.preferencia = preferencia;
  bienes.push_back(nuevoBien);
}
//Este metodo declara el ingreso del usuario
void ProblemaPresupuesto::establecerIngreso(double I){
  ingreso = I;
}

void ProblemaPresupuesto::resolver(){
  //Hacemos la suma de todas las preferencias
  sumaPreferencias = 0;
  for(Bien n: bienes){
    sumaPreferencias += n.preferencia;
  }
  //Modificamos directamente el vector con &
  //en el ciclo anterior solo haciamos lectura de preferencia
  for(Bien &b: bienes){
    b.cantidadOptima = (b.preferencia/sumaPreferencias)*(ingreso/b.precio); // Calculo de x_i
    b.gastoOptimo = b.precio*b.cantidadOptima;
  }
}

int main(){
  ProblemaPresupuesto pP1;

  
  return 0;
}
