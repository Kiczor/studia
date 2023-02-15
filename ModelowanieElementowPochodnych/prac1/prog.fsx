printfn "Hello World from F#"

//1
let a = 0
let b = 1
let l = [b; a]
let f ls =

    let (x::y::_) = ls

    (x+y)::ls

let g f x = f ( f x)
let n = g ( g ( g f) ) l

printf "res: %A\n" n

//2
let fst (a, b, c) = a
let mid (a, b, c) = b
let lst (a, b, c) = c

printf "res: %d\n" (fst (1,2,3))

//3
let factorial n = List.fold (fun a b -> a * b) 1 [1 .. n]

printf "factorial 6: %d\n" (factorial 6)

let binomialCoefficient n k = (factorial n) / ( (factorial k) * (factorial (n - k) ) )

printf "binomial coefficient 7 4: %d\n" (binomialCoefficient 7 4)

let pascal n = List.map (binomialCoefficient n) [0 .. n]

printf "pascal 5: %A\n" (pascal 5)

type facultytype = 
    | PPT
    | IZ
    | IT
    | EFM
    | MAT

type myRecord = 
    {   StudentName: string;
        GPA: float;
        Faculty: facultytype }

let s1 = { StudentName = "Joe"; GPA = 3.5; Faculty = IT }
let examplelist = [ { StudentName = "Joe"; GPA = 3.5; Faculty = IT }; { StudentName = "Anna"; GPA = 3.4; Faculty = MAT }; { StudentName = "Joe2"; GPA = 5.0; Faculty = IT };
                    { StudentName = "John"; GPA = 3; Faculty = EFM }; { StudentName = "Alex"; GPA = 4.234; Faculty = IZ }; { StudentName = "Joanne"; GPA = 3.98; Faculty = IT }
                    { StudentName = "Joey"; GPA = 2.4; Faculty = IT }; { StudentName = "Joe"; GPA = 3.5; Faculty = PPT }; { StudentName = "Joe4"; GPA = 2.7; Faculty = IT }; { StudentName = "Joe3"; GPA = 3.5; Faculty = IZ } ]

let printITonly ls = printf "IT only: %A\n" (List.filter (fun x -> match x with
                                                                    | { StudentName = _; GPA = _; Faculty = IT } -> true
                                                                    | _ -> false) ls)

printITonly examplelist

let averageGPA f xs = 
    let (s, c) = List.fold (fun (sum, cnt) x -> match x with
                                                    | { StudentName = _; GPA = g; Faculty = fac } when fac = f -> (sum + g, cnt + 1.0)
                                                    | { StudentName = _; GPA = _; Faculty = _ } -> (sum, cnt) ) (0.0, 0.0) xs
    s / c

printf "average gpa in IZ: %f\n" (averageGPA IZ examplelist)