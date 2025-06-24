#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

struct Node {
    vector<string> strings;
    vector<Node*> children;
    int size;
    Node* parent;
    Node* child1;
    Node* child2;
    Node* child3;
    Node* child4;
    Node* child5;
    Node* child6;
    Node* child7;
    Node* child8;
    Node* child9;
    Node* child10;

    Node(vector<string>& newStrings) {
        strings = newStrings;
        parent = nullptr;
        size = 1;
        child1 = nullptr;
        child2 = nullptr;
        child3 = nullptr;
        child4 = nullptr;
        child5 = nullptr;
        child6 = nullptr;
        child7 = nullptr;
        child8 = nullptr;
        child9 = nullptr;
        child10 = nullptr;
        children.push_back(child1);
        children.push_back(child2);
        children.push_back(child3);
        children.push_back(child4);
        children.push_back(child5);
        children.push_back(child6);
        children.push_back(child7);
        children.push_back(child8);
        children.push_back(child9);
        children.push_back(child10);
    }
};

string getId(string str) {
    string id;
    int count = 0;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '|' && count == 1) {
            for (int j = i + 1; j < str.size(); j++) {
                if (str[j] == '|') {
                    id.insert(0, str.substr(i + 1, j - i - 1));
                    break;
                }
            }
            break;
        }
        else if (str[i] == '|') {
            count++;
        }
    }
    return id;
}

bool isLeaf(Node* node) {
    if ((node->children[0] == nullptr && node->children[1] == nullptr && node->children[2] == nullptr && node->children[3] == nullptr && node->children[4] == nullptr && node->children[5] == nullptr && node->children[6] == nullptr && node->children[7] == nullptr && node->children[8] == nullptr && node->children[9] == nullptr)) {
        return true;
    }
    else {
        return false;
    }
}

Node* addToNodeNormally(Node* root, Node* temp, string str) {
    temp->strings.push_back(str);
    temp->size++;
    for (int i = 0; i < temp->size - 1; i++) {
        for (int j = i + 1; j < temp->size; j++) {
            if (stoll(getId(temp->strings[j])) < stoll(getId(temp->strings[i]))) {
                string swap = temp->strings[j];
                temp->strings[j] = temp->strings[i];
                temp->strings[i] = swap;
            }
        }
    }
    return root;
}

string extractPrefix(string input) {
    string result;
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == '|') {
            result.insert(0, input.substr(0, i));
            break;
        }
    }
    return result;
}

Node* splitRoot(Node* temp, string str) {
    vector<string> tempVector;
    int tempSize = temp->size;
    for (int i = 0; i < temp->size; i++) {
        tempVector.push_back(temp->strings[i]);
    }
    tempVector.push_back(str);
    for (int i = 0; i < temp->size; i++) {
        for (int j = i + 1; j < temp->size + 1; j++) {
            if (stoll(getId(tempVector[j])) < stoll(getId(tempVector[i]))) {
                string swap = tempVector[j];
                tempVector[j] = tempVector[i];
                tempVector[i] = swap;
            }
        }
    }
    int splitIndex;
    if (tempSize % 2 == 1) {
        splitIndex = tempSize / 2;
    }
    else {
        splitIndex = tempSize / 2;
    }
    int i = tempSize - 1;
    while (temp->strings[i] != tempVector[splitIndex - 1]) {
        i--;
        temp->strings.pop_back();
    }
    if (tempSize % 2 == 0) {
        temp->size = tempSize - splitIndex;
    }
    else {
        temp->size = tempSize - splitIndex - 1;
    }
    vector<string> right;
    for (int j = splitIndex + 1; j < tempSize + 1; j++) {
        right.push_back(tempVector[j]);
    }
    Node* rightOfRoot = new Node(right);
    rightOfRoot->size = tempSize - temp->size;
    vector<string> newRootStrings;
    newRootStrings.push_back(tempVector[splitIndex]);
    Node* newRoot = new Node(newRootStrings);
    newRoot->children[0] = temp;
    newRoot->children[1] = rightOfRoot;
    temp->parent = newRoot;
    rightOfRoot->parent = newRoot;
    return newRoot;
}

