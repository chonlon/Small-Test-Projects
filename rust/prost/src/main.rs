mod proto;
use bytes::{Buf, BufMut};
use proto::Person;
use prost::Message;


fn main() {
    // proto::Person;

    let person = Person::new(
        "John Doe".to_string(),
        "kkk".to_string(),
        0,
    vec![]);
    
    let v1 = person.encode_length_delimited_to_vec();

    let v2 = person.encode_to_vec();
    let len = person.encoded_len();
    print!("person default len: {} ", len);
    print!("v1 {v1:?} ");
    print!("v2 {v2:?} ");
    println!("{person:?}");
    {
        let v1 = v1.as_slice();
    }

    {
        let v1: &[u8] = v1.as_ref();
    }


    let de_person = Person::decode(
        v2.as_slice()
    ).unwrap();
    println!("{de_person:?}");
}
