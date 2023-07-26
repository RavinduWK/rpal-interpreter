#include "CSEMachine.h"

CSEMachine::CSEMachine(treeNode* topNode) {
    this->top = topNode;
}

CSEMachine::CSEMachine(){
    numEnvironment = -1;
    PE = createNewEnvironment();
    environmentStack.push(PE);
    deltas = new vector<Control *>;
    rootDelta = new Control(Control::DELTA, deltas->size());
}

CSEMachine::~CSEMachine() {

}

bool CSEMachine::checkInbuilt(string funcName) {
    if (std::find(inbuiltFuncVector.begin(), inbuiltFuncVector.end(), funcName) != inbuiltFuncVector.end()){
        return true;
    } else {
        return false;
    }
}

void CSEMachine::binaryOperation(int type){

    control.pop_back();
    Control *rand1 = execStack.top() ;
    execStack.pop();
    Control *rand2 = execStack.top() ;
    execStack.pop();
    Control *result = new Control() ;
    result->controlType = Control::INTEGER;
    switch(type)
      {
      case Control::AUG :
    result->controlType = Control::TUPLE;
    result->ctrlTuples;
    if( rand1->controlType != Control::NIL ){
      if( rand1->controlType == Control::TUPLE){
        for(int i=0;i<rand1->ctrlTuples.size(); i++)
          result->ctrlTuples.push_back(rand1->ctrlTuples.at(i));
      }
      else{
        result->ctrlTuples.push_back(rand1) ;
      }
    }
    if( rand2->controlType != Control::NIL ){
      if( rand2->controlType == Control::TUPLE){
        for(int i=0;i<rand2->ctrlTuples.size(); i++)
          result->ctrlTuples.push_back(rand2->ctrlTuples.at(i));
      }
      else
        result->ctrlTuples.push_back(rand2);
    }
    break ;
      case Control::EXP :
    if(rand1->controlType == Control::INTEGER && rand2->controlType == Control::INTEGER) {
        result->controlVal = to_string(pow(atoi(rand1->controlVal.c_str()), atoi(rand2->controlVal.c_str())));
        break ;
      }
    else {
        cout << "Incompatible arguments for the operator '**'" ;
        exit(1) ;
      }
    break ;
      case Control::GR :
    if(rand1->controlType == Control::INTEGER && rand2->controlType == Control::INTEGER){
      if( atoi(rand1->controlVal.c_str()) > atoi(rand2->controlVal.c_str()) )
        result->controlType = Control::TRUE;
      else
        result->controlType = Control::FALSE;
      break ;
    }
    else{
      cout << "Incompatible arguments for the operator 'GR'" << endl ;
      exit(1) ;
    }
    break ;
      case Control::GE :
    if(rand1->controlType == Control::INTEGER && rand2->controlType == Control::INTEGER) {
        if( atoi(rand1->controlVal.c_str()) >= atoi(rand2->controlVal.c_str()) )
          result->controlType = Control::TRUE;
        else
          result->controlType = Control::FALSE;
        break ;
      }
    else {
        cout << "Incompatible arguments for the operator 'GE'" ;
        exit(1) ;
      }
    break ;
      case Control::LS :
    if(rand1->controlType == Control::INTEGER && rand2->controlType == Control::INTEGER) {
        if( atoi(rand1->controlVal.c_str()) < atoi(rand2->controlVal.c_str()) )
          result->controlType = Control::TRUE;
        else
          result->controlType = Control::FALSE;
        break ;
      }
    else {
        cout << "Incompatible arguments for the operator 'LS'" ;
        exit(1) ;
      }
    break ;
      case Control::LE :
    if(rand1->controlType == Control::INTEGER && rand2->controlType == Control::INTEGER) {
        if( atoi(rand1->controlVal.c_str()) <= atoi(rand2->controlVal.c_str()) )
          result->controlType = Control::TRUE;
        else
          result->controlType = Control::FALSE;
        break ;
      }
    else {
        cout << "Incompatible arguments for the operator 'LE'" ;
        exit(1) ;
      }
    break ;
      case Control::EQ :
    if( rand1->controlType == Control::STRING && rand2->controlType == Control::STRING) {
        if( rand1->controlVal.compare(rand2->controlVal) == 0)
          result->controlType = Control::TRUE;
        else
          result->controlType = Control::FALSE;
                }
    else if( rand1->controlType == Control::INTEGER && rand2->controlType == Control::INTEGER )  {
        if( rand1->controlVal == rand2->controlVal )
          result->controlType = Control::TRUE;
        else
          result->controlType = Control::FALSE;
      }
    else if((rand1->controlType == Control::TRUE || rand1->controlType == Control::FALSE) && (rand1->controlType == Control::TRUE || rand2->controlType == Control::FALSE)){
        result->controlType = rand1->controlType == rand2->controlType?Control::TRUE: Control::FALSE;
      }
    else {
        cout << "Incompatible arguments for the operator 'EQ'" ;
        exit(1) ;
      }
    break ;
      case Control::NE :
    if( rand1->controlType == Control::STRING && rand2->controlType == Control::STRING ) {
        if( rand1->controlVal.compare(rand2->controlVal) != 0)
          result->controlType = Control::TRUE;
        else
          result->controlType = Control::FALSE;
                }
    else if( rand1->controlType == Control::INTEGER && rand2->controlType == Control::INTEGER ) {
        if( rand1->controlVal != rand2->controlVal)
          result->controlType = Control::TRUE;
        else
          result->controlType = Control::FALSE;
      }
    else if((rand1->controlType == Control::TRUE || rand1->controlType == Control::FALSE) && (rand1->controlType == Control::TRUE || rand2->controlType == Control::FALSE)){
        result->controlType = rand1->controlType != rand2->controlType?Control::TRUE: Control::FALSE;
      }
    else {
        cout << "Incompatible arguments for the operator 'NE'" ;
        exit(1) ;
      }
    break ;
      case Control::OR :
    if( (rand1->controlType == Control::TRUE || rand1->controlType == Control::FALSE ) &&
        (rand2->controlType == Control::TRUE || rand2->controlType == Control::FALSE) ) {
        bool op1 = (rand1->controlType == Control::TRUE )? true : false ;
        bool op2 = ( rand2->controlType == Control::TRUE )? true : false ;
        bool res = op1 | op2 ;
        result->controlType =res? Control::TRUE : Control::FALSE;
      }
    else {
        cout << "Incompatible arguments for the operator 'OR'" ;
        exit(1) ;
      }
    break ;
      case Control::AND_LOGICAL :
    if( (rand1->controlType == Control::TRUE || rand1->controlType == Control::FALSE ) &&
        (rand2->controlType == Control::TRUE || rand2->controlType == Control::FALSE) ) {
        bool op1 = (rand1->controlType == Control::TRUE)?true:false;
        bool op2 = (rand2->controlType == Control::TRUE)?true:false;
        bool res = op1 & op2;
        result->controlType = res? Control::TRUE : Control::FALSE;
      }
    else {
        cout << "Incompatible arguments for the operator 'AND'" ;
        exit(1) ;
      }
    break ;
      case Control::ADD :
    if(rand1->controlType == Control::INTEGER && rand2->controlType == Control::INTEGER){
        result->controlVal = to_string(atoi(rand1->controlVal.c_str()) + atoi(rand2->controlVal.c_str()));
        break ;
      }
    else{

        cout << "Incompatible arguments for the operator '+'" ;
        exit(1) ;
      }
    break ;

      case Control::SUBTRACT :
    if(rand1->controlType == Control::INTEGER && rand2->controlType == Control::INTEGER){
        result->controlVal = to_string(atoi(rand1->controlVal.c_str()) - atoi(rand2->controlVal.c_str()));
        break ;
      }
    else {
        cout << "Incompatible arguments for the operator '-'" ;
        exit(1) ;
      }
    break ;
      case Control::MULTIPLY :
    if(rand1->controlType == Control::INTEGER && rand2->controlType == Control::INTEGER){
        result->controlVal = to_string(atoi(rand1->controlVal.c_str()) * atoi(rand2->controlVal.c_str()));
        break ;
      }
    else{
        cout << "Incompatible arguments for the operator '*'" ;
        exit(1) ;
      }
    break ;
      case Control::DIVIDE :
    if(rand1->controlType == Control::INTEGER && rand2->controlType == Control::INTEGER) {
        result->controlVal = to_string(atoi(rand1->controlVal.c_str()) / atoi(rand2->controlVal.c_str()));
        break ;
      }
    else {
        cout << "Incompatible arguments for the operator '*'" ;
        exit(1) ;
      }
    break ;
      default:
          cout << "UnHandled binary operator , type: " << type << endl;
      }

    execStack.push(result) ;

}

