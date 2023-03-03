#include<iostream>
#include<cstdlib>
using namespace std;

int main(int argc, char* argv[]){
    int num = 0,arv,round = argc;        
            if(argc == 1){
            cout << "Please input numbers to find average."; 
        }
    else { 
    for(int i = 1 ; i < round ; i++){
        num += atoi(argv[i]);
    }
    arv = num/(round-1);
    cout << "---------------------------------"<<endl;
    cout << "Average of "<< round-1 << " numbers = "<<arv<<endl;
    cout << "---------------------------------"<<endl;
    }
    return 0;
}
