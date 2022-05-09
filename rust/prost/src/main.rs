pub mod person {
    include!(concat!(env!("OUT_DIR"), "/person.rs"));
}

fn main() {
    let person = person::Person::default();
    println!("{person:?}");
    println!("Hello, world!");
}
