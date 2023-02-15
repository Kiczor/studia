namespace View

open OptionsCalculator

[<AutoOpen>]
module Types =

    type State =
        {
            MarketData: MarketDataViewModel
            CalcConfig: CalculationConfigViewModel
            Trades: PaymentViewModel list
            Options: OptionsModel.TradeOption list
        }

    type Command = State -> State
