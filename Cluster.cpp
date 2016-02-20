//
// Created by Matthew Michaelis on 2/16/2016.
//

#include "Cluster.h"

namespace Clustering {

   LNode::LNode(const Point &p, LNodePtr n) : point(p){
       next = n;
    }

    Cluster::Cluster(){
        __size = 0;
        __points = nullptr;
    }

    Cluster::Cluster(const Cluster &C1){
        __size = C1.getSize();
        __cpy(C1.__points);
    }

    Cluster& Cluster::operator=(const Cluster & other){
        if(this != &other){
            //delete & copy
            //double *newVal = new double{other.getDims()};
            __size = other.__size;
            __del();
            __cpy(other.__points);
        }
        return *this;
    }
    Cluster::~Cluster(){

    }

    int Cluster::getSize() const{
        return __size;
    }

    void Cluster::__del(){
        LNodePtr temp;
        LNodePtr prev;
        while(__points != nullptr){
            temp = __points;
            if(temp->next == nullptr){
                delete temp;
                __points = nullptr;
                return;
            }
            prev = temp;
            temp = temp->next;
            while(temp->next != nullptr){
                temp = temp->next;
                prev = prev->next;
            }
            prev->next = nullptr;
            delete temp;
        }
    }

    void Cluster::__cpy(LNodePtr pts){
        if(pts != nullptr){
            LNodePtr null = nullptr;
            LNode *head = new LNode(pts->point,null);
            LNodePtr ptsCurr = pts->next;
            __points = head;
            LNodePtr curr = __points;

            while(ptsCurr != nullptr){
                curr->next = new LNode(ptsCurr->point,null);
                curr = curr->next;
                ptsCurr = ptsCurr->next;
            }
        }
    }

    bool Cluster::__in(const Point &p) const{

    }

    void Cluster::add(const Point & pNew) {

        if (__points == nullptr) {
            LNode *N = new LNode(pNew, nullptr);
            __points = N;
            ++__size;
            return;
        }

        if (__points->next == nullptr) {
            LNode *N = new LNode(pNew, nullptr);
            if(N->point <= __points->point){
                N->next = __points;
                __points = N;
                ++__size;
                return;
            } else {
                __points->next = N;
                ++__size;
                return;
            }
        }

        LNode *N = new LNode(pNew, nullptr);
        LNodePtr temp = __points->next;
        LNodePtr prev = __points;
        if(N->point <= __points->point){
            __points = N;
            N->next = prev;
            ++__size;
            return;
        }

        if(N->point < temp->point){
            prev->next = N;
            N->next = temp;
            ++__size;
            return;
        }

        while (temp->next != nullptr) {
            if(N->point < temp->point){
                prev->next = N;
                N->next = temp;
                ++__size;
                return;
            }
            temp = temp->next;
            prev = prev->next;
        }
        temp->next = N;
        ++__size;
    }


    const Point & Cluster::remove(const Point &P1) {
        // Check if the given point exists in the cluster.

            LNodePtr temp = __points;

            if (temp->point == P1) {

                temp = __points;
                if (__size > 0) {
                    __points = __points->next;
                    --__size;
                }
                delete temp;
            } else {
                int i = 0;
                LNodePtr prev = temp;
                temp = temp->next;

                for (; i < __size; ++i) {
                    if (temp->point == P1) {
                        if (temp->next == nullptr) {
                            prev->next = nullptr;
                            delete temp;
                            __size--;
                        } else {
                            prev->next = temp->next;
                        }
                    }
                    temp = temp->next;
                    prev = prev->next;
                }
            }
        return P1;
    }

    bool Cluster::contains(const Point & P1){

        LNodePtr temp;
        if(P1 == __points->point){
            return true;
        }
        if(__points->next == nullptr){
            return false;
        }
        temp = __points->next;
        for(int i = 0; i < __size; ++i){
            if(temp->point == P1){
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    const Point &Cluster::operator[](unsigned int index) const{
        LNodePtr temp;
        temp = __points;

        if(index == 0){
            return __points->point;
        }

        for(int i = 0; i < index; ++i){
            temp = temp->next;
        }
        return temp->point;
    }

    bool operator==(const Cluster & C1, const Cluster &C2){
        if(C1.__size != C2.__size){
            return false;
        }

        for(int i = 0; i < C1.__size; ++i){
            if(C1[i] != C2[i]){
                return false;
            }
        }
        return true;
    }
    bool operator!=(const Cluster & C1, const Cluster & C2){
        return !(C1 == C2);
    }
}