void CSEMachine::escapeSeqence(string printStr){
  for( int i = 0 ; i < printStr.length() ; i++ ){
  char ch1 = printStr.at(i) ;
    if( ch1 == '\\'){
      i++ ;
      if( i < printStr.length() ){
        char ch2 = printStr.at(i) ;
        if( ch2 == 'n' )
      cout << endl;
        else if( ch2 == 't' )
      cout << "\t" ;
        else
      cout <<  ch1 << ch2 ;
      }
    }
    else
      cout << ch1 ;
    }
    cout.flush();
}

void CSEMachine::applyThisRator(Control* rator){
    Control* temp;
    Control* toPush;
    if(rator->variables.front() == "Print"){
        string print_str = execStack.top()->toStr();
        escapeSeqence(print_str); //WHY?
        execStack.pop();
        toPush = new Control(Control::DUMMY);
    }else if(rator->variables.front() == "Order"){
        Control *tuple = execStack.top() ;
        execStack.pop();
        Control *order = new Control();
        order->controlType = Control::INTEGER;
        if( tuple->controlType == Control::TUPLE){
            order->controlVal = to_string(tuple->ctrlTuples.size());
        }else if( tuple->controlType == Control::NIL ){
            order->controlVal = to_string(0);
        }else{
            cout <<  "Invalid argument for 'Order'" << endl ;
            exit(1) ;
        }
        toPush = order;
    }else if(rator->variables.front() == "Isinteger"){
        temp = execStack.top();
        execStack.pop();
        toPush = new Control(temp->controlType == Control::INTEGER ? Control::TRUE : Control::FALSE);
    }else if(rator->variables.front() == "Istruthvalue"){
        temp = execStack.top();
        execStack.pop();
        toPush = new Control((temp->controlType == Control::TRUE || temp->controlType == Control::FALSE) ? Control::TRUE : Control::FALSE);
    }else if(rator->variables.front() == "Isstring"){
        temp = execStack.top();
        execStack.pop();
        toPush = new Control(temp->controlType == Control::STRING ? Control::TRUE : Control::FALSE);
    }else if(rator->variables.front() == "Istuple"){
        temp = execStack.top();
        execStack.pop();
        toPush = new Control((temp->controlType == Control::TUPLE || temp->controlType == Control::NIL) ? Control::TRUE : Control::FALSE);
    }else if(rator->variables.front() == "Isfunction"){
        temp = execStack.top();
        execStack.pop();
        toPush = new Control(temp->controlType == Control::LAMBDA ? Control::TRUE : Control::FALSE);
    }else if(rator->variables.front() == "Isdummy"){
        temp = execStack.top();
        execStack.pop();
        toPush = new Control(temp->controlType == Control::DUMMY ? Control::TRUE : Control::FALSE);
    }else if(rator->variables.front() == "Stem"){
        if(execStack.top()->controlType == Control::STRING){
            Control *strControl= new Control(Control::STRING);
            strControl->controlVal = execStack.top()->controlVal.substr(0, 1);
            execStack.pop();
            toPush = strControl;
        }else{
            cout << "STEM: Expecting String" << endl;
            exit(1);
        }
    }else if(rator->variables.front() == "Stern"){
        if(execStack.top()->controlType == Control::STRING){
            Control *strControl = new Control(Control::STRING);
            strControl->controlVal = execStack.top()->controlVal.substr(1, execStack.top()->controlVal.length()-1);
            execStack.pop();
            toPush = strControl;
        }else{
            cout << "STERN: Expecting String" << endl;
            exit(1);
        }
    }else if(rator->variables.front() == "ItoS"){
        if(execStack.top()->controlType == Control::INTEGER){
           Control *strControl = new Control(Control::STRING);
           strControl->controlVal = execStack.top()->controlVal;
           execStack.pop();
           toPush = strControl;
        }else{
            cout << "Itos: Expecting Integer" << endl;
            exit(1);
        }
    }else if(rator->variables.front() == "Conc"){ //could have check for string here
        Control *concl = new Control(Control::NAME);
        concl->variables.push_back("Conclambda");
        concl->variables.push_back(execStack.top()->controlVal);
        execStack.pop();
        toPush = concl;
    }else if(rator->variables.front() == "Conclambda"){
        Control *concatVars = new Control(Control::STRING, rator->variables.at(1)+ execStack.top()->controlVal);
        execStack.pop();
        toPush = concatVars;
    }else if(rator->variables.front() == "Null"){
        Control *boolR = new Control();
        if(execStack.top()->controlType == Control::NIL || (execStack.top()->controlType == Control::TUPLE && execStack.top()->ctrlTuples.empty()))
            boolR->controlType = Control::TRUE;
        else
            boolR->controlType = Control::FALSE;
        execStack.pop();
        toPush = boolR;
    }else{
        cout << "ERROR: value:%" << rator->controlVal << "%type:" << rator->controlType << endl;
        printCS();
        return;
    }
    execStack.push(toPush);
}