Node** splitInLeaf(Node* temp, string str, Node* prevTemp, Node* leftPtr, Node* rightPtr, Node* parentOfParent) {
    vector<string> tempVector;
    vector<Node*> pointerArray;
    int oldSize = 0;
    for (int i = 0; i < temp->size + 1; i++) {
        if (temp->children[i] != nullptr) {
            if (temp->children[i] == prevTemp) {
                pointerArray.push_back(leftPtr);
                pointerArray.push_back(rightPtr);
                oldSize++;
                oldSize++;
            }
            else {
                pointerArray.push_back(temp->children[i]);
                oldSize++;
            }
        }
    }
    bool isNotLeaf = !isLeaf(temp);
    int tempSize = temp->size;
    for (int i = 0; i < temp->size; i++) {
        tempVector.push_back(temp->strings[i]);
    }
    tempVector.push_back(str);
    for (int i = 0; i < temp->size; i++) {
        for (int j = i + 1; j < temp->size + 1; j++) {
            if (stoll(getId(tempVector[j])) < stoll(getId(tempVector[i]))) {
                string swap = tempVector[j];
                tempVector[j] = tempVector[i];
                tempVector[i] = swap;
            }
        }
    }
    temp->strings.push_back(str);
    temp->size++;
    for (int i = 0; i < temp->size - 1; i++) {
        for (int j = i + 1; j < temp->size; j++) {
            if (stoll(getId(temp->strings[j])) < stoll(getId(temp->strings[i]))) {
                string swap = temp->strings[j];
                temp->strings[j] = temp->strings[i];
                temp->strings[i] = swap;
            }
        }
    }
    int splitIndex;
    if (tempSize % 2 == 1) {
        splitIndex = tempSize / 2;
    }
    else {
        splitIndex = tempSize / 2;
    }
    int i = tempSize;
    while (temp->strings[i] != tempVector[splitIndex - 1]) {
        i--;
        temp->strings.pop_back();
    }
    if (tempSize % 2 == 0) {
        temp->size = tempSize - splitIndex;
    }
    else {
        temp->size = tempSize - splitIndex - 1;
    }
    vector<string> right;
    for (int j = splitIndex + 1; j < tempSize + 1; j++) {
        right.push_back(tempVector[j]);
    }
    Node* rightOfRoot = new Node(right);
    rightOfRoot->size = tempSize - temp->size;
    vector<string> usedStrings;
    int usedSize = 0;
    bool wasValid = true;
    int onlyOneRight = 0;
    int onlyOneLeft = 0;
    if (isNotLeaf) {
        for (int i = 0; i < 10; i++) {
            rightOfRoot->children[i] = nullptr;
        }
        for (int i = rightOfRoot->size; i > -1; i--) {
            for (int j = oldSize - 1; j > -1; j--) {
                wasValid = true;
                if (pointerArray[j] != nullptr) {
                    for (int y = 0; y < usedSize; y++) {
                        if (pointerArray[j]->strings[0] == usedStrings[y]) {
                            wasValid = false;
                            break;
                        }
                    }
                    if (i == rightOfRoot->size) {
                        if (stoll(getId(pointerArray[j]->strings[0])) >= stoll(getId(rightOfRoot->strings[i - 1])) && wasValid) {
                            rightOfRoot->children[i] = pointerArray[j];
                            pointerArray[j]->parent = rightOfRoot;
                            usedStrings.push_back(pointerArray[j]->strings[0]);
                            usedSize++;
                            break;
                        }
                    }
                    else if (i != rightOfRoot->size && i != 0) {
                        if (stoll(getId(pointerArray[j]->strings[0])) >= stoll(getId(rightOfRoot->strings[i - 1])) && stoll(getId(pointerArray[j]->strings[pointerArray[j]->size - 1])) <= stoll(getId(rightOfRoot->strings[i])) && wasValid) {
                            rightOfRoot->children[i] = pointerArray[j];
                            pointerArray[j]->parent = rightOfRoot;
                            usedStrings.push_back(pointerArray[j]->strings[0]);
                            usedSize++;
                            break;
                        }
                    }
                    else {
                        if (stoll(getId(pointerArray[j]->strings[0])) >= stoll(getId(tempVector[splitIndex])) && stoll(getId(pointerArray[j]->strings[pointerArray[j]->size - 1])) <= stoll(getId(rightOfRoot->strings[i])) && wasValid && onlyOneRight == 0) {
                            rightOfRoot->children[i] = pointerArray[j];
                            pointerArray[j]->parent = rightOfRoot;
                            usedStrings.push_back(pointerArray[j]->strings[0]);
                            usedSize++;
                            onlyOneRight++;
                            break;
                        }
                    }
                }
            }
        }
    }
    Node* leftOfRoot = temp;
    if (isNotLeaf) {
        for (int i = 0; i < 10; i++) {
            leftOfRoot->children[i] = nullptr;
        }
        for (int i = 0; i < leftOfRoot->size + 1; i++) {
            for (int j = 0; j < oldSize; j++) {
                wasValid = true;
                if (pointerArray[j] != nullptr) {
                    for (int y = 0; y < usedSize; y++) {
                        if (pointerArray[j]->strings[0] == usedStrings[y]) {
                            wasValid = false;
                            break;
                        }
                    }
                    if (i == 0) {
                        if (stoll(getId(pointerArray[j]->strings[pointerArray[j]->size - 1])) <= stoll(getId(leftOfRoot->strings[i])) && wasValid) {
                            leftOfRoot->children[i] = pointerArray[j];
                            pointerArray[j]->parent = leftOfRoot;
                            usedStrings.push_back(pointerArray[j]->strings[0]);
                            usedSize++;
                            break;
                        }
                    }
                    else if (i != leftOfRoot->size) {
                        if (stoll(getId(pointerArray[j]->strings[0])) >= stoll(getId(leftOfRoot->strings[i - 1])) && stoll(getId(pointerArray[j]->strings[pointerArray[j]->size - 1])) <= stoll(getId(leftOfRoot->strings[i])) && wasValid) {
                            leftOfRoot->children[i] = pointerArray[j];
                            pointerArray[j]->parent = leftOfRoot;
                            usedStrings.push_back(pointerArray[j]->strings[0]);
                            usedSize++;
                            break;
                        }
                    }
                    else {
                        if (stoll(getId(pointerArray[j]->strings[0])) >= stoll(getId(leftOfRoot->strings[i - 1])) && stoll(getId(pointerArray[j]->strings[pointerArray[j]->size - 1])) <= stoll(getId(tempVector[splitIndex])) && wasValid && onlyOneLeft == 0) {
                            leftOfRoot->children[i] = pointerArray[j];
                            pointerArray[j]->parent = leftOfRoot;
                            usedStrings.push_back(pointerArray[j]->strings[0]);
                            usedSize++;
                            onlyOneLeft++;
                            break;
                        }
                    }
                }
            }
        }
    }
    vector<string> middle;
    middle.push_back(tempVector[splitIndex]);
    Node* middleNode = new Node(middle);
    Node** nodeArray = new Node*[3];
    nodeArray[0] = leftOfRoot;
    nodeArray[1] = middleNode;
    nodeArray[2] = rightOfRoot;
    return nodeArray;
}

