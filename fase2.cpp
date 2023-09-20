/**
 * Proyecto 2 - fase 2
 * Temario 11: Tiempo de conteo de votos por departamento
 * Integrantes: - Francis Aguilar #22243
 *              - Angela Garcia #22869
 *              - Diego Garcia #22404         
 *              - Jose Rodriguez #21060
 * 
 * Implementar concepto de hilos, loops paralelos, hilos privados, allocate y reduction, 
 * 
 * **/

//librerias 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>     //cout, cin, endl
#include <pthread.h>	//pthread_
#include <omp.h>
#include <ctime>

//esto es lo de allocate que es lo de new, para como asignar los cosos en la memoria
    int *votos; 


using namespace std; //para no escribir en todo std::
clock_t start_t, end_t;

//----funciones----

//metodo tipo unsigned, porque de esta forma solo acepta 0 y numeros positivos 
unsigned int Votos(unsigned int NDepartamentos){    
    
    int VotoT=0;
    int VotoDt=0;
    votos = new int[NDepartamentos]; //Crear arreglo
    string departamentos[] = {"Alta Verapaz", "Baja Verapaz", "Chimaltenango", "Chiquimula", "El Progreso", "Escuintla", "Ciudad de Guatemala", "Huehuetenango", "Izabal",
        "Jalapa", "Jutiapa", "Peten", "Quetzaltenango", "Quiche", "Retalhuleu", "Sacatepequez", "San Marcos", "Santa Rosa", "Solola", "Suchitepequez", "Totonicapan", "Zacapa"
    };
    
    string *departamentos_dir; // se declara el puntero 
    departamentos_dir = &departamentos[0]; // el puntero apunta al primer elemento del array 
    
    

    #pragma omp parallel for ordered
    for (int i=0; i <NDepartamentos; ++i){
        #pragma omp ordered
        std::cout << "Thread " << omp_get_thread_num() << " is processing iteration " << i << std::endl;
    
        start_t = clock(); //Se activa el contador de tiempo después de haber pedido los votos que hubo en cada departamento

        #pragma omp critical
            {
                //pedir el numero de votos del departamento 
                //VotoDt
                cout<<"Ingrese el valor total de votos de "<< *departamentos_dir <<": ";
                departamentos_dir++;
                cin>>VotoDt;
                //VotoT += VotoDt; //esto no deberia de estar asi
                //aqui es donde se supone que guarda los votos en el array
                votos[i] = VotoDt;
                
            }
        
        }

    end_t = clock(); //Se termina el conteo del tiempo


    //la suma de todos los votos del vector (no lo he probado, xq falta lo de allocate, pero tengo fe)

    #pragma omp parallel for reduction(+:VotoT)
    for (int i = 0; i < NDepartamentos; ++i) {
        VotoT += votos[i]; // Sumar todos los votos
    }
    

    return VotoT;

}



//----main----
int main(){

	double total_t;

    int NumDepartamentos = 22;
    //supongo que aquí va lo del tiempo jijija
    cout << "xd "<< Votos(NumDepartamentos) << endl;

    total_t = difftime(end_t,start_t)/CLOCKS_PER_SEC;
    cout << "Tiempo de trabajo: " << total_t << endl;
    delete[] votos;

    //mostrar el tiempo 
    return 0;

}
