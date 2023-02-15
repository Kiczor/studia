namespace OptionsCalculator

open System
open MathNet.Numerics.Distributions

module OptionsModel =
    let rnd = Random()
    let normalrandom =
        let u1 = rnd.NextDouble()
        let u2 = rnd.NextDouble()
        (sqrt (-2.0 * (log u1))) * (sin (2.0 * Math.PI * u2))

    let simulateBrownianAsian(S0, K, T, r, sigma, n) =
        let randomzs = [ for i in 0 .. n -> double(Normal.Sample(0.0, 1.0)) ]
        let l1 = (T / double(n)) * (r - (sigma * sigma) / 2.0)
        let prices = List.fold (fun acc elem -> ((List.head acc) * (exp (l1 + sigma * (sqrt (T / double(n))) * elem ) ) ) :: acc ) [S0] randomzs
        (List.sum prices) / double(n)

    let calculateBinomialTreeAmerican(S0, K, T, r, sigma, n, callorput) =
        let dt = T / double(n)
        let up = (exp (sigma * (sqrt dt)))
        let down = 1.0 / up
        let a = (exp (r * dt))
        let p = (a - down) / (up - down)
        let q = 1.0 - p

        let startv = [ for i in 0 .. n -> S0 * (up ** i) * (down ** (double(n) - double(i))) ]
        startv = match callorput with
                    | "put" -> List.map (fun x -> (max 0.0 (K - x))) startv
                    | _ -> List.map (fun x -> (max 0.0 (x - K))) startv

        let withoutlast xs =
                match xs with
                | [] | [_] -> []
                | ls -> ls |> List.rev |> List.tail |> List.rev

        let rec iteratetree( j, v, st ) = 
            if j = 0 then
                List.head v
            else 
                //printfn "price vector: %A\n" v
                //printfn "st vector: %A\n" st
                let v2 = List.map2 (fun x y -> (exp (-r * dt)) * (x * p + y * q) ) (withoutlast v) (List.tail v) 
                let st2 = List.tail (List.map (fun x -> x * up) st)

                let v2 = match callorput with
                            | "put" -> List.map2 (fun x y -> (max x (K - y))) v2 st2
                            | _ -> List.map2 (fun x y -> (max x (y - K))) v2 st2
                iteratetree( j - 1, v2, st2 )

        let v = List.rev startv
        let st = List.rev [ for i in 0 .. n -> S0 * (up ** i) * (down ** (double(n) - double(i))) ] //price at t
        iteratetree( n, v, st )

    let cdf x =
        Normal.CDF(0.0, 0.0, x)

    type OptionType = 
        | EuropeanPut
        | EuropeanCall
        | AsianPut
        | AsianCall
        | AmericanPut
        | AmericanCall

    type TradeOption (optionS0: double, optionK: double, optionT: double, optionr:double, optionsigma: double, optiontype: OptionType) =
        //let S0, K, T, r, sigma, otype = optionS0, optionK, optionT, optionr, optionsigma, optiontype
        let S0 = optionS0
        let K = optionK
        let T = optionT
        let r = optionr
        let sigma = optionsigma
        let otype = optiontype

        let CalculateEuropeanCall() =
            let d1 = ((log (S0 / K)) + ((r + (sigma * sigma) / 2.0) * T)) / (sigma * (sqrt T))
            let d2 = d1 - sigma * (sqrt T)
            S0 * (cdf d1) - K * (exp (- r * T)) * (cdf d2)

        let CalculateEuropeanPut() =
            let d1 = ((log (S0 / K)) + ((r + (sigma * sigma) / 2.0) * T)) / (sigma * (sqrt T))
            let d2 = d1 - sigma * (sqrt T)
            - S0 * (cdf (-1.0 * d1)) + K * (exp (- r * T)) * (cdf (-1.0 * d2))
        
        let CalculateAsianCall() = 
            let tries = 10000 //tries
            let averages = [ for i in 0 .. tries -> simulateBrownianAsian(S0, K, T, r, sigma, 200) ]
            let A = (List.sum averages) / double(tries)
            max 0.0 (A - K) //payoff

        let CalculateAsianPut() =
            let tries = 10000 //tries
            let averages = [ for i in 0 .. tries -> simulateBrownianAsian(S0, K, T, r, sigma, 200) ]
            let A = (List.sum averages) / double(tries)
            max 0.0 (K - A) //payoff

        let CalculateAmericanCall() =
            calculateBinomialTreeAmerican(S0, K, T, r, sigma, 200, "call")
        
        let CalculateAmericanPut() = 
            calculateBinomialTreeAmerican(S0, K, T, r, sigma, 200, "put")

        member this.CalculateValue() = 
            match otype with
            | EuropeanCall -> CalculateEuropeanCall()
            | EuropeanPut -> CalculateEuropeanPut()
            | AsianCall -> CalculateAsianCall()
            | AsianPut -> CalculateAsianPut()
            | AmericanCall -> CalculateAmericanCall()
            | AmericanPut -> CalculateAmericanPut()

        member this.pS0 = S0
        member this.pK = K 
        member this.pT = T
        member this.pr = r
        member this.psigma = sigma
        member this.ptype = otype
        member this.delta = match otype with
                            | EuropeanCall | EuropeanPut -> cdf ((log (S0 / K)) + ((r + (sigma * sigma) / 2.0) * T)) / (sigma * (sqrt T))
                            | _ -> 0.0
    