Node* addToNodeWithPointers(Node* root, Node* temp, string str, Node* left, Node* right) {
    temp->strings.push_back(str);
    temp->size++;
    for (int i = 0; i < temp->size - 1; i++) {
        for (int j = i + 1; j < temp->size; j++) {
            if (stoll(getId(temp->strings[j])) < stoll(getId(temp->strings[i]))) {
                string swap = temp->strings[j];
                temp->strings[j] = temp->strings[i];
                temp->strings[i] = swap;
            }
        }
    }
    if (temp->strings[temp->size - 1] == str) {
        temp->children[temp->size] = right;
        right->parent = temp;
    }
    else {
        int i = 0;
        for (i = 0; i < temp->size; i++) {
            if (temp->strings[i] == str) {
                break;
            }
        }
        for (int j = temp->size; j > i + 1; j--) {
            temp->children[j] = temp->children[j - 1];
        }
        temp->children[i + 1] = right;
    }
    return root;
}

Node* splitInRootAndReturnRoot(Node* root, Node* temp, string str, Node* left, Node* right) {
    Node** threeNodes = splitInLeaf(root, str, temp, left, right, nullptr);
    Node* leftTemp = threeNodes[0];
    string middleStr = threeNodes[1]->strings[0];
    Node* rightTemp = threeNodes[2];
    vector<string> newRootStrings;
    newRootStrings.push_back(middleStr);
    root = new Node(newRootStrings);
    root->size = 1;
    root->children[0] = leftTemp;
    leftTemp->parent = root;
    root->children[1] = rightTemp;
    rightTemp->parent = root;
    root->parent = nullptr;
    return root;
}

