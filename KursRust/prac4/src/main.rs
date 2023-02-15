use std::fs::File;
use std::io::prelude::*;
use std::path::Path;
use std::ops;

pub struct Image 
{
    width: u32,
    height: u32,
    pixels: Vec<Vec<(i32, i32, i32)>>,
}

impl Image
{
    fn new(w: u32, h: u32) -> Image
    {
        Image
        {
            width: w,
            height: h,
            pixels: vec![vec![(0, 0, 0); w as usize]; h as usize],
        }
    }

    fn setpixel(&mut self, x: usize, y: usize, val: (i32, i32, i32))
    {
        self.pixels[x][y] = val;
    }

    fn getpixel(self, x: usize, y: usize) -> (i32, i32, i32)
    {
        return self.pixels[x][y];
    }

    fn converttoppm(self) -> String
    {
        let mut res = String::from("P3 ");
        res += &self.width.to_string();
        res.push(' ');
        res += &self.height.to_string();
        res.push(' ');
        res.push_str("255\n");
        for v in self.pixels
        {
            for i in 0..self.width
            {
                let p = v[i as usize];
                if i != self.width
                {
                    res += &(p.0.to_string() + " " + &p.1.to_string() + " " + &p.2.to_string() + " ");
                }
                else
                {
                    res += &(p.0.to_string() + " " + &p.1.to_string() + " " + &p.2.to_string());
                }
            }
            res.push_str("\n");
        }
        return res;
    }

    fn writetofile(self, s: &str)
    {
        let path = Path::new(s);
        let display = path.display();

        let mut file = match File::create(&path) {
            Err(why) => panic!("couldn't create {}: {}", display, why),
            Ok(file) => file,
        };

        match file.write_all(self.converttoppm().as_bytes()) {
            Err(why) => panic!("couldn't write to {}: {}", display, why),
            Ok(_) => println!("successfully wrote to {}", display),
        }
    }
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

fn drawmandelbrot(im_width: u32, im_height: u32, iterations: i32)
{
    let mut mandelbrot: Image = Image::new(im_width, im_height);
    let midx: f64 = (im_width / 2).try_into().unwrap();
    let midy: f64 = (im_height / 2).try_into().unwrap();
    for i in 0..im_height
    {
        for j in 0..im_width
        {
            let x = ( ((j as f64) - midx) / midx ) * 2.0;
            let y = ( ((i as f64) - midy) / midy ) * 2.0;

            
            let mut z: Complex = Complex::new( 0.0, 0.0 );
            let c: Complex = Complex::new( x, y );
            for iter in 0..iterations
            {
                z = (z * z) + c;
            }

            if (z.get_val().0 * z.get_val().0) + (z.get_val().1 * z.get_val().1) > 4.0
            {
                mandelbrot.setpixel(i as usize, j as usize, (0,0,0));
            }
            else
            {
                mandelbrot.setpixel(i as usize, j as usize, (255,255,255));
            }
        }
    }

    mandelbrot.writetofile("mandelbrot.ppm");
}

fn main() {
    println!("Hello, world!");

    let ca: Complex = Complex::new(1.0, 2.0);
    let cb: Complex = Complex::new(2.0, 3.0);
    let cc: Complex = ca * cb + ca;
    println!("cc: {} {}", cc.get_val().0, cc.get_val().1);
    println!("ca: {} {}", ca.get_val().0, ca.get_val().1);
    println!("cb: {} {}", cb.get_val().0, cb.get_val().1);
    let mut obrazek: Image = Image::new(100, 100);
    for i in 0..100
    {
        for j in 0..100
        {
            if i > j
            {
                obrazek.setpixel(i, j, (200, 100, 50));
            }
            else
            {
                obrazek.setpixel(i, j, (100, 100, 50));
            }
        }
    }

    obrazek.writetofile("obrazek.ppm");
    drawmandelbrot(1000, 1000, 30);
}
