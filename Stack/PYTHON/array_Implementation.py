class CustomStack:
    def __init__(self, size=10):
        self.data = [None] * size
        self.size = size
        self.index = -1

    def __del__(self):
        del self.data

    def isempty(self):
        return self.index == -1

    def top(self):
        if self.isempty():
            print("Warning: Stack is Empty")
            return None
        return self.data[self.index]

    def push(self, val):
        if self.index + 1 == self.size:
            print("Error: Stack Is Full")
            return
        self.index += 1
        self.data[self.index] = val

    def pop(self):
        if self.index == -1:
            print("Stack Is Empty")
            return
        self.index -= 1



stk = CustomStack()
stk.pop()
print(stk.isempty())
stk.push(11)
print(stk.isempty())
print(stk.top())
stk.pop()
print(stk.top())
print(stk.isempty())

