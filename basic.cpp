#include "./nthu_bike.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <cmath>
#define maxBikeType 50
int** point; //matrix map nya di bikin universal variable spy bisa di akses di semua class dll
double depreciationConst;
int rentalCountLim;




using namespace std;
/*////////////////////////VECTOR CLASS///////////////////////*/
template <typename T> class vectorClass {

    // arr is the integer pointer
    // which stores the address of our vector
    T* arr;
 
    // capacity is the total storage
    // capacity of the vector
    int capacity;
 
    // current is the number of elements
    // currently present in the vector
    int current;
public:

    // Default constructor to initialise
    // an initial capacity of 1 element and
    // allocating storage using dynamic allocation
    vectorClass()
    {
        arr = new T[1];
        capacity = 1;
        current = 0;
    }
    /*vectorClass(int row, T inside)
    {
        arr = new T[row];
        capacity = row;
        current = row;
        for(int i=0;i<row;i++){
            arr[i]=inside;
        }
    }*/
       //destructor to deallocate storage allocated by dynamic allocation
       //to prevent memory leak
 
    // Function to add an element at the last
    void push_back(T data)
    {
 
        // if the number of elements is equal to the
        // capacity, that means we don't have space to
        // accommodate more elements. We need to double the
        // capacity
        if (current == capacity) {
            T* temp = new T[2 * capacity];
 
            // copying old array elements to new array
            for (int i = 0; i < capacity; i++) {
                temp[i] = arr[i];
            }
 
            // deleting previous array
            delete[] arr;
            capacity *= 2;
            arr = temp;
        }
 
        // Inserting data
        arr[current] = data;
        current++;
    }
 
    // function to add element at any index
    void push_back(T data, int index)
    {
 
        // if index is equal to capacity then this
        // function is same as push defined above
        if (index == capacity)
            push_back(data);
        else
            arr[index] = data;
    }
 
    // function to extract element at any index
    T get(int index)
    {
 
        // if index is within the range
        if (index < current)
            return arr[index];
    }
    T& operator [](int i){
                return arr[i]; //INI YANG BIKIN ERROR ANJENG, return type ny harus address bkn cm T doang EEK
    }
 
    // function to delete last element
    void pop() { current--; }
    
    void clear(){current=0;}
 
    // function to get size of the vector
    int size() { return current; }
 
    // function to get capacity of the vector
    int getcapacity() { return capacity; }
 
    // function to print array elements
    void outputVector()
    {
        for (int i = 0; i < current; i++) {
            cout << arr[i] << endl;
        }
    
    }
    int operator /(int i){
        return arr[current]/i;
    }
    void operator =(T i){
        arr[current]=i;
    }
    T* operator &(){
        return arr;
    }
    
    T& operator *(){
        return *arr; //gatau bener ap salah
    }
    
    void operator =(vectorClass<T> i){
        arr=i.arr;
        capacity=i.capacity;
     
        // current is the number of elements
        // currently present in the vector
        current=i.current;
    }

};


/*//////////////////////////THE CLASSES/////////////////////////////*/
class User {
public:
    string userID;
    vectorClass<int> accBikeType; //debug
    int start, end;
    int startStat, endStat;
    bool *bikeType;
    User(string ID, vectorClass<int> bikes, int st, int en, int staSta, int endSta){
        bikeType = new bool[maxBikeType];
        for(int i=0;i<maxBikeType;i++){
            bikeType[i]=false;
        }
        accBikeType=bikes;
        int index=0;
        userID=ID;
        while(index<bikes.size()){
            
            bikeType[bikes[index]]=true;
            index++;
        }
        start=st;
        end=en;
        startStat=staSta;
        endStat=endSta;
    }
    User(){
        vectorClass<int> *temp = new vectorClass<int>;
        bikeType = new bool[maxBikeType];
        for(int i=0;i<maxBikeType;i++){
            bikeType[i]=false;
        }
        accBikeType=*temp;
        userID="0";
        start=0;
        end=0;
        startStat=0;
        endStat=0;
    }
    friend ostream& operator << (ostream &os,  User &person){
        int index=0;
        os<< person.userID<<" "; //user debug
       
    
        while(index<person.accBikeType.size()){
            if(index!=0)os<<",";
            os<<"B"<<person.accBikeType[index];
            index++;
        }
        os<<" "<<person.start<<" "<<person.end<<" "<<person.startStat<<" "<<person.endStat;
        return os;
    }
    int operator / (int a){
        return start/a;
    }
    
