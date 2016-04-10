class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class SingleLinkedList:
    def __init__(self):
        self.firstNode = None
        self.lastNode = None

    def push_back(self, data):
        if not self.firstNode:
            self.firstNode = self.lastNode = Node(data)
        else:
            self.lastNode.next = Node(data)
            self.lastNode = self.lastNode.next

    def push_front(self, data):
        if not self.firstNode:
            self.firstNode = self.lastNode = Node(data)
        else:
            node = Node(data)
            node.next = self.firstNode
            self.firstNode = node

    def __iter__(self):
        return self.generator()

    def generator(self):
        node = self.firstNode
        while node:
            yield node.data
            node = node.next

def main():
    myList = SingleLinkedList()
    myList.push_front(0)
    myList.push_back(1)
    myList.push_back(2)
    myList.push_back(3)
    myList.push_back(4)
    myList.push_front(-1)

    for n in myList:
        print(n)

main()