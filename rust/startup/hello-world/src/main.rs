#[derive(Debug)]
struct Soo {
    a: i32,
    b: i32,
}
pub fn main() {

    let mut s = Some(5);
    let mut soo = Some(Soo { a: 5, b: 6 });
    soo.as_mut().unwrap().a = 1;
    s.as_mut().as_mut() = 1;
    println!("{soo:?}");

}