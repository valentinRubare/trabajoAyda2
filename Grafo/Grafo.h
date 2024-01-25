#ifndef GRAFO_H_
#define GRAFO_H_

#include <list>
#include <set>
#include <map>
#include <queue>
#include <vector>

using namespace std;

template <typename C> class Grafo
{
public:
	class Arco
	{
	public:
		Arco();
		Arco(int adyacente, const C & costo);
		int devolver_adyacente() const;
		const C & devolver_costo() const;
	private:
		int vertice;
		C costo;
	}; // class Arco

public:
	// NOTA: Dependiendo de la implementación puede ser necesario incluir otras funciones constructuras
	Grafo();
	Grafo(const Grafo & otroGrafo);

	~Grafo();
	Grafo & operator = (const Grafo & otroGrafo);
	// Devuelve true si la cantidad de vértices es cero
	bool esta_vacio() const;
	// Indica la cantidad de vértices del grafo
	int devolver_longitud() const;
	bool existe_vertice(int vertice) const;
	bool existe_arco(int origen, int destino) const;
	// PRE CONDICION: existe_arco(origen, destino)
	const C & costo_arco(int origen, int destino) const;
	void devolver_vertices(list<int> & vertices) const;
	void devolver_adyacentes(int origen, list<Arco> & adyacentes) const;
	void agregar_vertice(int vertice);
	// POST CONDICION: Para todo vértice v != vertice: !existeArco(v, vertice) && !existeArco(vertice, v)
	void eliminar_vertice(int vertice);
	// PRE CONDICION: existeArco(origen, destino)
	void modificar_costo_arco(int origen, int destino, const C & costo);
	// PRE CONDICION: existeVertice(origen) && existeVertice(destino)
	// POST CONDICION: existeArco(origen, destino)
	void agregar_arco(int origen, int destino, const C & costo);
	// POST CONDICION: !existeArco(origen, destino)
	void eliminar_arco(int origen, int destino);
	void vaciar();
private:
	/*
	 * Definir la estructura interna
	 */

	 map<int,list<Arco>> grafo;
}; // class Grafo










/*
 * Arco
 */

template <typename C> Grafo<C>::Arco::Arco() //O(1)
{

}

template <typename C> Grafo<C>::Arco::Arco(int adyacente, const C & costo)  //O(1)
{
    this->vertice = adyacente; //modifico mis variables de la parte privada con los parametros que se le pasan
    this->costo = costo;
}

template <typename C> int Grafo<C>::Arco::devolver_adyacente() const //O(1)
{
        return vertice;
}

template <typename C> const C & Grafo<C>::Arco::devolver_costo() const //O(1)
{
        return costo;
}


/*
 * Grafo
 */

template <typename C> Grafo<C>::Grafo()
{
}

template <typename C> Grafo<C>::Grafo(const Grafo & otroGrafo) //O(1)
{
    this->operator=(otroGrafo);
}

template <typename C> Grafo<C>::~Grafo()
{

}

template <typename C> Grafo<C> & Grafo<C>::operator = (const Grafo & otroGrafo) //O(v) siendo v vertices
{
    grafo.clear();
    typename map<int,list<Arco>>::const_iterator itOtrog = otroGrafo.grafo.begin();
    while (itOtrog != otroGrafo.grafo.end()) {
        grafo[itOtrog->first] = itOtrog->second;
        itOtrog++;
    }
    return *this;
}

template <typename C> bool Grafo<C>::esta_vacio() const //O(1)
{
    return grafo.empty();
}

template <typename C> int Grafo<C>::devolver_longitud() const //O(1)
{
    return grafo.size();
}

template <typename C> bool Grafo<C>::existe_vertice(int vertice) const  //O(log v) siendo v los vertices.
{                                                                       //defino un iterador que me posiciona en el vertice si es que exista,caso contrario llega al final
     bool existe = false;
    typename map<int ,list<Arco>>::const_iterator itF = grafo.find(vertice);
    if (itF != grafo.end())
        existe = true;
    return existe;
}

