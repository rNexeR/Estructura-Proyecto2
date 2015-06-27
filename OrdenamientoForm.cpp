#include "OrdenamientoForm.h"
#include "ui_OrdenamientoForm.h"

OrdenamientoForm::OrdenamientoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrdenamientoForm)
{
    ui->setupUi(this);
}

OrdenamientoForm::~OrdenamientoForm()
{
    delete ui;
}

void OrdenamientoForm::binSort(int sarray[], int array_size) {

    const int max = array_size;
    // use bucket[x][max] to hold the current count
    int bucket[10][max+1];
    // init bucket counters
    for(int x=0;x<10;x++) bucket[x][max] = 0;
    // main loop for each digit position
    for(int digit = 1; digit <= 1000000000; digit *= 10) {
        // array to bucket
        for(int i = 0; i < max; i++) {
            // get the digit 0-9
            int dig = (sarray[i] / digit) % 10;
            // add to bucket and increment count
            bucket[dig][bucket[dig][max]++] = sarray[i];
        }
        // bucket to array
        int idx = 0;
        for(int x = 0; x < 10; x++) {
            for(int y = 0; y < bucket[x][max]; y++) {
                sarray[idx++] = bucket[x][y];
            }
            // reset the internal bucket counters
            bucket[x][max] = 0;
        }
    }

}

void OrdenamientoForm::merge(int a[], const int low, const int mid, const int high)
{
    // Variables declaration.
    int * b = new int[high+1-low];
    int h,i,j,k;
    h=low;
    i=0;
    j=mid+1;
    // Merges the two array's into b[] until the first one is finish
    while((h<=mid)&&(j<=high))
    {
        if(a[h]<=a[j])
        {
            b[i]=a[h];
            h++;
        }
        else
        {
            b[i]=a[j];
            j++;
        }
        i++;
    }
    // Completes the array filling in it the missing values
    if(h>mid)
    {
        for(k=j;k<=high;k++)
        {
            b[i]=a[k];
            i++;
        }
    }
    else
    {
        for(k=h;k<=mid;k++)
        {
            b[i]=a[k];
            i++;
        }
    }
    // Prints into the original array
    for(k=0;k<=high-low;k++)
    {
        a[k+low]=b[k];
    }
    delete[] b;
}

void OrdenamientoForm::merge_sort( int a[], const int low, const int high )		// Recursive sort ...
{

    int mid;
    if( low < high )
    {
        mid = ( low + high ) / 2;
        merge_sort( a, low, mid );
        merge_sort( a, mid + 1, high );
        merge( a, low, mid, high );
    }

}

// Función para dividir el array y hacer los intercambios
int OrdenamientoForm::divide(int *array, int start, int end) {
    int left;
    int right;
    int pivot;
    int temp;

    pivot = array[start];
    left = start;
    right = end;

    // Mientras no se cruzen los índices
    while (left < right) {
        while (array[right] > pivot) {
            right--;
        }

        while ((left < right) && (array[left] <= pivot)) {
            left++;
        }

        // Si todavía no se cruzan los indices seguimos intercambiando
        if (left < right) {
            temp = array[left];
            array[left] = array[right];
            array[right] = temp;
        }
    }

    // Los índices ya se han cruzado, ponemos el pivot en el lugar que le corresponde
    temp = array[right];
    array[right] = array[start];
    array[start] = temp;

    // La nueva posición del pivot
    return right;
}

// Función recursiva para hacer el ordenamiento
void OrdenamientoForm::quicksort(int *array, int start, int end)
{

    int pivot;

    if (start < end) {
        pivot = divide(array, start, end);

        // Ordeno la lista de los menores
        quicksort(array, start, pivot - 1);

        // Ordeno la lista de los mayores
        quicksort(array, pivot + 1, end);
    }

}

int* OrdenamientoForm::burbujaSort(int valores[]){

    int* sort = valores;
    bool swapped = false;
    int sorted = 0;
    do{
        swapped = false;
        for(int x = 0; x<(cant-sorted); x++){
            if(sort[x] > sort[x+1]){
                int y = sort[x];
                sort[x] = sort[x+1];
                sort[x+1] = y;
                swapped=true;
            }
        }
        sorted++;
    }while(swapped);
    for(int x = 0; x<300; x++)
        ui->bubble_2->addItem(QString::number(sort[x]));

    return sort;
}

void OrdenamientoForm::swap(int &x,int &y)
{
    int temp=x;
    x=y;
    y=temp;
}
void OrdenamientoForm::heapify(int x, int a[], int n, int hs)
{
    int left=(2*x);
    int right=(2*x)+1;
    int large;
    if((left<=hs)&&(a[left]>a[x]))
    {
        large=left;
    }
    else
    {
        large=x;
    }
    if((right<=hs)&&(a[right]>a[large]))
    {
        large=right;
    }
    if(x!=large)
    {
        swap(a[x],a[large]);
        heapify(large, a, n, hs);
    }
}
void OrdenamientoForm::BuildMaxHeap(int a[], int n, int hs)
{
    for(int i=n/2;i>0;i--)
    {
        heapify(i, a, n, hs);
    }
}
void OrdenamientoForm::HeapSort(int a[], int n)
{

    int hs=n;
    BuildMaxHeap(a,n, hs);
    for(int i=hs;i>1;i--)
    {
        swap(a[1],a[i]);
        hs--;
        heapify(1, a, n, hs);
    }

}

void OrdenamientoForm::on_bubble_clicked()//Buble
{
    QTime inicio = QTime::currentTime();
    burbujaSort(valores1);
    QTime final = QTime::currentTime();
    ui->txtbubble->setText(QString::number(inicio.secsTo(final)));
}

void OrdenamientoForm::on_random_clicked()
{
    for(int x = 0; x<cant; x++){
        int valor = (rand()%1000) +1;
        valores1[x] = valor;
        valores2[x] = valor;
        valores3[x] = valor;
        valores4[x] = valor;
        valores5[x] = valor;
        ui->lista->addItem(QString::number(valor));
    }
}

void OrdenamientoForm::on_quick_clicked()//Bin
{
    QTime inicio = QTime::currentTime();
    binSort(valores2, cant);
    QTime final = QTime::currentTime();
    for(int x = 0; x<300; x++)
        ui->binSort->addItem(QString::number(valores2[x]));
    ui->txtbin->setText(QString::number(inicio.secsTo(final)));
}

void OrdenamientoForm::on_quick_3_clicked()//Quick
{
    QTime inicio = QTime::currentTime();
    quicksort(valores3, 0, cant);
    QTime final = QTime::currentTime();
    for(int x = 0; x<300; x++)
        ui->quick_2->addItem(QString::number(valores3[x]));
    ui->txtquick->setText(QString::number(inicio.secsTo(final)));
}

void OrdenamientoForm::on_pushButton_clicked()//merge
{
    QTime inicio = QTime::currentTime();
    merge_sort(valores4,0,cant);
    QTime final = QTime::currentTime();
    for(int x = 0; x<300; x++)
        ui->merge->addItem(QString::number(valores4[x]));
    ui->txtmerge->setText(QString::number(inicio.secsTo(final)));
}

void OrdenamientoForm::on_pushButton_2_clicked()//Heap
{
    QTime inicio = QTime::currentTime();
    HeapSort(valores5, cant);
    QTime final = QTime::currentTime();
    for(int x = 2; x<302; x++)
        ui->heap->addItem(QString::number(valores5[x]));
    ui->txtheap->setText(QString::number(inicio.secsTo(final)));
}
