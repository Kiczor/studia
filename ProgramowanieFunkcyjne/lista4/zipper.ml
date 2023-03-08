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
| NodeL( ctx, v, tr ) -> ( , )
| NodeR( tr, v, ctx ) ->
| Root -> ( c, t )

let left (Node(l, r), c) =
(l, left( c, r ))
