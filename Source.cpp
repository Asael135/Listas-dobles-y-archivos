#include<iostream>
#include<conio.h>
#include<fstream>//libreria para gestioanar la entrada y salida de archivos//
#include<Windows.h>


//--PARA QUE ESTE PTOYECTO JALE TIENES QUE: configuracion > propiedades>character set > cambiar de unicode a mulibit//
//esto hara que sea incluso mas facil de trabajar sin las conversiones de winapi//

using namespace std;

//decalracion de el nodo de la lista//
struct nodoPasajeros {
    nodoPasajeros* anterior;
    char nombre[40];
    int pasaporte;
    char nacionalidad[20];
    nodoPasajeros* siguiente;
};

//DECLARACION DE LOS PUNTEROS GOBALES NECESARIOS PARA RECORRER LAS LISTAS Y NO PERDER EL INICIO//

nodoPasajeros* inicioPasajeros = nullptr;//para no perder le incio de la lsita//
nodoPasajeros* finPasajeros = nullptr;//marca del final de la lista//
nodoPasajeros* actualPasajeros = nullptr;//este puntero es que se iguala a inicio para comenzar a recorrero o modificar los datos//

//DECLARACION DE LAS FUNCIONES PARA OPERAR EN LA LISTA//

void agregarPasajero(nodoPasajeros* nuevo) {//se agrega un pasajero mandando como parametro el nodo creado
    //agregar a la lista
    if (inicioPasajeros == nullptr)//si la lista esta vacia
    {
        inicioPasajeros = nuevo;
        finPasajeros = nuevo;//el incicio y el fin son el mismo porque solo hay uno
    }
    else {
        finPasajeros->siguiente = nuevo;
        nuevo->anterior = finPasajeros;
        finPasajeros = nuevo;
    }

}

void capturaPasajeros(nodoPasajeros* nodo) {//agregamo sel nuevo pasajero mandando como parametro un nodo al cual accedemos a cada una de sus declaraciones
    system("cls");
    cout << "--CAPTURA DE PASAJERO--\n";
    cout << "Pasaporte: "; cin >> nodo->pasaporte;
    cout << "Nombre: "; cin >> nodo->nombre;
    cout << "Nacionalidad: "; cin >> nodo->nacionalidad;
}

void eliminarPrimerPasajero() {
    actualPasajeros = inicioPasajeros;
    if (inicioPasajeros != nullptr)//si la lista no esta vacia
    {
        if (inicioPasajeros == finPasajeros)//si solo hay un elemento en la lista
        {
            inicioPasajeros = nullptr;
            finPasajeros = nullptr;//desligamos los punteros
        }
        else
        {
            inicioPasajeros = actualPasajeros->siguiente;
            inicioPasajeros->anterior = nullptr;//reajustamos punteros
        }

        delete actualPasajeros;//borras el nodo
    }

}

void eliminarUltimoPasajero() {
    actualPasajeros = finPasajeros;
    if (finPasajeros != nullptr)//si la lista no esta vacia
    {
        if (inicioPasajeros == finPasajeros)//si solo hay uno
        {
            inicioPasajeros = nullptr;
            finPasajeros = nullptr;//desligamos los punteros
        }
        else
        {
            finPasajeros = actualPasajeros->anterior;
            finPasajeros->siguiente = nullptr;//reajustamos punteros
        }

        delete actualPasajeros;//borras el nodo
    }

}

void eliminarPasajero() {
    if (actualPasajeros == inicioPasajeros)//si el que vas a borrar es el primero
    {
        eliminarPrimerPasajero();
    }
    else
    {
        if (actualPasajeros == finPasajeros)//si el que vas a borrar es el ultimo
        {
            eliminarUltimoPasajero();
        }
        else
        {
            actualPasajeros->anterior->siguiente = actualPasajeros->siguiente;
            actualPasajeros->siguiente->anterior = actualPasajeros->anterior;//reajustamos punteros de un nodio en medio de la lista
            delete actualPasajeros;//borramos
        }
    }
}


