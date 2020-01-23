//
// Created by hadrian on 03-Dec-19.
//

#include <iostream>
#include "Polynomial.h"
#include "StringUtils.h"

static const char POLY_INPUT_END = ',';

Polynomial::MonomNode *Polynomial::createNode(const Monomial &monomial) {
    MonomNode *node = new MonomNode;

    // We don't want a dependency between this Polynomial and outside world monomials, hence take a copy.
    node->monomial = new Monomial(monomial);
    node->next = node->prev = nullptr;

    return node;
}

Polynomial::Polynomial():head(nullptr) { }

Polynomial::Polynomial(const Polynomial &polynomial):head(nullptr) {
    // We use a deep copy and not just copy, because the destructor
    // destroys the monomial nodes, so if we use a regular copy from B to A, and then
    // the destructor of B is called, A refers to addresses that were destroyed, and this is illegal.
    *this += polynomial;
}

Polynomial::~Polynomial() {
    clear();
}

void Polynomial::add(const Monomial &monomial) {
    // The zero monomial got no meaning, so ignore it.
    if (monomial.getCoefficient() != 0) {
        // If Polynomial is empty, just add the monomial as a node.
        if (head == nullptr) {
            head = createNode(monomial);
        }
        // Otherwise, we have monomials in this Polynomial already. Check if we should insert as first node.
        else if (head->monomial->getDegree() < monomial.getDegree()) {
            MonomNode *node = createNode(monomial);
            node->next = head;
            head->prev = node;
            head = node;
        } else {
            // Locate where we should insert it.
            // List of monomials is ordered by their degrees, in descending order.
            MonomNode *iter = head;
            while ((iter->monomial->getDegree() > monomial.getDegree()) && (iter->next != nullptr)) {
                iter = iter->next;
            }

            // Add to existing monomial
            if (iter->monomial->getDegree() == monomial.getDegree()) {
                doAddToNode(iter, monomial);
            } else {
                MonomNode *node = createNode(monomial);

                // Determine if we should insert before iterator, or iterator is tail element.
                if (iter->monomial->getDegree() < monomial.getDegree()) {
                    node->next = iter;
                    node->prev = iter->prev;
                    iter->prev->next = node;
                    iter->prev = node;
                }
                // Insert last
                else {
                    iter->next = node;
                    node->prev = iter;
                }
            }
        }
    }
}

void Polynomial::doAddToNode(Polynomial::MonomNode *monomialNode, const Monomial &monomial) {
    *(monomialNode->monomial) += monomial;

    // Do not keep zeroes in the list.
    if (monomialNode->monomial->getCoefficient() == 0) {
        if (monomialNode->prev != nullptr) {
            monomialNode->prev->next = monomialNode->next;
        }
        // Otherwise, this is head.
        else {
            head = monomialNode->next;
        }

        if (monomialNode->next != nullptr) {
            monomialNode->next->prev = monomialNode->prev;
        }

        delete monomialNode->monomial;
        delete monomialNode;
    }
}

void Polynomial::clear() {
    MonomNode *iter = head;

    while (iter) {
        MonomNode *temp = iter;
        iter = iter->next;

        delete temp->monomial;
        delete temp;
    }

    head = nullptr;
}

void Polynomial::print() const {
    std::cout << *this;
}

Polynomial &Polynomial::operator+=(const Polynomial &another) {
    MonomNode *iter = another.head;

    while (iter != nullptr) {
        // This copies the monomial.
        add(*(iter->monomial));
        iter = iter->next;
    }

    return *this;
}

Polynomial &Polynomial::operator+=(const Monomial &monomial) {
    add(monomial);
    return *this;
}

Polynomial Polynomial::operator+(const Polynomial &another) const {
    return (Polynomial(*this) += another);
}

Polynomial Polynomial::operator+(const Monomial &monomial) const {
    return (Polynomial(*this) += monomial);
}

Polynomial &Polynomial::operator-=(const Polynomial &another) {
    MonomNode *iter = another.head;

    while (iter != nullptr) {
        *this -= *(iter->monomial);
        iter = iter->next;
    }

    return *this;
}

Polynomial &Polynomial::operator-=(const Monomial &monomial) {
    add(-(monomial));
    return *this;
}

Polynomial Polynomial::operator-(const Polynomial &another) const {
    return (Polynomial(*this) -= another);
}

Polynomial Polynomial::operator-(const Monomial &monomial) const {
    return (Polynomial(*this) -= monomial);
}

Polynomial Polynomial::operator-() const {
    return (Polynomial() -= *this);
}

Polynomial &Polynomial::operator*=(const Polynomial &another) {
    // Save a copy of ourselves, cause the result is going to override us.
    Polynomial temp(*this);
    MonomNode *ourIter, *otherIter;

    // Clear ourselves, so the result can be safely added to us.
    clear();

    // In case one of them is empty, result will be empty.
    if ((temp.head != nullptr) && (another.head != nullptr)) {
        for (ourIter = temp.head; ourIter != nullptr; ourIter = ourIter->next) {
            for (otherIter = another.head; otherIter != nullptr; otherIter = otherIter->next) {
                *this += (*(ourIter->monomial) * *(otherIter->monomial));
            }
        }
    }

    return *this;
}