    void operator = ( User &b){ //gara gara ini anjengg, biketype nya hrs d samain juga AAAAAA
        for(int i=0;i<maxBikeType;i++){
            bikeType[i]=b.bikeType[i];
        }
        userID=b.userID;
        accBikeType=b.accBikeType;
        start=b.start;
        end=b.end;
        startStat=b.startStat;
        endStat=b.endStat;
     
    }
    bool getBool(int type){
        return bikeType[type];
    }
    bool operator > (const User &b){
        return stoi(userID.substr(1))>stoi(b.userID.substr(1));
    }
    
};



/*/////////////////////////////// DIJKSTRA ALGO /////////////////////////////*/
int minDistance(int dist[], bool sptSet[], int sz)
{
    // Initialize min value
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < sz; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}

// Function that implements Dijkstra's single source
// shortest path algorithm for a graph represented using
// adjacency matrix representation
void dijkstra(int sz, int** graph, int src)
{
    int dist[sz]; // The output array.  dist[i] will hold the
                 // shortest
    // distance from src to i
 
    bool sptSet[sz]; // sptSet[i] will be true if vertex i is
                    // included in shortest
    // path tree or shortest distance from src to i is
    // finalized
 
    // Initialize all distances as INFINITE and stpSet[] as
    // false
    for (int i = 0; i < sz; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
 
    // Distance of source vertex from itself is always 0
    dist[src] = 0;
 
    // Find shortest path for all vertices
    for (int count = 0; count < sz - 1; count++) {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to
        // src in the first iteration.
        int u = minDistance(dist, sptSet, sz);
 
        // Mark the picked vertex as processed
        sptSet[u] = true;
 
        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < sz; v++)
 
            // Update dist[v] only if is not in sptSet,
            // there is an edge from u to v, and total
            // weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v]
                && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
 
    // print the constructed distance array
    for(int i=0;i<sz;i++){
        graph[src][i]=dist[i];
        graph[i][src]=dist[i];//
    }
    
}

/*/////////////////////////////////////////MAX HEAP///////////////////////*/
template<typename T>
void max_heap(T *a, int m, int n) {
   T t;
    int j;
   t = a[m];
   j = 2 * m;
   while (j <= n) {
      if (j < n && a[j+1] > a[j])
         j = j + 1;
      if (t > a[j])
         break;
      else if (t <= a[j]) {
         a[j / 2] = a[j];
         j = 2 * j;
      }
   }
   a[j/2] = t;
   return;
}
template<typename T>
void build_maxheap(T *a,int n) { //TODO!! build_maxheap dilakuin setelah semuanya masuk, mesti bikin jg pas dy delete spy O(log n)
   int k;
   for(k = n/2; k >= 1; k--) {
      max_heap(a,k,n);
   }
}
/*//////////////////HEAPIFY///////////////////////////////////////////////*/
template<typename T>

void heapifyMaxHeap(T *arr, int n, int i)
{
    int largest = i; // Initialize largest as root
    int l = 2 * i ; // left = 2*i + 1
    int r = 2 * i + 1; // right = 2*i + 2
 
    // If left child is larger than root
    if (l <= n && arr[l] > arr[largest]) //TODO , yakin <n ?
        largest = l;
 
    // If right child is larger than largest so far
    if (r <= n && arr[r] > arr[largest])
        largest = r;
 
    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);
 
        // Recursively heapify the affected sub-tree
        heapifyMaxHeap(arr, n, largest);
    }
}
/*//////////////////////////////HEAP DELETION/////////////////////////////*/


