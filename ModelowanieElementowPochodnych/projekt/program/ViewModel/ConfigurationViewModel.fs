namespace OptionsCalculator

[<AutoOpen>]
module ConfigurationViewModel =

    type MarketDataViewModel() =

        let mutable map: Map<string, string> = Map.empty

        member this.AddFxRate(targetCcy: string, tradeCcy: string, value: string) =
            let fxKey =
                ConfigurationModel.getFXRateKey (Currency.Parse targetCcy, Currency.Parse tradeCcy)
            // just to validate
            let _floatValue = float value
            map <- Map.add fxKey value map

        member this.GetAllFxRates() =
            map |> Map.filter (fun key _ -> key.StartsWith("FX::"))

        member this.Snap() = ConfigurationModel.MarketData(map)

    type CalculationConfigViewModel() =

        let mutable map: Map<string, string> = Map.empty

        member this.BaseCurrency
            with get () = map.TryFind ConfigurationModel.Keys.baseCurrency |> Option.defaultValue "None"
            and set (ccy: string) = map <- Map.add ConfigurationModel.Keys.baseCurrency ccy map

        member this.Snap() =
            ConfigurationModel.CalculationConfig(map)
