class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

    def get_data(self):
        return self.data

    def get_next(self):
        return self.next

    def set_next(self, next_node):
        self.next = next_node


class CustomStack:
    def __init__(self):
        self.head = None

    def isempty(self):
        return self.head is None

    def top(self):
        if self.isempty():
            print("Warning: Stack is Empty")
            return None
        return self.head.get_data()

    def pop(self):
        if self.isempty():
            return
        self.head = self.head.get_next()

    def push(self, value):
        container = Node(value)
        if not self.isempty():
            container.set_next(self.head)
        self.head = container


stk = CustomStack()
stk.pop()
print(stk.isempty())
stk.push(3)
print(stk.isempty())
print(stk.top())
stk.pop()
print(stk.top())
print(stk.isempty())