void CSEMachine::handleName(Control* temp, Control* currControl, Control* rator, Environment* newEnv, int deltaIndex){
    if(checkInbuilt(currControl->variables.front())){
        control.pop_back();
        execStack.push(currControl) ;
    } else {
        temp = currEnvironment->lookup(currControl->variables.front());
        if(temp != NULL){
            control.pop_back();
            execStack.push(temp) ;
        } else {
            cout << " Unknown name" +  currControl->controlVal << endl;
        }
    }
}

void CSEMachine::rule411(Control* temp, Control* currControl, Control* rator, Environment* newEnv, int deltaIndex){
    newEnv = createNewEnvironment();
    newEnv->assignParent(environmentMap.find(rator->ass_env)->second);
    currEnvironment = newEnv ;
    if( rator->variables.size() == 1 ){
        currEnvironment->symbolTable[rator->variables.at(0)] = execStack.top();
        execStack.pop();
    } else {
        temp = execStack.top(); //Contain tuple pls
        execStack.pop() ;
        if( temp->controlType == Control::TUPLE && rator->variables.size() == temp->ctrlTuples.size() )
        {
            for( int i = 0 ; i < rator->variables.size() ; i++ )
            {
                currEnvironment->symbolTable[rator->variables.at(i)] = temp->ctrlTuples.at(i);
            }
        } else {
            cout << "Number/Type of arguments to a function doesn't match. rator variable size: "  << rator->variables.size() << " temp tuples->size:" << temp->ctrlTuples.size() << endl;
            exit(1);
        }
    }
    environmentStack.push(currEnvironment);
    control.push_back(new Control(Control::ENV, currEnvironment->id, false));
    execStack.push(new Control(Control::ENV, currEnvironment->id, false));
    for(int i=0;i<deltas->at(rator->index)->ctrlStruct->size();i++){
        control.push_back(deltas->at(rator->index)->ctrlStruct->at(i));
    }
}

