fn number(bus_stops:&[(i32,i32)]) -> i32 {
    bus_stops.iter().fold(0, |a, (into, off)| a + into - off)
}