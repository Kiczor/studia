type 'a tree =
| Leaf
| Node of 'a tree * 'a * 'a tree

type 'a tree_context =
| Root
| NodeL of 'a tree_context * 'a * 'a tree
| NodeR of 'a tree * 'a * 'a tree_context

type 'a zipper = 'a tree_context * 'a tree

let treetozipper t = (Root, t)

let up ( c, t ) =
match c with
| NodeL( ctx, v, tr ) -> ( ctx, Node( t, v, tr ) )
| NodeR( tr, v, ctx ) -> ( ctx, Node( tr, v, t ) )
| Root -> ( c, t )

let left ( c, Node(l, v, r) ) =
       ( NodeL( c, v, r ), l )

let right ( c, Node( l, v, r ) ) =
        ( NodeR( l, v, c ), r )

let rec zippertotree ( c, t ) = if c == Root then t else zippertotree( up ( c, t ) ) 

let swapunder ( c, t ) nt = (c, nt)