Node* insert(Node* root, int order, string str) {
    if (root == nullptr) {
        vector<string> acc;
        acc.push_back(str);
        root = new Node(acc);
    }
    else {
        Node* temp = root;
        if (temp->children[0] == nullptr && temp->children[1] == nullptr && temp->children[2] == nullptr && temp->children[3] == nullptr && temp->children[4] == nullptr && temp->children[5] == nullptr && temp->children[6] == nullptr && temp->children[7] == nullptr && temp->children[8] == nullptr && temp->children[9] == nullptr) {
            if ((temp->size < order - 1 && temp == root)) {
                root = addToNodeNormally(root, temp, str);
            }
            else {
                Node* newRoot = splitRoot(temp, str);
                root = newRoot;
            }
        }
        else {
            while (!isLeaf(temp)) {
                for (int i = 0; i < temp->size; i++) {
                    if (stoll(getId(str)) <= stoll(getId(temp->strings[i])) && i == 0) {
                        if (i == 0) {
                            temp = temp->children[0];
                            break;
                        }
                        else if (i == 1) {
                            temp = temp->children[1];
                            break;
                        }
                        else if (i == 2) {
                            temp = temp->children[2];
                            break;
                        }
                        else if (i == 3) {
                            temp = temp->children[3];
                            break;
                        }
                        else if (i == 4) {
                            temp = temp->children[4];
                            break;
                        }
                        else if (i == 5) {
                            temp = temp->children[5];
                            break;
                        }
                        else if (i == 6) {
                            temp = temp->children[6];
                            break;
                        }
                        else if (i == 7) {
                            temp = temp->children[7];
                            break;
                        }
                        else if (i == 8) {
                            temp = temp->children[8];
                            break;
                        }
                    }
                    else if (i == temp->size - 1) {
                        if (i + 1 == 1) {
                            temp = temp->children[1];
                            break;
                        }
                        else if (i + 1 == 2) {
                            temp = temp->children[2];
                            break;
                        }
                        else if (i + 1 == 3) {
                            temp = temp->children[3];
                            break;
                        }
                        else if (i + 1 == 4) {
                            temp = temp->children[4];
                            break;
                        }
                        else if (i + 1 == 5) {
                            temp = temp->children[5];
                            break;
                        }
                        else if (i + 1 == 6) {
                            temp = temp->children[6];
                            break;
                        }
                        else if (i + 1 == 7) {
                            temp = temp->children[7];
                            break;
                        }
                        else if (i + 1 == 8) {
                            temp = temp->children[8];
                            break;
                        }
                        else if (i + 1 == 9) {
                            temp = temp->children[9];
                            break;
                        }
                    }
                    else if (stoll(getId(str)) > stoll(getId(temp->strings[i])) && stoll(getId(str)) < stoll(getId(temp->strings[i + 1]))) {
                        if (i + 1 == 1) {
                            temp = temp->children[1];
                            break;
                        }
                        else if (i + 1 == 2) {
                            temp = temp->children[2];
                            break;
                        }
                        else if (i + 1 == 3) {
                            temp = temp->children[3];
                            break;
                        }
                        else if (i + 1 == 4) {
                            temp = temp->children[4];
                            break;
                        }
                        else if (i + 1 == 5) {
                            temp = temp->children[5];
                            break;
                        }
                        else if (i + 1 == 6) {
                            temp = temp->children[6];
                            break;
                        }
                        else if (i + 1 == 7) {
                            temp = temp->children[7];
                            break;
                        }
                        else if (i + 1 == 8) {
                            temp = temp->children[8];
                            break;
                        }
                        else if (i + 1 == 9) {
                            temp = temp->children[9];
                            break;
                        }
                    }
                }
            }
            if (temp->size < order - 1) {
                root = addToNodeNormally(root, temp, str);
            }
            else {
                Node* parentOfTemp = temp->parent;
                Node* leftTemp = nullptr;
                Node* rightTemp = nullptr;
                string middleStr;
                Node** threeNodes = splitInLeaf(temp, str, nullptr, nullptr, nullptr, nullptr);
                leftTemp = threeNodes[0];
                middleStr = threeNodes[1]->strings[0];
                rightTemp = threeNodes[2];
                int onlyOne = 0;
                while (1) {
                    if (temp->parent->size < order - 1 && onlyOne == 0) {
                        onlyOne++;
                        root = addToNodeWithPointers(root, temp->parent, middleStr, leftTemp, rightTemp);
                        break;
                    }
                    else if (temp->parent->size >= order - 1 && temp->parent == root) {
                        root = splitInRootAndReturnRoot(root, temp, middleStr, leftTemp, rightTemp);
                        break;
                    }
                    else if (temp->parent->size >= order - 1 && temp->parent != root) {
                        Node* prevTemp = temp;
                        temp = temp->parent;
                        threeNodes = splitInLeaf(temp, middleStr, prevTemp, leftTemp, rightTemp, temp->parent);
                        leftTemp = threeNodes[0];
                        middleStr = threeNodes[1]->strings[0];
                        rightTemp = threeNodes[2];
                    }
                }
            }
        }
    }
    return root;
}

