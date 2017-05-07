#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

const int CHECK = -2147483648;
const int storeCol = 5; //first two for x, y, third for demand, forth for fixed cost, fifth for price
const int centerCol = 4; //first two for x, y, third for capacity, forth for fixed cost
const int A = 4;
const int BinA = 2;
const int CinA = 2;
const int B = 3;
const int C = 3;

//basic function
int posiProfit(int *storeInfo, int *centerInfo, int cost);//if profitPerGood(i,j) is positive
int distance(int *storePosit, int *centerPosit);
int numOfSet(int num, bool *setList);
void set(bool *centerSet, bool *storeSet, int **setTable, int **storeInfo, int **centerInfo, int transInfo[]);

//functionA
int coffeeTeaOrMe(int storeNum, int centerNum, int cost, bool *storeSet, bool *centerSet, int **profitTable, int **storeInfo, int **centerInfo, int transInfoA[A]);
//for functionA
int newStore(int j, int storeNum, bool* storeSet, int** profitTable, int** storeInfo, int** centerInfo, int transInfoB[BinA]);
int nowYouSeeMe(int storeNum, int bestJ, bool *storeSet, int **profitTable, int **storeInfo, int centerCapa, int transInfoC[CinA]);
//functonB
int newStoreOutside(int storeNum, int centerNum, bool* storeSet, bool* centerSet, int** profitTable, int** storeInfo, int** centerInfo, int transInfoB[B]);
//functionC
int catchMeIfYouCan(int storeNum, int centerNum, bool *storeSet, bool *centerSet, int **profitTable, int **storeInfo, int **centerInfo, int transInfoC[C]);

int main(){
    //initialization part
    int centerNum = 0;
    int storeNum = 0;
    int cost = 0;
    cin >> centerNum >> storeNum >> cost;
    int **storeInfo = new int*[storeNum];
    int **centerInfo = new int*[centerNum];
    for (int i = 0; i < storeNum; i++){
        storeInfo[i] = new int[storeCol];
        for (int j = 0; j < storeCol; j++)
            storeInfo[i][j] = 0;
    }
    for (int i = 0; i < centerNum; i++){
        centerInfo[i] = new int[centerCol];
        for (int j = 0; j < centerCol; j++)
            centerInfo[i][j] = 0;
    }
    
    //cin part
    for (int i = 0; i < storeNum; i++){
        for (int j = 0; j < 2; j++)
            cin >> storeInfo[i][j];
    }//store positioin
    for (int i = 0; i < centerNum; i++){
        for (int j = 0; j < 2; j++)
            cin >> centerInfo[i][j];
    }//center position
    for (int i = 0; i < storeNum; i++)
        cin >> storeInfo[i][2];//demand
    for (int i = 0; i < storeNum; i++)
        cin >> storeInfo[i][3];//fixed cost
    for (int i = 0; i < storeNum; i++)
        cin >> storeInfo[i][4];//price
    for (int i = 0; i < centerNum; i++)
        cin >> centerInfo[i][3];//fixed cost
    for (int i = 0; i < centerNum; i++)
        cin >> centerInfo[i][2];//capacity
    
    //match store & center if profitPerGood is positive
    int **profitTable = new int*[storeNum];
    for (int i = 0; i < storeNum; i++){
        profitTable[i] = new int[centerNum];
    }
    
    for (int i = 0; i < storeNum; i++){
        for (int j = 0; j < centerNum; j++){
            int value = posiProfit(storeInfo[i],centerInfo[j],cost);
            if (value)
                profitTable[i][j] = value;
            else
                profitTable[i][j] = 0;
        }
    }
    
    //for cout record
    bool *storeSet = new bool[storeNum];
    bool *centerSet = new bool[centerNum];
    int **setTable = new int*[storeNum];
    for (int i = 0; i < storeNum; i++)
        storeSet[i] = 0;
    for (int i = 0; i < centerNum; i++)
        centerSet[i] = 0;
    for (int i = 0; i < storeNum; i++){
        setTable[i] = new int[centerNum];
        for (int j = 0; j < centerNum; j++)
            setTable[i][j] = 0;
    }
    
    //main algorithm
    int transInfoA[A] = {0};
    int profitA = coffeeTeaOrMe(storeNum,centerNum,cost,storeSet,centerSet,profitTable,storeInfo,centerInfo,transInfoA);
    if (profitA != CHECK && profitA > 0)
        set(centerSet,storeSet,setTable,storeInfo,centerInfo,transInfoA);
    int transInfoB[B] = {0};
    int profitB = newStoreOutside(storeNum,centerNum,storeSet,centerSet,profitTable,storeInfo,centerInfo,transInfoB);
    if (profitB != CHECK && profitB > 0)
        set(centerSet,storeSet,setTable,storeInfo,centerInfo,transInfoB);
    int transInfoC[C] = {0};
    int profitC = catchMeIfYouCan(storeNum,centerNum,storeSet,centerSet,profitTable,storeInfo,centerInfo,transInfoC);
    if (profitC != CHECK && profitC > 0)
        set(centerSet,storeSet,setTable,storeInfo,centerInfo,transInfoC);
    
    //if return value == CHECK, then nothing happened
    
    
    
    /*
     //just for text
     cout << "profit: " << profitA << "\n";
     for (int i = 0; i < A; i++)
     cout << transInfoA[i] << " ";
     cout << "\n";
     */
    
    //cout section
    int centerSetNum = numOfSet(centerNum,centerSet);
    int storeSetNum = numOfSet(storeNum,storeSet);
    cout << centerSetNum;
    for (int i = 0; i < centerNum; i++){
        if (centerSet[i])
            cout << " " << i+1;
    }
    cout << "\n";//new line
    cout << storeSetNum;
    for (int i = 0; i < storeNum; i++){
        if (storeSet[i])
            cout << " " << i+1;
    }
    cout << "\n";//new line
    for (int i = 0; i < storeNum; i++){
        for (int j = 0; j < centerNum; j++){
            if (j != 0)
                cout << " ";
            cout << setTable[i][j];
        }
        cout << "\n";
    }
    
    //delete section
    for (int i = 0; i < storeNum; i++)
        delete[] storeInfo[i];
    delete[] storeInfo;
    for (int i = 0; i < centerNum; i++)
        delete[] centerInfo[i];
    delete[] centerInfo;
    for (int i = 0; i < storeNum; i++){
        delete[] profitTable[i];
    }
    delete[] profitTable;
    delete[] centerSet;
    delete[] storeSet;
    for (int i = 0; i < storeNum; i++)
        delete[] setTable[i];
    delete[] setTable;
    
    return 0;
}

