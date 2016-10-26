#include <iostream>
#include <cmath>
using namespace std;
#include <fstream>

int menu ();
void funcionfactorial(double op1, double op2, double &resultado, ofstream &archivo);
void funcionpotencia(double op1, double op2, double &resultado,ofstream &archivo);
void operacionesbasicas (char factorial, char raiz, char reset, char suma, char restar, char producto, char division, char potencia, double op1, double op2, char operador, double &resultado, ofstream &archivo);
void configuracion (char &suma, char &restar, char &producto, char &division, char &raiz, char &factorial, char &potencia, char &reset, char &salir, char &simplificacion, ofstream &archivo2);
void fcargar (char &suma, char &restar, char &producto, char &division, char &raiz, char &factorial, char &potencia, char &reset, char &salir, char &simplificacion, ifstream &archivo3);
void reducir(int &num1,int &den1);
int mcd(int a, int b);
void potencial(int &resultado1, int &resultado2, int &num2, ofstream &archivo);
void fcase2(ofstream &archivo, char salir, bool terminar1, char suma, char restar, char producto, char division, char potencia, char simplificacion, char reset, int num1, char simbolo, char operador, int den1, int num2, int den2);


int main(){ 
	int num1 = 0, num2 = 0, den1= 1, den2 = 1;
    char const simbolo = '|';
    bool terminar1;
	int opcion;
	double op1,op2,resultado=0, resta;
	char operador , p , salida, reset= 'C' , suma = '+', restar = '-', producto = '*' , division ='/', raiz = 'r', factorial= '!', potencia = '^' , simplificacion = 's', salir = 'x';
	bool errorExpresion = false, salirMenuPrincipal = false, terminar , errorEntero = false, errorPositivo = false, errorFraccion =false;
	ofstream archivo, archivo2;
	ifstream archivo3;
	archivo.open("log.txt");
	archivo3.open("conf.txt");
		if(archivo3.is_open())
		{
			fcargar(suma, restar, producto, division, raiz, factorial, potencia, reset, salir, simplificacion, archivo3);
		}
	 archivo3.close();

	ifstream cambio;
	cambio.open("conf.txt");
	cambio >> suma >> restar >> producto >> division >> factorial >> potencia >> raiz >> reset >> salir >> simplificacion;
			
	do{
	opcion= menu();
	cin.sync();
	switch(opcion)
	{	
		case 1:
		 {
			terminar=false;
			while(terminar != true){
			cout << "Introduzca una expresion aritmetica (sin espacios) (x para teminar)" << endl;
		    cout << suma << ": suma  " << restar << ": resta  " << producto << ": producto  " << raiz << ": raiz  " << division << ": division  " << potencia << ": potencia  "<< factorial << ": factorial  " << simplificacion << ": s " << reset << ": reset  "<< endl;
            cin.sync();
            p= cin.peek();
            if ( p == suma || p == restar || p == producto || p == raiz || p == division || p == factorial || p== potencia || p == reset )
               op1 = resultado;
            else if (p == salir)
            {
            terminar = true;
             cin >> salida;  
            }
            else
            cin >> op1;
			archivo << " > " << op1;
            if(terminar != true){
				cin.get(operador);
				archivo << operador;
				while(operador != '\n'){
				if(operador == factorial || operador == raiz || operador == reset)
                   operacionesbasicas (factorial,  raiz, reset, suma, restar, producto, division, potencia, op1, op2, operador, resultado, archivo);
				else 	
					cin >> op2;
					archivo << op2 <<endl;
					if(operador == suma || operador == restar || operador == producto || operador == division || operador == potencia){
 					  operacionesbasicas (factorial, raiz, reset, suma, restar, producto, division, potencia, op1, op2, operador, resultado, archivo);									                                                                    
						}
						op1=resultado;
						cin.get(operador);
					}
								cout << resultado << endl;
								archivo << resultado <<endl;  
					} //termina el if 

			} // termina el while
	} /// termina el case1

		break;
		
	    case 2:

			fcase2(archivo, salir, terminar1, suma, restar, producto, division, potencia, simplificacion, reset, num1, simbolo, operador, den1, num2, den2);
			
			break;

			case 3:
			 {  
				configuracion (suma, restar, producto, division, raiz, factorial, potencia, reset, salir, simplificacion, archivo2);
			}	
			break;
			
			case 4:
					salirMenuPrincipal=true;
			break;
		
			default:
					cout <<" Introduzca un numero valido "<<endl;
			break;
		}

	
		}while(salirMenuPrincipal != true);
		archivo.close();
		archivo2.close();
		cambio.close();
		
	   return 0;

	}
	int menu (){
		  cout << "1.-Calculadora"<<endl;
		  cout << "2.-Calculadora: Modo fracciones"<< endl;
		  cout << "3.-Configuracion"<<endl;
		  cout << "4.-Salir"<<endl;
		  int op;
		  cout << "Opcion: ";
		  cin >> op;
		  return op;
	}

