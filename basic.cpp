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



using namespace std;
/*//////////////////////////THE CLASSES/////////////////////////////*/


class User {
public:
    string userID;
    string accBikeType;
    int start, end;
    string startStat, endStat;
    User(string ID, string bikes, int st, int en, string staSta, string endSta){
        userID=ID;
        accBikeType=bikes;
        start=st;
        end=en;
        startStat=staSta;
        endStat=endSta;
    }
    User(){
        userID="0";
        accBikeType="0";
        start=0;
        end=0;
        startStat="0";
        endStat="0";
    }
    friend ostream& operator << (ostream &os, const User &person){
        os<< person.userID<<" "<<person.accBikeType<<" "<<person.start<<" "<<person.end<<" "<<person.startStat<<" "<<person.endStat;
        return os;
    }
    int operator / (int a){
        return start/a;
    }
    
    void operator = (const User &b){
        userID=b.userID;
        accBikeType=b.accBikeType;
        start=b.start;
        end=b.end;
        startStat=b.startStat;
        endStat=b.endStat;
     
    }
    
};


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
    vectorClass(int row, T inside)
    {
        arr = new T[row];
        capacity = row;
        current = row;
        for(int i=0;i<row;i++){
            arr[i]=inside;
        }
    }
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
 
    // function to get size of the vector
    int size() { return current; }
 
    // function to get capacity of the vector
    int getcapacity() { return capacity; }
 
    // function to print array elements
    void print()
    {
        for (int i = 0; i < current; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
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
    void addBike(int ID, int rentcount, double initPrice, int startTime){
        id=ID;
        rentCount=rentcount;
        price=initPrice;
        minTime=startTime;
        
    }
    
    friend ostream& operator << (ostream &os, const BicId &bike){
        os<<bike.id<<" "<<bike.rentCount<<" "<<bike.price<<" "<<bike.minTime;
        return os;
    }
    bool operator > (BicId a){
        return price>a.price ? true : false;
    }
    bool operator <= (BicId a){
        return price<=a.price ? true : false;
    }
    void operator = (const BicId a){
        id=a.id;
        rentCount=a.rentCount;
        price=a.price;
        minTime=a.minTime;
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
    BicId *bikes;
    int curr; //if curr == capacity-1 double the capacity, copy semuanya ( num of bikes=curr)
    int capacity;
    BicType(int num, int ID, int rentcount, double initPrice, int startTime){
        key = num;
        left = NULL;
        right = NULL;
        height = 1; // new node is initially
                          // added at leaf

        curr=1;
        capacity=30;
        bikes = new BicId[capacity];
        bikes[curr].addBike(ID, rentcount, initPrice, startTime);
    }
    void add(int ID, int rentcount, double initPrice, int startTime){ //TODO!
        if(curr==capacity-1){
            ResizeArray(bikes, capacity);
            capacity*=2;
        }
        curr++;
        bikes[curr].addBike(ID, rentcount, initPrice, startTime);
    }
    void print(){
        for(int i=1;i<=curr;i++){
            cout<<"B"<<key<<" "<<bikes[i]<<endl;
        }
    }
    void buildHeap(){
        build_maxheap(bikes, curr);
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
 
/* Helper function that allocates a
   new node with the given key and
   NULL left and right pointers. */
BicType* newBicType(int key, int ID, int rentcount, double initPrice, int startTime)
{
    BicType* node = new BicType(key, ID,  rentcount,  initPrice,  startTime);
    
    return(node);
}

BicType* addMoreBike(BicType* node, int ID, int rentcount, double initPrice, int startTime)
{
    node->add(ID,  rentcount,  initPrice,  startTime);
    
    return(node);
}
 
// A utility function to right
// rotate subtree rooted with y
// See the diagram given above.
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
 
// Recursive function to insert a key
// in the subtree rooted with node and
// returns the new root of the subtree.
BicType* insert(BicType* node, int key, int bikeID, int rentcount, double initPrice, int startTime)
{
    /* 1. Perform the normal BST insertion */
    if (node == NULL)
        return(newBicType(key, bikeID,   rentcount,  initPrice, startTime));
    
 
    if (key < node->key)
        node->left = insert(node->left, key, bikeID,   rentcount,  initPrice, startTime);
    else if (key > node->key)
        node->right = insert(node->right, key, bikeID,   rentcount,  initPrice, startTime);
    else // Equal keys are not allowed in BST
        //panggil buat tambahin Bikes ! TODO!!!!!!!!!!
    { addMoreBike(node, bikeID, rentcount, initPrice, startTime);
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

void heapifyRoot(BicType *root){
    if(root != NULL)
    {
        heapifyRoot(root->left);
        root->buildHeap();
        heapifyRoot(root->right);
    }
}
 
/*//////////////////////////THE STATION CLASS/////////////////////////////*/


class Station{
public:
    bool shortestPath; //ud pernah di dijkstra blm
    int numBicType;//number of bicycle type
    BicType* root; //bikin avl tree
    
    Station(){
        root=NULL;
        numBicType=0;
        shortestPath=false;
    }
    void insertBike(int type, int bikeID,int rentcount,double initPrice, int startTime){
        root=insert(root,type, bikeID,  rentcount,  initPrice, startTime);
        numBicType++;
    }
    void outputType(){
        preOrder(root);
    }
    void outputAll(){
        inOrder(root);
    }
    void heapify(){
        heapifyRoot(root);
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





class Node{
    
};

class mainList{
    
};



/*//////////////////////////THE MAIN FUNCTION/////////////////////////////*/
void basic(string selectedCase){
  
    
    
    cout << "start your basic version of data structure final from here!" << endl;
    string casePath= "./testcases/"+selectedCase;
    ifstream map, userReq, bike, bikeInfo;
    map.open(casePath+"/map.txt");
    userReq.open(casePath+"/user.txt");
    bike.open(casePath+"/bike.txt");
    bikeInfo.open(casePath+"/bike_info.txt");
    vectorClass<User> request; //Store user requests
    string temp1, temp2, temp3, temp4;
    int a,b;
    double doubleTemp;
    string line, out;
    
    
   
    int col=1;
    int** point; //dont forget to delete the memory
    
    
    double depreciationConst;
    int rentalCountLim;
    
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
           
          listStation[station].insertBike(bikeType, a, b, doubleTemp, 0);
            
            
        }
        cout<<endl<<endl;
       for(int i=0;i<col;i++){
           cout<<"S"<<i<<endl<<endl;
           listStation[i].heapify();
           cout<<"outputType: "<<endl;
           listStation[i].outputType();
           cout<<endl;
           cout<<"outputAll: "<<endl;
           cout<<endl;
           listStation[i].outputAll();
           cout<<endl;
        }
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
    cout<<"after dijkstra"<<endl<<endl; //di dijkstra kalo butuh aja
    /*for(int i=0;i<col;i++){
        dijkstra(col, point, i);
    }*/
    
    for (int i=0; i<col;i++){
        for(int j=0;j<col;j++){
            cout<<point[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    int flag=0;
    if(userReq.is_open()){
        while(getline(userReq,line)){
            stringstream stream;
            stream<<line;
            stream>>temp1>>temp2>>a>>b>>temp3>>temp4;
            User temp(temp1,temp2,a,b,temp3,temp4);
            request.push_back(temp);
            flag++;
            
        }
        userReq.close();
    }else cout<< "unable to open"<<endl;
  
    countSort<User>(&request,request.size()); //sort the request with manual radix sort
    /* //JANGAN D DELETE ini buat print request.
    for(int i=0;i<request.size();i++){
        cout<<request[i]<<endl;
    }*/
 
   
    
}


