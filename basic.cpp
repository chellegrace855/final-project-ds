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
template <typename T>
class vectorClass {

    T* arr;
 
    int capacity;
 
    int current;
public:

    vectorClass()
    {
        arr = new T[1];
        capacity = 1;
        current = 0;
    }
    ~ vectorClass()
    {
        delete [] arr;
    }
    
    void push_back(T data)
    {

        if (current == capacity) {
            T* temp = new T[2 * capacity];
 
            for (int i = 0; i < capacity; i++) {
                temp[i] = arr[i];
            }
 
            delete[] arr;
            capacity *= 2;
            arr = temp;
        }
 
        arr[current] = data;
        current++;
    }
 
    void push_back(T data, int index)
    {
 
        if (index == capacity)
            push_back(data);
        else
            arr[index] = data;
    }
 
  
    T get(int index)
    {
 
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
            cout <<arr[i] << "\n";
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
class BicId{
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
        
        os<<bike.id<<" "<<"B"<<bike.bikeType<<" "<<bike.price<<" "<<bike.rentCount<<"\n";
        return os;
    }
    bool operator > (BicId a){ //todo
        return price>a.price ? true : false;
    }
    bool operator <= (BicId a){//todo
        
        return price<=a.price ? true : false;
    }
    bool operator >= (BicId a){//todo
        if (price==a.price){
            return id<a.id? true:false;
        }
        return price>a.price ? true : false;
    }
    void operator = (const BicId a){ //todo
        id=a.id;
        rentCount=a.rentCount;
        price=a.price;
        minTime=a.minTime;
        bikeType = a.bikeType;
    }
    
};

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
    vectorClass<BicId> theBikes;
    
    Station(){
       // root=NULL;
     
        vectorClass<BicId> *a = new vectorClass<BicId>;
        theBikes= *a;
        
    }
    void insertBike(int type, int bikeID,int rentcount,double initPrice, int startTime){
       // root=insert(root,type); // TODO
        BicId* temp= new BicId(type, bikeID,  rentcount,  initPrice, startTime);
        theBikes.push_back(*temp);

    }

    BicId* deleteBike(int startTime, int endTime, int station1, int station2, bool* type){
        int index=0;
        BicId* temp = NULL;
     
        while(theBikes.size()>0&&index<theBikes.size()){
            
            if((theBikes[index].minTime<=startTime)&&((startTime+point[station1][station2])<endTime)&&(type[theBikes[index].bikeType]==true)&&(theBikes[index].rentCount<rentalCountLim)&&(theBikes[index].price>0.0)){ //COMEBACK  //todo
                /*if((--search(root, theBikes[index].bikeType)->curr)<1){
                    root=deleteNode(root, theBikes[index].bikeType);
                    
                    
                }*/
 
                //kurangin jumlah sepeda di bic type di station ini
                //cek klo curr == 0 delete node bic type nya
                
                swap(theBikes[index], theBikes[theBikes.size()-1]);
                temp=&theBikes[theBikes.size()-1];
                //debug
                theBikes.pop();
                mergeSort(&theBikes, 0, theBikes.size()-1);
                break;
            }
            index++;
        }
        mergeSort(&theBikes, 0, theBikes.size()-1);
        return temp;
    }
    void printBike(){
        theBikes.outputVector();
    }

    void mergesort(){
        mergeSort(&theBikes, 0, theBikes.size()-1);
    }
    void ascendBikeSort(){
        int i,j;
        BicId key;
        for (i = 1; i < theBikes.size(); i++)
        {
            key = theBikes[i];
            j = i - 1;
            while (j >= 0 && theBikes[j].id > key.id)
            {
                theBikes[j + 1] = theBikes[j];
                j = j - 1;
            }
            theBikes[j + 1] = key;
        }
        
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
  
    
    
    cout << "start your basic version of data structure final from here!" << "\n";
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
    } else cout<< "unable to open"<<"\n"<<"\n";
    