template <typename C> bool Grafo<C>::existe_arco(int origen, int destino) const //O(log (a,v)) v vertices a aristas
{
    bool existe = false;
    typename map<int, list<Arco>>::const_iterator itF = grafo.find(origen);
    if (itF->first != grafo.end()){
        typename list<Arco>::const_iterator itS = itF->second.find(destino);
        if (itS != NULL)
            existe = true;
    }
    return existe;
}

template <typename C> const C & Grafo<C>::costo_arco(int origen, int destino) const           //O(a) a aristas
{
    typename map<int ,list<Arco>>::const_iterator itF = grafo.find(origen);
        typename list<Arco>::const_iterator itS = itF->second.begin();
        while ((itS != itF->second.end()) && (itS->devolver_adyacente()!=destino))
            itS++;
    return itS->devolver_costo();
}

template <typename C> void Grafo<C>::devolver_vertices(list<int> & vertices) const   //o(v) v vertices
{
    typename map<int, list<Arco>>::const_iterator itF = grafo.begin();
    while (itF != grafo.end()){
        vertices.push_back(itF->first);
        itF++;
    }
}

template <typename C> void Grafo<C>::devolver_adyacentes(int origen, list<Arco> & adyacentes) const  //Complejidad O(v) siendo v vertices
{
    typename map<int, list<Arco>>::const_iterator itF = grafo.find(origen);
    if( itF != grafo.end()){
      typename list<Arco>::const_iterator itS = itF->second.begin();
      while(itS != itF->second.end()){
         adyacentes.push_back(Arco(itS->devolver_adyacente(),itS->devolver_costo()));
         itS++;
      }
    }
}

template <typename C> void Grafo<C>::agregar_vertice(int vertice)  //o(log v) v vertices
{
    typename map<int, list<Arco>>::iterator itF = grafo.find(vertice);
    if (itF == grafo.end()) //Utilizamos esto para verificar que no se repite
    grafo[vertice] = list<Arco>();
}

template <typename C> void Grafo<C>::eliminar_vertice(int vertice)   //O(v*a) v vertices a aristas
{
    typename map<int ,list<Arco>>::iterator itF = grafo.find(vertice);
        grafo.erase(itF);
        itF=grafo.begin();
        typename list<Arco>::iterator itS;
        while (itF != grafo.end()){
            itS=itF->second.begin();
            while ((itS != itF->second.end()) && (itS->devolver_adyacente()!=vertice))
                itS++;
            if (itS != itF->second.end())
                itF->second.erase(itS);
            itF++;
        }
}

template <typename C> void Grafo<C>::modificar_costo_arco(int origen, int destino, const C & costo) //con la pre condicion de que exista el arco,O(a) a aristas
{
    typename map<int, list<Arco>>::iterator itF=grafo.find(origen);
    typename list<Arco>::iterator itS = itF->second.begin();
    while (itS->devolver_adyacente()!=destino)
        itS++;
    itS->editar_arco(costo);
}

template <typename C> void Grafo<C>::agregar_arco(int origen, int destino, const C & costo) //O(log v) v vertice
{
    typename map<int,list<Arco>>::iterator it=grafo.find(origen);
    it->second.push_back(Arco(destino, costo));

}

template <typename C> void Grafo<C>::eliminar_arco(int origen, int destino) //O(e) e aristas
{
    typename map<int,list<Arco>>::iterator itF = grafo.find(origen);
    typename list<Arco>::iterator itS = itF->second.begin();
    while (itS != itF->second.end())
    {
        if (itS->devolver_adyacente() == destino)
        {
            itF->second.erase(itS);
            break;
        }
        itS++;
    }
}

template <typename C> void Grafo<C>::vaciar()  //O(1)
{
    grafo.clear();
}

#endif /* GRAFO_H_ */


