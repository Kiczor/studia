namespace View

open System
open OptionsCalculator

module Main =
    let init () : State =

        let md = MarketDataViewModel()
        let conf = CalculationConfigViewModel()

        // these could be loaded from files
        conf.BaseCurrency <- "USD"
        md.AddFxRate("USD", "EUR", string 0.87)
        md.AddFxRate("USD", "GBP", string 0.90)

        {
            MarketData = md
            CalcConfig = conf
            Trades = []
            Options = []
        }

    let rec loop (s: State) =
        Console.WriteLine "Waiting for command:"
        let commandKey = Console.ReadLine()

        match Commands.tryParse commandKey with
        // exit loop
        | None -> 0
        | Some cmd -> loop (cmd s)

    [<EntryPoint>]
    let main _args =
        let state = init ()
        Console.WriteLine Commands.Messages.typeHelp
        Console.WriteLine Commands.Messages.typeQuit
        loop (state)