int posiProfit(int *storeInfo, int *centerInfo, int cost){
    int dist = distance(storeInfo,centerInfo);
    int profit = storeInfo[4] - dist*cost;
    if (profit > 0)
        return profit;
    else
        return 0;
}

int distance(int *storePosit, int *centerPosit){
    int deltaX = abs(storePosit[0] - centerPosit[0]);
    int deltaY = abs(storePosit[1] - centerPosit[1]);
    return deltaX + deltaY;
}

int numOfSet(int num, bool *setList){
    int setNum = 0;
    for (int i = 0; i < num; i++){
        if (setList[i])
            setNum++;
    }
    return setNum;
}

void set(bool *centerSet, bool *storeSet, int **setTable, int **storeInfo, int **centerInfo, int transInfo[]){
    centerSet[transInfo[0]] = 1;
    storeSet[transInfo[1]] = 1;
    storeInfo[transInfo[1]][2] -= transInfo[2];
    centerInfo[transInfo[0]][2] -= transInfo[2];
    setTable[transInfo[1]][transInfo[0]] += transInfo[2];
}

//functionA
int coffeeTeaOrMe(int storeNum, int centerNum, int cost, bool *storeSet, bool *centerSet, int **profitTable, int **storeInfo, int **centerInfo, int transInfoA[4]){
    int maxProfit = CHECK;
    for( int j = 0; j < centerNum; j++ ){
        if( centerSet[j] == false ){
            //check if centerJ didn't bulit yet
            int transInfoB[BinA] = {0}; //prepare for functionB
            int profitB = newStore( j, storeNum, storeSet, profitTable, storeInfo, centerInfo, transInfoB); //call functionB
            int transInfoC[CinA] = {0};  //prepare for functionC
            int profitC = nowYouSeeMe(storeNum,j,storeSet,profitTable,storeInfo,centerInfo[j][2],transInfoC);  //call functionC
            int profit = profitB;
            bool isB = 1;
            if( profitB < profitC ){
                profit = profitC;
                isB = 0;
            }
            profit -= centerInfo[j][3];
            
            if( profit > maxProfit ){
                maxProfit = profit;  //maxNetProfit
                transInfoA[0] = j;  //center
                if(isB){
                    //decided by functionB
                    transInfoA[1] = transInfoB[0];  //store
                    transInfoA[2] = transInfoB[1];  //transAm
                    transInfoA[3] = 1;  //build
                }
                else{
                    //decided by functionC
                    transInfoA[1] = transInfoC[0];  //store
                    transInfoA[2] = transInfoC[1];  //transAm
                    transInfoA[3] = 0 ;//allocate
                }
            }
        }
    }
    return maxProfit;
}

//for functionA
int newStore(int j, int storeNum, bool* storeSet, int** profitTable, int** storeInfo, int** centerInfo, int transInfoB[2]){
    int netProfitB=0;
    int maxProfitB=CHECK;
    int storeOfMaxB=-1;
    int category = 0;
    for(int i=0; i<storeNum; i++){
        if(storeSet[i]==false){
            if(profitTable[i][j]!=0){
                if(storeInfo[i][2]<=centerInfo[j][2]){
                    netProfitB+=(profitTable[i][j]*storeInfo[i][2]);
                    netProfitB-=storeInfo[i][3];
                }
                else{
                    netProfitB+=(profitTable[i][j]*centerInfo[j][2]);
                    netProfitB-=storeInfo[i][3];
                    category = 1;
                }
                if(netProfitB>maxProfitB){
                    maxProfitB=netProfitB;
                    storeOfMaxB=i;
                }
            }
        }
    }
    if (storeOfMaxB != -1){
        transInfoB[0]=storeOfMaxB;
        if(category)
            transInfoB[1] = centerInfo[j][2];
        else
            transInfoB[1]=storeInfo[storeOfMaxB][2];
    }
    return maxProfitB;
}

