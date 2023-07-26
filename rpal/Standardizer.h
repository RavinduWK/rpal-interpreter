
#ifndef Standardizer_H_
#define Standardizer_H_

#include "lexer.h"
#include "treeNode.h"

using namespace std;

class Standardizer {
    void standardize(treeNode*);
    void standardizeLET(treeNode*);
    void standardizeWHERE(treeNode*);
    void standardizeWITHIN(treeNode*);
    void standardizeREC(treeNode*);
    void standardizeFCNFORM(treeNode*);
    void standardizeLAMBDA(treeNode*);
    void standardizeAND(treeNode*);
    void standardizeAT(treeNode*);

public:
    Standardizer(treeNode* topNode);
    virtual ~Standardizer();
};

#endif /* Standardizer_H_ */