void CSEMachine::rule12(Control* temp, Control* currControl, Control* rator, Environment* newEnv, int deltaIndex){
    Control *eta = new Control(execStack.top()) ;
    execStack.pop();
    eta->controlType = Control::ETA;
    execStack.push(eta);
}

void CSEMachine::rule13(Control* temp, Control* currControl, Control* rator, Environment* newEnv, int deltaIndex){
    control.push_back(new Control(Control::GAMMA));
    control.push_back(new Control(Control::GAMMA));
    execStack.push(rator);
    Control *lambda = new Control(Control::LAMBDA, &(rator->variables), NULL, rator->index) ;
    lambda->ass_env = rator->ass_env;
    execStack.push(lambda);
}

void CSEMachine::rule10(Control* temp, Control* currControl, Control* rator, Environment* newEnv, int deltaIndex){
    if( execStack.top()->controlType == Control::INTEGER ){
    temp = rator->ctrlTuples.at(atoi(execStack.top()->controlVal.c_str()) - 1) ;
    execStack.pop();
    execStack.push(temp) ;
    } else{
        cout << "Expected an integer while indexing tuples!";
        exit(1) ;
    }
}


void CSEMachine::handleGAMMA(Control* temp, Control* currControl, Control* rator, Environment* newEnv, int deltaIndex){
    control.pop_back();
    rator = execStack.top() ;
    execStack.pop();
    if( rator->controlType== Control::LAMBDA ){
        rule411(temp, currControl, rator, newEnv, deltaIndex);
    }else if( rator->controlType == Control::YSTAR ){
        rule12(temp, currControl, rator, newEnv, deltaIndex);
    } else if( rator->controlType == Control::ETA ){
        rule13(temp, currControl, rator, newEnv, deltaIndex);
    }else if(rator->controlType == Control::TUPLE){ //Rule 10
        rule10(temp, currControl, rator, newEnv, deltaIndex);
    } else {
        applyThisRator(rator);
    }
}


