#include <iostream>
#include <vector>

using namespace std;

void Merge(vector<int> &arr, int inicio, int mitad, int final)
{
    int izq, der;
    izq = mitad - inicio + 1;
    der = final - mitad;

    vector<int> arr_izq(izq);
    vector<int> arr_der(der);

    for (int i = 0; i < izq; i++)
    {
        arr_izq[i] = arr[inicio + i];
    }
    for (int j = 0; j < der; j++)
    {
        arr_der[j] = arr[mitad + 1 + j];
    }

    int i = 0, j = 0, k = inicio;

    while (i < izq && j < der)
    {
        if (arr_izq[i] <= arr_der[j])
        {
            arr[k] = arr_izq[i];
            i++;
        }
        else
        {
            arr[k] = arr_der[j];
            j++;
        }
        k++;
    }

    while (i < izq)
    {
        arr[k] = arr_izq[i];
        i++;
        k++;
    }

    while (j < der)
    {
        arr[k] = arr_der[j];
        j++;
        k++;
    }
}

void MergeSort(vector<int> &arr, int inicio, int final)
{
    int mitad;
    if (inicio < final)
    {
        mitad = inicio + (final - inicio) / 2;
        MergeSort(arr, inicio, mitad);
        MergeSort(arr, mitad + 1, final);
        Merge(arr, inicio, mitad, final);
    }
}

int Particionar(vector<int> &arr, int inicio, int fin)
{
    int pivote = arr[fin];
    int i = inicio - 1;

    for (int j = inicio; j <= fin - 1; j++)
    {
        if (arr[j] <= pivote)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[fin]);
    i++;
    return i;
}

void QuickSort(vector<int> &arr, int inicio, int fin)
{
    if (inicio < fin)
    {
        int pivote = Particionar(arr, inicio, fin);
        QuickSort(arr, inicio, pivote - 1);
        QuickSort(arr, pivote + 1, fin);
    }
}

int BinarySearch(vector<int> &arr, int dato)
{
    int inicio = 0;
    int fin = arr.size() - 1;
    while (inicio <= fin)
    {
        int medio = (inicio + fin) / 2;
        if (arr[medio] == dato)
            return medio;
        else if (arr[medio] < dato)
            inicio = medio + 1;
        else
            fin = medio - 1;
    }
    return -1;
}

int main()
{

    vector<int> arr = {9, 2, 5, 1, 7, 3, 98, 25, 14, 33, 225};

    // MergeSort(arr, 0, arr.size() - 1);
    cout << "Posicion de 98: " << BinarySearch(arr, 98) << endl;

    QuickSort(arr, 0, arr.size() - 1);

    for (int i : arr)
    {
        cout << i << " - ";
    }

    cout << "Posicion de 98 nuevo: " << BinarySearch(arr, 98) << endl;

    return 0;
}
