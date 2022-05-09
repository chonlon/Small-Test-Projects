mod person;

pub use person::*;
pub use person::person::*;


impl Person {
    pub fn new(
        name: impl Into<String>,
        email: impl Into<String>,
        id: i32,
        phones: impl Into<Vec<PhoneNumber>>) -> Self {
        Person {
            name: name.into(),
            email: email.into(),
            id,
            phones: phones.into(),
            ..Default::default()
        }
    }
}

impl PhoneNumber {
    pub fn new(number: impl Into<String>, phone_type: PhoneType) -> Self {
        PhoneNumber {
            number: number.into(),
            phone_type: phone_type.into(),
        }
    }
}
