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

double PotenciaNumero(double base, int exponente)
{
    if (exponente == 0)
    {
        return 1;
    }
    double mitad = PotenciaNumero(base, exponente / 2);
    double resultado = mitad * mitad;
    if (exponente % 2 == 1)
    {
        resultado *= base;
    }

    return resultado;
}

vector<vector<int>> SumaResta(const vector<vector<int>> &A, const vector<vector<int>> &B, bool suma_resta)
{
    int rows = A.size();
    int cols = A[0].size();
    vector<vector<int>> result(rows, vector<int>(cols, 0));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (suma_resta)
                result[i][j] = A[i][j] + B[i][j];
            else
                result[i][j] = A[i][j] - B[i][j];
        }
    }
    return result;
}

// Función para multiplicar matrices utilizando el algoritmo de Strassen
vector<vector<int>> Strassen(const vector<vector<int>> &A, const vector<vector<int>> &B)
{
    int rowsA = A.size();
    int colsA = A[0].size();
    int rowsB = B.size();
    int colsB = B[0].size();

    if (colsA != rowsB)
    {
        return {};
    }

    if (rowsA == 1 && colsA == 1 && rowsB == 1 && colsB == 1)
    {
        vector<vector<int>> result(1, vector<int>(1, 0));
        result[0][0] = A[0][0] * B[0][0];
        return result;
    }

    int maxSize = max(max(rowsA, colsA), max(rowsB, colsB));
    int size = 1;
    while (size < maxSize)
    {
        size *= 2;
    }

    // Rellenar las matrices con ceros hasta el tamaño adecuado
    vector<vector<int>> paddedA(size, vector<int>(size, 0));
    vector<vector<int>> paddedB(size, vector<int>(size, 0));

    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < colsA; j++)
        {
            paddedA[i][j] = A[i][j];
            paddedB[i][j] = B[i][j];
        }
    }

    // Dividir las matrices en submatrices más pequeñas
    int mid = size / 2;
    vector<vector<int>> A11(mid, vector<int>(mid, 0));
    vector<vector<int>> A12(mid, vector<int>(mid, 0));
    vector<vector<int>> A21(mid, vector<int>(mid, 0));
    vector<vector<int>> A22(mid, vector<int>(mid, 0));
    vector<vector<int>> B11(mid, vector<int>(mid, 0));
    vector<vector<int>> B12(mid, vector<int>(mid, 0));
    vector<vector<int>> B21(mid, vector<int>(mid, 0));
    vector<vector<int>> B22(mid, vector<int>(mid, 0));

    for (int i = 0; i < mid; i++)
    {
        for (int j = 0; j < mid; j++)
        {
            A11[i][j] = paddedA[i][j];
            A12[i][j] = paddedA[i][j + mid];
            A21[i][j] = paddedA[i + mid][j];
            A22[i][j] = paddedA[i + mid][j + mid];
            B11[i][j] = paddedB[i][j];
            B12[i][j] = paddedB[i][j + mid];
            B21[i][j] = paddedB[i + mid][j];
            B22[i][j] = paddedB[i + mid][j + mid];
        }
    }

    // Calculamos los productos
    vector<vector<int>> P1 = Strassen(SumaResta(A11, A22, 1), SumaResta(B11, B22, 1));
    vector<vector<int>> P2 = Strassen(SumaResta(A21, A22, 1), B11);
    vector<vector<int>> P3 = Strassen(A11, SumaResta(B12, B22, 0));
    vector<vector<int>> P4 = Strassen(A22, SumaResta(B21, B11, 0));
    vector<vector<int>> P5 = Strassen(SumaResta(A11, A12, 1), B22);
    vector<vector<int>> P6 = Strassen(SumaResta(A21, A11, 0), SumaResta(B11, B12, 1));
    vector<vector<int>> P7 = Strassen(SumaResta(A12, A22, 0), SumaResta(B21, B22, 1));

    // Calculamos las submatrices
    vector<vector<int>> C11 = SumaResta(SumaResta(SumaResta(P1, P4, 1), P7, 1), P5, 0);
    vector<vector<int>> C12 = SumaResta(P3, P5, 1);
    vector<vector<int>> C21 = SumaResta(P2, P4, 1);
    vector<vector<int>> C22 = SumaResta(SumaResta(SumaResta(P1, P3, 1), P2, 0), P6, 1);

    // Pasamos los resultados a la matriz final
    vector<vector<int>> result(size, vector<int>(size, 0));

    for (int i = 0; i < mid; i++)
    {
        for (int j = 0; j < mid; j++)
        {
            result[i][j] = C11[i][j];
            result[i][j + mid] = C12[i][j];
            result[i + mid][j] = C21[i][j];
            result[i + mid][j + mid] = C22[i][j];
        }
    }

    // Eliminamos los ceros que quedan al borde
    vector<vector<int>> finalResult(rowsA, vector<int>(colsB, 0));

    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < colsB; j++)
        {
            finalResult[i][j] = result[i][j];
        }
    }

    return finalResult;
}

int main()
{

    vector<int> arr = {9, 2, 5, 1, 7, 3, 98, 25, 14, 33, 225};

    /////// MERGE SORT //////
    // MergeSort(arr, 0, arr.size() - 1);

    /////// QUICK SORT ///////
    QuickSort(arr, 0, arr.size() - 1);

    cout << "Array Ordenado: " << endl;
    for (int i : arr)
        cout << i << " - ";

    /////// BINAR SEARCH ///////
    cout << "\n---------\nPosicion de 98 nuevo: " << BinarySearch(arr, 98) << endl;

    /////// POTENCIA NUMERO //////
    double base = 3;
    int exponente = 10;
    cout << base << " elevado a " << exponente << ": " << PotenciaNumero(base, exponente) << endl;

    /////// MATRIZ STRASSEN //////

    vector<vector<int>> A = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    vector<vector<int>> B = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};

    vector<vector<int>> result = Strassen(A, B);

    cout << "---------\nMatriz A x Matriz B" << endl;
    for (int i = 0; i < result.size(); i++)
    {
        for (int j = 0; j < result[0].size(); j++)
            cout << result[i][j] << " ";
        cout << endl;
    }

    return 0;
}