void CSEMachine::handleBeta(Control* temp, Control* currControl, Control* rator, Environment* newEnv, int deltaIndex){
    control.pop_back();
    if(execStack.top()->controlType == Control::TRUE){
        control.pop_back();
        if(control.at(control.size() - 1)->controlType == Control::DELTA){
            deltaIndex = control.at(control.size() -1)->index;
            control.pop_back();
        }else{
            cout << "Delta Expected " << control.at(control.size() -1)->controlType << endl;
            exit(1);
        }
    }else if(execStack.top()->controlType == Control::FALSE){
        if(control.at(control.size() - 1)->controlType == Control::DELTA){
            deltaIndex = control.at(control.size() -1)->index;
            control.pop_back();
            control.pop_back();
        }else{
            cout << "Delta Expected, found, " << control.at(control.size() -1)->controlType << endl;
            exit(1);
        }
    }else{
        cout << " '->' operator Expected a bool value"  << endl;
        exit(1);
    }
    execStack.pop();
    for(int i=0; i< deltas->at(deltaIndex)->ctrlStruct->size() ; i++){
        control.push_back(deltas->at(deltaIndex)->ctrlStruct->at(i));
    }
}

void CSEMachine::handleEnv(Control* temp, Control* currControl, Control* rator, Environment* newEnv, int deltaIndex){
    temp = execStack.top() ;
    execStack.pop();
    if( execStack.top()->controlType == Control::ENV && execStack.top()->index == currControl->index ){
        control.pop_back();
        execStack.pop();
        execStack.push(temp) ;

        environmentStack.pop() ;
        currEnvironment = environmentStack.top() ;
    }else{
        cout << "Environment markers do not match!" << endl;
        exit(1) ;
    }
}

void CSEMachine::handleTau(Control* temp, Control* currControl, Control* rator, Environment* newEnv, int deltaIndex){
    control.pop_back();
    temp = new Control() ;
    temp->controlType = Control::TUPLE;
    temp->ctrlTuples.clear();
    for(int i=0; i<currControl->index; i++ )
    {
        temp->ctrlTuples.push_back(execStack.top()) ;
        execStack.pop() ;
    }
    execStack.push(temp) ;

}

void CSEMachine::handleNeg(Control* temp, Control* currControl, Control* rator, Environment* newEnv, int deltaIndex){
    control.pop_back();
    if(execStack.top()->controlType == Control::INTEGER )
        execStack.top()->controlVal = to_string(-1*atoi(execStack.top()->controlVal.c_str()));
    else
    {
        cout << "Neg: Int not found" << endl;
        exit(1) ;
    }
}

