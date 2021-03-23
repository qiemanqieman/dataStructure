#include <iostream>

class polynomial{
private:
    struct node{
        double coef;
        int rank;
        node* next;
        node() = default;
        node(double c, int r, node* ne = nullptr):coef(c),rank(r),next(ne){}
        ~node() = default;
    };

    node* head;
    void insert(const node* n);

public:
    explicit polynomial(){head = new node();}
    polynomial(const polynomial &other);
    polynomial(polynomial &&other) noexcept;
    polynomial& operator=(const polynomial &p);
    polynomial& operator=(polynomial &&p) noexcept;
    ~polynomial(){clear();delete head;};

    void clear();
    void create();
    polynomial operator+(const polynomial &other) const;
    polynomial operator-(const polynomial &other) const;
    void show() const;
};

polynomial::polynomial(const polynomial &other){
    head = new node();
    node * p = head, *q = other.head->next;
    while(q){
        p->next = new node(q->coef,q->rank, nullptr);
        p = p->next;
        q = q->next;
    }
}

polynomial::polynomial(polynomial &&other) noexcept {
if (this == &other) return;
head = new node();
head->next = other.head->next;
other.head->next = nullptr;
}

polynomial& polynomial::operator=(const polynomial &p){
    if (this == &p) return *this;
    this->clear();
    node* n = p.head->next, *q = this->head;
    while(n){
        q->next = new node(n->coef,n->rank, nullptr);
        q = q->next;
        n = n->next;
    }
    return *this;
}

polynomial& polynomial::operator=(polynomial &&p) noexcept {
    if (this == &p) return *this;
    this->clear();
    this->head->next = p.head->next;
    p.head->next = nullptr;
    return *this;
}

void polynomial::insert(const node* n) {
    node* p = head;
    while(p->next){
        if (n->rank < p->next->rank)
            break;
        p = p->next;
    }
    p->next = new node(n->coef, n->rank, p->next);
}

void polynomial::clear() {
    node* p = head->next, *q;
    head->next = nullptr;
    while(p){
        q = p->next;
        delete p;
        p = q;
    }
}

void polynomial::create() {
    std::cout << "creating polynomial, please input pairs of coefficient and rank(-1 to stop):" << '\n';
    double co; int ra;
    node* tmp;
    while(true){
        std::cin >> co;
        if (co == EOF) break;
        std::cin >> ra;
        if (ra == EOF) break;
        tmp = new node(co,ra);
        this->insert(tmp);
        delete tmp;
    }
}

polynomial polynomial::operator+(const polynomial &other) const {
    node *p = this->head->next, *q = other.head->next, *tmp;
    polynomial res;
    while(p and q){
        if(p->rank < q->rank) {
            res.insert(p);
            p = p->next;
        }
        else if (p->rank == q->rank) {
            tmp = new node(p->coef + q->coef, p->rank, nullptr);
            res.insert(tmp);
            delete tmp;
            p = p->next;
            q = q->next;
        }
        else {
            res.insert(q);
            q = q->next;
        }
    }
    while(p){
        res.insert(p);
        p = p->next;
    }
    while(q){
        res.insert(q);
        q = q->next;
    }
    return res;
}

polynomial polynomial::operator-(const polynomial &other) const {
    node *p = this->head->next, *q = other.head->next, *tmp;
    polynomial res;
    while(p and q){
        if(p->rank < q->rank) {
            res.insert(p);
            p = p->next;
        }
        else if (p->rank == q->rank) {
            tmp = new node(p->coef - q->coef, p->rank, nullptr);
            res.insert(tmp);
            delete tmp;
            p = p->next;
            q = q->next;
        }
        else {
            res.insert(q);
            q = q->next;
        }
    }
    while(p){
        res.insert(p);
        p = p->next;
    }
    while(q){
        res.insert(q);
        q = q->next;
    }
    return res;
}

void polynomial::show() const {
    node* p = head->next;
    std::cout << "\n(coef, rank):\n";
    while(p) {
        std::cout << "(" << p->coef << ", " << p->rank << ") + ";
        p = p->next;
    }
    std::cout << "\b\b";
}