int nowYouSeeMe(int storeNum, int bestJ, bool *storeSet, int **profitTable, int **storeInfo, int centerCapa, int transInfoC[2]){
    int *storeDem = new int[storeNum];
    for(int i = 0; i < storeNum; i++){
        storeDem[i] = storeInfo[i][2];
    }
    
    int transStore = -1, transAm = 0, profit = CHECK, category = 0;
    for(int i = 0; i < storeNum; i++){
        int temPro = 0, type = 0;
        if(storeSet[i] && profitTable[i][bestJ] && storeDem[i] && centerCapa){ //if the store & center are built and still have demand & capacity
            if(storeDem[i] >= centerCapa){
                temPro = profitTable[i][bestJ] * centerCapa;
                type = 0;//if demand >= capacity, to know which amount is used
            }
            else{
                temPro = profitTable[i][bestJ] * storeDem[i];
                type = 1;
            }
            if(temPro > profit){
                profit = temPro;
                transStore = i;
                category = type;
                if(category){
                    transAm = storeDem[transStore];
                }
                else{
                    transAm = centerCapa;
                }
            }
        }
    }
    
    if(profit > 0){
        transInfoC[0] = transStore;
        transInfoC[1] = transAm;
    }
    
    delete[]storeDem;
    return profit;
}

//functionB
int newStoreOutside(int storeNum, int centerNum, bool* storeSet, bool* centerSet, int** profitTable, int** storeInfo, int** centerInfo, int transInfoB[3]){
    
    int netProfitB=0;
    int maxProfitB=CHECK;
    int storeOfB=-1;
    int category = 0;
    int centerOfB=-1;
    for(int i=0; i<storeNum; i++){
        for(int j=0; j<centerNum; j++){
            if(storeSet[i]==false){
                if(profitTable[i][j]!=0 && centerSet[j]==true){
                    if(storeInfo[i][2]<=centerInfo[j][2]){
                        netProfitB+=(profitTable[i][j]*storeInfo[i][2]);
                        netProfitB-=storeInfo[i][3];
                    }
                    else{
                        netProfitB+=(profitTable[i][j]*centerInfo[j][2]);
                        netProfitB-=storeInfo[i][3];
                        category = 1;
                    }
                    if(netProfitB>maxProfitB){
                        maxProfitB=netProfitB;
                        storeOfB=i;
                        centerOfB=j;
                    }
                }
            }
        }
    }
    
    
    if (maxProfitB != CHECK){
        transInfoB[0]=centerOfB;
        transInfoB[1]=storeOfB;
        if(category)
            transInfoB[2] = centerInfo[centerOfB][2];
        else
            transInfoB[2]=storeInfo[storeOfB][2];
    }
    
    return maxProfitB;
}

//functionC
int catchMeIfYouCan(int storeNum, int centerNum, bool *storeSet, bool *centerSet, int **profitTable, int **storeInfo, int **centerInfo, int transInfoC[3]){
    int *storeDem = new int[storeNum];
    for(int i = 0; i < storeNum; i++){
        storeDem[i] = storeInfo[i][2];
    }
    
    int *centerCapa = new int[centerNum];
    for(int i = 0; i < centerNum; i++){
        centerCapa[i] = centerInfo[i][2];
    }
    int transStore = -1, transCenter = -1, transAm = 0, profit = CHECK, category = 0;
    for(int i = 0; i < storeNum; i++){
        if(storeSet[i]){
            for(int j = 0; j < centerNum; j++){
                int temPro = 0, type = 0;
                if(centerSet[j] && profitTable[i][j] && storeDem[i] && centerCapa[j]){ //if the store & center are built and still have demand & capacity
                    if(storeDem[i] >= centerCapa[j]){
                        temPro = profitTable[i][j] * centerCapa[j];
                        type = 0;//if demand >= capacity, to know which amount is used
                    }
                    else{
                        temPro = profitTable[i][j] * storeDem[i];
                        type = 1;
                    }
                    if(temPro > profit){
                        profit = temPro;
                        transStore = i;
                        transCenter = j;
                        category = type;
                        if(category){
                            transAm = storeDem[transStore];
                        }
                        else{
                            transAm = centerCapa[transCenter];
                        }
                    }
                }
            }
        }
        
    }
    
    if(profit > 0){
        transInfoC[0] = transCenter;
        transInfoC[1] = transStore;
        transInfoC[2] = transAm;
    }
    
    delete[]storeDem;
    delete[]centerCapa;
    return profit;
}