void CSEMachine::execCSE(){
    Control *temp = NULL;
    Control *currControl = NULL;
    Control *rator = NULL;
    Environment *newEnv = NULL;
    int deltaIndex = -1;
    while(!control.empty()){
        //printCS();
        currControl = control.at(control.size()-1);
        temp = NULL;
        switch(currControl->controlType){
        case Control::INTEGER :
        case Control::STRING :
        case Control::TRUE :
        case Control::FALSE :
        case Control::DUMMY :
        case Control::YSTAR :
            control.pop_back();
            execStack.push(currControl) ;
            break;
        case Control::NAME:
            handleName(temp, currControl, rator, newEnv, deltaIndex);
            break;
        case Control::NIL :
            currControl->ctrlTuples.clear();
            control.pop_back();
            execStack.push(currControl) ;
            break ;
        case Control::LAMBDA : //CSE Rule 2
            currControl->ass_env = currEnvironment->id;
            control.pop_back();
            execStack.push(currControl) ;
            break ;
        case Control::GAMMA:
            handleGAMMA(temp, currControl, rator, newEnv, deltaIndex);
            break;
        case Control::NOT :
            control.pop_back();
            temp = execStack.top() ;
            if( temp->controlType == Control::TRUE || temp->controlType == Control::FALSE ){
                temp->controlType =  temp->controlType ==  Control::TRUE ? Control::FALSE : Control::TRUE;
            }else{
                cout << "Expecting a bool value for operator 'not'" << endl;
                exit(1) ;
            }
            break ;
        //CSE Rule 6
        case Control::GR :
        case Control::GE :
        case Control::LS :
        case Control::LE :
        case Control::EQ :
        case Control::NE :
        case Control::AUG :
        case Control::OR :
        case Control::AND_LOGICAL :
        case Control::ADD :
        case Control::SUBTRACT :
        case Control::MULTIPLY :
        case Control::DIVIDE :
        case Control::EXP :
            binaryOperation(currControl->controlType) ;
            break ;
        case Control::TAU:
            handleTau(temp, currControl, rator, newEnv, deltaIndex);
            break ;
        case Control::NEG : //CSE Rule 7
            handleNeg(temp, currControl, rator, newEnv, deltaIndex);
            break ;
        case Control::ENV:
            handleEnv(temp, currControl, rator, newEnv, deltaIndex);
            break;
        case Control::BETA:
            handleBeta(temp, currControl, rator, newEnv, deltaIndex);
            break;
        default:
            cout << "Unknown Control Type: " << currControl->controlType << endl;
            break;
        }
    }
}

Environment* CSEMachine::createNewEnvironment(){
    tempEnvironment = new Environment(numEnvironment);
    environmentMap[numEnvironment] =  tempEnvironment;
    numEnvironment++;
    return tempEnvironment;
}

void CSEMachine::printCS(){
    for(int i=0; i < control.size() ; i++){
        cout << control.at(i)->toStr() << " " ;
    }
    printf ("---------");
    stack<Control *> temp;
    while(!execStack.empty()){
        cout << execStack.top()->toStr() << " " ;
        temp.push(execStack.top());
        execStack.pop();
    }
    printf ("\n");
    while(!temp.empty()){
      execStack.push(temp.top());
      temp.pop();
    }
}


void CSEMachine::deltaPrint(){
    for(int j = 0; j < deltas->size(); j++){
        cout << deltas->at(j)->toStr() << " : ";
        for(int k = 0; k < deltas->at(j)->ctrlStruct->size(); k++){
            cout << deltas->at(j)->ctrlStruct->at(k)->toStr() << " ";
        }
        cout << endl;
    }
}

void CSEMachine::init(treeNode *root){
    deltas->push_back(rootDelta);
    flattenTree(root,rootDelta, deltas);
    //deltaPrint();
    control.push_back(new Control(Control::ENV, 0, false));
    execStack.push(new Control(Control::ENV, 0, false));
    for(int i=0; i< rootDelta->ctrlStruct->size(); i++)
        control.push_back(rootDelta->ctrlStruct->at(i));
    environmentStack.push(createNewEnvironment());
    environmentStack.top()->assignParent(PE);
    currEnvironment = environmentStack.top();
}

void CSEMachine::run(treeNode *root){
    init(root);
    execCSE();
    if(!control.empty() || environmentStack.size() != 1){
        printf("stack/env_stack is not empty");
    }
    printf ("\n");
}

void CSEMachine::flattenDeltaThen(treeNode* node, Control *delta,vector<Control *> *deltas){
    Control *deltaThen = new Control(Control::DELTA, deltas->size());
    deltas->push_back(deltaThen);
    delta->ctrlStruct->push_back(new Control(Control::DELTA, deltas->size()-1)); //delta then
    if(node->childNode->siblingNode->type == treeNode::TERNARY){
        flattenTree(node->childNode->siblingNode, deltaThen, deltas);
    }else{
        vector<string> *tempvariables = NULL;
        if(node->childNode->siblingNode->type == treeNode::TAU){
            treeNode *temp = node->childNode->siblingNode->childNode;
            tempvariables = new vector<string>;
            while(temp!= NULL){
                tempvariables->push_back(temp->nodeString); // will these be any useful
                temp = temp->siblingNode;
            }
        }
        deltaThen->addCtrl(node->childNode->siblingNode, node->childNode->siblingNode->type, node->childNode->siblingNode->nodeString, tempvariables, deltaThen, deltas->size());
        if(node->childNode->siblingNode->childNode != NULL)
            flattenTree(node->childNode->siblingNode->childNode, deltaThen, deltas);
    }
}

