class CustomStack:
    def __init__(self):
        self.data = []
        self.index = -1

    def isempty(self):
        return self.index == -1

    def top(self):
        if self.isempty():
            print("Warning: Stack is Empty")
            return None
        return self.data[self.index]

    def push(self, val):
        self.index += 1
        self.data.append(val)

    def pop(self):
        if self.index == -1:
            print("Stack Is Empty")
            return
        self.index -= 1



stk = CustomStack()
stk.pop()
print(stk.isempty())
stk.push(6)
print(stk.isempty())
print(stk.top())
stk.pop()
print(stk.top())
print(stk.isempty())


