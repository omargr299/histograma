#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>

#define MAXNUMS 5 //Constante quye deifne la cantidad maxima de datos a ingresar

using namespace std;

void sort(int nums[], int tam){// funcion que ordena los datos de menor a mayor
    int aux;
    for(int i=0; i<tam-1; i++){ // ciclo para recorrer el arreglo de datos hasta el penultimo dato

        for (int j = i+1; j < tam; j++) // ciclo para recorrer el arreglo de datos del segundo hasta el ultimo dato
        {
            if(nums[i]<=nums[j]) continue; // condicion que compara un dato con el que le sigue

            // si el dato es mayor al que le sigue se intercambian la posicion
            aux = nums[i];
            nums[i] = nums[j];
            nums[j] = aux;
        }

    }

}

string h(int nums[], int cantidad, int mayor){ // funcion para graficar el hsitograma de manera horizontal

    string grafica = ""; // aqui se guadar la grafica

    grafica += "Horizontal\n"; // se le agrega un titulo
    for(int i=0; i<cantidad; i++){ // filas

        grafica += to_string(nums[i]) + " "; // escribimos el dato al inicio de cada fila

        for(int j=0;j<mayor;j++){ // columnas

            // escribimos el numero de asteriscos que nos indica el dato
            if(j < nums[i])
                grafica += "*";
        }

      if(i<cantidad-1) grafica += "\n"; // se le agrega un slato de linea despues deagreagar una fila de datos
    }

    return grafica; // se regresa la grafica
}

int Espacios(int numero){ // grafica para contar los espacios que va a ocupar un dato en la grafica
    int espacios = 0; 

    if (numero<10) return 0; // regresa 0 si el numero es menor a 10
    
    numero/=10;
    for (; numero>0; numero/=10) // ciclo que cuenta los espacios que va ocupar un numero
        espacios++;
    

    return espacios; // regresa el numero de espacios
}

string v(int nums[], int cantidad, int mayor){ // funcion para graficar el hsitograma de manera vertical

    string grafica = ""; // aqui se guadar la graficas

    grafica += "Horizontal\n"; // se le agrega un titulo

    for(int i=mayor; i>=0; i--){ //fila

        for(int j=0;j<cantidad;j++){ // columnas

            if(i == 0)  // al final de cxada columna escribimos el dato
                grafica += to_string(nums[j]);
            else{
                // escribimos el numero de asteriscos que nos indica el dato

                for (int k = 0; k < Espacios(nums[j]); k++) // ciclo para agregar espacios si el numero es mayor a 9
                {
                    grafica+=" ";
                }

                // escribimos el numero de asteriscos o espacios que nos indica el dato
                if (i <= nums[j]) 
                    grafica += "*";
                else
                    grafica += " ";

            }

            if(j<cantidad-1) grafica += " "; // se agrega un espacio para separar las columnas
        }
        if(i>0) grafica += "\n"; // se le agrega un slato de linea despues deagreagar una fila de datos

    }
    return grafica; // se regresa la grafica
}

void EscribirArchivo(string grafica){ // funcion que escribe el histograma en un archivo de texto
    ofstream file; // archivo en el que escribe el histograma

    file.open(".\\histograma.txt"); // abre o crea el archivo depiendo si existe o no
    file << grafica; // escribe la grafica
    file.close(); // cierra el archivo
}

string Graficar(int nums[], int cantidad, int mayor){ // funcion que pregunta de que manera quieres graficar el hsitograma
    int opcion;
    string respuesta,grafica;
    opcion = 0;

    // ciclo en el que se pregunta la manera quiere 
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
            opcion = stoi(respuesta,NULL,10); // comprueba que hayas ingresado un numero
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
    return " ";
}

int checkH(string nombre,int numeros[], int *cantidad, int *mayor){ //funcion que comprueba que la grafica horizontal no este corrupta
    // obtenemos el archivo y nos saltamos el titulo
    ifstream archivo(nombre);
    string linea;
    getline(archivo,linea);

    int numlinea=0; // lleva la cuenta de los renglones que hemos leido
    int cuenta = 0; // lleva la cuenta de los datos que hemos leido

    // ciclo que va leyendo el archivo hasta que se termine
    while (!archivo.eof()) {
        archivo >> linea; // leemos un renglon del archivo
        try{
           if(!(numlinea%2) ) // comprobamos que estamos leyendo la columna de datos
            {
                numeros[cuenta] = stoi(linea,nullptr,10); // comprabamos que todos los datos sean numericos
                if (numeros[cuenta] > *mayor) // obtnemos el dato mayor
                    *mayor = numeros[cuenta];

                cuenta++; // aumentamos la cuenta de los datos leidos
                *cantidad = cuenta; 
            }
            else{ // si no estamos leyendo la columna de asteriscos
                if ((int)linea.length()!=numeros[cuenta-1]) throw 1; // si no hay la cantidad de asteriscos que marca el dato leido lanzamos un error
            }
        }
        catch(const exception& e){ // error si no coinciden el numero de asteriscos con el dato
            cout << "no coinciden las barras con los datos";
            return 1;
        }
        catch(int e){ // error si algun dato no es numerico
            cout << "todos los datos deben ser numericos";
            return e;
        }
        numlinea++; // aumentamos la cuenta de los renglones leidos

    }

    return 0; // todo salio bien
}

