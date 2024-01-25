#include "Grafo.h"
#include "Servicios.h"

#include "iostream"

using namespace std;

template <typename C>
ostream & operator << (ostream & salida, const Grafo<C> & grafo)
{
	// Recorremos todos los vertices
	list<int> vertices;
	grafo.devolver_vertices(vertices);
	list<int>::iterator v = vertices.begin();
	while (v != vertices.end()) {
		salida << "    " << *v << "\n";
		// Recorremos todos los adyacentes de cada vertice
		list<typename Grafo<C>::Arco> adyacentes;
		grafo.devolver_adyacentes(*v, adyacentes);
		typename list<typename Grafo<C>::Arco>::iterator ady = adyacentes.begin();
		while (ady != adyacentes.end()) {
			salida << "    " << *v << "-> " << ady->devolver_adyacente() << " (" << ady->devolver_costo() << ")\n";
			ady++;
		}
		v++;
	}
	return salida;
}

int main(int argc, char **argv)
{
	Grafo<int> g;

	// Cargamos un grafo dirigido
	// Primero los vértices
	g.agregar_vertice(1);
	g.agregar_vertice(2);
	g.agregar_vertice(3);
	g.agregar_vertice(4);
	g.agregar_vertice(5);
	g.agregar_vertice(6);
	g.agregar_vertice(7);

	// Luego los arcos
	g.agregar_arco(1, 2, 1);
	g.agregar_arco(1, 3, 1);
	g.agregar_arco(1, 4, 1);
	g.agregar_arco(2, 6, 2);
	g.agregar_arco(3, 5, 3);
	g.agregar_arco(4, 7, 4);
	g.agregar_arco(5, 6, 5);

	int menu=0;
    while (menu != 4){
    cout << "Que desea hacer?" << endl;
    cout << "1: Hacer DFS FOREST " << endl;
     cout << "2: Hacer BFT FOREST " << endl;
      cout << "3: Hacer camino, con longitud, origen y destino" << endl;
       cout << "4: salir" << endl;
    cin >> menu;
    if ((menu>4)or(menu<1))
        cout <<"No ingreso una de las opciones" << endl;
    else {
            switch (menu) {
                case 1 : {
                    list<int> orden;
                    dfs_forest(g,orden);
                    imprimir_forest(orden);
                    menu =0;
                    break;
                }
                case 2 : {
                    list<int> orden;
                    bfs_forest(g,orden);
                    imprimir_forest(orden);
                    menu =0;
                    break;
                }
                case 3 : {
                    set<int> marcados;
                    list<int> camino;
                    int longi;
                    cout << "Cargar Longitud" << endl;
                    cin >> longi;
                    list<list<int> > cami; //Aca guardamos todos los caminos con esa long
                    int org;
                    cout << "Cargar origen" << endl;
                    cin >> org;
                    int des;
                    cout << "Cargar des" << endl;
                    cin >> des;
                    caminos(g,org, marcados, camino,des,(longi-1),cami);
                    menu =0;
                    break;
                }
            }
        }
   }

	return 0;
}
