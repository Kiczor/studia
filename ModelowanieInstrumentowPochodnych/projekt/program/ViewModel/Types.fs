namespace OptionsCalculator

[<AutoOpen>]
module Types =

    type Currency =
        | USD
        | GBP
        | EUR

        static member All = [| USD; GBP; EUR |]

        static member Parse(s: string) =
            match s.ToUpper() with
            | "USD" -> USD
            | "GBP" -> GBP
            | "EUR" -> EUR
            | _ -> failwithf "Unknown Currency name '%s'" s

    type Money =
        {
            Value: float
            Currency: Currency
        }
