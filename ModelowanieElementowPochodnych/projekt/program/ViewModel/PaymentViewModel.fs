namespace OptionsCalculator

open System
open PaymentModel

type PaymentViewModel(record: Payment.Record) =

    let mutable recordState = record

    let mutable value: Money option = None

    new() = PaymentViewModel(Payment.makeRandom ())

    member this.Name
        with get () = recordState.Name
        and set (v: string) = recordState <- { recordState with Name = v }

    member this.Expiry
        with get () = recordState.Expiry.ToShortDateString()
        and set (v: string) =
            let date = DateTime.Parse(v)
            recordState <- { recordState with Expiry = date }

    member this.Currency
        with get () = recordState.Currency.ToString()
        and set (v: string) =
            let ccy = Currency.Parse(v)
            recordState <- { recordState with Currency = ccy }

    member this.Principal
        with get () = recordState.Principal.ToString()
        and set (v: string) = recordState <- { recordState with Principal = Int64.Parse(v) }

    member this.Value
        with get (): Money =
            match value with
            | Some v -> v
            | None -> failwith "Trade not calculated."
        and set (v: Money) = value <- Some v

    member this.Calculate(data: MarketDataViewModel, config: CalculationConfigViewModel) =

        let inputs: Payment.ValuationInputs =
            {
                Trade = recordState
                Data = data.Snap()
                Config = config.Snap()
            }

        let money = Payment.ValuationModel(inputs).Calculate()

        this.Value <- money
