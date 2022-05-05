fn main() {
    let x = 1;
    let str = "const str";
    let mut dstr = String::from("dynamic str");
    modify_str(&mut dstr);

    println!("{x} {str} \n{dstr}");
}


fn modify_str(str: &mut String) {
    str.push_str(" is awesome");
}

fn dangle() -> &'static String {
    static s: String = String::from("hello");

    &s
}