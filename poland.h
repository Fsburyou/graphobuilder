#ifndef POLAND_H
#define POLAND_H

#endif // POLAND_H

#include <string>
#include <cmath>
#include <iostream>
using namespace std;

struct Stack {
    double number;
    char znak;
    Stack *next;
};

const double PI = 3.14159265;

const double EPS = 1E-5;

Stack *top1 = nullptr;
Stack *top2 = nullptr;

int pr = 0;

void Error(string s) {
    int bal = 0;
    int skobznak = 0;
    for (unsigned int i = 0; i < s.length(); i++) {
        if (s[i] == '(')
            bal += 1;
        if (s[i] == ')')
            bal -= 1;
        if (bal < 0)
            pr = -1;
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^') {
            if (s[i + 1] == '+' || s[i + 1] == '-' || s[i + 1] == '*' || s[i + 1] == '/' || s[i + 1] == '^')
                pr = -1;
        }
        if (s[i] == '(' && i < (s.length() - 1) && s[i + 1] == ')')
            pr = -1;
        if (s[i] == '(')
            skobznak = -1;
        else
            skobznak = 0;
        if (s[i] == '+' || s[i] == '*' || s[i] == '/') {
             if (skobznak == -1)
                 pr = -1;
        } else {
            skobznak = 0; }
        if (s[i] == ')' && i != 0) {
            if (s[i - 1] == '+' || s[i - 1] == '-' || s[i - 1] == '*' || s[i - 1] == '/')
                pr = -1; }
        }
    if (s[s.length() - 1] == '+' || s[s.length() - 1] == '-')
            pr = -1;
    if (s[s.length() - 1] == '*' || s[s.length() - 1] == '/')
            pr = -1;
    if (s[0] == '*' || s[0] == '/' || s[0] == '+')
        pr = -1;
    if (bal != 0)
        pr = -1; }

void Error1(string s) {
    for (unsigned int i = 0; i < s.length(); i++) {
        if ('a' <= s[i] && s[i] <= 'z' && s[i] != 's' && s[i] != 'c'
           && s[i] != 't' && s[i] != 'q' && s[i] != 'l')
            pr = -1;
        if ('A' <= s[i] && s[i] <= 'Z')
            pr = -1;
    }
}

void push(Stack *& t, char ch, double num) {
    Stack *p = new(Stack);
    p->number = num;
    p->znak = ch;
    p->next = t;
    t = p;
}

Stack pop(Stack *&t) {
    if (t != nullptr) {
        Stack k = (*t);
        t = (*t).next;
        return k;}
}

void replaceall(string &s, string from, string to) {
    size_t ind = s.find(from);
    while (ind != std::string::npos) {
        s.replace(ind, from.length(), to);
        ind = s.find(from, ind + to.length()); }
}

void apply(char znak) {
    double b = pop(top1).number;
    double c = 0.0;
    if (pr == -1)
        return;
    if (znak == '+' || znak == '-' || znak == '*'
        || znak == '/' || znak == '^') {
         double a = pop(top1).number;
    if (znak == '^') {
        if ((b < 0 && a != 0) || b >= 0)
            c = pow(a, b);
        else
            pr = -1; }

    if (znak == '-')
        c = a - b;

    if (znak == '+')
        c = a + b;

    if (znak == '*')
        c = a * b;

    if (znak == '/' && abs(b) > EPS)
        c =  a / b;

    if (znak == '/' && abs(b) <= EPS)
        pr = -1;
    } else {
    if (znak == 's')
        c = sin(b);

    if (znak == 'c')
        c = cos(b);

    if (znak == 't')
    {
        if (abs(int(b) % int(2 * PI)  - PI / 2) <= EPS)
            pr = -1;
        else
            c = tan(b);
    }

    if (znak == 'q' && b >= EPS) {
        c = sqrt(b); }
    if (znak == 'q' && b < 0) {
        pr = -1; }
    if (znak == 'l' && b > EPS)
        c = log(b);
    if (znak == 'l' && b <= EPS)
        pr = -1; }
    if (pr != -1)
        push(top1, '@', c);
}

int prior(char s1) {
    if (s1 == '(')
        return 0;

    if (s1 == '+' || s1 == '-')
        return 1;

    if (s1 == '*' || s1 == '/')
        return 2;

    if (s1 == 'q' || s1 == '^')
        return 3;
    return 4;
}

int calcc(string s, double &ans) {

    pr = 0;
    Error(s);
    replaceall(s, "sin", "s");
    replaceall(s, "cos", "c");
    replaceall(s, "tg", "t");
    replaceall(s, "sqrt", "q");
    replaceall(s, "ln", "l");
    Error1(s);
    for (unsigned int i = 0; i < s.length(); i++) {
        double sborchisla = 0.0;
        int cnt = 0;
        if ('0' <= s[i] && s[i] <= '9') {
            while ('0' <= s[i] && s[i] <= '9') {
                sborchisla *= 10.0;
                sborchisla += s[i] - '0';
                i++;}
            if (s[i] == '.'){
                i++;
                while ('0' <= s[i] && s[i] <= '9') {
                    sborchisla *= 10.0;
                    sborchisla += s[i] - '0';
                    cnt++;
                    i++;}
                for (int j = 0; j < cnt; j++) {
                    sborchisla /= 10.0;
                }
            }
            push(top1, '@', sborchisla);}
        if (s[i] == '(')
            push(top2, s[i], 0.0);
        if (s[i] == ')') {
            while ((*top2).znak != '(' && pr != -1) {
                apply(pop(top2).znak);}
            pop(top2);}
        if (s[i] == '-')
            if (s[i - 1] == '(' || i == 0)
                push(top1, '@', 0.0);
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' ||
            s[i] == 's' || s[i] == 'l' || s[i] == 'c' || s[i] == 't' ||
            s[i] == '^' || s[i] == 'q') {
            while (top2 != nullptr && prior(s[i]) <= prior((*top2).znak) && pr != -1) {
                apply((*top2).znak);
                pop(top2);}
            push(top2, s[i], 0.0);}
    }
    while (top2 != nullptr && pr != -1) {
        apply((*top2).znak);
        pop(top2);}
    if (pr != -1) {
        ans = (pop(top1)).number;
        return 0;
    }
    return -1;
}