void operacionesbasicas (char factorial, char raiz, char reset, char suma, char restar, char producto, char division, char potencia, double op1, double op2, char operador, double &resultado, ofstream &archivo)
{
   if(operador == factorial || operador == raiz || operador == reset){
		if (operador == raiz){
			if (op1 < 0)	{
				cout << " Debe ser positivo, ejecute nuevamente" << endl;
				archivo << "*** ERROR ***" << endl;
			}
		    else 
				resultado = sqrt(op1);
		}
			else if (operador == factorial)
					funcionfactorial(op1, op2, resultado, archivo);
				 else 
					resultado = 0;  // C mayuscula
}
   else 
         if(operador == suma){
			resultado= op1 + op2;						
		}
		else
			if(operador == restar){
				resultado= op1 - op2;
			}
			else
				if(operador == producto){
					resultado= op1 * op2;
				}
				else
					if(operador == division){
						resultado= op1 / op2;
					}	
					else
						if(operador == potencia)
							funcionpotencia(op1, op2, resultado, archivo);
 }

void funcionfactorial(double op1, double op2, double &resultado, ofstream &archivo)
{
		double resta = int (op1) -op1; //   floor(op1) - op1;
		resultado = op1;
		if ( resta == 0){
		if ( op1 > 0){
			for ( int i = 1 ; i < op1 ; i++)
				resultado = resultado * i;
		}
		else 
			cout << "Debe ser positivo, ejecute nuevamente" << endl;
			archivo << "*** ERROR ***" << endl;
		}
		else 
			cout << "Debe ser entero, ejecute nuevamente"<<endl;
			archivo << "*** ERROR ***" << endl;
	}

void funcionpotencia(double op1, double op2, double &resultado,ofstream &archivo)
{
			double resta = int (op2) - op2;
			resultado = op1;
			if(resta == 0){
			for (int i=1; i<op2; i++)
			resultado *=op1;
			}
			else
			     cout << "Debe ser entero, ejecute nuevamente"<<endl;
				archivo << "*** ERROR ***" << endl;
}	

void configuracion (char &suma, char &restar, char &producto, char &division, char &raiz, char &factorial, char &potencia, char &reset, char &salir, char &simplificacion, ofstream &archivo2)
{
         archivo2.open("conf.txt");
		 char p;
         cout << "Para cambiar el caracter " << suma << " (intro para mantener la misma) = ";
			cin.sync();
			cin.get(p);			   
            if (p!='\n')
				suma = p;
			archivo2 << suma;		
			cout << "Para cambiar el caracter " << restar << " (intro para mantener la misma) = ";	
			cin.sync();
			cin.get(p);
			if (p!='\n')
				restar = p;
			archivo2 << restar;		
			cout << "Para cambiar el caracter " << producto << " (intro para mantener la misma) = ";
			cin.sync();
			cin.get(p);
            if (p !='\n')
				producto = p;
			archivo2 << producto;			
			cout << "Para cambiar el caracter " << division << " (intro para mantener la misma) = "; 
			cin.sync();
			cin.get(p);
            if (p !='\n')
				division = p;
			archivo2 << division;	            
			cout << "Para cambiar el caracter " << factorial << " (intro para mantener la misma) = ";
			cin.sync();
			cin.get(p);
            if (p !='\n')
				factorial = p;
			archivo2 << factorial;				
			cout << "Para cambiar el caracter "  << potencia << " (intro para mantener la misma) = ";
			cin.sync();
			cin.get(p);
            if (p !='\n')
				potencia = p;
			archivo2 << potencia;					
			cout << "Para cambiar el caracter " << raiz << " (intro para mantener la misma) = ";
			cin.sync();
			cin.get(p);
            if (p !='\n')
				raiz = p;
			archivo2 << raiz;	           
		    cout << "Para cambiar el caracter " << reset << " (intro para mantener la misma) = ";
			cin.sync();
			cin.get(p);
            if (p !='\n')
				reset = p;
			archivo2 << reset;
			cout << "Para cambiar el caracter " << salir << " (intro para mantener la misma) = ";
			cin.sync();
			cin.get(p);
            if (p !='\n')
				salir = p;
			archivo2 << salir;
			cout << "Para cambiar el caracter " << simplificacion << " (intro para mantener la misma) = ";
			cin.sync();
			cin.get(p);
            if (p !='\n')
				simplificacion = p;
			archivo2 << simplificacion;
}

