#include <iostream>
using namespace std;
struct Cart {
	double cost;
	int MaKhach;
	char SanPham[10][20];
	int SoLuong[20];
	int Count;
	Cart* next;
};
typedef Cart* PCart;
struct Queue {
	int MAX_SIZE;
	PCart rear;
	PCart front;
};
typedef Queue* PQueue;
void init(PQueue q, int MAX) {
	q->rear = q->front = NULL;
	q->MAX_SIZE = MAX;
}
bool isEmpty(PQueue q) {
	return q->front == NULL;
}
int count_queue(Queue* q) {
    PCart tmp = q->front;
    int c = 0;
    while (tmp) {
        c++;
        tmp = tmp->next;
    }
    return c;
}
bool isFull(PQueue q) {
    return count_queue(q) == q->MAX_SIZE;
}
void enqueue(PQueue q, PCart c) {
    if (isFull(q)) {
        cout << "Hang doi day" << endl;
        delete c;
        return;
    }
    if (isEmpty(q)) {
        q->front = q->rear = c;
    }
    else {
        q->rear->next = c;
        q->rear = c;
    }
}
void dequeue(PQueue q) {
    if (isEmpty(q)) {
        cout << "Hang doi rong, khong co gi de thanh toan!" << endl;
        return;
    }
    PCart temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    delete temp;
}
double totalCost(PQueue q) {
    double totalCost = 0;
    PCart temp = q->front;
    while (temp != NULL) {
        totalCost += temp->cost;
        temp = temp->next;
    }
    return totalCost;
}
int countProduct(PQueue q, const char* SanPham) {
    int Count = 0;
    Cart* temp = q->front;
    while (temp != nullptr) {
        for (int i = 0; i < temp->Count; ++i) {
            if (strcmp(temp->SanPham[i], SanPham) == 0) {
                Count += temp->SoLuong[i];
            }
        }
        temp = temp->next;
    }
    return Count;
}
int main() {
    Queue q;
    init(&q, 20);

    PCart cart1 = new Cart;
    cart1->cost = 100.0;
    cart1->MaKhach = 1;
    cart1->Count = 2;
    for (int i = 0; i < 20; i++) {
        cart1->SanPham[0][i] = "TraSua"[i];
        if ("TraSua"[i] == '\0') break;
    }
    cart1->SoLuong[0] = 2;
    for (int i = 0; i < 20; i++) {
        cart1->SanPham[1][i] = "Pizza"[i];
        if ("Pizza"[i] == '\0') break;
    }
    cart1->SoLuong[1] = 1;
    cart1->next = NULL;

    enqueue(&q, cart1);

    PCart cart2 = new Cart;
    cart2->cost = 50.0;
    cart2->MaKhach = 2;
    cart2->Count = 1;
    for (int i = 0; i < 20; i++) {
        cart2->SanPham[0][i] = "TraSua"[i];
        if ("TraSua"[i] == '\0') break;
    }
    cart2->SoLuong[0] = 1;
    cart2->next = NULL;
    enqueue(&q, cart2);
    cout << "Tong doanh thu: " << totalCost(&q) << endl;
    cout << "So luong 'TraSua' da ban: " << countProduct(&q, "TraSua") << endl;
    dequeue(&q);
    cout << "Tong doanh thu sau khi thanh toan: " << totalCost(&q) << endl;
    dequeue(&q);
    cout << "Hang doi rong: " << (isEmpty(&q) ? "Yes" : "No") << endl;

    return 0;
}

