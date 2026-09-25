//g++ -Wall -Wextra -std=c++17 -o programa archivo.cpp
//Angel Manuel Ruvalcaba Garcia
//Multiplicador de Lagrange
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
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
  utilidadOptima = calcularUtilidad(); // primero, porque calcularLambda() depende de este valor
  lambda = calcularLambda();
}

double ProblemaPresupuesto::calcularUtilidad(){
  double producto = 1;
  for(Bien n: bienes){
    producto *= pow(n.cantidadOptima,n.preferencia);
  }
  return producto;
}

double ProblemaPresupuesto::calcularLambda(){
  double res = (bienes[0].preferencia * utilidadOptima) / (bienes[0].cantidadOptima * bienes[0].precio);
  return res;
}
//Este metodo lo que hace es validar que lo que estamos haciendo no 
//pase del presupuesto inicial, viendo que todo este bien
bool ProblemaPresupuesto::validarRestriccion(){
  double epsilon = 1e-6, sumaGastos=0,diferencia;
  for(Bien n: bienes){
    sumaGastos += n.gastoOptimo;
  }
  diferencia = fabs(sumaGastos-ingreso);
  return diferencia<epsilon;
}

void ProblemaPresupuesto::mostrarResultados(){
  cout<<"****RESULTADOS****\n";
  for(Bien n: bienes){
    cout<<n.nombre<<" Cantidad optima = "<<n.cantidadOptima<<", Gasto optimo = "<<n.gastoOptimo<<endl;
  }
  cout<<"Utilidad Optima = "<<calcularUtilidad()<<endl;
  cout<<"Lambda = "<<calcularLambda()<<endl;
  cout<<"¿Restriccion cumplida? "<<endl;
  if(validarRestriccion()){
    cout<<"Si"<<endl;
  }else{
    cout<<"No"<<endl;
  }
}

int main(){
  ProblemaPresupuesto pp;
  int n;
  string nombre;
  double precio, preferencia,ingreso;
  cout<<"Ingresos:"<<endl;
  cin>>ingreso;
  pp.establecerIngreso(ingreso);
  cout<<"¿Cuantos productos vas a ingresar"<<endl;
  cin>>n;
  for(int i = 0;i<n;i++){
    cout<<"**Ingresa el producto**"<<endl;
    cout<<"Nombre:"<<endl;
    cin>>nombre;
    cout<<"Preferencia (1/10):"<<endl;
    cin>>preferencia;
    cout<<"Precio del producto:"<<endl;
    cin>>precio;
    pp.agregarBien(nombre,precio,preferencia);
  }
  pp.resolver();
  pp.mostrarResultados();
  
  return 0;
}
