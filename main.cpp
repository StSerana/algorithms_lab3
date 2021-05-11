#include <iostream>
using namespace std;

// Функция вывода матрицы
void PrintMatr(int **mas, int m) {
    int i, j;
    for (i = 0; i<m; i++) {
        for (j = 0; j<m; j++)
            cout << mas[i][j] << " ";
        cout << endl;
    }
}
// Получение матрицы без i-й строки и j-го столбца
void GetMatr(int **mas, int **p, int i, int j, int m) {
    int ki, kj, di, dj;
    di = 0;
    for (ki = 0; ki<m - 1; ki++) { // проверка индекса строки
        if (ki == i) di = 1;
        dj = 0;
        for (kj = 0; kj<m - 1; kj++) { // проверка индекса столбца
            if (kj == j) dj = 1;
            p[ki][kj] = mas[ki + di][kj + dj];
        }
    }
}

//Вычисление определителя матрицы
int Determinant(int** A)
{
    int N = sizeof(A) / sizeof(int);
    int** B = new int*[N];
    int denom = 1, exchanges = 0;
    for (int i = 0; i < N; ++i)
    {
        B[i] = new int[N];
        for (int j = 0; j < N; ++j)
            B[i][j] = A[i][j];
    }
    for (int i = 0; i < N-1; ++i)
    { int maxN = i, maxValue = abs(B[i][i]);
        for (int j = i+1; j < N; ++j)
        {
            int value = abs(B[j][i]);
            if (value > maxValue){ maxN = j; maxValue = value; }
        }
        if (maxN > i)
        {
            int* t = B[i];
            B[i] = B[maxN];
            B[maxN] = t;
            ++exchanges;
        }
        else {
            if (maxValue == 0) return maxValue;
        }
        int value1 = B[i][i];
        for (int j = i+1; j < N; ++j)
        {
            int value2 = B[j][i];
            B[j][i] = 0;
            for (int k = i+1; k < N; ++k) B[j][k] = (B[j][k]*value1-B[i][k]*value2)/denom;
        }
        denom = value1;
    }
    if (exchanges%2) return -B[N-1][N-1];
    else return B[N-1][N-1];
}

// Получение обратной матрицы
int** InverseMatrix(int** A, int k)
{
    int det = Determinant(A);
    if (det == 0)
        cout << "Обратной матрицы не существует";
    int N = k;
    int** invA = new int*[k];
    for (int i = 0; i < N; i++) {
        invA[i] = new int[N];
    }
    for (int i = 0; i < N; i++)
    {
        invA[i] = new int[k];
        for (int j = 0; j < N; j++)
        {
            int** B = new int*[j];
            int sign = ((i+j)%2==0) ? 1 : -1;
            for (int m = 0; m < j; m++)
            {
                B[m] = new int[j];
                for (int n = 0; n < i; n++)
                    B[m][n] = A[m][n];
                for (int n = i+1; n < N; n++)
                    B[m][n-1] = A[m][n];
            }
            for (int m = j+1; m < N; m++)
            {
                B[m-1] = new int [m];
                for (int n = 0; n < i; n++)
                    B[m-1][n] = A[m][n];
                for (int n = i+1; n < N; n++)
                    B[m-1][n-1] = A[m][n];
            }
            try {
                invA[i][j] = sign * Determinant(B) / det;
            }catch (int a){
                invA[i][j] = 0;
            }

        }
    }
    return invA;
}

// Умножение матрицы на вектор
int* MatrMultiply(int n, int m, int** matrix, int* vektor) // если необходимы целочисленные значения, можно заменить на int
{
    int* res = new int[n];
    for (int i=0;i<n;i++)
    {
        int temp = 0;
        for (int j=0;j<m;j++)
        {
            temp += matrix[i][j]*vektor[j];
        }
        res[i] = temp;
    }
    return res;
}

int main() {
    int m, i, j, d;
    int **mas;
    system("chcp 1251");
    system("cls");
    cout << "Введите размерность квадратной матрицы: ";
    cin >> m;
    mas = new int*[m];
    for (i = 0; i<m; i++) {
        mas[i] = new int[m];
        for (j = 0; j<m; j++) {
            cout << "mas[" << i << "][" << j << "]= ";
            cin >> mas[i][j];
        }
    }
    PrintMatr(mas, m);
    d = Determinant(mas);
    cout << "Определитель матрицы равен " << d << endl;
    cout << "Обратная матрица: " << endl;
    //PrintMatr(InverseMatrix(mas, m), m);
    int vectorLength;
    cout << "Введите длину вектора ";
    cin >> vectorLength;
    int* vector = new int[vectorLength];
    cout << "Введите вектор" << endl;
    for (int k = 0; k < vectorLength; ++k) {
        cin >> vector[k];
    }
    cout << "Умножение матрицы на вектор" << endl;
    int* result = MatrMultiply(m, vectorLength, mas, vector);
    for(int i = 0; i < vectorLength; i++){
        cout << result[i] << " ";
    }
    cin.get(); cin.get();
    return 0;
}