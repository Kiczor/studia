namespace View

open System
open OptionsCalculator

[<RequireQualifiedAccess>]
module Commands =

    [<RequireQualifiedAccess>]
    module Keys =

        [<Literal>]
        let help = "help"

        [<Literal>]
        let quit = "quit"

        [<Literal>]
        let fx = "fx"

        [<Literal>]
        let baseCcy = "base"

        [<Literal>]
        let summary = "summary"

        [<Literal>]
        let addTrade = "add"

        [<Literal>]
        let addOption = "addoption"

    [<RequireQualifiedAccess>]
    module Messages =

        let private typeHelper key whatItDoes =
            String.Format("Type '{0}' {1}.", key, whatItDoes)

        let typeHelp = typeHelper Keys.help "for available commands."
        let typeQuit = typeHelper Keys.quit "to exit."
        let typeSummary = typeHelper Keys.summary "to print summary."

        let typeAddTrade =
            typeHelper Keys.addTrade "to add a Payment trade with random field values."

        let typeAddOption =
            typeHelper Keys.addOption "to add a Option."

        let typeBaseCcy =
            typeHelper Keys.baseCcy " followed by currency code to set base (target) currency (e.g. base USD)."

        let typeFX =
            typeHelper
                Keys.fx
                "followed by target and trade currency codes and float value to add FX rate (e.g. fx USD EUR 1.25)."

        let unknownCommand (key: string) =
            String.Format("Unknown command '{0}'", key)



    type Command = State -> State

    let unknownCmd (unknownKey: string) (s: State) =
        Console.WriteLine(Messages.unknownCommand unknownKey)
        Console.WriteLine Messages.typeHelp
        Console.WriteLine Messages.typeQuit
        s

    let addFXCommand (target, trade, value) (s: State) =
        s.MarketData.AddFxRate(target, trade, value)
        s

    let (|FX|_|) (input: string) =
        try
            match input.ToLowerInvariant().Split() |> Array.toList with
            | [ Keys.fx; target; trade; value ] -> Some(target, trade, value)
            | _ -> None
        with _ ->
            None

    let addTradeOption( s0, k, t, r, sigma, ot ) (s: State) =
        { s with Options = OptionsModel.TradeOption( s0, k, t, r, sigma, ot ) :: s.Options }

    let (|NewOption|_|) (input: string) =
        try
            match input.ToLowerInvariant().Split() |> Array.toList with
            | [ Keys.addOption; s0; k; t; r; sigma; ot ] -> Some( double(s0), double(k), double(t), double(r), double(sigma), match ot with
                                                                                                                                | "eput" -> OptionsModel.EuropeanPut
                                                                                                                                | "ecall" -> OptionsModel.EuropeanCall
                                                                                                                                | "asianput" -> OptionsModel.AsianPut
                                                                                                                                | "asiancall" -> OptionsModel.AsianCall
                                                                                                                                | "americanput" -> OptionsModel.AmericanPut
                                                                                                                                | "americancall" -> OptionsModel.AmericanCall )
            | _ -> None
        with _ ->
            None

    let setBaseCcyCommand target (s: State) =
        s.CalcConfig.BaseCurrency <- target
        s

    let (|BaseCcy|_|) (input: string) =
        try
            match input.ToLowerInvariant().Split() |> Array.toList with
            | [ Keys.baseCcy; ccy ] -> Some ccy
            | _ -> None
        with _ ->
            None

    // this could be extended to allow entering input values
    let addTradeCommand (s: State) =
        { s with Trades = PaymentViewModel() :: s.Trades }

    let helpCmd (s: State) =
        Console.WriteLine Messages.typeQuit
        Console.WriteLine Messages.typeFX
        Console.WriteLine Messages.typeBaseCcy
        Console.WriteLine Messages.typeSummary
        Console.WriteLine Messages.typeAddTrade
        Console.WriteLine Messages.typeAddOption
        s

    let summaryCmd (s: State) =

        Console.WriteLine(String.Format("Base currency : {0}", s.CalcConfig.BaseCurrency))
        Console.WriteLine("MarketData:")

        match s.MarketData.GetAllFxRates() with
        | empty when empty.IsEmpty -> Console.WriteLine("No Fx rates. Use fx command to add fx data.")
        | rates ->
            rates
            |> Map.iter (fun key value -> Console.WriteLine(String.Format("{0} {1}", key.ToUpper(), value)))

        Console.WriteLine("Trades")

        match s.Trades with
        | [] -> Console.WriteLine("No trades. Use addTrade to add new payments.")
        | ls ->
            let printValue (m: Money) =
                String.Format("{0} {1}", string m.Currency, string m.Value)

            let printTrade (t: PaymentViewModel) =
                t.Calculate(s.MarketData, s.CalcConfig)

                String.Format(
                    "Name: {0}\n\tExpiry: {1}\n\tCurrency: {2}\n\tPrincipal: {3}\n\tValue: {4}",
                    t.Name,
                    t.Expiry,
                    t.Currency,
                    t.Principal,
                    printValue t.Value
                )
                |> Console.WriteLine

            ls |> Seq.iter printTrade

        match s.Options with
        | [] -> Console.WriteLine("No options. Use addoption to add new options.")
        | ls ->
            let printOption (t: OptionsModel.TradeOption) =
                let value = t.CalculateValue()
                let ttype = match t.ptype with
                                | OptionsModel.EuropeanCall -> "European Call"
                                | OptionsModel.EuropeanPut -> "European Put"
                                | OptionsModel.AsianCall -> "Asian Call"
                                | OptionsModel.AsianPut -> "Asian Put"
                                | OptionsModel.AmericanCall -> "American Call"
                                | OptionsModel.AmericanPut -> "American Put"

                String.Format(
                    "Option\n\tinitial stock price: {0}\n\tstrike: {1}\n\ttime of expiration: {2}\n\tinterest rate: {3}\n\tsigma(standard deviation): {4}\n\ttype:{5}\n\tprice: {6}\n\tdelta: {7}",
                    t.pS0,
                    t.pK,
                    t.pT,
                    t.pr,
                    t.psigma,
                    ttype,
                    value,
                    t.delta
                )
                |> Console.WriteLine

            ls |> Seq.iter printOption

        s

    let tryParse (key: string) : Command option =
        match key.ToLowerInvariant() with
        | Keys.quit -> None
        | Keys.help -> Some helpCmd
        | Keys.summary -> Some summaryCmd
        | Keys.addTrade -> Some addTradeCommand
        | FX info -> addFXCommand info |> Some
        | NewOption a -> addTradeOption a |> Some
        | BaseCcy ccy -> setBaseCcyCommand ccy |> Some
        | unknownKey -> unknownCmd unknownKey |> Some