void limpiarLista() {//para liberar la memoria despues de guardar en el archivo
    system("cls");

    nodoPasajeros* nodoAEliminar = inicioPasajeros;//puntero del tipo nodo pasajeros

    while (nodoAEliminar != nullptr)//mientras el nodo no sea el ultimo
    {
        nodoPasajeros* nodoSiguiente = nodoAEliminar->siguiente;
        delete nodoAEliminar;
        nodoAEliminar = nodoSiguiente;//vas avanzando y borrando el anterior
    }

    inicioPasajeros = nullptr; // Actualizar el puntero de inicio
    actualPasajeros = nullptr; // Asegurarse de que el puntero actual también se actualiza

    cout << "MEMORIA LIMPIA Y ARCHIVO GUARDADO\n";
    system("PAUSE>NULL");
}

//--AHOR ASI YA JALA LO QUE EL SEMESTRE PASADO NO, MALDITA SEA QUE EMOCION--//  
//(Leer declaraciones de variables en el main parar entender)//

void LeerDelArchivo(char archivo[]) {//mandamos como parametro la direccion que ya creamos
    ifstream archivoALeer(archivo, ios::binary);//varivale local, le especifico que la ruta del archivo que quiero abrir y que lo queiro abrir en modo binario
    if (archivoALeer.is_open())//si se abrio
    {
        nodoPasajeros* nuevo = new nodoPasajeros;//creas tu nodo
        archivoALeer.read((char*)nuevo,sizeof(nodoPasajeros));//lees del archivo en el nodo especificando el tamaño de bytes del la decalracion
        nuevo->anterior = nullptr;
        nuevo->siguiente = nullptr;//se ajsutan punteros
        
        while (!archivoALeer.eof())//mientras no se llegue al final del archivo
        {
            agregarPasajero(nuevo);//agregamos nuevo pasajero
            nuevo = new nodoPasajeros;//creando nuevos nodos
            archivoALeer.read((char*)nuevo, sizeof(nodoPasajeros));//seaparando memorias
            nuevo->anterior = nullptr;
            nuevo->siguiente = nullptr;//ajustando el archivo
        }
        archivoALeer.close();//cuand llego al final del archivo lo cerramos
        cout << "ARCHIVO CARGADO COMPLETO\n";
    }
    else
    {
        cout << "No se pudo leer el archivo\n";
    }
    
}

void escribeEnElArchivo(char archivo[]) {//mandamos como parametro la direccion que ya creamos

    ofstream archivoAEscribir;//vsriable local del tipo ofstream
    archivoAEscribir.open(archivo, ios::binary | ios::trunc);
    //lo abrimos mandando como aprametro la direccion, que lo que quiero abrir como bianrio, que quiero que se sobreescriba completo
    
    if (archivoAEscribir.is_open())//si se abrio
    {
        actualPasajeros = inicioPasajeros;
        while (actualPasajeros!=nullptr)//recorremos toda la lista
        {
            archivoAEscribir.write((char*)actualPasajeros,sizeof(nodoPasajeros));
            //escribimos nodo por nodo separando en espaciolos bytes de nuestra declaracion completa

            actualPasajeros = actualPasajeros->siguiente;
        }

    }
    else
    {
        cout << "El archivo no se pudo abrir\n";
    }
}



