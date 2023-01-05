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
/*//////////////////////////THE STATION CLASS/////////////////////////////*/

class Station{
    bool shortestPath;
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
        while(getline(bike,line)){
            stringstream stream;
            stream<<line;
            cout<<line<<endl;
            stream>>temp1>>a>>temp2>>doubleTemp>>b;
            //cout<<temp1<<" "<<a<<" "<<temp2<<" "<<doubleTemp<<" "<<b<<endl;
            
        }
        bike.close();
    }
    
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
    
    for(int i=0;i<request.size();i++){
        cout<<request[i]<<endl;
    }
 
   
    
}


