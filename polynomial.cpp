#include <iostream>
#include <sstream> 
using namespace std;

// Node structure for the linked list
struct Node {
    int coeff;  // Coefficient
    int exp;    // Exponent
    Node* next;
};

// Function to create a new node
Node* createNode(int coeff, int exp) {
    Node* newNode = new Node();
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = nullptr;
    return newNode;
}

// Function to insert a node into a polynomial in sorted order by exponent
void insertNode(Node*& head, int coeff, int exp) {
    Node* newNode = createNode(coeff, exp);
    if (!head || exp > head->exp) {
        newNode->next = head;
        head = newNode;
        return;
    }

    Node* temp = head;
    while (temp->next && temp->next->exp > exp) {
        temp = temp->next;
    }

    if (temp->exp == exp) {
        temp->coeff += coeff;  
        delete newNode;
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

// Function to add two polynomials
Node* addPolynomials(Node* poly1, Node* poly2) {
    Node* result = nullptr;
    while (poly1 && poly2) {
        if (poly1->exp == poly2->exp) {
            insertNode(result, poly1->coeff + poly2->coeff, poly1->exp);
            poly1 = poly1->next;
            poly2 = poly2->next;
        } else if (poly1->exp > poly2->exp) {
            insertNode(result, poly1->coeff, poly1->exp);
            poly1 = poly1->next;
        } else {
            insertNode(result, poly2->coeff, poly2->exp);
            poly2 = poly2->next;
        }
    }

    while (poly1) {
        insertNode(result, poly1->coeff, poly1->exp);
        poly1 = poly1->next;
    }

    while (poly2) {
        insertNode(result, poly2->coeff, poly2->exp);
        poly2 = poly2->next;
    }

    return result;
}

// Function to multiply two polynomials
Node* multiplyPolynomials(Node* poly1, Node* poly2) {
    Node* result = nullptr;
    for (Node* p1 = poly1; p1; p1 = p1->next) {
        for (Node* p2 = poly2; p2; p2 = p2->next) {
            insertNode(result, p1->coeff * p2->coeff, p1->exp + p2->exp);
        }
    }
    return result;
}

// Function to display a polynomial
void displayPolynomial(Node* poly) {
    while (poly) {
        cout << poly->coeff << "x^" << poly->exp;
        if (poly->next) cout << " + ";
        poly = poly->next;
    }
    cout << endl;
}

// Main function
int main() {
    while (true) {
        Node* polys[11] = {nullptr};  // Array to store up to 11 polynomials
        int numPolys;

        cout << "Enter the number of polynomials (up to 11): ";
        cin >> numPolys;
        cin.ignore(); 

        for (int i = 0; i < numPolys; i++) {
            cout << "Enter terms for polynomial " << i + 1 
                 << " (format: coeff exp, one line per term, leave blank to finish):\n";
            string line;
            while (true) {
                getline(cin, line);
                if (line.empty()) break;
                istringstream iss(line);
                int coeff, exp;
                iss >> coeff >> exp;
                insertNode(polys[i], coeff, exp);
            }
        }

        // Add all polynomials
        Node* sum = polys[0];
        for (int i = 1; i < numPolys; i++) {
            sum = addPolynomials(sum, polys[i]);
        }

        // Multiply all polynomials
        Node* product = polys[0];
        for (int i = 1; i < numPolys; i++) {
            product = multiplyPolynomials(product, polys[i]);
        }

        cout << "\nSum of polynomials: ";
        displayPolynomial(sum);

        cout << "\nProduct of polynomials: ";
        displayPolynomial(product);

        // Ask if the user wants to run the program again
        cout << "\nDo you want to enter another set of polynomials? (yes/no): ";
        string response;
        getline(cin, response);
        if (response == "no" || response == "No") {
            break;
        }
    }

    return 0;
}