string extractSecondId(string input) {
    string result;
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == '|') {
            result.insert(0, input.substr(9, 2));
            break;
        }
    }
    return result;
}

int treeHeight(Node* root, int order) {
    Node* temp = root;
    int height = 1;
    int stop = 0;
    while (1) {
        stop = 0;
        for (int i = 0; i < order; i++) {
            if (i == order - 1 && temp->children[i] == nullptr) {
                stop = 1;
            }
            else if (temp->children[i] != nullptr) {
                temp = temp->children[i];
                height++;
                break;
            }
        }
        if (stop == 1) {
            break;
        }
    }
    return height;
}

int checkQueue(int tail, int head, vector<Node*> queue) {
    int nullCount = 0;
    for (int i = tail; i <= head; i++) {
        if (queue[i] == nullptr) {
            nullCount++;
        }
    }
    if (head - tail + 1 == nullCount) {
        return 0;
    }
    else {
        return 1;
    }
}

void printTree(Node* root, int order) {
    int height = treeHeight(root, order);
    int tail = 0;
    int head = -1;
    int elementCount = 0;
    vector<Node*> queue;
    for (int i = 0; i < order; i++) {
        queue.push_back(root->children[i]);
        head++;
        elementCount++;
    }
    for (int i = 0; i < order - 1; i++) {
        if (i < root->size) {
            cout << extractSecondId(root->strings[i]);
            if (i != order - 2) {
                cout << "+";
            }
        }
        else {
            cout << "oo";
            if (i != order - 2) {
                cout << "+";
            }
        }
    }
    cout << endl;
    int newRow = 0;
    int level = 1;
    while (checkQueue(tail, head, queue)) {
        Node* tempPrint = queue[tail++];
        elementCount--;
        if (tempPrint != nullptr) {
            for (int i = 0; i < order; i++) {
                queue.push_back(tempPrint->children[i]);
                head++;
                elementCount++;
            }
            for (int i = 0; i < order - 1; i++) {
                if (i < tempPrint->size) {
                    cout << extractSecondId(tempPrint->strings[i]);
                    if (i != order - 2) {
                        cout << "+";
                    }
                    else {
                        cout << "||";
                    }
                }
                else {
                    cout << "oo";
                    if (i != order - 2) {
                        cout << "+";
                    }
                    else {
                        cout << "||";
                    }
                }
            }
        }
        else {
            for (int i = 0; i < order; i++) {
                queue.push_back(nullptr);
                head++;
                elementCount++;
            }
            cout << "||";
        }
        newRow++;
        if (newRow == pow(order, level)) {
            cout << endl;
            newRow = 0;
            level++;
        }
    }
    return;
}

