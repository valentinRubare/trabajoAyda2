#ifndef SERVICIOS_H_INCLUDED
#define SERVICIOS_H_INCLUDED
#include "iostream"

using namespace std;
#include <list>



//IMPRIMIR Y IMPRIMIR FOREST

void imprimir (list<int> & camino,int destino)// complejidad O(n) Por q en el peor de los casos recorre la lista de caminos completa
{
    list<int>:: iterator it = camino.begin();
    while (it != camino.end()){

        cout<< *it<< "---";
        if(*it == destino)
           cout<<" "<< endl;
        it++;
        }
}

void imprimir_forest(list<int> orden){    // complejidad O(n). Por q en el peor de los casos recorre la lista de orden completa
    list<int>:: iterator it = orden.begin();
    while (it != orden.end()){
        cout<< *it<< "---";
        it++;
        }
}

//..............................................................

//DFS_FOREST_ , BFS_FOREST_ CAMINOSS

template <typename C>
void dfs_forest(const Grafo<C> & grafo, list<int> & orden){ // O(max(n,a)) Siendo n la lista de vertices  y a las aristas
list<int> listaver;
    grafo.devolver_vertices(listaver);
     typename  list<int>::iterator itL = listaver.begin();
     int maxv=grafo.devolver_longitud() ;
     char arV[maxv];
    for(int i=0; i<maxv;i++){
        arV[i]= 'b' ;
    }

        int j=0;

  while(itL != listaver.end()){
        if(arV[j]=='b'){
            orden.push_back(*itL);
            DFS(grafo,*itL,arV,orden);  //O(a)
        }
        j++;
        itL++;
   }

}




template <typename C>
void bfs_forest(const Grafo<C> & grafo, list<int> & orden){  // O(k*n*a) Ya que se realiza k vcs BFS siendo k la lista de vertices
    list<int> listaver;
    grafo.devolver_vertices(listaver);
     typename  list<int>::iterator itL = listaver.begin();
     int maxv=grafo.devolver_longitud() ;
     char arV[maxv];
    for(int i=0; i<maxv;i++){
        arV[i]= 'b' ;
    }
        int j=0;
    while(itL != listaver.end()){
        if(arV[j]=='b'){
            orden.push_back(*itL);
            BFS(grafo,*itL,arV,orden); //O(n*a)
        }
        j++;
        itL++;
   }
}




template <typename C>
void caminos(Grafo<C> & grafo, int origen,set<int> & visita, list<int> & camino, int destino,int longi,list<list<int> > & cami){
    visita.insert(origen);                              // O(n) siendo n todos los vertices del grafo
    camino.push_back(origen);
    list<typename Grafo<C>::Arco> adyacentes;
    grafo.devolver_adyacentes(origen, adyacentes);
    typename list<typename Grafo<C>::Arco>::iterator ady = adyacentes.begin();
    if((origen == destino)&&(longi>=0)){
        imprimir(camino,destino);
        cami.push_back(camino);
    }
    else{
       while((ady != adyacentes.end())&&(longi>0)){
          if (visita.find(ady->devolver_adyacente()) == visita.end()){
                caminos(grafo, ady->devolver_adyacente(),visita, camino, destino,longi-1,cami);
          }
         ady++;
       }
     }
     camino.remove(origen);
     visita.erase(origen); // debo ir borrando elementos,asi puedo encontrar mas caminos para el dfs

}


//........................................


//DFS , BFS



template <typename C>
void BFS(const  Grafo<C> & grafo, int origen, char arV[],list<int> & orden) // Complejidad O(n*a) siendo n la cantidad de elementos de la fila y a las aristas.
{
 arV[origen-1]= 'g';
    list<int> fila;
    fila.push_back(origen);
    typename list<int>::iterator itf = fila.begin();

while (itf!=fila.end()){
    list<typename Grafo<C>::Arco> adyacentes;
     grafo.devolver_adyacentes(*itf, adyacentes);
     typename list<typename Grafo<C>::Arco>::iterator ady = adyacentes.begin();
        while (ady!=adyacentes.end()){
            if (arV[ady->devolver_adyacente()-1]=='b'){
                arV[ady->devolver_adyacente()-1]='g';
                orden.push_back(ady->devolver_adyacente());
                fila.push_back(ady->devolver_adyacente());
            }
            ady++;
        }
        itf=fila.begin();
        fila.erase(itf);
        itf=fila.begin();
}

    arV[origen-1]='n';
}


template <typename C>
void DFS(const Grafo<C> & grafo, int origen, char arV[],list<int> & orden) // Complejidad O(a) siendo "a" las aristas.
{
 arV[origen-1]= 'g';
    list<typename Grafo<C>::Arco> adyacentes;
    grafo.devolver_adyacentes(origen, adyacentes);
    typename list<typename Grafo<C>::Arco>::iterator ady = adyacentes.begin();

    while (ady != adyacentes.end()){
            int aux = ady->devolver_adyacente();
             if (arV[aux-1]=='b'){ //Esto era lo q nos daba error
            orden.push_back(aux);
            DFS(grafo,aux,arV,orden);
          }
         ady++;
       }
    arV[origen-1]='n';
}



#endif // SERVICIOS_H_INCLUDED