void CSEMachine::flattenDeltaElse(treeNode* node, Control *delta,vector<Control *> *deltas){
    Control *deltaElse = new Control(Control::DELTA, deltas->size());
    deltas->push_back(deltaElse);
    delta->ctrlStruct->push_back(new Control(Control::DELTA, deltas->size()-1));

    if(node->childNode->siblingNode->siblingNode->type == treeNode::TERNARY){
        flattenTree(node->childNode->siblingNode->siblingNode,deltaElse, deltas);
    }else{
        vector<string> *tempvariables = NULL;
        if(node->childNode->siblingNode->siblingNode->type == treeNode::TAU){
            treeNode *temp = node->childNode->siblingNode->siblingNode->childNode;
            tempvariables = new vector<string>;
            while(temp!= NULL){
                tempvariables->push_back(temp->nodeString);
                temp = temp->siblingNode;
            }
        }
        deltaElse->addCtrl(node->childNode->siblingNode->siblingNode, node->childNode->siblingNode->siblingNode->type, node->childNode->siblingNode->siblingNode->nodeString, tempvariables, deltaElse, deltas->size());
        if(node->childNode->siblingNode->siblingNode->childNode != NULL)
            flattenTree(node->childNode->siblingNode->siblingNode->childNode,deltaElse, deltas);
    }
}

void CSEMachine::flattenTernary(treeNode* node, Control *delta,vector<Control *> *deltas){
    flattenDeltaThen(node, delta, deltas);

    flattenDeltaElse(node, delta, deltas);

    Control *beta = new Control(Control::BETA);
    delta->ctrlStruct->push_back(new Control(Control::BETA, "beta"));
    delta->addCtrl(node->childNode, node->childNode->type, node->childNode->nodeString, NULL, NULL, deltas->size());
    if(node->childNode->childNode != NULL)
        flattenTree(node->childNode->childNode, delta, deltas);
}

void CSEMachine::flattenLAMBDA(treeNode* node, Control *delta,vector<Control *> *deltas){
    Control *temp = NULL;
    vector<string> *variables = NULL;
    variables = new vector<string>();
    if(treeNode::IDENTIFIER == node->childNode->type){
        variables->push_back(node->childNode->nodeString);
    }else if(treeNode::COMMA == node->childNode->type){
        treeNode *temp = node->childNode->childNode;
        while(NULL != temp){
            variables->push_back(temp->nodeString);
            temp = temp->siblingNode;
        }
    }else{
        cout << "Expected Identifier or Comma, but din't find" << endl;
    }
    temp = new Control(Control::DELTA, deltas->size());
    deltas->push_back(temp);
    delta->addCtrl(node, node->type, node->nodeString, variables, temp, deltas->size());
    flattenTree(node->childNode->siblingNode, temp, deltas);

    if(NULL != node->siblingNode)
        flattenTree(node->siblingNode,delta, deltas);

}

void CSEMachine::flattenTree(treeNode* node, Control *delta,vector<Control *> *deltas){
    Control *temp_del_ptr = NULL;
    vector<string> *variables = NULL;
    if(treeNode::LAMBDA == node->type){
        flattenLAMBDA(node, delta, deltas);
    }else if(node->type == treeNode::TERNARY){
        flattenTernary(node, delta, deltas);
    }else{
        if(node->type == treeNode::TAU){
            variables = new vector<string>();
            treeNode *temp = node->childNode;
            while(temp!= NULL){
                variables->push_back(temp->nodeString);
                temp = temp->siblingNode;
            }
        }
        delta->addCtrl(node, node->type, node->nodeString, variables, temp_del_ptr, deltas->size());
        if(NULL != node->childNode){
            flattenTree(node->childNode, delta, deltas);
        }
        if(NULL != node->siblingNode){
            flattenTree(node->siblingNode, delta,deltas);
        }
    }
}
