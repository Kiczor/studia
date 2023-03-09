namespace OptionsCalculator

open System

module ConfigurationModel =

    module Keys =

        [<Literal>]
        let baseCurrency = "valuation::baseCurrency"

    let getFXRateKey (target: Currency, trade: Currency) =
        String.Format("FX::{0}{1}", string target, string trade)

    type Lookup<'T>(key: string, data: Map<string, string>, parse: string -> 'T) =

        member this.TryGet() : 'T option = data.TryFind key |> Option.map parse

    type MarketData(current: Map<string, string>) =

        member this.FxRate(fxRateKey: string) =
            Lookup<float>(fxRateKey, current, float)

    type CalculationConfig(current: Map<string, string>) =

        member this.BaseCurrency = Lookup<Currency>(Keys.baseCurrency, current, Currency.Parse)
