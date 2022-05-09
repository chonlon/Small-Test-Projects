/// define a person
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct Person {
    #[prost(string, tag="1")]
    pub name: ::prost::alloc::string::String,
    /// Unique ID number for this person.
    #[prost(int32, tag="2")]
    pub id: i32,
    #[prost(string, tag="3")]
    pub email: ::prost::alloc::string::String,
    #[prost(bytes="vec", tag="4")]
    pub private_data: ::prost::alloc::vec::Vec<u8>,
    #[prost(map="string, string", tag="5")]
    pub school: ::std::collections::HashMap<::prost::alloc::string::String, ::prost::alloc::string::String>,
    #[prost(message, repeated, tag="6")]
    pub phones: ::prost::alloc::vec::Vec<person::PhoneNumber>,
}
/// Nested message and enum types in `Person`.
pub mod person {
    #[derive(Clone, PartialEq, ::prost::Message)]
    pub struct PhoneNumber {
        #[prost(string, tag="1")]
        pub number: ::prost::alloc::string::String,
        #[prost(enumeration="PhoneType", tag="2")]
        pub phone_type: i32,
    }
    #[derive(Clone, Copy, Debug, PartialEq, Eq, Hash, PartialOrd, Ord, ::prost::Enumeration)]
    #[repr(i32)]
    pub enum PhoneType {
        Mobile = 0,
        Home = 1,
        Work = 2,
    }
}
/// Our address book file is just one of these.
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct AddressBook {
    #[prost(message, repeated, tag="1")]
    pub people: ::prost::alloc::vec::Vec<Person>,
}
