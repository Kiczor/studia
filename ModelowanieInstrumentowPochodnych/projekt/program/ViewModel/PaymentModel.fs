namespace OptionsCalculator

open System
open ConfigurationModel

module PaymentModel =

    [<RequireQualifiedAccess>]
    module Payment =

        type Record =
            {
                Name: string
                Expiry: DateTime
                Currency: Currency
                Principal: int64
            }


        // utilities to create random Payment
        let private rand = Random()

        let makeRandom () =
            {
                Name = sprintf "Payment-%04d" (rand.Next(9999))
                Expiry = (DateTime.Now.AddMonths(rand.Next(1, 6))).Date
                Currency = Currency.All.[rand.Next(Currency.All.Length)]
                Principal = int64 (rand.Next())
            }

        type ValuationInputs =
            {
                Trade: Record
                Data: MarketData
                Config: CalculationConfig
            }

        type ValuationModel(inputs: ValuationInputs) =

            member this.Calculate() : Money =

                let tradeCcy = inputs.Trade.Currency
                let targetCcy = inputs.Config.BaseCurrency.TryGet() |> Option.defaultValue tradeCcy

                let fxRateOption =
                    let fxRateKey = getFXRateKey (targetCcy, tradeCcy)
                    inputs.Data.FxRate(fxRateKey).TryGet()

                let fxRate, finalCcy =
                    match fxRateOption with
                    | Some fxRate -> fxRate, targetCcy
                    | None -> 1.0, tradeCcy

                {
                    // this should take the time value of money into account in order to be correct
                    Value = (float inputs.Trade.Principal) / fxRate
                    Currency = finalCcy
                }