int main() {

    char carpeta[MAX_PATH] = "";//variable tipo char con el numero maximo de caracteres que pude contener 
    char archi[] = "\\pasajeros.bin";//declaracion del archivo
    GetCurrentDirectory(MAX_PATH, carpeta);//funcion magica para obtener el directorio de trabajo actual, a mi carpeta se le asigna mi directorio actual
    strcat_s(carpeta, archi);//entonces se concatena todo y tienes la ubicacion exacta del archivo, que maravilla
    int pasaporte_a_buscar = 0;
    short opc = 0, _opc = 0;
    bool encontrado = false;

    printf("%s", carpeta);
    //C:\Users\Asael\OneDrive\Escritorio\C++ CODE\Listas Ligadas y Guardar en archivos\pasajeros.bin
    //ejemplo de como se concateno todo, que maravilla

    LeerDelArchivo(carpeta);//leemos del archivo especific de pasajeros .bin

    do
    {
        system("cls");
        cout << "SISTEMA DE PASAJEROS\n";
        cout << "1.Agregar pasajero\n";
        cout << "2.Remover primer pasajero\n";
        cout << "3.Remover ultimo pasajero\n";
        cout << "4.Buscar Pasajero\n";
        cout << "5.Lista de pasajeros\n";
        cout << "6.Lista de pasajeros inversa\n";
        cout << "7.sALIR\n";
        cin >> opc;

        switch (opc)
        {
        case 1:
        {

            actualPasajeros = new nodoPasajeros;//se reserva un espacio en memoria para el nodo//
            actualPasajeros->anterior = nullptr;
            actualPasajeros->siguiente = nullptr;
            capturaPasajeros(actualPasajeros);//mandamos aa funcion capturar(donde se pone el nombre etc...) mandando como parametro el nodo actual que es igual a un nodo creado//
            agregarPasajero(actualPasajeros);//despues de capturarlo lo mandamos a la funcion de agregar donde revisamos si la lsita esta vacia o no y esas validaciones;
            cout << "Pasajero agregado\n";


        }break;
        case 2:
        {//borrar como si fuera cola
            eliminarPrimerPasajero();
            cout << "Primer pasajero eliminado\n";

        }break;
        case 3:
        {//borrar como si fuera pila
            eliminarUltimoPasajero();
            cout << "Ultimo pasajero elimiando\n";
        }break;
        case 4:
        {//buscar
            encontrado = false;
            system("cls");
            cout << "Captura de pasaporte para buscar: \n";
            cin >> pasaporte_a_buscar;
            actualPasajeros = inicioPasajeros;
            while (actualPasajeros != nullptr)
            {
                if (actualPasajeros->pasaporte == pasaporte_a_buscar)
                {
                    encontrado = true;
                    break;
                }
                actualPasajeros = actualPasajeros->siguiente;

            }
            if (encontrado)
            {
                cout << "Nombre: "; cout << actualPasajeros->nombre << endl;
                cout << "Nacionalidad: "; cout << actualPasajeros->nacionalidad << endl;
                cout << "Pasaporte: "; cout << actualPasajeros->pasaporte << endl;
                cout << "Desea 1)Modificar 2)Eliminar\n";
                cin >> _opc;
                if (_opc == 1)
                {
                    capturaPasajeros(actualPasajeros);
                    cout << "Datos modificados";
                }
                if (_opc == 2)
                {
                    eliminarPasajero();
                    cout << "Pasajero eliminado\n";
                }

                cout << "Pasajero encontrado\n";
            }
            else
            {
                cout << "No existe pasajero\n";
            }
        }break;
        case 5:
        {
            system("cls");
            actualPasajeros = inicioPasajeros;
            cout << "NOMBRE PASAJERO-PASAPOTE-NACIONALIDAD\n";
            while (actualPasajeros != nullptr)
            {
                //mostrar el nodo//
                cout << actualPasajeros->nombre << " , " << actualPasajeros->pasaporte << " , " << actualPasajeros->nacionalidad << endl;

                actualPasajeros = actualPasajeros->siguiente;
            }
            cout << "Fin de la lista\n";
            system("PAUSE>NULL");

        }break;
        case 6:
        {
            system("cls");
            actualPasajeros = finPasajeros;
            cout << "NOMBRE PASAJERO-PASAPOTE-NACIONALIDAD\n";
            while (actualPasajeros != nullptr)
            {
                //mostrar el nodo//
                cout << actualPasajeros->nombre << " , " << actualPasajeros->pasaporte << " , " << actualPasajeros->nacionalidad << endl;

                actualPasajeros = actualPasajeros->anterior;
            }
            cout << "Fin de la lista\n";
            system("PAUSE>NULL");

        }break;


        }





    } while (opc < 7);

    escribeEnElArchivo(carpeta);//se pasa como parametro al direccion del archivo pasajeros.bin


    limpiarLista();



    return 0;
}
