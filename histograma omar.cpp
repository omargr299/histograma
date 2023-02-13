#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>


#define MAXNUMS 5 //Constante quye deifne la cantidad maxima de datos a ingresar

using namespace std;

void sort(int nums[], int tam){
    int aux;
    for(int i=0; i<tam-1; i++){

        for (int j = i+1; j < tam; j++)
        {
            if(nums[i]<=nums[j]) continue;

            aux = nums[i];
            nums[i] = nums[j];
            nums[j] = aux;
        }

    }

}

string h(int nums[], int cantidad, int mayor){

    string grafica = "";

    grafica += "Horizontal\n";
    for(int i=0; i<cantidad; i++){ // filas
        
        grafica += to_string(nums[i]) + " "; // escribimos el dato al inicio de cada fila
        
        for(int j=0;j<mayor;j++){ // columnas

            // escribimos el numero de asteriscos que nos indica el dato
            if(j < nums[i])
                grafica += "*";
        }

      if(i<cantidad-1) grafica += "\n";
    }

    return grafica;
}

int Espacios(int numero){
    int espacios = 0;
    if (numero<10) return 0;
    numero/=10;
    for (; numero>0; numero/=10)
    {
        espacios++;
    }

    return espacios;
}

string v(int nums[], int cantidad, int mayor){

    string grafica = "";

    grafica += "Vertical\n";

    for(int i=mayor; i>=0; i--){ //fila

        for(int j=0;j<cantidad;j++){ // columnas

            if(i == 0)  // al final de cxada columna escribimos el dato
                grafica += to_string(nums[j]);
            else{
                // escribimos el numero de asteriscos que nos indica el dato
                for (int k = 0; k < Espacios(nums[j]); k++)
                {
                    grafica+=" ";
                }
                
                
                if (i <= nums[j])
                    grafica += "*";
                else
                    grafica += " ";

            }

            if(j<cantidad-1) grafica += " ";
        }
        if(i>0) grafica += "\n";

    }
    return grafica;
}

void EscribirArchivo(string grafica){
    ofstream file;

    file.open(".\\histograma.txt");
    file << grafica;
    file.close();
}

string Graficar(int nums[], int cantidad, int mayor){
    int opcion;
    string respuesta,grafica;
    opcion = 0;
    while (opcion!=3)
    {
        // le pedimos al usuairo de que manera quiere graficar sus datos
        system("cls");
		cout<<"-----------HISTOGRAMA---------"<<endl;
		cout<<"Elige el tipo de grafica"<<endl;
		cout<<"1.-Vertical"<<endl;
		cout<<"2.-Horizontal"<<endl;
		cout<<"3.-Volver al menu"<<endl;
		cout<<"Como deseas imprimir la grafica? ";
		cin>>respuesta;

        try{
            opcion = stoi(respuesta,NULL,10);
        }
        catch(const exception& e){
            opcion = 0;
        }

        switch (opcion) // analizamos la opcion que pidio el usuario y la relaizamos
        {
            case 1: // manera verticar
                system("cls");
                grafica = v(nums,cantidad,mayor);
                return grafica;
                break;

            case 2: //manera horizonatla
                system("cls");
                grafica = h(nums,cantidad,mayor);
                return grafica;
                break;

            case 3: // volvemos al menu
                break;

            default: // para todas loas opciones que no sean las anteriores
                system("cls");
                cout << "Opcion no disponible" << endl << "Por favor eliga una opcion de las que estan en el menu" << endl;
                system("pause");
                break;
            }
    }
}

int checkH(string nombre,int numeros[], int *cantidad, int *mayor){
    ifstream archivo(nombre);
    string linea;
    getline(archivo,linea);

    int numlinea=0;
    int cuenta = 0;

    while (!archivo.eof()) { 
        archivo >> linea;  
        try{
           if(!(numlinea%2) )
            {   
                numeros[cuenta] = stoi(linea,nullptr,10); 
                if (numeros[cuenta] > *mayor) 
                    *mayor = numeros[cuenta];

                cuenta++; 
                *cantidad = cuenta;}
            else{
                if (linea.length()!=numeros[cuenta-1]) throw 1;
            }
        }
        catch(const exception& e){
            return 1;
        }
        catch(int e){
            return e;
        }
        numlinea++;

    }

    return 0;
}

