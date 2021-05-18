#include <iostream>
using namespace std;

// Функция вывода матрицы
void PrintMatr(float **mas, int m) {
    int i, j;
    for (i = 0; i<m; i++) {
        for (j = 0; j<m; j++)
            cout << mas[i][j] << " ";
        cout << endl;
    }
}
// Получение матрицы без i-й строки и j-го столбца
void GetMatr(float **mas, float **p, int i, int j, int m) {
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

// Рекурсивное вычисление определителя
int Determinant(float **mas, int m) {
    int i, j, d, k, n;
    float **p;
    p = new float*[m];
    for (i = 0; i<m; i++)
        p[i] = new float[m];
    j = 0; d = 0;
    k = 1; //(-1) в степени i
    n = m - 1;
    if (m<1){
        cout << "Определитель вычислить невозможно!" << endl;
        return 0;
    }
    if (m == 1) {
        d = mas[0][0];
        return(d);
    }
    if (m == 2) {
        d = mas[0][0] * mas[1][1] - (mas[1][0] * mas[0][1]);
        return(d);
    }
    if (m>2) {
        for (i = 0; i<m; i++) {
            GetMatr(mas, p, i, 0, m);
            cout << mas[i][j] << endl;
            PrintMatr(p, n);
            d = d + k * mas[i][0] * Determinant(p, n);
            k = -k;
        }
    }
    return(d);
}

// Получение обратной матрицы
float** InverseMatrix(float** A, int k)
{
    int det = Determinant(A,k);
    if (det == 0){
        cout << "Обратной матрицы не существует" << endl;
        return A;
    }
    int N = k;
    float** invA = new float*[k];
    for (int i = 0; i < N; i++) {
        invA[i] = new float[N];
    }
    for (int i = 0; i < N; i++)
    {
        invA[i] = new float[k];
        for (int j = 0; j < N; j++)
        {
            float** B = new float*[j];
            int sign = ((i+j)%2==0) ? 1 : -1;
            for (int m = 0; m < j; m++)
            {
                B[m] = new float[j];
                for (int n = 0; n < i; n++)
                    B[m][n] = A[m][n];
                for (int n = i+1; n < N; n++)
                    B[m][n-1] = A[m][n];
            }
            for (int m = j+1; m < N; m++)
            {
                B[m-1] = new float[m];
                for (int n = 0; n < i; n++)
                    B[m-1][n] = A[m][n];
                for (int n = i+1; n < N; n++)
                    B[m-1][n-1] = A[m][n];
            }
            try {
                int det2 = Determinant(B, k - 1);
                invA[i][j] = sign * (float)det2 / (float)det;
            }catch (int a){
                invA[i][j] = 0;
            }

        }
    }
    return invA;
}

// Умножение матрицы на вектор
float* MatrMultiply(int n, int m, float** matrix, int* vektor)
{
    float* res = new float[n];
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

//Решение квадратной системы линейных уравнений методом обратной матрицы
int* solve(){

}

int main() {
    int m, i, j, d;
    float **mas;
    system("chcp 1251");
    system("cls");
    cout << "Введите размерность квадратной матрицы: ";
    cin >> m;
    mas = new float*[m];
    for (i = 0; i<m; i++) {
        mas[i] = new float[m];
        for (j = 0; j<m; j++) {
            cout << "mas[" << i << "][" << j << "]= ";
            cin >> mas[i][j];
        }
    }
    PrintMatr(mas, m);
    d = Determinant(mas,m);
    cout << "Определитель матрицы равен " << d << endl;
    cout << "Обратная матрица: " << endl;
    PrintMatr(InverseMatrix(mas, m), m);
    int vectorLength;
    cout << "Введите длину вектора ";
    cin >> vectorLength;
    int* vector = new int[vectorLength];
    cout << "Введите вектор" << endl;
    for (int k = 0; k < vectorLength; ++k) {
        cin >> vector[k];
    }
    cout << "Умножение матрицы на вектор" << endl;
    float* result = MatrMultiply(m, vectorLength, mas, vector);
    for(int i = 0; i < vectorLength; i++){
        cout << result[i] << " ";
    }
    cin.get(); cin.get();
    return 0;
}