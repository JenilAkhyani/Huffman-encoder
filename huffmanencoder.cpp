#include<bits/stdc++.h>
using namespace std;
struct heapnode{
    char item;
    int freq;
    struct heapnode *left,*right;
}*root;
struct heap{
    int size;
    int capacity;
    struct heapnode **array;
};
void printarray(int arr[],int n){
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);

    printf("\n");
}
int isLeaf(struct heapnode *root) {
  return !(root->left) && !(root->right);
}
void printcode(struct heapnode *root,int arr[],int top){
    if (root->left) {
        arr[top] = 0;
        printcode(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        printcode(root->right, arr, top + 1);
    }
    if (isLeaf(root)) {
        printf("  %c   | ", root->item);
        printarray(arr, top);
    }
    
}
void buildHtree(char pchar[],int pfreq[],int size){

    struct heap *heap=(struct heap*)malloc(sizeof(struct heap));
    heap->capacity=size;
    heap->array=(struct heapnode**)malloc(heap->capacity*sizeof(struct heapnode*));
    heap->size=size-1;
    for(int i=0;i<size;i++){
        heap->array[i]=(struct heapnode*)malloc(sizeof(struct heapnode));
        heap->array[i]->left=heap->array[i]->right=NULL;
        heap->array[i]->item=pchar[i];
        heap->array[i]->freq=pfreq[i];
    }
    while(heap->size>0){
        if(root==NULL){
            root=(struct heapnode*)malloc(sizeof(struct heapnode));
            (root->left)=(heap->array[(heap->size)--]);
            (root->right)=(heap->array[(heap->size)--]);
            root->item='$';
            root->freq=root->left->freq+root->right->freq;
        }
        else{
            struct heapnode *temp;
            temp=(struct heapnode*)malloc(sizeof(struct heapnode));
            if(root->freq+(heap->array[heap->size]->freq) < (heap->array[heap->size]->freq+heap->array[heap->size-1]->freq)){
                if(root->freq < (heap->array[heap->size]->freq)){
                    temp->left=root;
                    temp->right=heap->array[(heap->size)--];
                    temp->item='$';
                    temp->freq=temp->left->freq+temp->right->freq;
                    root=temp;
                }
                else{
                    temp->right=root;
                    temp->left=heap->array[(heap->size)--];
                    temp->item='$';
                    temp->freq=temp->left->freq+temp->right->freq;
                    root=temp;
                }
            }
            else{
                (temp->left)=(heap->array[(heap->size)--]);
                (temp->right)=(heap->array[(heap->size)--]);
                temp->item='$';
                temp->freq=temp->left->freq+temp->right->freq;
                struct heapnode *temp1;
                temp1=(struct heapnode*)malloc(sizeof(struct heapnode));
                if(root->freq < temp->freq){
                    temp1->left=root;
                    temp1->right=temp;
                    temp1->item='$';
                    temp1->freq=root->freq+temp->freq;
                    root=temp1;
                }
                else{
                    temp1->right=root;
                    temp1->left=temp;
                    temp1->item='$';
                    temp1->freq=root->freq+temp->freq;
                    root=temp1;
                }
            }
        }
    }
    if(heap->size==0){
        struct heapnode *temp;
        temp=(struct heapnode*)malloc(sizeof(struct heapnode));
        if(root==NULL){
            root=(struct heapnode*)malloc(sizeof(struct heapnode));
            (root->left)=(heap->array[(heap->size)--]);
            root->item='$';
            root->freq=root->left->freq;
            root->right=NULL;
        }
        else{

            if(root->freq < heap->array[heap->size]->freq){
                temp->left=root;
                temp->right=heap->array[heap->size];
                temp->freq=root->freq+heap->array[heap->size]->freq;
                temp->item='$';
                root=temp;
            }
            else{
                temp->right=root;
                temp->left=heap->array[heap->size];
                temp->freq=root->freq+heap->array[heap->size]->freq;
                temp->item='$';
                root=temp;
            }
        }
    }
    int arr[54],top=0;
    printcode(root,arr,top);
    return;
}


int main(){
    int freq[54]={0};
    string in;
    cout<<"Enter the message you want to send:"<<endl;
    cout<<"NOTE:The message can contain space and full stop also "<<endl;
    getline(cin,in);

    for(int i=0;i<in.size();i++){
        if(in[i]>='A'&&in[i]<='Z'){
            freq[(in[i]-65)]++;
        }
        else if(in[i]>='a'&&in[i]<='z'){
            freq[(in[i]-71)]++;
        }
        else if(in[i]==32){
            freq[52]++;
        }
        else{
            freq[53]++;
        }
    }
    char *pchar;
    pchar=(char *)malloc(1*sizeof(char));
    int count=0;
    int *pfreq;
    pfreq=(int *)malloc(1*sizeof(int));
    for(int j=0;j<54;j++){
        if(freq[j]!=0){
            if(count!=0){
                    pchar=(char*)realloc(pchar,(count+1)*sizeof(char));
                    pfreq=(int*)realloc(pfreq,(count+1)*sizeof(int));
                }
            if(j<26){
                cout<<"The frequency of "<<(char)('A'+j)<<" is:"<<freq[j]<<endl;
                pchar[count]=(char)('A'+j);
                pfreq[count]=freq[j];
                count++;
            }
            else if(j<52){
                cout<<"The frequency of "<<(char)('A'+j+6)<<" is:"<<freq[j]<<endl;
                pchar[count]=(char)('A'+j+6);
                pfreq[count]=freq[j];
                count++;
            }
            else if(j==52){
                cout<<"The frequency of space is:"<<freq[j]<<endl;
                pchar[count]=(char)(' ');
                pfreq[count]=freq[j];
                count++;
            }
            else{
                cout<<"The frequency of . is:"<<freq[j]<<endl;
                pchar[count]=(char)('.');
                pfreq[count]=freq[j];
                count++;
            }
        }
    }
    cout<<endl;
    for(int i=0;i<count-1;i++){
        for(int j=i+1;j<count;j++){
            if(pfreq[i]<pfreq[j]){
                int temp1;
                temp1=pfreq[i];
                pfreq[i]=pfreq[j];
                pfreq[j]=temp1;
                char temp2;
                temp2=pchar[i];
                pchar[i]=pchar[j];
                pchar[j]=temp2;
            }
        }
    }
    for(int i=0;i<count;i++){
        cout<<"char:"<<pchar[i]<<" -> "<<pfreq[i]<<endl;
    }
    buildHtree(pchar,pfreq,count);
    
    return 0;
}