#include <iostream>
#include<vector>
#include <sstream>
#include <map>
#include <fstream>
#include <cstring>  
#include <string>
using namespace std;

/* Act 1.3 - Comprehensive Activity of Basic Concepts and Fundamental Algorithms
    Javier Eric Hernández A01635390
    Carlos Eduardo Arellano A01641620
 */

string* split(string d,string* datos){
    //split: O(n)
    //Separates the string into an array of strings
    int n=0;
    for(int i=0; i<d.size();i++){
        if(d[i]==' ' && n<4){
            n=n+1;
        }else{
            datos[n]+=d[i];
        }
    }
    return datos;
}

vector<string*> cargaDatos(string data){
    //cargaDatos O(n)
    //Loads the data from the file into a vector of strings
    std::ifstream fe;
    string d;
    vector<string*> datos;
    fe.open(data);
    if (fe.is_open()){  
        while (getline(fe,d)){
            string* linea=new string[5];
            linea=split(d,linea);
            datos.push_back(linea);
        }
    }
    fe.close();
    return datos;
}
void imprimir(vector<string*> datos){
    //imprimir: O(n)
    //Prints the data from the vector
    for(int i=0;i<datos.size();i++){
        for(int j=0;j<5;j++){
            cout<<datos[i][j]<<" ";
        }
        cout<<endl;
    }
}
bool fechaMayor(string* fecha1,string* fecha2){
    //fechaMayor: O(1)
    //Compares two dates and returns true or false
    map<string,int> mes={{"Jan",1},{"Feb",2},{"Mar",3},{"Apr",4},{"May",5},{"Jun",6},{"Jul",7},{"Aug",8},{"Sep",9},{"Oct",10},{"Nov",11},{"Dec",12}};
    stringstream ss(fecha1[2]),ss1(fecha2[2]);
    string d1,d2;
    if(mes[fecha1[0]]<mes[fecha2[0]]){
        return true;
    }else if(mes[fecha1[0]]>mes[fecha2[0]]){
        return false;
    }else if(stoi(fecha1[1])<stoi(fecha2[1])){
        return true;
    }else if(stoi(fecha1[1])>stoi(fecha2[1])){
        return false;
    }
    for(int i=0;i<4;i++){
        getline(ss,d1,':');
        getline(ss1,d2,':');
        if(stoi(d1)<stoi(d2)){
            return true;
        }else if(stoi(d1)>stoi(d2)){
            return false;
        }
    }
    return true;
}
void Merge(vector<string*> &arr, int const s,int const m , int const e){
    //Merge
    //Fusiona el arreglo
    int const n1=m-s+1;
    int const n2=e-m;
    auto L= new string*[n1],R= new string*[n2];
    for(int i=0;i<n1;i++){
        L[i]=arr[s+i];
    }
    for(int j=0;j<n2;j++){
        R[j]=arr[m+1+j];
    }

    int i=0,j=0,k=s;

    while(i<n1 && j<n2){
        if(fechaMayor(L[i],R[j])){
            arr[k]=L[i];
            i++;
        }else{
            arr[k]=R[j];
            j++;
        }
        k++;
    }
    while(i<n1){
        arr[k]=L[i];
        i++;
        k++;
    }
    while(j<n2){
        arr[k]=R[j];
        j++;
        k++;
    }
    delete[] L;
    delete[] R;
}
void merge_sort(vector<string*> &arr,int const s, int const e){
    //Merge Sort
    //Estable
    //O(n log(n))
    if(s >= e){
        return;
    }
    int mid=s+(e-s)/2;
    merge_sort(arr,s,mid);
    merge_sort(arr,mid+1,e);
    Merge(arr,s,mid,e);
} 
int find(vector<string*>d,string* date){
    //Seartch algorithm
    //Busca la fecha en el arreglo
    int i=0,j=d.size()-1;
    while(i<=j){
        if((d[i][0]==date[0]) && (d[i][1]==date[1])){
            return i;
        }
        i++;
    }
    i=0;
    while(fechaMayor(d[i],date)&& i<j){
        i++;
    }
    return i;
}
int finde(vector<string*>d,string* date){
    //Seartch algorithm
    //Busca la fecha en el arreglo
    int i=0,j=d.size()-1;
    while(i<=j){
        if((d[j][0]==date[0]) && (d[j][1]==date[1])){
            return j;
        }
        j--;
    }
    j=d.size()-1;
    while(fechaMayor(date,d[j])&& j>=i){
        j--;
    }
    return j;
}


void search(vector<string*>d,string* date_start, string* date_end){
    //Search: O(n)
    //Searches for the dates in the vector and prints the data between those dates
    int start=find(d,date_start),end=finde(d,date_end);
    if(start==-1 || end==-1){
        cout<<"No se encontraron datos"<<endl;
    }else{
        cout<<"Datos encontrados"<<endl;
        for(int i=end;i>=start;i--){
            cout<<d[i][0]<<" "<<d[i][1]<<" "<<d[i][2]<<" "<<d[i][3]<<" "<<d[i][4]<<endl;
        }
    }
}
string* DateMaker(string s){
    //DateMaker: O(1)
    //Creates a date from a string
    string* date=new string[3];
    stringstream ss(s);
    for(int i=0;i<3;i++){
        getline(ss,date[i],' ');
    }
    return date;
}
void rellenar(vector<string*> d){
    //rellenar: O(n)
    //Creates a file with the data sorted data from the vector
    string s="";
    for(int i=0;i<d.size();i++){
       s+=d[i][0]+" "+d[i][1]+" "+d[i][2]+" "+d[i][3]+" "+d[i][4]+"\n";
    }
    ofstream archivo;
    archivo.open("output.txt");
    archivo<<s;
    archivo.close();
}
int main(){
    string i,f;
    string* in,*fi;
    vector<string*> d=cargaDatos("bitacora.txt");
    cout<<"Information downloaded"<<endl;
    merge_sort(d,0,d.size()-1);
    rellenar(d);
    cout<<"----Search----"<<endl;
    cout<<"Enter a range of dates"<<endl;
    cout<<"Enter the start date Format MM (first 3 letters) DD: ";
    getline(cin,i);
    cout<<"Enter the end date Format MM (first 3 letters) DD: ";
    getline(cin,f);
    in=DateMaker(i);
    fi=DateMaker(f);
    search(d,in,fi);
    return 1;
}