// Function to delete the root from Heap
template<typename T>
void heapifyInsertion(T* arr, int n, int i)
{
    // Find parent
    int parent = (i - 1) / 2;
 
    if (parent> 0) {
        // For Max-Heap
        // If current node is greater than its parent
        // Swap both of them and call heapify again
        // for the parent
        if (arr[i] > arr[parent]) {
            swap(arr[i], arr[parent]);
 
            // Recursively heapify the parent node
            heapifyInsertion(arr, n, parent);
        }
    }
}
 


 
/*///////////////////////////////////RESIZEEEE////////////////////////////*/
template<typename T>
void ResizeArray(T *&orig, int size) {
    T *resized = new T[size * 2];
    for (int i = 0; i < size; i ++)
        resized[i] = orig[i];
    delete [] orig;
    orig = resized;
}
/*////////////////////////////BICYCLE ID CLASS////////////////////////////*/
class BicId{ //TODO!!
public:
    int bikeType;
    int id;
    int rentCount;
    double price;
    int minTime; //(if the start time of the user is < than time than reject)
    
    BicId(){
        id=0;
        rentCount=0;
        price=0.0;
        minTime=0;
    }
    BicId(int type, int ID, int rentcount, double currPrice, int startTime){
        bikeType = type;
        id=ID;
        rentCount=rentcount;
        price=currPrice;
        minTime=startTime;
    }
    friend ostream& operator << (ostream &os, const BicId &bike){
        
        os<<"B"<<bike.bikeType<<" "<<bike.id<<" "<<bike.rentCount<<" "<<bike.price<<" "<<bike.minTime;
        return os;
    }
    bool operator > (BicId a){ //todo
        return price>a.price ? true : false;
    }
    bool operator <= (BicId a){//todo
        
        return price<=a.price ? true : false;
    }
    bool operator >= (BicId a){//todo
        
        return price>=a.price ? true : false;
    }
    void operator = (const BicId a){ //todo
        id=a.id;
        rentCount=a.rentCount;
        price=a.price;
        minTime=a.minTime;
        bikeType = a.bikeType;
    }
    
};
/*//////////////////////////AVL TREE THINGY///////////////////////////////*/
class BicType
{
    public:
    int key;
    BicType *left;
    BicType *right;
    int height;
   // BicId *bikes;
    int curr; //if curr == capacity-1 double the capacity, copy semuanya ( num of bikes=curr)
    BicType(int num){
        key = num;
        left = NULL;
        right = NULL;
        height = 1; // new node is initially
                          // added at leaf
        curr=1;
    }
    
    void print(){
        cout<<"B"<<key<<" has "<<curr<<" bikes"<<endl;
    }
    
    int size(){
        return curr; //notes : if curr==0 delete bic type
    }

};
 
