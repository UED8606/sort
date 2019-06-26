// 素数
#define N 2999

int A[N];
int B[N];

// *p と *q の値を入れ替える関数
void swap(int *p, int *q){
    int tmp;
    tmp = *p;
    *p = *q;
    *q = tmp;
}

int quick_select(int A[], int n, int k){
    int i, j, pivot;
    pivot = A[0];
    for(i = j = 1; i < n; i++){
        if(A[i] <= pivot){
            swap(A+i, A+j);
            j++;
        }
    }
    
    if(j == k+1) return pivot;
    else if(j < k+1) return quick_select(A+j, n-j, k-j);
    else return quick_select(A+1, j-1, k);
}
//k+1番目に小さい値を返す

int median_of_median(int A[], int n){
    if(n <= 5 && n%2 == 1) return quick_select(A, n, (n-1)/2);
    else if(n <= 5) return (quick_select(A, n, n/2-1) + quick_select(A, n ,n/2))/2;
    else {
        int i,x;
        x = 0;
        for(i = 0;i < (n+9)/5;i++){
            if(n-x>=5){
                B[i] = median_of_median(A+x, 5);
                x=x+5;
            }
            else B[i] = median_of_median(A+x, n-x);
        }
        return median_of_median(B, (n+4)/5);
    }
}

int main(){
    int i;
    A[0] = 0;
    A[1] = 17; //原始元
    for(i=2;i<N;i++){
        A[i] = (long long int) A[i-1] * A[1] % N;
    }
    for(i=0;i<N;i++){
        if(quick_select(A, N, i) != i) printf("ERROR %d %d\n", i, quick_select(A, N, i));
        //    printf("%d th element is %d\n", i, quick_select(A, N, i));
    }
}
