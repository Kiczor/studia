mod utils;

use wasm_bindgen::prelude::*;
use std::ops;
use std::convert::TryInto;
use std::cmp::max;

// When the `wee_alloc` feature is enabled, use `wee_alloc` as the global
// allocator.
/*#[cfg(feature = "wee_alloc")]
#[global_allocator]
static ALLOC: wee_alloc::WeeAlloc = wee_alloc::WeeAlloc::INIT;
*/

#[wasm_bindgen]
extern {
    fn alert(s: &str);
}

#[wasm_bindgen]
pub fn greet() {
    alert("Hello, fraktal!");
}

#[derive(Copy, Clone)]
pub struct Complex
{
    re: f64,
    im: f64,
}

impl Complex
{
    fn new(r: f64, i: f64) -> Complex
    {
        Complex
        {
            re: r,
            im: i,
        }
    }

    fn set(&mut self, r: f64, i:f64)
    {
        self.re = r;
        self.im = i;
    }

    fn get_val(self) -> (f64, f64)
    {
        return (self.re, self.im);
    }
}

impl ops::Add<Complex> for Complex
{
    type Output = Complex;
    fn add(self, b: Complex) -> Complex
    {
        let bv: (f64, f64) = b.get_val();
        return Complex::new( self.re + bv.0, self.im + bv.1 );
    }
}

impl ops::Sub<Complex> for Complex
{
    type Output = Complex;
    fn sub(self, b: Complex) -> Complex
    {
        let bv: (f64, f64) = b.get_val();
        return Complex::new( self.re - bv.0, self.im - bv.1 );
    }
}

impl ops::Mul<Complex> for Complex
{
    type Output = Complex;
    fn mul(self, b: Complex) -> Complex
    {
        let bv: (f64, f64) = b.get_val();
        return Complex::new( self.re * bv.0 - self.im * bv.1, self.re * bv.1 + self.im * bv.0 ); //(a + bi)(c + di) = (ac + bd) (bc + ad)i 
    }
}

impl ops::Div<Complex> for Complex
{
    type Output = Complex;
    fn div(self, b: Complex) -> Complex
    {
        let bv: (f64, f64) = b.get_val();
        return Complex::new( (self.re * bv.0 + self.im * bv.1) / (bv.0 * bv.0 + bv.1 * bv.1), (self.im * bv.0 - self.re * bv.1) / (bv.0 * bv.0 + bv.1 * bv.1) );
    }
}

#[wasm_bindgen]
pub struct FractalImage
{
    width: u32,
    height: u32,
    iterations: u32,
    currentz: Vec<Vec<Complex>>,
    pixels: Vec<u8>,
    over: Vec<Vec<bool>>,
}

#[wasm_bindgen]
impl FractalImage
{
    pub fn new(w: u32, h: u32) -> FractalImage
    {
        FractalImage
        {
            width: w,
            height: h,
            iterations: 0,
            currentz: vec![vec![Complex::new( 0.0, 0.0 ); w as usize]; h as usize],
            pixels: vec![0; 4*(w * h) as usize],
            over: vec![vec![false; w as usize]; h as usize], 
        }
    }
    pub fn width(&self) -> u32 {
        self.width
    }

    pub fn height(&self) -> u32 {
        self.height
    }

    pub fn pixels(&self) -> *const u8{
        self.pixels.as_ptr()
    }

    pub fn get_index(&self, row: u32, column: u32) -> usize {
        (row * 4 * self.width + column * 4) as usize
    }

    pub fn tick(&mut self)
    {
        let midx: f64 = (self.width / 2).try_into().unwrap();
        let midy: f64 = (self.height / 2).try_into().unwrap();

        if self.iterations > 30
        {
            return;
        }

        self.iterations += 1 as u32;

        for i in 0..self.height
        {
            for j in 0..self.width
            {
                let x = ( ((j as f64) - midx) / midx ) * 2.0;
                let y = ( ((i as f64) - midy) / midy ) * 2.0;

                let c: Complex = Complex::new( x, y );

                let z = self.currentz[i as usize][j as usize];
                self.currentz[i as usize][j as usize] = (z * z) + c;

                let z = self.currentz[i as usize][j as usize];
                let idx = self.get_index(i, j);

                if self.over[i as usize][j as usize]
                {
                    continue;
                }
                if (z.get_val().0 * z.get_val().0) + (z.get_val().1 * z.get_val().1) > 1000.0
                {
                    self.over[i as usize][j as usize] = true;
                }
                if (z.get_val().0 * z.get_val().0) + (z.get_val().1 * z.get_val().1) > 4.0
                {
                    self.pixels[idx] = max(self.pixels[idx], 0);
                    self.pixels[idx+1] = max(self.pixels[idx + 1], 0);
                    self.pixels[idx+2] = max(self.pixels[idx + 2], 0);
                    self.pixels[idx+3] = 255;
                }
                else
                {
                    //self.over[i as usize][j as usize] = true;

                    self.pixels[idx] = (self.iterations as u8) * 8;
                    self.pixels[idx+1] = (self.iterations as u8) * 8;
                    self.pixels[idx+2] = (self.iterations as u8) * 8;
                    self.pixels[idx+3] = 255;
                }
            }
        }
    }
}