Polynomial &Polynomial::operator*=(const Monomial &monomial) {
    *this *= (Polynomial() += monomial);
    return *this;
}

Polynomial Polynomial::operator*(const Polynomial &another) const {
    return (Polynomial(*this) *= another);
}

Polynomial Polynomial::operator*(const Monomial &monomial) const {
    return (Polynomial(*this) *= (Polynomial() += monomial));
}

const Polynomial &Polynomial::operator=(const Polynomial &polynomial) {
    if (this != &polynomial) {
        this->clear();
        *this += polynomial;
    }

    return *this;
}

const Polynomial &Polynomial::operator=(const Monomial &monomial) {
    this->clear();
    *this += monomial;
    return *this;
}

double Polynomial::operator()(int x) const {
    double result = 0;
    MonomNode *iter = head;

    while (iter != nullptr) {
        result += ((*(iter->monomial))(x));
        iter = iter->next;
    }

    return result;
}

double &Polynomial::operator[](int degree) {
    static double coeffOfNonExistingDegree;

    // Reset it every time we subscript, cause it is not const, and user might change it.
    coeffOfNonExistingDegree = 0;

    MonomNode *iter = head;

    while (iter != nullptr) {
        if (iter->monomial->getDegree() == degree) {
            return iter->monomial->getCoefficientProperty();
        }

        iter = iter->next;
    }

    return coeffOfNonExistingDegree;
}

bool Polynomial::operator==(const Polynomial &another) const {
    bool equals = this == &another;

    if (!equals) {
        equals = true;
        MonomNode *ourIter = head, *otherIter = another.head;

        // Polynomials are ordered, so just compare the monomials in one loop, exit when there is any difference.
        while (equals && (ourIter != nullptr) && (otherIter != nullptr)) {
            if (*(ourIter->monomial) != *(otherIter->monomial)) {
                equals = false;
            }

            ourIter = ourIter->next;
            otherIter = otherIter->next;
        }

        // Make sure we compared all of the elements.
        equals = equals && (ourIter == nullptr) && (otherIter == nullptr);
    }

    return equals;
}

bool Polynomial::operator!=(const Polynomial &another) const {
    return !(*this == another);
}

bool Polynomial::operator==(const Monomial &monomial) const {
    return ((head == nullptr) && (monomial.getCoefficient() == 0)) ||
            ((head != nullptr) && (head->next == nullptr) && (*(head->monomial) == monomial));
}

bool Polynomial::operator!=(const Monomial &monomial) const {
    return !(*this == monomial);
}

Polynomial operator+(const Monomial &monomial, const Polynomial &polynomial) {
    return polynomial + monomial;
}

Polynomial operator-(const Monomial &monomial, const Polynomial &polynomial) {
    return monomial + (-polynomial);
}

Polynomial operator*(const Monomial &monomial, const Polynomial &polynomial) {
    return polynomial * monomial;
}

bool operator==(const Monomial &monomial, const Polynomial &polynomial) {
    return polynomial == monomial;
}

bool operator!=(const Monomial &monomial, const Polynomial &polynomial) {
    return polynomial != monomial;
}

std::ostream &operator<<(std::ostream &out, const Polynomial &polynomial) {
    if (polynomial.head == nullptr) {
        out << '0';
    } else {
        Polynomial::MonomNode *iter = polynomial.head;

        // Print first element.
		if ((*(iter->monomial)).getCoefficient() < 0) {
			out << "-";
		}
        out << *(iter->monomial);

		// Now print the rest
        for (iter = iter->next; iter != nullptr; iter = iter->next) {
			out << " ";

            // Append '+' only. A minus is appended by monomial's print.
            if ((*(iter->monomial)).getCoefficient() > 0) {
                out << "+";
            } else if ((*(iter->monomial)).getCoefficient() < 0) {
				out << "-";
			}

            out << " " << *(iter->monomial);
        }
    }

    return out;
}

std::istream &operator>>(std::istream &in, Polynomial &polynomial) {
    // Make sure polynomial is empty, to let users re-use the same polynomial references.
    polynomial.clear();

    int c;
    while (((c = StringUtils::peekIgnoringWhitespace(in)) != EOF) && (c != std::char_traits<char>::to_int_type(POLY_INPUT_END))) {
        Monomial inputMonomial;
        in >> inputMonomial;
        polynomial += inputMonomial;
    }

    // Remove comma and the enter.
    if (c != EOF) {
        in.get();
        while ((in.peek() != EOF) && isspace(in.peek()) && (in.get() != std::char_traits<char>::to_int_type('\n')));
    }

    return in;
}