int checkV(string nombre,int numeros[], int *cantidad, int *mayor){ //funcion que comprueba que la grafica vertical no este corrupta
    // obtenemos el archivo y nos saltamos el titulo
    ifstream archivo(nombre);
    string linea,copia;
    char anterior = 0;
    getline(archivo,linea);

    int numlinea=0; // lleva la cuenta de los renglones que hemos leido
    int cuenta = 0; // lleva la cuenta de los datos que hemos leido

    *cantidad = 0; //cantidad final de datos
    int pos = 0; // columna en la que te encuentras
    int espacios= 0; // cantidad de espacios que hay entre columnas

    // ciclo que va leyendo el archivo hasta que se termine para obtener los datos
    while (!archivo.eof()) {
        getline(archivo,linea); //leemos un renglon del archivo

        if(numlinea>0 && *cantidad!=(int)linea.length()) return 1; // combramos que todas los renglones se la misma longitud

        *cantidad = linea.length(); // obtenemos la longitd del renglon actual para comapralo despues
        
        for(char c : linea){// ciclo que va revisando todos los carcteres de cada renglon
            if(pos>0 && pos < *cantidad) copia = linea.substr(pos,pos+1); // obtemos un copia del renglo
            else copia = linea; // si es la ultima simplemnte copiamostodo

            if(c!=' ' && c!='*' && ((int)anterior<48 || (int)anterior>57)){ // compramos que le caracter actual no sea un espacio un asterisco y que no le anteceda un numero
                try{
                    numeros[cuenta] = stoi(copia,nullptr,10); // comprabmos que el caracter actual sea un numero
                    pos+=2; // avanzamos dos posiciones para leer el siguiente dato
                    pos+=Espacios(numeros[cuenta]); // compramos si el dato es mayor a 9 y los espacios que ocupa
                    if(pos < *cantidad) copia = linea.substr(pos,pos+1); // si aun quedan datos por leer recortamos el renglon


                    if (numeros[cuenta] > *mayor) // obtenmos el dato mayor
                        *mayor = numeros[cuenta];

                    cuenta++; // aumentamos la cuenta de los datos leidos
                }
                catch(const exception& e){ // error si un dato no es numerico
                    return 1;
                }
            }
            anterior = c; // guardamos el caracter para despues
        }
        numlinea++; // aumentamos la cuenta de los renglones que hemos leido
    }

    espacios= 0; // resteamos la cantidad de espacios
    for (int i = 0; i<cuenta; i++) // obtemos la cantidad total de espacios que tienen los renglones
    {
        espacios += Espacios(numeros[i]);
    }

    if(*cantidad != cuenta+(cuenta-1)+espacios) return 1; // comporbamos que la cantidad de espacios sean correctos
    *cantidad = cuenta; // guardamos la cuenta de cuantos datos llebamos
    archivo.close(); // cerramos el archivo

    archivo.open(nombre); // abrimos neuevamente el archivo para que empiece desde el principio
    getline(archivo,linea);

    int col = 0; // nos dice la columna en la que estamos
    // reseatmos las cuentas 
    cuenta = 0;
    numlinea--;
    anterior=' ';

    // ciclo que va leyendo el archivo hasta que se termine para comprobar que el formato este correcto 
    while (!archivo.eof()) {

        getline(archivo,linea); //leeemos un renglon
        if(numlinea<=0) continue; // comprobamos que no estemos en la linea final

        espacios=Espacios(numeros[0]); // contamos los espacios que ocupa el primer dato
        for (int i = espacios; i > 0; i--) // nos preparamos para saber cuantos espacios hay al inicio
            col--;

        for(char c : linea){ // ciclo que va revisando todos los carcteres de cada renglon
            if((col%2 || col < 0) && espacios>0 ){ // compramos que estemos en una de espacios
                if(c!=' ') return 1; // si el caracter no es un espacio lanzamos un error
                espacios--;
            }
            else{ // si no es una columna de dato
                // comprobamos que la columna tenga el numero correcto de asteriscos
                if(numlinea>numeros[cuenta] && c!=' ') return 1; // comprobamos que el caracter no sea un espacio
                if(numlinea<=numeros[cuenta] && c!='*') return 1; // comprobamos que el caracter no sea un espacio
                cuenta++;
                espacios = Espacios(numeros[cuenta])+1;
            }

            if(espacios==0 || !(col%2) || col<0) // comprobamos que no estemos en una columna de espacios para avanzar
                col++;

            anterior = c;
        }
        col = 0;
        cuenta = 0;
        numlinea--;
    }

    return 0; // todo termino bien
}

int LeerArchivo(int numeros[], int *cantidad, int *mayor){ // funcion para leer el archivo
    string nombre, linea,graf;
    *mayor = 0 ; *cantidad=0;

    cout << "Ingresa el nombre del archivo: "; // obtemos el nombre del archivo
    cin >> nombre;

    nombre = "./" + nombre + ".txt"; // le damos el formato correcto
    ifstream archivo(nombre);  // obtenemos el archivo

    int modo=0;
    string tipo;
    archivo >> tipo; // leemos el titulon para saber que tipo de hgrafica es

    // vemos que tipo es la grafica
    if(tipo=="Horizontal") modo=1;
    else if(tipo=="Vertical") modo=0;
    else return 1; // si no es niguno de estos lanzamos un error

    system("cls");
    string grafica;
    // mandamos acomprobar si el formato esta correcto
    if (modo) {
        if(checkH(nombre,numeros,cantidad,mayor)) return 1; // si no esta correcto lanzamos un error
        grafica = h(numeros,*cantidad,*mayor); // mandamos a graficar
        }
    else {
        if(checkV(nombre,numeros,cantidad,mayor)) return 1; // si no esta correcto lanzamos un error
        grafica = v(numeros,*cantidad,*mayor); // mandamos a graficar
        }
    cout << grafica << endl;
    archivo.close(); // cerramos el archivo
    return 0;
}


void PedirDatos(int numeros[], int *cantidad, int *mayor){ // funcion para pedir los datos
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
        catch(const exception& e) // error si un dato no es numerico
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
    system("cls");

}