// A utility function to get the
// height of the tree
int height(BicType *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 
// A utility function to get maximum
// of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}
 



BicType *rightRotate(BicType *y)
{
    BicType *x = y->left;
    BicType *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;
 
    // Return new root
    return x;
}
 
// A utility function to left
// rotate subtree rooted with x
// See the diagram given above.
BicType *leftRotate(BicType *x)
{
    BicType *y = x->right;
    BicType *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    // Update heights
    x->height = max(height(x->left),
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;
 
    // Return new root
    return y;
}
 
// Get Balance factor of node N
int getBalance(BicType *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
BicType* minValueNode(BicType* node)
{
    BicType* current = node;
  
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
  
    return current;
}

BicType* deleteNode(BicType* root, int key)
{
      
    // STEP 1: PERFORM STANDARD BST DELETE
    if (root == NULL)
        return root;
  
    // If the key to be deleted is smaller
    // than the root's key, then it lies
    // in left subtree
    if ( key < root->key )
        root->left = deleteNode(root->left, key);
  
    // If the key to be deleted is greater
    // than the root's key, then it lies
    // in right subtree
    else if( key > root->key )
        root->right = deleteNode(root->right, key);
  
    // if key is same as root's key, then
    // This is the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) ||
            (root->right == NULL) )
        {
            BicType* temp = root->left ?
                         root->left :
                         root->right;
  
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
            *root = *temp; // Copy the contents of
                           // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            BicType* temp = minValueNode(root->right);
  
            // Copy the inorder successor's
            // data to this node
            root->key = temp->key;
  
            // Delete the inorder successor
            root->right = deleteNode(root->right,
                                     temp->key);
        }
    }
  
    // If the tree had only one node
    // then return
    if (root == NULL)
    return root;
  
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left),
                           height(root->right));
  
    // STEP 3: GET THE BALANCE FACTOR OF
    // THIS NODE (to check whether this
    // node became unbalanced)
    int balance = getBalance(root);
  
    // If this node becomes unbalanced,
    // then there are 4 cases
  
    // Left Left Case
    if (balance > 1 &&
        getBalance(root->left) >= 0)
        return rightRotate(root);
  
    // Left Right Case
    if (balance > 1 &&
        getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
  
    // Right Right Case
    if (balance < -1 &&
        getBalance(root->right) <= 0)
        return leftRotate(root);
  
    // Right Left Case
    if (balance < -1 &&
        getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
  
    return root;
}
// Recursive function to insert a key
// in the subtree rooted with node and
// returns the new root of the subtree.
BicType* insert(BicType* node, int key)
{
    /* 1. Perform the normal BST insertion */
    if (node == NULL){
        BicType* newbiketype = new BicType(key);
        
        return newbiketype ;
    }
    
 
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Equal keys are not allowed in BST
        //panggil buat tambahin Bikes ! TODO!!!!!!!!!!
    { node->curr++; //todo
        return node;}
 
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                        height(node->right));
 
    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = getBalance(node);
 
    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    
    return node;
}
void preOrder(BicType *root)
{
    if(root != NULL)
    {
        cout << root->key << " ";
        
        preOrder(root->left);
        preOrder(root->right);
    }
}
void inOrder(BicType *root)
{
    if(root != NULL)
    {
        inOrder(root->left);
        root->print();
        inOrder(root->right);
    }
}

/*//////////////////////////////TAKE THE BIKE TYPES///////////////////////*/
vectorClass<int> bikeTypeConvert(string biketypes){
    vectorClass<int> temp;
    stringstream stream(biketypes);
    int store;
    string token;
    while(getline(stream,token,',')){
        store=stoi(token.substr(1));
        temp.push_back(store);
    }
    return temp;
}
BicType* search( BicType* root, int key)
{
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->key == key)
       return root;
    
    // Key is greater than root's key
    if (root->key < key)
       return search(root->right, key);
 
    // Key is smaller than root's key
    return search(root->left, key);
}
 /*////////////////////MERGE SORTING ALGO/////////////////////////////////*/
template<typename T>
void merge(T array[], int const left, int const mid,
           int const right)
{
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;
 
    // Create temp arrays
    auto *leftArray = new T[subArrayOne],
         *rightArray = new T[subArrayTwo];
 
    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];
 
    auto indexOfSubArrayOne
        = 0, // Initial index of first sub-array
        indexOfSubArrayTwo
        = 0; // Initial index of second sub-array
    int indexOfMergedArray
        = left; // Initial index of merged array
 
    // Merge the temp arrays back into array[left..right]
    while (indexOfSubArrayOne < subArrayOne
           && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne]
            >= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray]
                = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray]
                = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray]
            = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray]
            = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}
 
// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted */
template<typename T>
void mergeSort(T array[], int const begin, int const end)
{
    if (begin >= end)
        return; // Returns recursively
 
    auto mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}
/*//////////////////////////THE STATION CLASS/////////////////////////////*/


class Station{
public:
    //bool shortestPath; //dijkstra lgsg aj
    int numBic;//number of bicycle type
   // BicType* root; //bikin avl tree
    vectorClass<BicId> theBikes;
    
    Station(){
       // root=NULL;
        numBic=0;
        
    }
    void insertBike(int type, int bikeID,int rentcount,double initPrice, int startTime){
       // root=insert(root,type); // TODO
        BicId* temp= new BicId(type, bikeID,  rentcount,  initPrice, startTime);
        theBikes.push_back(*temp);
        numBic++;
    }

