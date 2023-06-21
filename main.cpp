#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

#define PRZYB_ZERO 1.0e-16

int * LU(int n, double **A) {
    int *index;
    double myMax;
    int candidate;
    index = new int[n];


    for (int i = 0; i < n; i++) {
        index[i] = i;
    }

    for (int i = 0; i < n; i++) {
        if (fabs(A[index[i]][i]) <= PRZYB_ZERO) {
            myMax = 0.0;
            candidate=index[i];   // not sure
            for (int k = i + 1; k < n; k++) {
                if (fabs(A[index[k]][i]) > myMax) {
                    myMax = fabs(A[index[k]][i]);
                    candidate = k;
                }
            }
            swap(index[i], index[candidate]);

        }

        for(int j=i+1; j<n; j++) {
            double factor = A[index[j]][i] / A[index[i]][i];
            A[index[j]][i]=factor;
            for(int k=i+1; k<n; k++) {
                A[index[j]][k] -= factor * A[index[i]][k];
            }
        }

    }
    return index;
}

void solveLU(int n, double **LU, double *b, const int *index){

    //L*y=b
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            b[index[i]] -= LU[index[i]][j] * b[index[j]];
        }
    }
    //U*x=y
    for (int i = n-1; i >= 0; i--) {
        for (int j = i+1; j < n; j++) {
            b[index[i]] -= LU[index[i]][j] * b[index[j]];
        }
        b[index[i]] /= LU[index[i]][i];
    }
}



int main() {

    double ** A;
    double *b;
    ifstream plik("matrix.txt");
    A= new double*[4];
    b=new double[4];
    for (int i = 0; i < 4; ++i) {
        A[i]=new double[4];
        for (int j = 0; j < 4; ++j) {
            plik >> A[i][j];
        }
    }

    for (int i = 0; i < 4; ++i) {
        plik >> b[i];
    }

    int * index;


    index = LU(4, A);

    cout << "Macierz L i U: "<<endl;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << A[i][j] << " ";
        }
        cout << '\n';
    }
    cout <<'\n';
    cout <<"Tablica index: ";
    for (int j = 0; j < 4; ++j) {
        cout << index[j] << " ";
    }
    cout << endl << endl;
    solveLU(4, A, b, index);
    cout << "Wynik: ";
    for (int j = 0; j < 4; ++j) {
        cout << b[index[j]] << " ";
    }


    return 0;
}