
#include <fstream>
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;
ifstream fin("algsort.in");
int v[10000005];

int getMax(int arr[], int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}
 
//count sort modificat
void countSort(int arr[], int n, int imp,int base)
{
    int *output= new int[n+1]; 
    int i, count[base+1] = { 0 };
 
    // count
    for (i = 0; i < n; i++)
        count[(arr[i] / imp) % base]++;
 
    //suma 
    for (i = 1; i < base; i++)
        count[i] += count[i - 1];
 
    //output base on suma
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / imp) % base] - 1] = arr[i];
        count[(arr[i] / imp) % base]--;
    }
 
    
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}
 

void radixsort(int arr[], int n,int base)
{
    //nr max
    int m = getMax(arr, n);
 
    //trecerea prin digit in functie de baze
    for (int imp = 1; m / imp > 0; imp *= base)
        countSort(arr, n, imp,base);
}

//merge sort
void merge(int arr[], int p, int q, int r) {

    int n1 = q - p + 1;
    int n2 = r - q;

    int *L = new int[n1];
    int *R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[p + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[q + 1 + j];

    // i=primul vector , j = al doilea , k = cel sortat
    int i, j, k;
    i = 0;
    j = 0;
    k = p;

    //pana la golirea unui vector
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }


    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
}

void mergeSort(int array[], int const begin, int const end)
{
    if (begin >= end)
        return; 
  
    auto mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}

int shellSort(int arr[], int n)
{
    
    for (int gap = n/2; gap > 0; gap /= 2)
    {
        
        for (int i = gap; i <= n; i += 1)
        {
            int temp = arr[i];
  
            //muta elementele la dreapta pana ajung la locul lor
            int j;            
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
              
            //revert prima linie din for
            arr[j] = temp;
        }
    }
    return 0;
}

void quicksort(int left, int right)
{
    if(left>=right)
        return;
    int firstfree=left;
    int mid=(left+right)/2;
    swap(v[right], v[mid]);
    for(int i=left; i<=right-1; i++)
        if(v[i]<v[right])
        {
            swap(v[i], v[firstfree]);
            firstfree++;
        }
    swap(v[right], v[firstfree]);
    quicksort(left, firstfree-1);
    quicksort(firstfree+1, right);
}
void ReInitialize(int arr[],int n){
    for(int i=0; i<=n; i++)
            v[i]=arr[i];
}

void isSorted(int arr[],int n){
    int sort=1;
    for(int i=1; i<n; i++)
            if(v[i]>v[i+1])
                sort=0;
    if(sort==1)
        cout<<" sortat";
    else 
        cout<<" nu e sortat";


}
//count sort
void CountingSort(int a[],int n)
    {
        int max = getMax(a,n);

        int* temp = new int[max+1]{0};
        for(int i = 0;i<=n;i++)
        {
            temp[a[i]]++;
        }
        
        int k = 0;
        for(int i = 0;i<=max;i++)
        {
            for(int j = 0;j<temp[i];j++)
                a[k++] = i;
        }

    }

int main()
{   
    int *stabil = new int[9999999];
    int t;
    
    fin>>t;

    
    while(t>0){
        int n,m,base;
        fin>>n>>m>>base;
        for(int i=0; i<=n; i++)
            stabil[i]=rand()%m;
        cout <<"N = "<< n << ", M = " << m << " Base:"<<base<<endl;
        


    ReInitialize(stabil,n);

        auto start = high_resolution_clock::now();
        CountingSort(v, n);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "CountingSort" ;isSorted(v,n) ;
        cout<<" in "<< duration.count() << " microsecunde" << endl;

        ReInitialize(stabil,n);
        
         start = high_resolution_clock::now();
        quicksort(1,n);
         stop = high_resolution_clock::now();
         duration = duration_cast<microseconds>(stop - start);
        cout << "QuickSort" ;isSorted(v,n) ;
        cout<<" in "<< duration.count() << " microsecunde" << endl;
        
        ReInitialize(stabil,n);

        start = high_resolution_clock::now();
        shellSort(v,n);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        cout << "ShellSort" ;isSorted(v,n) ;
        cout<<" in "<< duration.count() << " microsecunde" << endl;
        

       
        ReInitialize(stabil,n);

        start = high_resolution_clock::now();
        mergeSort(v, 1, n );
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        cout << "MergeSort" ;isSorted(v,n) ;
        cout<<" in "<< duration.count() << " microsecunde" << endl;


        ReInitialize(stabil,n);

        start = high_resolution_clock::now();
        radixsort(v, n+1,base);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        cout << "Radixsort" ;isSorted(v,n) ;
        cout<<" in "<< duration.count() << " microsecunde" << endl;

        

        start = high_resolution_clock::now();
        sort(v, v + n);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        cout << "C++ Sort" ;isSorted(v,n) ;
        cout<<" in "<< duration.count() << " microsecunde" << endl;


        
        
        t--;
        cout <<"\n\n";
    }
    
    return 0;
}