void reducir(int &num1,int &den1)
{
     int aux;
     aux=den1;
     den1=den1/mcd(num1,den1);
     num1=num1/mcd(num1,aux);
}

int mcd(int a,int b)
{
        int r;
        while (b!=0)
        {
              r=(a%b);
              a=b;
              b=r;  
        }
        return a;
} 

void potencial(int &resultado1, int &resultado2, int &num2, ofstream &archivo)
{
  int num1;
  int den1;
  double resta = int(num2) - num2;
   num1 = resultado1;
   den1 = resultado2;
   if(resta == 0)
   {
      for (int i=1; i < num2; i++){
           resultado1 *= num1;
           resultado2 *= den1;
      }
   }
   else
		cout << "Debe ser entero , ejecute nuevamente" << endl;
		archivo << "*** ERROR ***" << endl;
}

void fcargar (char &suma, char &restar, char &producto, char &division, char &raiz, char &factorial, char &potencia, char &reset, char &salir, char &simplificacion, ifstream &archivo3)
{
	char aux;

	archivo3 >> aux;
	suma = aux;
	archivo3 >> aux;
	restar = aux;
	archivo3 >> aux;
	producto = aux;
	archivo3 >> aux;
	division = aux;
	archivo3 >> aux;
	factorial = aux;
	archivo3 >> aux;
	potencia = aux;
	archivo3 >> aux;
	raiz = aux;
	archivo3 >> aux;
	reset = aux;
	archivo3 >> aux;
	salir = aux;
	archivo3 >> aux;
	simplificacion = aux;

}

void fcase2(ofstream &archivo, char salir, bool terminar1, char suma, char restar, char producto, char division, char potencia, char simplificacion, char reset, int num1, char simbolo, char operador, int den1, int num2, int den2)
{
	terminar1 = false;
		cout << "Introduzca una expresion aritmetica (sin espacios) (x para teminar)" << endl;
		    cout << suma << ": suma  " << restar << ": resta  " << producto << ": producto  "<< division << ": division  " << potencia << ": potencia  " << simplificacion << ": simplificacion " << endl;
			cout << reset << ": reset  "<< endl;
         while(!terminar1){
			cout << "Introduzca una expresion aritmetica (sin espacios)" << endl;
			do{
				if(isdigit(cin.peek())){
					cin >> num1;
					if(cin.peek() == simbolo){ 
						cin.get();
						cin >> den1;
					}else{ den1 = 1; }
				}
				operador = cin.get();
				if(operador != simplificacion && operador != reset && operador != salir && operador != potencia  && operador != '\n'){
					cin >> num2;
					if(cin.peek() == simbolo){ 
						cin.get();
						cin >> den2;
					}else{ den2 = 1; }
				}
				if(operador == suma){
					num1 = num1 * den2 + num2 * den1;
					den1 = den1 * den2;
				}else if(operador == restar){
					num1 = num1 * den2 - num2 * den1;
					den1 = den1 * den2;
				}else if(operador == producto){
					num1 = num1 * num2;
					den1 = den1 * den2;
				}else if(operador == division){
					num1= num1 * den2;
					den1 = den1 * num2;	
				}else if(operador == potencia){
					cin >> num2;
					potencial(num1, den1, num2, archivo);
				}else if(operador == simplificacion){
					reducir(num1, den1);
				}else if(operador == reset){
					num1 = 0;
					den1 = 1;
				}else if(operador == salir){
					terminar1 = true;
				}
			}while(operador != '\n' );
			if(!terminar1){ cout << num1 << "|" << den1 << endl; }
			cin.sync();
		 }	//Fin while
}
