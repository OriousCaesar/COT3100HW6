#include <iostream>

using namespace std;

class relation{
private:
    int size;
    int* domain;
    int* range;
public:
    relation(){size = 0; domain = nullptr; range = nullptr;}
    relation(int size, int* domain, int* range){this->size = size; this->domain = domain; this->range = range;}
    int atD(int i){return domain[i];}
    int atR(int i){return range[i];}
    int getSize(){return size;}
    bool isIn(int* pair){
        for(int i = 0; i<size; i++){
            if(pair[0] != domain[i]) continue;
            if(pair[1] != range[i]) continue;
            return true;
        }
        return false;
    }
};

bool isReflexive(int* domain, int domSize, relation testing){
    for(int i = 0; i<domSize; i++){
        int pair[2] = {domain[i], domain[i]};
        if(!testing.isIn(pair)) return false;
    }
    return true;
}
bool isIrreflexive(int* domain, int domSize, relation testing){
    for(int i = 0; i<domSize; i++){
        int pair[2] = {domain[i], domain[i]};
        if(testing.isIn(pair)) return false;
    }
    return true;
}
bool isSymmetric(int* domain, int domSize, relation testing){
    for(int i = 0; i<domSize; i++){
        for(int j = 0; j<domSize; j++){
            int pairA[2] = {domain[i], domain[j]};
            int pairB[2] = {domain[j], domain[i]};
            if(testing.isIn(pairA))
                if(!testing.isIn(pairB)) return false;
        }
    }
    return true;
}
bool isAntiSymmetric(int* domain, int domSize, relation testing){
    for(int i = 0; i<domSize; i++){
        for(int j = 0; j<domSize; j++){
            int pairA[2] = {domain[i], domain[j]};
            int pairB[2] = {domain[j], domain[i]};
            if(testing.isIn(pairA) && testing.isIn(pairB))
                if(domain[i] != domain[j]) return false;
        }
    }
    return true;
}
bool isAsymmetric(int* domain, int domSize, relation testing){
    return isAntiSymmetric(domain, domSize, testing) && isIrreflexive(domain, domSize, testing);
}
bool isTransitive(int* domain, int domSize, relation testing){
    for(int i = 0; i<domSize; i++){
        for(int j = 0; j<domSize; j++){
            for(int k = 0; k<domSize; k++){
                int pairA[2] = {domain[i], domain[j]};
                int pairB[2] = {domain[j], domain[k]};
                int pairC[2] = {domain[i], domain[k]};
                if(testing.isIn(pairA) && testing.isIn(pairB))
                    if(!testing.isIn(pairC)) return false;
            }
        }
    }
    return true;
}

int main(){
    const int size = 2;
    const int sizeSq = size*size;
    const int relationCount = 1 << sizeSq;
    int set[size] = {0,1};

    int domain[sizeSq];
    int range[sizeSq];
    for(int i = 0; i<sizeSq; i++){
        domain[i] = set[i/size];
        range[i] = set[i%size];
    }
    relation setSquared(sizeSq, domain, range);

    relation relations[relationCount];
    int relDomain[relationCount][sizeSq];
    int relRange[relationCount][sizeSq];

    for(int i = 0; i<relationCount; i++){
        int subsetSize = 0;
        for(int j = 0; j<sizeSq; j++){
            if(i & (1 << j)){
                relDomain[i][subsetSize] = domain[j];
                relRange[i][subsetSize] = range[j];
                subsetSize++;
            }
        }
        relations[i] = relation(subsetSize, relDomain[i], relRange[i]);
    }


    for(int i = 0; i<relationCount; i++){
        cout << "Relation " << i+1 << ": {";
        int relSize = relations[i].getSize();
        for(int j = 0; j<relSize; j++){
            cout << "(" << relations[i].atD(j) << "," << relations[i].atR(j) << ")";
            if(j < relSize - 1) cout << ", ";
        }
        cout << "}" << endl;
    }
    cout << endl << endl;

    cout << "Reflexive:" << endl;
    for(int i = 0; i<relationCount; i++){
        if(isReflexive(set, size, relations[i]))
            cout << i+1 << ", ";
    }
    cout << endl;

    cout << "Irreflexive:" << endl;
    for(int i = 0; i<relationCount; i++){
        if(isIrreflexive(set, size, relations[i]))
            cout << i+1 << ", ";
    }
    cout << endl;

    cout << "Symmetric:" << endl;
    for(int i = 0; i<relationCount; i++){
        if(isSymmetric(set, size, relations[i]))
            cout << i+1 << ", ";
    }
    cout << endl;

    cout << "Anti-symmetric:" << endl;
    for(int i = 0; i<relationCount; i++){
        if(isAntiSymmetric(set, size, relations[i]))
            cout << i+1 << ", ";
    }
    cout << endl;

    cout << "Asymmetric:" << endl;
    for(int i = 0; i<relationCount; i++){
        if(isAsymmetric(set, size, relations[i]))
            cout << i+1 << ", ";
    }
    cout << endl;

    cout << "Transitive: " << endl;
    for(int i = 0; i<relationCount; i++){
        if(isTransitive(set, size, relations[i]))
            cout << i+1 << ", ";
    }
    cout << endl;

    return 0;
}