class DPA:
    def __init__(self, n, start, final):
        self.n = n
        self.start = start
        self.final = final
        self.stack = []
        self.transitions = [[] for _ in range(self.n)]

    def create_pexpr_dpa(self):
        for c in range(ord('0'), ord('9') + 1):
            self.list_insert(self.transitions[0], Transition(chr(c), '\0', None, 1))
        for c in range(ord('0'), ord('9') + 1):
            self.list_insert(self.transitions[1], Transition(chr(c), '\0', None, 1))

        self.list_insert(self.transitions[0], Transition('(', '\0', 'a', 2))
        self.list_insert(self.transitions[2], Transition('(', 'a', 'a', 2))

        for c in range (ord('0'), ord('9') + 1):
            self.list_insert(self.transitions[2], Transition(chr(c), 'a', None, 3))
        
        for c in range (ord('0'), ord('9') + 1):
            self.list_insert(self.transitions[3], Transition(chr(c), 'a', None, 3))
        
        self.list_insert(self.transitions[3], Transition('+', 'a', None, 4))
        self.list_insert(self.transitions[3], Transition('-', 'a', None, 4))
        self.list_insert(self.transitions[3], Transition('*', 'a', None, 4))
        self.list_insert(self.transitions[3], Transition('/', 'a', None, 4))

        self.list_insert(self.transitions[4], Transition('(', 'a', 'a', 2))

        for c in range(ord('0'), ord('9') + 1):
            self.list_insert(self.transitions[4], Transition(chr(c), 'a', None, 5))
        
        for c in range(ord('0'), ord('9') + 1):
            self.list_insert(self.transitions[5], Transition(chr(c), 'a', None, 5))
        
        self.list_insert(self.transitions[5], Transition(')', 'a', '\0', 6))
        self.list_insert(self.transitions[6], Transition(')', 'a', '\0', 6))

        self.list_insert(self.transitions[6], Transition('+', 'a', None, 4))
        self.list_insert(self.transitions[6], Transition('-', 'a', None, 4))
        self.list_insert(self.transitions[6], Transition('*', 'a', None, 4))
        self.list_insert(self.transitions[6], Transition('/', 'a', None, 4))

        self.list_insert(self.transitions[6], Transition(None, None, None, 7))

    def list_insert(self, l, n):
        l.append(n)

class Transition:
    def __init__(self, input_symbol, stack_symbol, stack_newtop, state):
         self.input_symbol = input_symbol
         self.stack_symbol = stack_symbol
         self.stack_newtop = stack_newtop
         self.next_state = state

def stack_check(stack, t):
    if t.input_symbol == '(' and (t.stack_symbol == '\0' or t.stack_symbol == 'a'):
        stack.append(t.stack_newtop)
    elif t.input_symbol == ')' and t.stack_symbol == 'a':
        try:
            stack.pop()
        except IndexError:
            return
    return stack

def match(string, dpa):
    current_state = dpa.start
    start_stack = list(dpa.stack) 
    i = 0 
    while(i < len(string)):
        state_transitions = dpa.transitions[current_state]
        transition_found = False
        
        for t in state_transitions:
            if t.input_symbol == string[i]:
                dpa.stack = stack_check(dpa.stack, t)
                current_state = t.next_state
                transition_found = True
                break

        if not transition_found:
            return 0
        i += 1

    if current_state in dpa.final and start_stack == dpa.stack:
        return 1
    return 0

if __name__ == "__main__":
    dpa = DPA(8, 0, [1, 6]) # TODO: 7 deve ser o estado final
    dpa.create_pexpr_dpa()

    print(match("((17 + 91) - (67 * (15 / 5)))", dpa))