    BicId* deleteBike(int startTime, int endTime, int station1, int station2, bool* type){
        int index=0;
        BicId* temp = NULL;
     
        while(theBikes.size()>0&&index<theBikes.size()){
            
            if((theBikes[index].minTime<=startTime)&&((startTime+point[station1][station2])<endTime)&&(type[theBikes[index].bikeType]==true)){ //COMEBACK  //todo
                /*if((--search(root, theBikes[index].bikeType)->curr)<1){
                    root=deleteNode(root, theBikes[index].bikeType);
                    
                    
                }*/
                numBic--;
                //kurangin jumlah sepeda di bic type di station ini
                //cek klo curr == 0 delete node bic type nya
                
                swap(theBikes[index], theBikes[theBikes.size()-1]);
                temp=&theBikes[theBikes.size()-1];
                //debug
                cout<<endl<<"sebelum pop: "<<endl<<theBikes.size()<<endl;
                theBikes.pop();
                if(theBikes.size()>0){
                    cout<<"setelah pop: "<<theBikes.size()<<endl;
                    mergeSort(&theBikes, 0, theBikes.size()-1);
                    
                }
                break;
            }
            index++;
        }
        
        return temp;
    }
    void printBike(){
        theBikes.outputVector();
    }
    /*void outputType(){
        preOrder(root);
    }
    void outputInfo(){
        inOrder(root);
    }*/
    void mergesort(){
        mergeSort(&theBikes, 0, theBikes.size()-1);
    }
    
};
/*//////////////////////////THE SORTING FUNCTION/////////////////////////////*/



template<class T>
void countSort(T *arr, int n)

{
    for(int exp=1;exp<1440;exp*=10){
        vectorClass<T> output;
        
        int i, count[10] = { 0 };
        
        for (i = 0; i < n; i++){
            count[(arr[i] / exp) % 10]++;
            T temp1;
            output.push_back(temp1);
        }
        
        for (i = 1; i < 10; i++){
            count[i] += count[i - 1];
        }
        
        for (i = n - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }
        
        for (i = 0; i < n; i++){
            arr[i] = output[i];
        }
    }
}

/*///////////////////////////////INSERTION SORT///////////*/
template <typename T>
void insertionSort(T arr[], int n)
{
    int i,j;
    T key;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
 
        // Move elements of arr[0..i-1],
        // that are greater than key, to one
        // position ahead of their
        // current position
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}