vector<string> findAccounts(Node* root, int order, string customerId) {
    int stepCount = 0;
    vector<string> results;
    int tail = 0;
    int head = -1;
    int elementCount = 0;
    vector<Node*> queue;
    for (int i = 0; i < root->size; i++) {
        stepCount++;
        if (getId(root->strings[i]) == customerId) {
            int valid = 1;
            if (i != 0) {
                if (getId(root->strings[i - 1]) == customerId) {
                    valid = 0;
                }
            }
            if (root->children[i] != nullptr && valid) {
                queue.push_back(root->children[i]);
                head++;
                elementCount++;
            }
            if (root->children[i + 1] != nullptr) {
                queue.push_back(root->children[i + 1]);
                head++;
                elementCount++;
            }
            results.push_back(root->strings[i]);
        }
        else if (i != root->size - 1 && getId(root->strings[i]) < customerId && getId(root->strings[i]) > customerId) {
            if (root->children[i + 1] != nullptr) {
                queue.push_back(root->children[i + 1]);
                head++;
                elementCount++;
            }
        }
        else if (i == root->size - 1 && getId(root->strings[i]) < customerId) {
            if (root->children[i + 1] != nullptr) {
                queue.push_back(root->children[i + 1]);
                head++;
                elementCount++;
            }
        }
        else if (i == 0 && getId(root->strings[i]) > customerId) {
            if (root->children[i] != nullptr) {
                queue.push_back(root->children[i]);
                head++;
                elementCount++;
            }
        }
    }
    while (elementCount != 0) {
        Node* tempResult = queue[tail++];
        elementCount--;
        for (int i = 0; i < tempResult->size; i++) {
            stepCount++;
            if (getId(tempResult->strings[i]) == customerId) {
                int valid = 1;
                if (i != 0) {
                    if (getId(tempResult->strings[i - 1]) == customerId) {
                        valid = 0;
                    }
                }
                if (tempResult->children[i] != nullptr && valid) {
                    queue.push_back(tempResult->children[i]);
                    head++;
                    elementCount++;
                }
                if (tempResult->children[i + 1] != nullptr) {
                    queue.push_back(tempResult->children[i + 1]);
                    head++;
                    elementCount++;
                }
                results.push_back(tempResult->strings[i]);
            }
            else if (i != tempResult->size - 1 && getId(tempResult->strings[i]) < customerId && getId(tempResult->strings[i]) > customerId) {
                if (tempResult->children[i + 1] != nullptr) {
                    queue.push_back(tempResult->children[i + 1]);
                    head++;
                    elementCount++;
                }
            }
            else if (i == tempResult->size - 1 && getId(tempResult->strings[i]) < customerId) {
                if (tempResult->children[i + 1] != nullptr) {
                    queue.push_back(tempResult->children[i + 1]);
                    head++;
                    elementCount++;
                }
            }
            else if (i == 0 && getId(tempResult->strings[i]) > customerId) {
                if (tempResult->children[i] != nullptr) {
                    queue.push_back(tempResult->children[i]);
                    head++;
                    elementCount++;
                }
            }
        }
    }
    cout << "Number of steps is " << stepCount << endl;
    return results;
}

string formatAccount(string account) {
    string result;
    string customerId;
    string accountId;
    string accountDetails;
    int index = 0;
    int delimiterCount = 0;
    int startIndex1 = 0;
    int startIndex2 = 0;
    int stop = 0;
    string accountCopy1 = account;
    string accountCopy2 = account;
    string accountCopy3 = account;
    int first1 = 1;
    int first2 = 1;
    int first3 = 1;
    int first4 = 1;
    while (1) {
        if (account[index] == '|') {
            delimiterCount++;
        }
        if (delimiterCount == 1 && first1) {
            customerId.insert(0, accountCopy1.substr(0, index));
            first1 = 0;
        }
        else if (delimiterCount == 2 && first2) {
            startIndex1 = index;
            first2 = 0;
        }
        else if (delimiterCount == 3 && first3) {
            accountId.insert(0, accountCopy2.substr(startIndex1, index - startIndex1));
            first3 = 0;
        }
        else if (delimiterCount == 4) {
            startIndex2 = index;
            first4 = 0;
        }
        else if (index == account.size()) {
            accountDetails.insert(0, accountCopy3.substr(startIndex2, index - startIndex2));
            break;
        }
        index++;
    }
    result = customerId + accountId + "|" + accountDetails;
    return result;
}

