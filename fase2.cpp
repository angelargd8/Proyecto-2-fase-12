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
#include <time.h>

using namespace std; //para no escribir en todo std::

//----funciones----

//metodo tipo unsigned, porque de esta forma solo acepta 0 y numeros positivos 
unsigned int Votos(unsigned int NDepartamentos){    
    
    int VotoT=0;
    int VotoDt=0;
    
    //esto es lo de allocate que es lo de new, para como asignar los cosos en la memoria
    int* votos=new int[NDepartamentos]; //no se si esta bien, alguien revise xd


    #pragma omp parallel for ordered
    for (int i=0; i <NDepartamentos; ++i){
        #pragma omp ordered
        std::cout << "Thread " << omp_get_thread_num() << " is processing iteration " << i << std::endl;
    
        #pragma omp critical
            {
                //pedir el numero de votos del departamento 
                //VotoDt
                cout<<"Ingrese el valor total de votos del departamento: ";
                cin>>VotoDt;
                VotoT += VotoDt; //esto no deberia de estar asi
                //aqui es donde se supone que guarda los votos en el array

                
            }
        
        }



    //la suma de todos los votos del vector (no lo he probado, xq falta lo de allocate, pero tengo fe)

    /*#pragma omp parallel for reduction(+:VotoT)
    for (int i = 0; i < NDepartamentos; ++i) {
        VotoT += votos[i]; // Sumar todos los votos
    }
    delete[] votos;// no se si esto va aqui la verdad
    */

    return VotoT;

}



//----main----
int main(){
    int NumDepartamentos = 22;
    //supongo que aquí va lo del tiempo jiji
    cout << "xd "<< Votos(NumDepartamentos) << endl;
    
    //mostrar el tiempo 
    return 0;

}