    listStation = new Station[col];
    
    
    if(bikeInfo.is_open()){ //bike info nya, jd harga, sm depreciation const sama rental count lim
        
  
        bikeInfo>>depreciationConst;
        bikeInfo>>rentalCountLim;
        //JANGAN DI DELETE!!!!
        /*while(getline(bikeInfo,line)){
            stringstream stream;
            stream<<line;
            //out<<line<<"\n";
        }*/
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
           
            stream>>temp1>>a>>temp2>>doubleTemp>>b;
            station = stoi(temp2.substr(1));
            bikeType = stoi(temp1.substr(1));
            if(doubleTemp>=0&&b<rentalCountLim&&station<col){
                listStation[station].insertBike(bikeType, a, b, doubleTemp, 0);
            } //kalo hargany lebih besar = dari 0, dan rental count kurang dari rental count lim masih bisa d pake, jadi di insert bike nya else gaush masuk
            
            
        }
   
       
        bike.close();
    }
    
    for(int i=0;i<col;i++){
        dijkstra(col, point, i);
    }
    int flag=0;
    vectorClass<int> intTemp;
 
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
    }else cout<< "unable to open"<<"\n";
    
    insertionSort(&request,request.size());
  
    countSort<User>(&request,request.size()); //sort the request with manual radix sort
    
    for(int i=0;i<col;i++){
        listStation[i].mergesort();
    }

    
  
    
 

    intTemp.clear();
    int indexReq=0;
    int indexBikeType=0;
    int indexBikeTypeVector;
    BicId* bikeStore=NULL;
    int revenue;

    while(indexReq<request.size()){
        indexBikeType=0;
        //cout<<request[indexReq]<<"\n";
        //BicId* deleteBike(int startTime, int endTime, int station1, int station2, bool* type) BALIK
        bikeStore=listStation[request[indexReq].startStat].deleteBike(request[indexReq].start,request[indexReq].end, request[indexReq].startStat, request[indexReq].endStat, request[indexReq].bikeType);
        if(bikeStore==NULL){
            reqResult<<request[indexReq].userID<<" 0 0 0 0 0"<<"\n";
        } else {
            //debug
            
            
            
            
            transferLog<<bikeStore->id<<" S"<<request[indexReq].startStat<<" S"<<request[indexReq].endStat<<" "<<request[indexReq].start<<" "<<request[indexReq].start+point[request[indexReq].startStat][request[indexReq].endStat]<<" "<<request[indexReq].userID<<"\n";
            //print ke reqResult
            revenue=point[request[indexReq].startStat][request[indexReq].endStat]*(bikeStore->price);
            //debug
            /*cout<<"bike id: "<<bikeStore->id<<" move from S"<<request[indexReq].startStat<<" to S"<<request[indexReq].endStat<<" by time "<<request[indexReq].start+point[request[indexReq].startStat][request[indexReq].endStat]<<"\n";
            */
            
            
            reqResult<<request[indexReq].userID<<" 1 "<<bikeStore->id<<" "<<request[indexReq].start<<" "<<request[indexReq].start+point[request[indexReq].startStat][request[indexReq].endStat]<<" "<<revenue<<"\n";
            /*
             void insertBike(int type, int bikeID,int rentcount,double initPrice, int startTime){
                // root=insert(root,type); // TODO
                 BicId* temp= new BicId(type, bikeID,  rentcount,  initPrice, startTime);
                 theBikes.push_back(*temp);
                 numBic++;
             }
             */
            //tambahin ke station end, yg ud d modifin, skalian di cek satu persatu
            
                listStation[request[indexReq].endStat].insertBike(bikeStore->bikeType, bikeStore->id, bikeStore->rentCount+1,bikeStore->price-depreciationConst, request[indexReq].start+point[request[indexReq].startStat][request[indexReq].endStat]);
                
             //todo balik!
            
            listStation[request[indexReq].endStat].mergesort();
            
            
        }
        indexReq++;
    }
    /*
     // station_id, bike_id, bike_type, rental_price, and rental_count
     S2 0 B1 9.95 1
     */
    for(int i=0;i<col;i++){
        listStation[i].ascendBikeSort();
        for(int j=0;j<listStation[i].theBikes.size();j++){
            finalBikes<<"S"<<i<<" "<<listStation[i].theBikes[j].id<<" B"<<listStation[i].theBikes[j].bikeType<<" "<<listStation[i].theBikes[j].price<<" "<<listStation[i].theBikes[j].rentCount<<"\n";
        }
    }
    
    
     transferLog.close();
     reqResult.close();
     finalBikes.close();

}



