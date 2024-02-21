//
// Created by referencecat on 23.11.23.
//

#ifndef A_DS_REMOTE_QUEUE_H
#define A_DS_REMOTE_QUEUE_H


template<class Item>
class Queue {
    Item *Q;
    int h, t, N;
public:
    Queue(int maxQ) : h(0), t(0), N(maxQ), Q(new Item[maxQ + 1]) {}

    int empty() const {
        return (h % N) == t;
    }

    void push(Item item) {
        Q[t++] = item;
        t %= N;
    }

    Item pop() {
        h %= N;
        return Q[h++];
    }
};

#endif //A_DS_REMOTE_QUEUE_H
