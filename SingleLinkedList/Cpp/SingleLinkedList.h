#pragma once

#include <iostream>

template <typename T>
class SingleLinkedList
{
    struct Node
    {
        explicit Node(T data) : data_(data), next_(nullptr) {}
        T data_;
        Node* next_;
    };

public:
    SingleLinkedList() : first_(nullptr), last_(nullptr) {}
    ~SingleLinkedList()
    {
        while (first_)
        {
            auto next = first_->next_;
            delete first_;
            first_ = next;
        }
    }

    void push_back(T data)
    {
        if (first_ == nullptr)
        {
            first_ = last_ = new Node(data);
        }
        else
        {
            last_->next_ = new Node(data);
            last_ = last_->next_;
        }
    }

    void walk() const
    {
        auto node = first_;
        while (node)
        {
            std::cout << node->data_ << std::endl;
            node = node->next_;
        }
    }

private:
    Node* first_;
    Node* last_;
};