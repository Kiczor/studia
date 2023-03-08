
def add_to_tree(e, t):
    if t == ():
        return (e, (), ())
    x, left, right = t

    if x == e:
        return t
    elif e > x:
        return (x, left, add_to_tree(e, right))
    else:
        return (x, add_to_tree(e, left), right)


def list_to_tree(L):
    t = ()
    for e in L:
        t = add_to_tree(e, t)
    return t

def tree_to_list(t):
    if t == ():
        return []
    x, left, right = t
    return tree_to_list(left) + [x] + tree_to_list(right)



def in_tree(e, t):
    if t == ():
        return False
    x, left, right = t

    if x == e:
        return True

    if e > x:
        return in_tree(e, right)
    else:
        return in_tree(e, left)

# add, __contains__, __or__,

class Set:
    def __init__(self, elems):
        self.tree = list_to_tree(elems)

    def __str__(self):
        elems = tree_to_list(self.tree)
        napisy = map(str, elems)
        return '{' + ', '.join(napisy)  + '}'

    def add(self, e):
        self.tree = add_to_tree(e, self.tree)

    def __contains__(self, e):
        return in_tree(e, self.tree)

    def __iter__(self):
        return iter(tree_to_list(self.tree))

    def __or__(self, y):
        new = Set(tree_to_list(self.tree))
        for e in y:
            new.add(e)
        return new

    def __len__( self ):
        return len( tree_to_list( self.tree ) )

    def __and__( self, y ):
        new = Set( tree_to_list( self.tree ) )
        for e in y:
            if not in_tree( e, self.tree ):
                new.add( e )
        return new

    def innne_or(self, y):
        new = Set([])
        for e in self:
            new.add(e)
        for e in y:
            new.add(e)
        return new

s1 = Set([1,5,4,2,7,7,99,11])
s2 = set([2,4,6,8])

#for n in range(22,33):
#    s1.add(n)

print (s1)

#for i in [10,20,30]:
#    print (i, i in s1)

print (s1 | s2)
print (s1)
print ( len( s1 ) )
print ( s1 & s2 )