int checkV(string nombre,int numeros[], int *cantidad, int *mayor){
    ifstream archivo(nombre);
    string linea,copia;
    char anterior;
    getline(archivo,linea);

    int numlinea=0;
    int cuenta = 0;

    *cantidad = 0;
    int pos = 0;
    int espacios= 0;

    while (!archivo.eof()) { 
        getline(archivo,linea);
        if(numlinea>0 && *cantidad!=linea.length()) return 1;

        
        
        *cantidad = linea.length();
        for(char c : linea){
            if(pos < *cantidad) copia = linea.substr(pos,pos+1);
            
            if(c!=' ' && c!='*' && (int)anterior<48 || (int)anterior>57){
                try{
                    numeros[cuenta] = stoi(copia,nullptr,10); 
                    pos+=2;
                    pos+=Espacios(numeros[cuenta]);
                    if(pos < *cantidad) copia = linea.substr(pos,pos+1);
    

                    if (numeros[cuenta] > *mayor) 
                        *mayor = numeros[cuenta];

                    cuenta++;
                }
                catch(const exception& e){
                    return 1;
                }
            }
            anterior = c;
        }
        numlinea++;
    }

    espacios= 0;
    for (int i = 0; i<cuenta; i++)
    {
        espacios += Espacios(numeros[i]);
    }

    if(*cantidad != cuenta+(cuenta-1)+espacios) return 1;
    *cantidad = cuenta;

    archivo.close();
    archivo.open(nombre);
    getline(archivo,linea);

    int col = 0, num=0;
    cuenta = 0;
    numlinea--;
    anterior=' ';
    while (!archivo.eof()) { 

        getline(archivo,linea);
        if(numlinea<=0) continue;
        
        for(char c : linea){

            if(col%2){
                if(c!=' ') return 1;
            }
            else{
                if(numlinea>numeros[cuenta] && c!=' ') return 1;
                if(numlinea<=numeros[cuenta] && c!='*') return 1;
                cuenta++;
                espacios = Espacios(numeros[cuenta]);
            }
            
            if(espacios==0 || !(col%2)) 
                col++;
            else
                espacios--;
                
            anterior = c;
        }
        col = 0;
        cuenta = 0;
        numlinea--;
    }

    return 0;
}

int LeerArchivo(int numeros[], int *cantidad, int *mayor){
    string nombre, linea,graf;
    int cuenta = 0;
    *mayor = 0 ; *cantidad=0;

    cout << "Ingresa el nombre del archivo: "; 
    cin >> nombre; 

    nombre = "./" + nombre + ".txt";
    ifstream archivo(nombre);
    
    int num=0,numlinea=0,modo=0;
    string tipo;
    archivo >> tipo;

    if(tipo=="Horizontal") modo=1;
    else if(tipo=="Vertical") modo=0;
    else return 1;
    
    system("cls");
    string grafica;
    if (modo) {
        if(checkH(nombre,numeros,cantidad,mayor)) return 1;
        grafica = h(numeros,*cantidad,*mayor);
        }
    else {
        if(checkV(nombre,numeros,cantidad,mayor)) return 1;
        grafica = v(numeros,*cantidad,*mayor);
        }
    cout << grafica << endl;
    archivo.close(); 
    return 0;
}


void PedirDatos(int numeros[], int *cantidad, int *mayor){
    string numero;
    int cuenta;

	cout<< "------ Pedir datos ------" <<endl;
cuenta =0;
    while(cuenta < MAXNUMS) // pedimos lo datos al usuario uno por uno
    {
        try
        {
            cout << "Ingresa el valor " << cuenta+1 << ": ";
            cin >> numero; // alamacenamos los datos

            numeros[cuenta] = stoi(numero,nullptr,10); // convertimos de string a int en base 10

            if (numeros[cuenta] > *mayor) // comprobamos que dato es mayor
                *mayor = numeros[cuenta];

            cuenta++; // llevamos la cuenta de los datos almacenados
            *cantidad = cuenta;
        }
        catch(const exception& e)
        {
            cout << "XXX Ingresa unicamente valores numericos XXX" << endl; // si el usairo ingreso un dato no numerico tonanos el error y le avismaos
        }

    }

}

int main(int argc, char const *argv[])
{
    int numeros[MAXNUMS], cuenta = 0, mayor = 0, opcion=0, error=0;
    string respuesta,grafica;

    opcion = 0;
    while (opcion!=3) // ciclo para las opciones
    {
        mayor = cuenta = 0;
        system("cls");
		cout<<" ------------------MENU---------------"<<endl;
		cout<<"1.-Realizar un nuevo histograma"<<endl;
		cout<<"2.-Leer documento"<<endl;
		cout<<"3.-Salir del programa"<<endl;
		cout<<"Que opcion deseas? ";
		cin>>respuesta;

        try{
            opcion = stoi(respuesta,NULL,10);
        }
        catch(const exception& e){
            opcion = 0;
        }

        switch (opcion) // analizamos la opcion que pidio el usuario y la relaizamos
        {
            case 1:
                system("cls");
                PedirDatos(numeros,&cuenta,&mayor); //tomamos los datos
                sort(numeros,cuenta);
                system("cls");
                grafica = Graficar(numeros,cuenta,mayor); // los graficamos
                cout << grafica << endl;
                EscribirArchivo(grafica); // Escribimos los datos en un archivo
                system("pause");
                break;

            case 2:
                system("cls");
                cout << endl << "------- Lectura de arcivo -------" << endl;
                error = LeerArchivo(numeros,&cuenta,&mayor); // Leemos un archivo
                if (error) cout << "XXX EL archivo esta corrupto XXX" << endl;
                system("pause");
                break;

            case 3:
                // Se termina el programa
                system("cls");
                cout << endl << "----- Gracias vuelva pronto -----" << endl;
                system("pause");
                break;

            default:
                // Todo lo que no sea las opciones anteriores
                system("cls");
                cout << endl <<"xxx Opcion no disponible. Por favor eliga una opcion de las que estan en el menu" << endl << endl;
                system("pause");
                break;
}
    }

}