/*//////////////////////////THE MAIN FUNCTION/////////////////////////////*/
void basic(string selectedCase){
  
    
    
    cout << "start your basic version of data structure final from here!" << endl;
    string casePath= "./testcases/"+selectedCase;
    ifstream map, userReq, bike, bikeInfo;
    
    ofstream transferLog("transfer_log.txt");
    ofstream reqResult("user_result.txt");
    ofstream finalBikes("station_status.txt");

    map.open(casePath+"/map.txt");
    userReq.open(casePath+"/user.txt");
    bike.open(casePath+"/bike.txt");
    bikeInfo.open(casePath+"/bike_info.txt");
    vectorClass<User> request; //Store user requests
    string temp1, temp2, temp3, temp4;
    int a,b,c,d;
    double doubleTemp;
    string line, out;

   
    int col=1;
     //dont forget to delete the memory
    
    
    
    
    Station* listStation;
    
    if(map.is_open()) //mapping
    {
        
        bool flag=false;
        int station1,station2, dist;
        vectorClass<int> firstvector;
        firstvector.push_back(0);
        while(getline(map,line)){
            stringstream stream;
            stream<<line;
            stream>>temp1>>temp2>>dist;
            station1 = stoi(temp1.substr(1));
            station2 = stoi(temp2.substr(1));
            cout<<"angka: "<<dist<<endl; //debug
            if(station1==0){
                firstvector.push_back(dist);
                col++;
             } else {
                 if(flag==false){ //first time so make the matrix
                  
                     point = new int*[col];
                     for(int i=0;i<col;i++){
                         point[i]= new int[col];
                         
                     }
                     for(int i=0;i<col;i++){
                        point[0][i]=firstvector[i];
                         point[i][0]=firstvector[i];
                     }
                     point[station1][station2]=dist;
                     point[station2][station1]=dist;
                     
                     flag=true;
                     
                 }else{
                     point[station1][station2]=dist;
                     point[station2][station1]=dist;
                 }
             }
            }

map.close();
    } else cout<< "unable to open"<<endl<<endl;
    
    listStation = new Station[col];
    
    
    if(bikeInfo.is_open()){ //bike info nya, jd harga, sm depreciation const sama rental count lim
        
  
        bikeInfo>>depreciationConst;
        bikeInfo>>rentalCountLim;
        cout<<"rentalCount: "<<rentalCountLim<<endl;
        cout<<"depreciationConst: "<<depreciationConst<<endl;
        while(getline(bikeInfo,line)){
            stringstream stream;
            stream<<line;
            cout<<line<<endl;
        }
        bikeInfo.close();
    }
    
    if(bike.is_open()){ //tiap bike id nya buat tiap bike type ada di station mana
        //B0 0 S1 10 0
        // Bike_Type, Bike_Id, Station_Id, Rental_Price, and Rental_Count
        //BicType* node, int key, int bikeID, int rentcount, double initPrice, int startTime
        //int type, int bikeID,int rentcount,double initPrice, int startTime
        int station, bikeType;
        while(getline(bike,line)){
            stringstream stream;
            stream<<line;
            cout<<line<<endl;
            stream>>temp1>>a>>temp2>>doubleTemp>>b;
            station = stoi(temp2.substr(1));
            bikeType = stoi(temp1.substr(1));
            if(doubleTemp>=0&&b<rentalCountLim&&station<col){
                listStation[station].insertBike(bikeType, a, b, doubleTemp, 0);
            } //kalo hargany lebih besar = dari 0, dan rental count kurang dari rental count lim masih bisa d pake, jadi di insert bike nya else gaush masuk
            
            
        }
        cout<<endl<<endl;
       
        bike.close();
    }
    
    
    cout<<endl;
    cout<<"before dijkstra"<<endl;
    for (int i=0; i<col;i++){
        for(int j=0;j<col;j++){
            cout<<point[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<"after dijkstra"<<endl<<endl;
    for(int i=0;i<col;i++){
        dijkstra(col, point, i);
    }
    
    for (int i=0; i<col;i++){
        for(int j=0;j<col;j++){
            cout<<point[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    int flag=0;
    vectorClass<int> intTemp;
    //User_Id, Accept_Bike_Type, Start_Time, End_Time, Start_Point, End_Point
    //U4 B1 327 469 S3 S1
    if(userReq.is_open()){
        intTemp.clear();
        while(getline(userReq,line)){
            stringstream stream;
            stream<<line;
            stream>>temp1>>temp2>>a>>b>>temp3>>temp4;
            intTemp=bikeTypeConvert(temp2);
            c=stoi(temp3.substr(1));
            d=stoi(temp4.substr(1));
         //   User(string ID, vectorClass<int> bikes, int st, int en, int staSta, int endSta){
            User temp(temp1,intTemp,a,b,c,d);//temp3, 4 jadi int, potong S depannya, temp2 jadi vector of int
            request.push_back(temp);
            flag++;
            
        }
        userReq.close();
    }else cout<< "unable to open"<<endl;
    
    insertionSort(&request,request.size());
  
    countSort<User>(&request,request.size()); //sort the request with manual radix sort
    
    for(int i=0;i<col;i++){
        listStation[i].mergesort();
    }
    for(int i=0;i<request.size();i++){
        cout<<request[i]<<endl;
    }
    
    //DEBUG
    /*
    BicId* temporaryDebug;
    
    for(int i=0;i<col;i++){
        
        cout<<"S"<<i<<endl<<endl;
        cout<<"outputType: "<<endl;
        listStation[i].outputType();
        cout<<endl;
        cout<<"outputInfo: "<<endl;
        cout<<endl;
        listStation[i].outputInfo();
        cout<<endl;
        cout<<"di station "<<i<<" ada bike:"<<endl;
        listStation[i].printBike();
        cout<<endl;
        listStation[i].mergesort();
        cout<<"di station "<<i<<" ada bike yang uda di atur:"<<endl;
        listStation[i].printBike();
        cout<<endl;
        temporaryDebug=listStation[i].deleteBike(4);
        cout<<"di station "<<i<<" ada bike yang uda di delete paling tinggi:"<<endl;
        listStation[i].printBike();
        cout<<endl;
        cout<<"outputType setelah deletion: "<<endl;
        listStation[i].outputType();
        cout<<endl;
        
     }*/
    cout<<endl;
    /*
    cout<<"mulai dr sini"<<endl;
    listStation[3].outputInfo();
    cout<<endl<<endl;
    
    listStation[3].root->left->deleteRoot();
    
    cout<<endl<<endl;
    
    listStation[3].outputInfo();
    
    
    cout<<endl<<"kelar"<<endl;

    
    */
    
    for(int i=0;i<col;i++){
        
        cout<<"S"<<i<<endl<<endl;
        /*
        cout<<"outputType sebelum proses: "<<endl;
        listStation[i].outputType();
        cout<<endl;
        cout<<"outputInfo sebelum proses: "<<endl;
        cout<<endl;
        listStation[i].outputInfo();
        cout<<endl;*/
        cout<<"di station "<<i<<" ada bike:"<<endl;
        listStation[i].printBike();
        cout<<endl;
        
        
     }

    intTemp.clear();
    int indexReq=0;
    int indexBikeType=0;
    int indexBikeTypeVector;
    BicId* bikeStore=NULL;
    int revenue;

    while(indexReq<request.size()){
        indexBikeType=0;
        //cout<<request[indexReq]<<endl;
        bikeStore=listStation[request[indexReq].startStat].deleteBike(request[indexReq].start,request[indexReq].end, request[indexReq].startStat, request[indexReq].endStat, request[indexReq].bikeType);
        if(bikeStore==NULL){
            reqResult<<request[indexReq].userID<<" 0 0 0 0 0"<<endl;
        } else {
            //print ke transfer log
            transferLog<<bikeStore->id<<" S"<<request[indexReq].startStat<<" S"<<request[indexReq].endStat<<" "<<request[indexReq].start<<" "<<request[indexReq].start+point[request[indexReq].startStat][request[indexReq].endStat]<<" "<<request[indexReq].userID<<endl;
            //print ke reqResult
            revenue=point[request[indexReq].startStat][request[indexReq].endStat]*(bikeStore->price);
            
            reqResult<<request[indexReq].userID<<" 1 "<<bikeStore->id<<" "<<request[indexReq].start<<" "<<request[indexReq].start+point[request[indexReq].startStat][request[indexReq].endStat]<<" "<<revenue<<endl;
            /*
             void insertBike(int type, int bikeID,int rentcount,double initPrice, int startTime){
                // root=insert(root,type); // TODO
                 BicId* temp= new BicId(type, bikeID,  rentcount,  initPrice, startTime);
                 theBikes.push_back(*temp);
                 numBic++;
             }
             */
            //tambahin ke station end, yg ud d modifin, skalian di cek satu persatu
            if(bikeStore->rentCount<rentalCountLim-1&&(bikeStore->price-depreciationConst)>0.0){
                listStation[request[indexReq].endStat].insertBike(bikeStore->bikeType, bikeStore->id, bikeStore->rentCount+1,bikeStore->price-depreciationConst, request[indexReq].start+point[request[indexReq].startStat][request[indexReq].endStat]);
                
            }
            
        }
        
       
        
       
        indexReq++;
    }
    cout<<endl<<endl<<"PROSEESSSSS!!!!"<<endl<<endl;
    for(int i=0;i<col;i++){
        
        cout<<"S"<<i<<endl<<endl;
        cout<<"di station "<<i<<" ada bike:"<<endl;
        listStation[i].printBike();
        cout<<endl;
        
        
     }
    
     transferLog.close();
     reqResult.close();
     finalBikes.close();

}