void deleteTree(Node* root) {
    delete root;
}

int main() {
    vector<string> tempVector;
    vector<string> excludeList;
    int order;
    Node* root = nullptr;
    int initialized = 0;
    while (1) {
        int choice;
        cout << endl << "Enter:" << endl << "1. - to create index over customer_account table" << endl
             << "2. - to print index to standard output" << endl
             << "3. - to print customer data" << endl
             << "4. - to add new record" << endl
             << "5. - to delete record from index" << endl
             << "6. - to delete all accounts of a customer" << endl
             << "7. - to delete index and exit" << endl;
        cin >> choice;
        if (choice == 1) {
            root = nullptr;
            cout << "Enter tree order (min 3 max 10)" << endl;
            cin >> order;
            if (order < 3 || order > 10) {
                cout << "Invalid tree order input" << endl;
                break;
            }
            ifstream in("CustomerAccount20.txt");
            string str;
            while (getline(in, str)) {
                root = insert(root, order, str);
                tempVector.push_back(str);
            }
            initialized = 1;
        }
        else if (choice == 2) {
            printTree(root, order);
        }
        else if (choice == 3) {
            string customerId;
            cout << "Enter C_ID of customer" << endl;
            cin >> customerId;
            int found = 0;
            ifstream in("Customer.txt");
            string customerData;
            while (getline(in, customerData)) {
                if (extractPrefix(customerData) == customerId) {
                    found = 1;
                    break;
                }
            }
            if (found == 1) {
                cout << "Successfully found customer " << customerId << "    " << customerData << endl;
                vector<string> accounts = findAccounts(root, order, customerId);
                if (accounts.size() == 0) {
                    int index = 0;
                    int delimiterCount = 0;
                    while (1) {
                        if (customerData[index] == '|') {
                            delimiterCount++;
                        }
                        if (delimiterCount == 4) {
                            break;
                        }
                        index++;
                    }
                    ofstream out("Output.txt");
                    string emptyPrefix;
                    emptyPrefix.insert(0, customerData.substr(0, index));
                    emptyPrefix += "|null|null|null|null";
                    out << emptyPrefix << "\n";
                }
                else {
                    int index = 0;
                    int delimiterCount = 0;
                    while (1) {
                        if (customerData[index] == '|') {
                            delimiterCount++;
                        }
                        if (delimiterCount == 4) {
                            break;
                        }
                        index++;
                    }
                    ofstream out("Output.txt");
                    string emptyPrefix;
                    emptyPrefix.insert(0, customerData.substr(0, index));
                    for (int g = 0; g < accounts.size(); g++) {
                        string formatted = formatAccount(accounts[g]);
                        string record = emptyPrefix + '|' + formatted;
                        out << record << "\n";
                    }
                }
            }
            else {
                cout << "Customer not found " << customerId << "    " << customerData << endl;
            }
        }
        else if (choice == 4) {
            string newRecord;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter new CustomerAccount" << endl;
            getline(cin, newRecord);
            if (initialized == 0) {
                root = nullptr;
                cout << "Enter tree order (min 3 max 10)" << endl;
                cin >> order;
                if (order < 3 || order > 10) {
                    cout << "Invalid tree order input" << endl;
                    break;
                }
                root = insert(root, order, newRecord);
                tempVector.push_back(newRecord);
                initialized = 1;
                continue;
            }
            else {
                string customerId = getId(newRecord);
                int found = 0;
                ifstream in("Customer.txt");
                string customerData;
                while (getline(in, customerData)) {
                    if (extractPrefix(customerData) == customerId) {
                        found = 1;
                        break;
                    }
                }
                if (found == 1) {
                    cout << "Successfully found customer " << customerId << "    " << customerData << endl;
                    vector<string> accounts = findAccounts(root, order, customerId);
                    if (accounts.size() == 0) {
                        root = insert(root, order, newRecord);
                        tempVector.push_back(newRecord);
                    }
                    else {
                        for (int g = 0; g < accounts.size(); g++) {
                            if (extractPrefix(accounts[g]) == extractPrefix(newRecord)) {
                                cout << "Account with same ID already exists" << endl;
                                break;
                            }
                            else if (extractPrefix(accounts[g]) != extractPrefix(newRecord) && g == accounts.size() - 1) {
                                root = insert(root, order, newRecord);
                                tempVector.push_back(newRecord);
                            }
                        }
                    }
                }
                else {
                    cout << "Customer not found " << customerId << "    " << customerData << endl;
                }
            }
        }
        else if (choice == 5) {
            vector<string> tempCopy = tempVector;
            tempVector.clear();
            string newRecord;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter CustomerAccount to delete " << endl;
            getline(cin, newRecord);
            string customerId = getId(newRecord);
            int found = 0;
            ifstream in("Customer.txt");
            string customerData;
            while (getline(in, customerData)) {
                if (extractPrefix(customerData) == customerId) {
                    found = 1;
                    break;
                }
            }
            if (found == 1) {
                cout << "Successfully found customer " << customerId << "    " << customerData << endl;
                vector<string> accounts = findAccounts(root, order, customerId);
                if (accounts.size() == 0) {
                    cout << "Requested account for deletion does not exist" << endl;
                }
                else {
                    for (int g = 0; g < accounts.size(); g++) {
                        if (extractPrefix(accounts[g]) == extractPrefix(newRecord)) {
                            cout << "Account with same ID exists" << endl;
                            root = nullptr;
                            excludeList.push_back(newRecord);
                            int z = 0;
                            while (tempCopy.size() != z) {
                                z++;
                                int skip = 0;
                                for (int y = 0; y < excludeList.size(); y++) {
                                    if (excludeList[y] == tempCopy[z - 1]) {
                                        skip = 1;
                                        break;
                                    }
                                }
                                if (skip == 1) {
                                    continue;
                                }
                                root = insert(root, order, tempCopy[z - 1]);
                                tempVector.push_back(tempCopy[z - 1]);
                            }
                            initialized = 1;
                            break;
                        }
                        else if (extractPrefix(accounts[g]) != extractPrefix(newRecord) && g == accounts.size() - 1) {
                            cout << "Requested account for deletion does not exist" << endl;
                        }
                    }
                }
            }
            else {
                cout << "Customer not found, cannot delete account " << customerId << "    " << customerData << endl;
            }
        }
        else if (choice == 6) {
            vector<string> tempCopy = tempVector;
            tempVector.clear();
            string newId;
            cout << "Enter CustomerAccount to delete " << endl;
            cin >> newId;
            string customerId = newId;
            int found = 0;
            ifstream in("Customer.txt");
            string customerData;
            while (getline(in, customerData)) {
                if (extractPrefix(customerData) == customerId) {
                    found = 1;
                    break;
                }
            }
            if (found == 1) {
                cout << "Successfully found customer " << customerId << "    " << customerData << endl;
                vector<string> accounts = findAccounts(root, order, customerId);
                if (accounts.size() == 0) {
                    cout << "Requested account for deletion does not exist" << endl;
                }
                else {
                    for (int g = 0; g < accounts.size(); g++) {
                        if (getId(accounts[g]) == newId) {
                            cout << "Account with same ID exists" << endl;
                            root = nullptr;
                            excludeList.push_back(newId);
                            int z = 0;
                            while (tempCopy.size() != z) {
                                z++;
                                int skip = 0;
                                for (int y = 0; y < excludeList.size(); y++) {
                                    if (excludeList[y] == getId(tempCopy[z - 1])) {
                                        skip = 1;
                                        break;
                                    }
                                }
                                if (skip == 1) {
                                    continue;
                                }
                                root = insert(root, order, tempCopy[z - 1]);
                                tempVector.push_back(tempCopy[z - 1]);
                            }
                            initialized = 1;
                            break;
                        }
                        else if (getId(accounts[g]) != newId && g == accounts.size() - 1) {
                            cout << "Requested account for deletion does not exist" << endl;
                        }
                    }
                }
            }
            else {
                cout << "Customer not found, cannot delete account " << customerId << "    " << customerData << endl;
            }
        }
        else if (choice == 7) {
            deleteTree(root);
            break;
        }
        else {
            cout << "Invalid input, try again" << endl;
        }
    }
    return 0;
}
