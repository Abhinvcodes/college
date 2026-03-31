import collections

# --- 1. GRAMMAR CONFIGURATION ---
# The first rule must be the augmented start rule
RULES = [
    ("E'", "E"),
    ("E", "E+T"),
    ("E", "T"),
    ("T", "T*F"),
    ("T", "F"),
    ("F", "(E)"),
    ("F", "id")
]

TERMINALS = ["id", "+", "*", "(", ")", "$"]
NON_TERMINALS = ["E", "T", "F"]

# --- 2. HELPER FUNCTIONS ---
def get_closure(items):
    """Expands a set of items by looking at what follows the dot."""
    closure_set = set(items)
    while True:
        new_items = set()
        for item in closure_set:
            # item format: "LHS->alpha.Bbeta"
            lhs, rhs = item.split("->")
            if "." in rhs:
                after_dot = rhs.split(".")[1].strip()
                if after_dot and after_dot[0].isupper():
                    B = after_dot[0]
                    for r_lhs, r_rhs in RULES:
                        if r_lhs == B:
                            new_items.add(f"{r_lhs}->.{r_rhs}")
        if new_items.issubset(closure_set):
            break
        closure_set.update(new_items)
    return tuple(sorted(list(closure_set)))

def get_goto(state_items, symbol):
    """Moves the dot across a symbol and returns the closure of the result."""
    moved_items = []
    for item in state_items:
        lhs, rhs = item.split("->")
        if f".{symbol}" in rhs:
            new_rhs = rhs.replace(f".{symbol}", f"{symbol}.")
            moved_items.append(f"{lhs}->{new_rhs}")
    return get_closure(moved_items)

# --- 3. FIRST AND FOLLOW SETS ---
# Simplified for this specific grammar
FOLLOW = {
    "E": ["+", ")", "$"],
    "T": ["+", "*", ")", "$"],
    "F": ["+", "*", ")", "$"],
    "E'": ["$"]
}

# --- 4. STATE GENERATION ---
states = []
state_map = {} # items -> index

start_item = get_closure(["E'->.E"])
states.append(start_item)
state_map[start_item] = 0

# Tables to store transitions
action_table = {}
goto_table = {}

i = 0
while i < len(states):
    current_items = states[i]
    
    # Check for Transitions (Shifts and Gotos)
    for symbol in TERMINALS + NON_TERMINALS:
        next_state_items = get_goto(current_items, symbol)
        if next_state_items:
            if next_state_items not in state_map:
                state_map[next_state_items] = len(states)
                states.append(next_state_items)
            
            target_idx = state_map[next_state_items]
            if symbol in TERMINALS:
                action_table[(i, symbol)] = ('s', target_idx)
            else:
                goto_table[(i, symbol)] = target_idx

    # Check for Reductions
    for item in current_items:
        if item.endswith("."):
            lhs, rhs_with_dot = item.split("->")
            rhs = rhs_with_dot[:-1] # remove dot
            
            # Find rule index
            for idx, (r_lhs, r_rhs) in enumerate(RULES):
                if r_lhs == lhs and r_rhs == rhs:
                    if lhs == "E'":
                        action_table[(i, "$")] = ('a', 0)
                    else:
                        for term in FOLLOW[lhs]:
                            action_table[(i, term)] = ('r', idx)
                    break
    i += 1

# --- 5. C CODE GENERATION ---
print("/* --- AUTO-GENERATED SLR(1) TABLES --- */")
print(f"#define NUM_STATES {len(states)}")
print("#define NUM_TERMS 6\n")

print("Action action_table[NUM_STATES][NUM_TERMS] = {")
for s in range(len(states)):
    row = []
    for term in TERMINALS:
        act = action_table.get((s, term), ('e', 0))
        row.append(f"{{'{act[0]}', {act[1]}}}")
    print(f"    {{ {', '.join(row)} }}, // State {s}")
print("};\n")

print("int goto_table[NUM_STATES][3] = {")
for s in range(len(states)):
    row = []
    for nt in NON_TERMINALS:
        val = goto_table.get((s, nt), -1)
        row.append(str(val))
    print(f"    {{ {', '.join(row)} }}, // State {s}")
print("};")